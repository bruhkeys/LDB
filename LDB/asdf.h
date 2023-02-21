#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <memoryapi.h>
HANDLE process_handle;
#include <vector>
using namespace std;
bool compareVectors(const std::vector<uint8_t>& vec1, const std::vector<uint8_t>& vec2) {
    // If the vectors have different sizes, they are not equal
    if (vec1.size() != vec2.size()) {
        return false;
    }

    // Iterate through the vectors and compare each element
    for (size_t i = 0; i < vec1.size(); i++) {
        if (vec1[i] != vec2[i]) {
            return false;
        }
    }

    // All elements are equal, so the vectors are equal
    return true;
}

void print_bytes(const std::vector<uint8_t>& bytes) {
    std::cout << "Bytes: ";
    for (const auto& byte : bytes) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;
}

bool patch_bytes(uintptr_t address, const std::vector<uint8_t>& new_bytes) {
    // Determine the size of the new bytes and allocate a buffer for them
    SIZE_T buffer_size = new_bytes.size();
    LPVOID buffer = VirtualAllocEx(process_handle, NULL, buffer_size, MEM_COMMIT, PAGE_READWRITE);
    if (buffer == NULL) {
        std::cerr << "Failed to allocate memory in target process\n";
        return false;
    }

    // Disable write protection for the target address
    DWORD old_protect;
    if (!VirtualProtectEx(process_handle, reinterpret_cast<LPVOID>(address), buffer_size, PAGE_EXECUTE_READWRITE, &old_protect)) {
        std::cerr << "Failed to disable write protection for address " << std::hex << address << std::endl;
        VirtualFreeEx(process_handle, buffer, buffer_size, MEM_RELEASE);
        return false;
    }

    // Write the new bytes to the target address
    SIZE_T bytes_written = 0;
    BOOL result = WriteProcessMemory(process_handle, reinterpret_cast<LPVOID>(address), new_bytes.data(), new_bytes.size(), &bytes_written);

    // Re-enable write protection for the target address
    if (!VirtualProtectEx(process_handle, reinterpret_cast<LPVOID>(address), buffer_size, old_protect, &old_protect)) {
        std::cerr << "Failed to re-enable write protection for address " << std::hex << address << std::endl;
        VirtualFreeEx(process_handle, buffer, buffer_size, MEM_RELEASE);
        return false;
    }

    VirtualFreeEx(process_handle, buffer, buffer_size, MEM_RELEASE);
    return result && (bytes_written == new_bytes.size());
}

uintptr_t find_address(const char* module_name, int offset, DWORD proc_id)
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, proc_id);
    if (snapshot == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error 0x1. try closing windows with Lockdown Browser in the name.\n contact me on Discord";
        return 0;
    }

    MODULEENTRY32 module = { sizeof(MODULEENTRY32) };
    uintptr_t base_address = 0;

    if (Module32First(snapshot, &module))
    {
        do
        {
            if (_stricmp(module.szModule, module_name) == 0)
            {
                base_address = reinterpret_cast<uintptr_t>(module.modBaseAddr);
                break;
            }
        } while (Module32Next(snapshot, &module));
    }

    CloseHandle(snapshot);

    if (base_address == 0)
    {
        std::cerr << "Failed to find module\n";
        return 0;
    }

    return base_address + offset;
}

uintptr_t* scanMemory(HANDLE hProcess, size_t& count)
{
    // Define the signature to search for
    unsigned char signature[] = { 0x8b, 0x55, 0xFF, 0x8b};
    int signatureSize = sizeof(signature) / sizeof(signature[0]);

    // Get the memory limits of the process
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    uintptr_t baseAddress = (uintptr_t)sysInfo.lpMinimumApplicationAddress;
    uintptr_t maxAddress = (uintptr_t)sysInfo.lpMaximumApplicationAddress;

    // Allocate an array to store the matching addresses
    const size_t maxMatches = 100;
    uintptr_t* matches = new uintptr_t[maxMatches];
    size_t matchCount = 0;

    while (baseAddress < maxAddress)
    {
        // Read a block of memory from the process
        unsigned char buffer[1024];
        SIZE_T bytesRead;
        if (ReadProcessMemory(hProcess, (void*)baseAddress, buffer, sizeof(buffer), &bytesRead))
        {
            // Search the block for the signature
            for (uintptr_t i = 0; i < bytesRead - signatureSize; i++)
            {
                if (memcmp(buffer + i, signature, signatureSize) == 0)
                {
                    uintptr_t matchAddress = baseAddress + i;
                    matches[matchCount++] = matchAddress;
                    if (matchCount >= maxMatches)
                    {
                        break;
                    }
                }
            }
        }

        // Check if we've found the maximum number of matches
        if (matchCount >= maxMatches)
        {
            break;
        }

        // Advance to the next block of memory
        baseAddress += sysInfo.dwPageSize;
    }

    // Update the count parameter and return the array of matches
    count = matchCount;
    return matches;
}
std::vector<uint8_t> BYTERPM(uintptr_t address, size_t count) {
    std::vector<uint8_t> buffer(count);
    SIZE_T bytesRead = 0;
    ReadProcessMemory(process_handle, reinterpret_cast<LPCVOID>(address), buffer.data(), count, &bytesRead);
    buffer.resize(bytesRead); // Resize the buffer to the actual number of bytes read
    return buffer;
}


template<typename T> T RPM(SIZE_T address) {
    T buffer;
    ReadProcessMemory(process_handle, (LPCVOID)address, &buffer, sizeof(T), NULL);
    return buffer;
}
MODULEENTRY32 get_module(const char* modName, DWORD proc_id) {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, proc_id);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry)) {
            do {
                if (!strcmp(modEntry.szModule, modName)) {
                    CloseHandle(hSnap);
                    return modEntry;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    MODULEENTRY32 module = { -1 };
    return module;
}
bool MemoryCompare(const BYTE* pData, const BYTE* pMask, const char* pszMask)
{
    for (; *pszMask; ++pszMask, ++pData, ++pMask)
    {
        if (*pszMask == 'x' && *pData != *pMask)
        {
            return false;
        }
    }
    return (*pszMask == NULL);
}

DWORD FindSignatureInModule(MODULEENTRY32 module, const char* sig, const char* mask)
{
    // Calculate the size of the module
    SIZE_T module_size = module.modBaseSize;

    // Allocate memory to store the module data
    BYTE* data = new BYTE[module_size];

    // Read the module data from the process memory
    SIZE_T bytes_read;
    ReadProcessMemory(GetCurrentProcess(), (LPCVOID)module.modBaseAddr, data, module_size, &bytes_read);

    // Search for the signature within the module data
    for (DWORD i = 0; i < module_size; i++) {
        if (MemoryCompare((const BYTE*)(data + i), (const BYTE*)sig, mask)) {
            // Compute the address of the signature within the module
            DWORD address = (DWORD)module.modBaseAddr + i;

            // Free the allocated memory
            delete[] data;

            // Return the address of the signature
            return address;
        }
    }

    // Free the allocated memory
    delete[] data;

    // Return 0 if the signature was not found
    return 0;
}

uintptr_t find_pattern(MODULEENTRY32 module, uint8_t* arr, const char* pattern, int offset) {
    uintptr_t scan = 0x0;
    const char* pat = pattern;
    uintptr_t firstMatch = 0;
    for (uintptr_t pCur = (uintptr_t)arr; pCur < (uintptr_t)arr + module.modBaseSize; ++pCur) {
        if (!*pat) { scan = firstMatch; break; }
        if (*(uint8_t*)pat == '\?' || *(uint8_t*)pCur == ((((pat[0] & (~0x20)) >= 'A' && (pat[0] & (~0x20)) <= 'F') ? ((pat[0] & (~0x20)) - 'A' + 0xa) : ((pat[0] >= '0' && pat[0] <= '9') ? pat[0] - '0' : 0)) << 4 | (((pat[1] & (~0x20)) >= 'A' && (pat[1] & (~0x20)) <= 'F') ? ((pat[1] & (~0x20)) - 'A' + 0xa) : ((pat[1] >= '0' && pat[1] <= '9') ? pat[1] - '0' : 0)))) {
            if (!firstMatch) firstMatch = pCur;
            if (!pat[2]) { scan = firstMatch; break; }
            if (*(WORD*)pat == 16191 /*??*/ || *(uint8_t*)pat != '\?') pat += 3;
            else pat += 2;
        }
        else { pat = pattern; firstMatch = 0; }
    }
    if (!scan) return 0x0;
    uint32_t read;
    ReadProcessMemory(process_handle, (void*)(scan - (uintptr_t)arr + (uintptr_t)module.modBaseAddr + offset), &read, sizeof(read), NULL);
    return read;
}

void patchmethod(int offsets, DWORD procid, const std::vector<uint8_t>& bytes, const std::vector<uint8_t>& errorbytes, const char* errormessage, const char* succmessage, const char* errorcode) {
    uintptr_t cn = find_address("LockDownBrowser.dll", offsets, procid);
    if (compareVectors(BYTERPM(cn, bytes.size()), errorbytes)) {
        printf(succmessage);
    }

    else if (compareVectors(BYTERPM(cn, bytes.size()), bytes)) {

        printf("[?]No need to relaunch the program!\r\n");
    }
    else { printf(errormessage); }
    bool success = patch_bytes(cn, bytes);
    if (!success) {
        std::cerr << "[!]Failed to patch bytes at " << errorcode << "[!]close any folder/program that has LDB in it make ticket on discord if that doesnt work" << std::endl;
    }
}

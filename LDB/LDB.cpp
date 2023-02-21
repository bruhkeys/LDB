#include "asdf.h"
#include "loader.h"

HKEY key;
DWORD value = 0x1;
extern HWND hwnd;
int patchbytess() {
    hwnd = hwnd;

    DWORD proc_id; GetWindowThreadProcessId(hwnd, &proc_id);
    process_handle = OpenProcess(PROCESS_VM_READ | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, false, proc_id);

    //sig-scan
    MODULEENTRY32 client = get_module("LockDownBrowser.dll", proc_id);
    auto bytes = new uint8_t[client.modBaseSize]; //making a variable size of the module

    DWORD bytes_read;

    uintptr_t dosome = find_address("LockDownBrowser.dll", 0x10A4, proc_id);
    patchmethod(0x10A4, proc_id, { 0xE9, 0x91, 0x00 }, { 0x0F, 0x84, 0x90 }, "[!]Failed to bypass keyboard security check!\r\n[!]Contact me on dc I'll update asap\r\n", "[+]Bypassed keyboard security check!\r\n", "fn");

    //part 2
    patchmethod(0x11DC, proc_id,{ 0xE9, 0x9F, 0x00, 0x00,0x00,0x00 }, { 0x0F,0x85, 0x9E, 0x00,0x00,0x00 },"[!]Failed to bypass keyboard hook!\r\n[!]Contact me on dc I'll update asap\r\n", "[+]Bypassed keyboard hook!\r\n","fn");
    print_bytes(BYTERPM(find_address("ntdll.dll", 0x9C2BB, proc_id), 4));
        uintptr_t kencarlson = (find_address("ntdll.dll", 0x9C2BB, proc_id));
        printf("kencarlson = %p\n", (void*)kencarlson);
        size_t count = 0;
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, proc_id);
        uintptr_t* matches = scanMemory(snapshot, count);
        for (size_t i = 0; i < count; i++)
        {
            std::cout << "Match found at address " << matches[i] << endl;
        }

    return 0;
 
}
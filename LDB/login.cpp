#include <iostream>
#include <string>
#include <Windows.h>
#include "loader.h"
#include <Windows.h>

#include <string>

#include <filesystem>
#include <chrono>
#define COLOR_RESET "\033[0m"
#define CARTI "\033[31m"
#define STUNNA "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define UZI "\033[34m"
#define JUICE "\033[35m"
#define XXX "\033[36m"



HWND hwnd;
int menu() {
	
	srand(time(NULL));
	int v2 = rand() % 5;
	switch (v2) {

	case 0:
    std::cout << "\x1b[38;5;201m" << R"(
      ::::::::      :::     ::::::::: ::::::::::: ::::::::::: )" << "\x1b[38;5;200m" << R"(
    :+:    :+:   :+: :+:   :+:    :+:    :+:         :+:      )" << "\x1b[38;5;199m" << R"(
   +:+         +:+   +:+  +:+    +:+    +:+         +:+       )" << "\x1b[38;5;198m" << R"(
  +#+        +#++:++#++: +#++:++#:     +#+         +#+        )" << "\x1b[38;5;197m" << R"(
 +#+        +#+     +#+ +#+    +#+    +#+         +#+         )" << "\x1b[38;5;196m" << R"(
#+#    #+# #+#     #+# #+#    #+#    #+#         #+#          )" << "\x1b[38;5;160m" << R"(
########  ###     ### ###    ###    ###     ###########          )" << "\x1b[38;5;124m" << COLOR_RESET << '\n';
	break;
	case 1:
		std::cout << "\x1b[38;5;238m" << R"(
      :::::::: ::::::::::: :::    ::: ::::    ::: ::::    :::     :::   )" << "\x1b[38;5;240m" << R"(
    :+:    :+:    :+:     :+:    :+: :+:+:   :+: :+:+:   :+:   :+: :+:  )" << "\x1b[38;5;242m" << R"(
   +:+           +:+     +:+    +:+ :+:+:+  +:+ :+:+:+  +:+  +:+   +:+  )" << "\x1b[38;5;244m" << R"(
  +#++:++#++    +#+     +#+    +:+ +#+ +:+ +#+ +#+ +:+ +#+ +#++:++#++:  )" << "\x1b[38;5;246m" << R"(
        +#+    +#+     +#+    +#+ +#+  +#+#+# +#+  +#+#+# +#+     +#+   )" << "\x1b[38;5;248m" << R"(
#+#    #+#    #+#     #+#    #+# #+#   #+#+# #+#   #+#+# #+#     #+#    )" << "\x1b[38;5;250m" << R"(
########     ###      ########  ###    #### ###    #### ###     ###    )" << "\x1b[38;5;252m" << COLOR_RESET << '\n';
		break;
	case 2:
		std::cout << "\x1b[38;5;46m" << R"(
      :::    ::: :::    ::: :::    ::: )" << "\x1b[38;5;47m" << R"(
     :+:    :+: :+:    :+: :+:    :+:  )" << "\x1b[38;5;48m" << R"(
     +:+  +:+   +:+  +:+   +:+  +:+    )" << "\x1b[38;5;49m" << R"(
     +#++:+     +#++:+     +#++:+      )" << "\x1b[38;5;50m" << R"(
   +#+  +#+   +#+  +#+   +#+  +#+      )" << "\x1b[38;5;51m" << R"(
 #+#    #+# #+#    #+# #+#    #+#      )" << "\x1b[38;5;87m" << R"(
###    ### ###    ### ###    ###      )" << "\x1b[38;5;123m" << COLOR_RESET << '\n';
		break;
	case 3:
		std::cout << "\x1b[38;5;45m" << R"(
      ::::::::   ::::::::   :::::::: )" << "\x1b[38;5;81m" << R"(
    :+:    :+: :+:    :+: :+:    :+: )" << "\x1b[38;5;117m" << R"(
   +:+    +:+ +:+    +:+ +:+    +:+  )" << "\x1b[38;5;153m" << R"(
   +#++:++#+  +#++:++#+  +#++:++#+   )" << "\x1b[38;5;189m" << R"(
        +#+        +#+        +#+    )" << "\x1b[38;5;225m" << R"(
#+#    #+# #+#    #+# #+#    #+#     )" << "\x1b[38;5;224m" << R"(
########   ########   ########       )" << "\x1b[38;5;223m" << COLOR_RESET << '\n';
		break;
	case 4:
		std::cout << "\x1b[38;5;208m" << R"(
     :::    ::: ::::::::: ::::::::::: )" << "\x1b[38;5;209m" << R"(
    :+:    :+:      :+:      :+:      )" << "\x1b[38;5;210m" << R"(
   +:+    +:+     +:+       +:+       )" << "\x1b[38;5;211m" << R"(
  +#+    +:+    +#+        +#+        )" << "\x1b[38;5;212m" << R"(
 +#+    +#+   +#+         +#+         )" << "\x1b[38;5;213m" << R"(
#+#    #+#  #+#          #+#          )" << "\x1b[38;5;177m" << R"(
########  ######### ###########        )" << "\x1b[38;5;141m" << COLOR_RESET<<'\n';
		
		break;

	}

	return 0;
}
int asdfasdfasdf() {
	// Print some colored text
	std::cout << CARTI << "       *+!:) !! slatt :(" << COLOR_RESET ;

	return 0;
}
int main(int argc, char* argv[]) {
	
	int asdf = 0;
	std::system("REG ADD HKCU\\CONSOLE /f /v VirtualTerminalLevel /t REG_DWORD /d 1");
	printf("\033[A\33[2K\r");
	menu();

	hwnd = FindWindowA(NULL, "LockDown Browser");
	printf("Waiting for LockDown Browser to open...\n");
	while (!hwnd) {
		hwnd = FindWindowA(NULL, "LockDown Browser");
		switch (asdf) {
		case 0:
			printf("\33[2K\r");
			printf("                 |");
			asdf++;
			break;
		case 1:
			printf("\33[2K\r");
			printf("                 /");
			asdf++;
			break;
		case 2:
			printf("\33[2K\r");
			printf("                 -");
			asdf++;
			break;
		case 3:
			printf("\33[2K\r");
			std::cout << "                 \\";
			asdf++;
			break;
		case 4:
			printf("\33[2K\r");
			asdfasdfasdf();
			Sleep(200);
			asdf = 0;
			break;

		}
		Sleep(200);
	}
	printf("\33[2K\r");
	printf("\033[A\33[2K\r");
	std::cout << "[1]login\n[2]inject\n[3]keybind inject\n";
	int a;
	while (true) {
		if (GetAsyncKeyState('1') & 0x8000) {
			 a = 1;
			break;

		}
		if (GetAsyncKeyState('2') & 0x8000) {
			 a = 2;
			break;
		}
		if (GetAsyncKeyState('3') & 0x8000) {
			 a = 3;
			break;
		}
		Sleep(50); // Sleep to reduce CPU usage
	}
	printf("\033[A\33[2K\r");
	printf("\033[A\33[2K\r");
	printf("\033[A\33[2K\r");
	switch (a)
	{
		case 1:

		break;
		case 2:
			patchbytess();
			break;
		case 3:
			patchbytess();
			break;
	default:
		break;
	}
	return 0;
}
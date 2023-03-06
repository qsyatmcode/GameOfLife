#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
#include "Life.h"

using namespace std;

// Clear console screen
void FillScreen(char fill = ' ') {
	COORD tl = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;

	GetConsoleScreenBufferInfo(console, &info);

	DWORD written, cells = info.dwSize.X * info.dwSize.Y;

	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, info.wAttributes, cells, tl, &written);

	SetConsoleCursorPosition(console, tl);
}

int main() {
	initscr();
	//std::ios::sync_with_stdio(false);

	Life life(128, 64);
	//Life life("testmap.txt");

	life.CoutGenerate();

	getch();

	while (true) {
		//refresh();
		clear();
		//FillScreen();

		life.CoutGenerate();

		life.Tick();

		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
		refresh();
	}
	endwin();
}
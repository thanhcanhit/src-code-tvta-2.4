#pragma once

// Standard lib
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string> // getline
#include <conio.h> // _getch
#include <string.h>
#include <algorithm> //transform

#include <windows.h> // console control

#include <io.h> // setmode
#include <fcntl.h> // _O_WTEXT for setmode

#include <locale> // set file to utf8
#include <codecvt> // utf 8

using namespace std;

//Color
enum COLOR {
	black = 0, blue = 1, green = 2, aqua = 3, red = 4, purple = 5,
	yellow = 6, white = 7, gray = 8, light_blue = 9, light_green = 10,
	light_aqua = 11, light_red = 12, light_purple = 13, light_yellow = 14,
	light_white = 15
};

static short WIDTH = 99, HEIGHT = 34, BACKGROUND_COLOR = light_white, COLOR = black;

enum {
	A = 10, B = 11, C = 12, D = 13, E = 14, F = 15,
	G = 16, H = 17, I = 18, J = 19, K = 20, L = 21,
	M = 22, N = 23, O = 24, P = 25, Q = 26, R = 27,
	S = 28, T = 29, U = 30, V = 31, W = 32, X = 33,
	Y = 34, Z = 35, DOT = 36, COMMA = 37, SLASH = 38,
	QUESTION = 39, EXCLAMATION = 40, A_ROUND = 41,
	HASHTAG = 42, PERCENT = 43, TWO_DOTS = 44,
	SEMI_COLON = 45, CIRCUMFLEX = 46, STAR = 47,
	ROUND_BRAC_L = 48, ROUND_BRAC_R = 49, SQUARE_BRAC_L = 50,
	SQUARE_BRAC_R = 51, DASH = 52, UNDER_SCORES = 53, LESS_THAN = 54,
	MORE_THAN = 55, SPACE = 56
};

wstring BIGCHAR[][6]{
	{L" ██████╗",L"██╔═████╗", L"██║██╔██║", L"████╔╝██║", L"╚██████╔╝", L" ╚═════╝ "},// 0
	{L"   ██╗", L"  ███║", L"  ╚██║", L"   ██║", L"   ██║", L"   ╚═╝"},// 1
	{L"██████╗ ", L"╚════██╗", L" █████╔╝", L"██╔═══╝ ", L"███████╗", L"╚══════╝"}, // 2
	{L"██████╗ ", L"╚════██╗", L" █████╔╝", L" ╚═══██╗", L"██████╔╝", L"╚═════╝ "}, // 3
	{L"██╗  ██╗", L"██║  ██║", L"███████║", L"╚════██║", L"     ██║", L"     ╚═╝"}, // 4
	{L"███████╗", L"██╔════╝", L"███████╗", L"╚════██║", L"███████║", L"╚══════╝"}, // 5
	{L" ██████╗", L"██╔════╝ ", L"███████╗ ", L"██╔═══██╗", L"╚██████╔╝", L" ╚═════╝"}, // 6
	{L"███████╗", L"╚════██║", L"    ██╔╝", L"   ██╔╝", L"   ██║", L"   ╚═╝"}, // 7
	{L" █████╗ ", L"██╔══██╗", L"╚█████╔╝", L"██╔══██╗", L"╚█████╔╝", L" ╚════╝"}, // 8
	{L" █████╗ ", L"██╔══██╗ ", L"╚██████║ ", L" ╚═══██║", L" █████╔╝ ", L" ╚════╝ "}, // 9
	{L" █████╗ ", L"██╔══██╗", L"███████║", L"██╔══██║", L"██║  ██║", L"╚═╝  ╚═╝"}, // A
	{L"██████╗ ", L"██╔══██╗", L"██████╔╝", L"██╔══██╗", L"██████╔╝", L"╚═════╝"}, // B
	{L" ██████╗", L"██╔════╝", L"██║ ", L"██║ ", L"╚██████╗", L" ╚═════╝"}, // C
	{L"██████╗ ", L"██╔══██╗", L"██║  ██║", L"██║  ██║", L"██████╔╝", L"╚═════╝ "}, // D
	{L"███████╗", L"██╔════╝", L"█████╗  ", L"██╔══╝  ", L"███████╗", L"╚══════╝"}, // E
	{L"███████╗", L"██╔════╝", L"█████╗  ", L"██╔══╝ ", L"██║    ", L"╚═╝   "}, // F
	{L" ██████╗ ", L"██╔════╝ ", L"██║  ███╗", L"██║   ██║", L"╚██████╔╝", L" ╚═════╝"}, // G
	{L"██╗  ██╗", L"██║  ██║", L"███████║", L"██╔══██║", L"██║  ██║", L"╚═╝  ╚═╝"}, // H
	{L"██╗", L"██║", L"██║", L"██║", L"██║", L"╚═╝"}, // I
	{L"     ██╗", L"     ██║", L"     ██║", L"██   ██║", L"╚█████╔╝", L" ╚════╝ "}, // J
	{L"██╗  ██╗", L"██║ ██╔╝", L"█████╔╝", L"██╔═██╗", L"██║  ██╗", L"╚═╝  ╚═╝"}, // K
	{L"██╗", L"██║    ", L"██║    ", L"██║    ", L"███████╗", L"╚══════╝"}, // L
	{L"███╗   ███╗", L"████╗ ████║", L"██╔████╔██║", L"██║╚██╔╝██║", L"██║ ╚═╝ ██║", L"╚═╝     ╚═╝"}, // M
	{L"███╗   ██╗", L"████╗  ██║", L"██╔██╗ ██║", L"██║╚██╗██║", L"██║ ╚████║", L"╚═╝  ╚═══╝"}, // N
	{L" ██████╗ ", L"██╔═══██╗", L"██║   ██║", L"██║   ██║", L"╚██████╔╝", L" ╚═════╝"}, // O
	{L"██████╗ ", L"██╔══██╗", L"██████╔╝", L"██╔═══╝ ", L"██║     ", L"╚═╝     "}, // P
	{L" ██████╗ ", L"██╔═══██╗", L"██║   ██║", L"██║▄▄ ██║", L"╚██████╔╝", L" ╚══▀▀═╝ "}, // Q
	{L"██████╗ ", L"██╔══██╗", L"██████╔╝", L"██╔══██╗", L"██║  ██║", L"╚═╝  ╚═╝"}, // R
	{L"███████╗", L"██╔════╝", L"███████╗", L"╚════██║", L"███████║", L"╚══════╝"}, // S
	{L"████████╗", L"╚══██╔══╝", L"   ██║   ", L"   ██║   ", L"   ██║   ", L"   ╚═╝   "}, // T
	{L"██╗   ██╗", L"██║   ██║", L"██║   ██║", L"██║   ██║", L"╚██████╔╝", L" ╚═════╝ "}, // U
	{L"██╗   ██╗", L"██║   ██║", L"██║   ██║", L"╚██╗ ██╔╝", L" ╚████╔╝ ", L"  ╚═══╝  "}, // V
	{L"██╗    ██╗", L"██║    ██║", L"██║ █╗ ██║", L"██║███╗██║", L"╚███╔███╔╝", L" ╚══╝╚══╝ "}, // W
	{L"██╗  ██╗", L"╚██╗██╔╝", L" ╚███╔╝ ", L" ██╔██╗ ", L"██╔╝ ██╗", L"╚═╝  ╚═╝"}, // X
	{L"██╗   ██╗", L"╚██╗ ██╔╝", L" ╚████╔╝ ", L"  ╚██╔╝  ", L"   ██║   ", L"   ╚═╝  "}, // Y
	{L"███████╗", L"╚══███╔╝", L"  ███╔╝ ", L" ███╔╝  ", L"███████╗", L"╚══════╝"}, // Z
	{L"   ", L"", L"", L"", L"██╗", L"╚═╝"}, // dot
	{L"   ", L"", L"", L"", L"▄█╗", L"╚═╝"}, // comma
	{L"    ██╗", L"   ██╔╝", L"  ██╔╝ ", L" ██╔╝  ", L"██╔╝   ", L"╚═╝    "}, // slash
	{L"██████╗ ", L"╚════██╗", L"  ▄███╔╝", L"  ▀▀══╝ ", L"  ██╗   ", L"  ╚═╝   "}, // question
	{L"██╗", L"██║", L"██║", L"╚═╝", L"██╗", L"╚═╝"}, // exclamation
	{L" ██████╗ ", L"██╔═══██╗", L"██║██╗██║", L"██║██║██║", L"╚█║████╔╝", L" ╚╝╚═══╝ "}, // a_round
	{L" ██╗ ██╗ ", L"████████╗", L"╚██╔═██╔╝", L"████████╗", L"╚██╔═██╔╝", L" ╚═╝ ╚═╝ "}, // hagtag
	{L"██╗ ██╗", L"╚═╝██╔╝", L"  ██╔╝ ", L" ██╔╝  ", L"██╔╝██╗", L"╚═╝ ╚═╝"}, // percent
	{L"   ", L"██╗", L"╚═╝", L"██╗", L"╚═╝", L""}, // two_dots
	{L"   ", L"██╗", L"╚═╝", L"▄█╗", L"▀═╝", L""}, // semi_colon
	{L" ███╗ ", L"██╔██╗", L"╚═╝╚═╝", L"", L"", L""}, // circumflex
	{L"     ", L"▄ ██╗▄", L" ████╗", L"▀╚██╔▀", L"  ╚═╝ ", L""}, // star
	{L" ██╗", L"██╔╝", L"██║ ", L"██║ ", L"╚██╗", L" ╚═╝"}, // round_brac_l
	{L"██╗ ", L"╚██╗", L" ██║", L" ██║", L"██╔╝", L"╚═╝ "}, // round_brac_r
	{L"███╗", L"██╔╝", L"██║ ", L"██║ ", L"███╗", L"╚══╝"}, // square_brac_l
	{L"███╗", L"╚██║", L" ██║", L" ██║", L"███║", L"╚══╝"}, // square_brac_r
	{L"      ", L"", L"█████╗", L"╚════╝", L"", L""}, // dash
	{L"        ", L"", L"", L"", L"███████╗", L"╚══════╝"}, // under_scores
	{L"  ██╗", L" ██╔╝", L"██╔╝ ", L"╚██╗ ", L" ╚██╗", L"  ╚═╝"}, // less_than
	{L"██╗  ", L"╚██╗ ", L" ╚██╗", L" ██╔╝", L"██╔╝ ", L"╚═╝  "}, // more_than
	{L"    ", L"    ", L"    ", L"    ", L"    ", L"    "}, // space
};

// BASE
void GoTo(int posX, int posY) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position{ static_cast<short>(posX), static_cast<short>(posY) };

	SetConsoleCursorPosition(hStdout, Position);
}

void PrintArrow(int y, int x = 36)
{
	GoTo(x, y);
	wcout << L"►";
}

void DelArrow(int y, int x = 36)
{
	GoTo(x, y);
	wcout << L" ";
}

int ChooseMenu(int firstLine, int quantity, int x, int k = 2)
{
	int choose = 1;
	int pos = firstLine;
	int last = firstLine + (quantity - 1) * k;
	PrintArrow(pos, x);

	char input = ' ';

	while (input != 13)
	{
		fflush(stdin);
		if (_kbhit())
		{
			input = _getch();
			switch (input)
			{
			case 72:
			case 65:
			case L'w':
				DelArrow(pos, x);
				choose--;
				pos -= k;
				if (pos < firstLine)
				{
					pos = last;
					choose = quantity;
				}
				PrintArrow(pos, x);
				break;
			case 80:
			case 66:
			case L's':
				DelArrow(pos, x);
				choose++;
				pos += k;
				if (pos > last)
				{
					pos = firstLine;
					choose = 1;
				}
				PrintArrow(pos, x);
				break;
			case 13:
				break;
			}
		}
	}

	return choose;
}
// END BASE

// CONSOLE SETTING
// Off
void offClose() {
	HWND hWnd = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hWnd, false);

	DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
}

void offMinimize() {
	HWND hWnd = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hWnd, false);

	DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
}

void offMaximize() {
	HWND hWnd = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hWnd, false);

	DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
}

void offScroll() {
	HWND hWnd = GetConsoleWindow();
	ShowScrollBar(hWnd, SB_BOTH, 0);
}

void offCursor() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = 0;

	SetConsoleCursorInfo(handle, &ConCurInf);
}

void offSelect()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}

void offChangeSize() {
	HWND hWnd = GetConsoleWindow();
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void fastOff() {
	offMinimize();
	offMaximize();
	offScroll();
	offCursor();
	offSelect();
	offChangeSize();
}

// On
void onScroll() {
	HWND hWnd = GetConsoleWindow();
	ShowScrollBar(hWnd, SB_BOTH, 1);
}

void onCursor() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = 1;

	SetConsoleCursorInfo(handle, &ConCurInf);
}

void onSelect()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleMode(hStdin, ENABLE_QUICK_EDIT_MODE);
}

void SetTitle(LPCWSTR title) {
	SetConsoleTitle(title);
}

void SetColor(int textColor = COLOR, int bgColor = BACKGROUND_COLOR) { // set màu cho những thứ tiếp theo mà bạn in ra
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int color_code = bgColor * 16 + textColor;
	SetConsoleTextAttribute(hStdout, color_code);
}

// Muốn set toàn bộ thì sài câu lệnh system("color ab) -> a là mã màu nền, b là màu chữ... mở cmd lên gõ color sẽ hiển thị ra các màu có thể chuyển

void SetSize(SHORT width = WIDTH, SHORT height = HEIGHT) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	SMALL_RECT WindowSize{};
	WindowSize.Top = 0;
	WindowSize.Left = 0;
	WindowSize.Right = width - 1;
	WindowSize.Bottom = height - 1;

	SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

void MaximizedConsole()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	onCursor();
}

void NormalConsole()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOWNORMAL);
	offCursor();
}

void MinimizeConsole() {
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_MINIMIZE);
	offCursor();
}

// END CONSOLE SETTING

// DRAW
void DrawRect(int x1, int y1, int x2, int y2) {
	GoTo(x1, y1); wprintf(L"┌");
	for (int i = x1 + 1; i < x2; i++) wprintf(L"─");
	GoTo(x2, y1); wprintf(L"┐");
	for (int i = y1 + 1; i < y2; i++) {
		GoTo(x1, i); wprintf(L"│");
		GoTo(x2, i); wprintf(L"│");
	}
	GoTo(x1, y2); wprintf(L"└");
	for (int i = x1 + 1; i < x2; i++) wprintf(L"─");
	GoTo(x2, y2); wprintf(L"┘");
}

void DrawRect2(int x1, int y1, int x2, int y2) {
	GoTo(x1, y1); wprintf(L"╔");
	for (int i = x1 + 1; i < x2; i++) wprintf(L"═");
	GoTo(x2, y1); wprintf(L"╗");
	for (int i = y1 + 1; i < y2; i++) {
		GoTo(x1, i); wprintf(L"║");
		GoTo(x2, i); wprintf(L"║");
	}
	GoTo(x1, y2); wprintf(L"╚");
	for (int i = x1 + 1; i < x2; i++) wprintf(L"═");
	GoTo(x2, y2); wprintf(L"╝");
}

void DrawBorderWindow() {
	DrawRect(1, 0, WIDTH - 1, HEIGHT - 1);
	GoTo(2, 1);
}

void DrawBorderWindow2() {
	DrawRect2(1, 0, WIDTH - 1, HEIGHT - 1);
	GoTo(2, 1);
}
//END DRAW

// TEXT
void PrintCenter(wstring s, short line = 0) {
	GoTo((WIDTH - s.length()) / 2 + 1, line);
	wcout << s;
}

void GoToPrint(int x, int y, wstring s) {
	GoTo(x, y);
	wcout << s;
}

void PrintCharASCII(wstring s[], int x, int y = 2, int n = 6) {
	for (int i = 0; i < n; i++) {
		GoToPrint(x, y, s[i]);
		y++;
	}
}

void PrintWordASCII(int s[], int n, int x, int y = 2) {
	for (int i = 0; i < n; i++) {
		PrintCharASCII(BIGCHAR[s[i]], x, y);
		unsigned int maxLengChar = 0;
		for (int j = 0; j < 6; j++) {
			if (BIGCHAR[s[i]][j].size() > maxLengChar) maxLengChar = BIGCHAR[s[i]][j].size();
		}
		x += maxLengChar;
	}
}

void DelLine(int line, int x = 2, int y = WIDTH - 2) {
	GoTo(x, line);
	for (int i = x; i < WIDTH - x - 1; i++) wcout << L' ';
}

void DelSomeLine(int line_start, int line_end, int x = 2) {
	for (int i = line_start; i <= line_end; i++) {
		DelLine(i, x);
	}
	GoTo(1, line_start);
}

int PrintMenu(wstring s[], int n, int x, int firstLine, int k = 2) {
	offCursor();
	int y = firstLine;
	for (int i = 0; i < n; i++) {
		s[i] = L"♦ " + s[i];
		GoToPrint(x, y, s[i]);
		y += k;
	}
	return ChooseMenu(firstLine, n, x - 3, k);
}

void Notice(wstring s) {
	system("cls");
	DrawRect(2, 13, WIDTH - 2, 17);
	PrintCenter(s, 15);
	GoToPrint(WIDTH - 30, HEIGHT - 2, L"♦ Ấn phím bất kỳ để tiếp tục");
	(void)_getch();
}

int Confirm(wstring s) {
	system("cls");
	DrawRect(2, 9, WIDTH - 2, 13);
	PrintCenter(s, 11);

	offCursor();
	int pos1 = WIDTH - WIDTH * 70 / 100 - 5;
	int pos2 = WIDTH - WIDTH * 30 / 100;
	DrawRect(pos1 - 5, 19, pos1 + 8, 21);
	GoToPrint(pos1, 20, L"YES");
	DrawRect(pos2 - 5, 19, pos2 + 8, 21);
	GoToPrint(pos2, 20, L"NO");

	int choose = 1;
	PrintArrow(20, pos1 - 3);

	char input = ' ';

	while (input != 13)
	{
		fflush(stdin);
		if (_kbhit())
		{
			input = _getch();
			switch (input)
			{
			case 37:
			case 67:
			case 77:
			case L'd':
				DelArrow(20, pos1 - 3);
				choose = 2;
				PrintArrow(20, pos2 - 3);
				break;
			case 39:
			case 68:
			case 75:
			case L'a':
				DelArrow(20, pos2 - 3);
				choose = 1;
				PrintArrow(20, pos1 - 3);
			case 13:
				break;
			}
		}
	}

	return choose;
}


// ANOTHER
short MaxDayOfMonth(short month, int year) {
	if (month == 0 || month == 2 || month == 4 || month == 6 || month == 7 || month == 9 || month == 11)
		return 31;
	else if (month == 3 || month == 5 || month == 8 || month == 10)
		return 30;
	else {
		if (year % 4 == 0) {
			if (year % 100 == 0) {
				if (year % 400 == 0)
					return 29;
				return 28;
			}
			return 29;
		}
		return 28;
	}
}
void StandardWString(wstring& s, int mode = 0) {
	// Del begin, end space
	while (s[0] == L' ') s.erase(s.begin());
	while (s[s.size() - 1] == L' ') s.erase(s.end() - 1);
	while (s.find(L"  ") != -1) s.erase(s.begin() + s.find(L"  "));
	transform(s.begin(), s.end(), s.begin(), ::tolower);

	transform(s.begin(), s.begin() + 1, s.begin(), ::toupper);
	if (mode == 1)
		for (unsigned int i = 0; i < s.size(); i++) {
			if (s[i] == L' ') transform(s.begin() + i + 1, s.begin() + i + 2, s.begin() + i + 1, ::toupper);
		}
}

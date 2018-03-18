#include "StdAfx.h"
#include "Screen.h"
#include <Windows.h>
#include <stdio.h>

void Screen::UpdateSize()
{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int h = csbi.srWindow.Bottom - csbi.srWindow.Top - 1;

	if (width == w && height == h)
		return;

	width = w;
	height = h;

	if (buf)
		delete[] buf;

	buf = new char[width * height + 1];
	buf[width * height] = 0;
	CleanBuf();
}

void Screen::CleanBuf()
{
	memset(buf, ' ', width * height);
}

Screen::Screen()
{
	width = 0;
	height = 0;
	buf = NULL;
}

Screen::~Screen()
{
	if (buf)
		delete[] buf;
}

void Screen::Prepare()
{
	UpdateSize();
	CleanBuf();
}

void Screen::Write(int x, int y, char c)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return;

	buf[y * width + x] = c;
}

void Screen::Draw()
{
	COORD pos = { 0, 0 };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
	puts(buf);
}

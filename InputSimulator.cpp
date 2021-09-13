#include <iostream>
#include "windows.h"

extern "C" __declspec(dllexport) void MouseEvent(bool aLeftOrRight, bool aDownOrUp, int x, int y)
{
	INPUT input = {};
	input.type = INPUT_MOUSE;
	
	if (x != 0 || y != 0)
	{
		input.mi.dx = x;
		input.mi.dy = y;
		input.mi.dwFlags = MOUSEEVENTF_MOVE;
	}
	else
	{
		if (aLeftOrRight && aDownOrUp)
			input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		if (aLeftOrRight && !aDownOrUp)
			input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		if (!aLeftOrRight && aDownOrUp)
			input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		if (!aLeftOrRight && !aDownOrUp)
			input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	}

	SendInput(1, &input, sizeof(INPUT));

	
}


extern "C" __declspec(dllexport) void MouseInterpolation(int x, int y, int speed)
{
	INPUT input = {};
	input.type = INPUT_MOUSE;
	input.mi.dx = x/5;
	input.mi.dy = y/5;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	int sleep = speed / 4;



	SendInput(1, &input, sizeof(INPUT));
	Sleep(sleep);
	SendInput(1, &input, sizeof(INPUT));
	Sleep(sleep);
	SendInput(1, &input, sizeof(INPUT));
	Sleep(sleep);
	SendInput(1, &input, sizeof(INPUT));
	Sleep(sleep);
	SendInput(1, &input, sizeof(INPUT));

}



extern "C" __declspec(dllexport) void SpecificKey(bool aDownOrUp, int vkCode)
{
	INPUT input = {};
	input.type = INPUT_KEYBOARD;
	input.ki.time = 0;
	input.ki.wScan = 0;
	input.ki.wVk = vkCode;
	if (aDownOrUp)
		input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}


extern "C" __declspec(dllexport) void SpecificExtendedKey(bool aDownOrUp, int vkCode)
{
	int key = MapVirtualKey(vkCode, 0x0);
	INPUT input = {};
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = key;
	input.ki.dwFlags = KEYEVENTF_SCANCODE;
	if (aDownOrUp)
		input.ki.dwFlags |= KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}


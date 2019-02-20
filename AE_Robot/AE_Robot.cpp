// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <Windows.h>  
#include <stdio.h>  
#include <string.h>  
#include <iostream>
using namespace std;

bool IsItemEnable(HWND hq, UINT item) {

	keybd_event(VK_MENU, 0, 0, 0);
	keybd_event('F', 0, 0, 0);
	keybd_event('F', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0, 0, 0);
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	Sleep(1000);
	auto menu = GetMenu(hq);
	auto subMenu = GetSubMenu(menu, 0);
	LPMENUITEMINFOA lpmii = new MENUITEMINFOA();
	lpmii->cbSize = sizeof(MENUITEMINFO);
	lpmii->fMask = MIIM_STATE | MIIM_ID | MIIM_TYPE;
	lpmii->fType = MFT_STRING;
	lpmii->cch = 1023;

	GetMenuItemInfoA(subMenu, item, MF_BYPOSITION, lpmii);
	return lpmii->fState == 0;
}
void Exe_AE() {

	HWND hq = FindWindow(L"AE_CApplication_15.0", NULL);
	SetForegroundWindow(hq);

	keybd_event(VK_MENU, 0, 0, 0);
	keybd_event('F', 0, 0, 0);
	keybd_event('F', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	keybd_event('X', 0, 0, 0);
	keybd_event('X', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(39, 0, 0, 0);
	keybd_event(39, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(40, 0, 0, 0);
	keybd_event(40, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(40, 0, 0, 0);
	keybd_event(40, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(0xD, 0, 0, 0);
	keybd_event(0xD, 0, KEYEVENTF_KEYUP, 0);
}
void Exe_Encoder() {
	HWND EncoderHq = FindWindow(L"Adobe Media Encoder CC 2018", NULL);
	SetForegroundWindow(EncoderHq);

	while (!IsItemEnable(EncoderHq, 10)) {
		Sleep(100);
	}

	keybd_event(VK_MENU, 0, 0, 0);
	keybd_event('F', 0, 0, 0);
	keybd_event('F', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(40, 0, 0, 0);
	keybd_event(40, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(40, 0, 0, 0);
	keybd_event(40, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(40, 0, 0, 0);
	keybd_event(40, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(40, 0, 0, 0);
	keybd_event(40, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(40, 0, 0, 0);
	keybd_event(40, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(40, 0, 0, 0);
	keybd_event(40, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(0xD, 0, 0, 0);

	while (IsItemEnable(EncoderHq, 10)) {
		Sleep(100);
	}

	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event('A', 0, 0, 0);
	keybd_event('A', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

	keybd_event(VK_DELETE, 0, 0, 0);
	keybd_event(VK_DELETE, 0, KEYEVENTF_KEYUP, 0);
}
int main(int argc, char* argv[])
{
	Exe_AE();
	Sleep(1000);
	Exe_Encoder();

	return 0;
}
// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <Windows.h>  
#include <stdio.h>  
#include <string.h>  
#include <iostream>
using namespace std;
/**
准备工作：
设置快捷键 After Effects 添加到encoder队列 ctrl + P
设置快捷键 Encoder 启动队列 ctrl + P
设置Encoder工作区显示窗口只有队列
*/

//菜单项是否可用
bool IsMenuItemEnable(HWND hq, UINT item1, UINT item2, UINT item3) {

	keybd_event(VK_MENU, 0, 0, 0);
	keybd_event('F', 0, 0, 0);
	keybd_event('F', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0, 0, 0);
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	Sleep(1000);
	auto menu = GetMenu(hq);
	auto subMenu = GetSubMenu(menu, item1);
	
	LPMENUITEMINFOA lpmii = new MENUITEMINFOA();
	lpmii->cbSize = sizeof(MENUITEMINFO);
	lpmii->fMask = MIIM_STATE | MIIM_ID | MIIM_TYPE;
	lpmii->fType = MFT_STRING;
	lpmii->cch = 1023;

	if (item3 == -1) {
		GetMenuItemInfoA(subMenu, item2, MF_BYPOSITION, lpmii);
	}
	else {
		auto subsubMenu = GetSubMenu(subMenu, item2);
		GetMenuItemInfoA(subsubMenu, item3, MF_BYPOSITION, lpmii);
	}
	
	return lpmii->fState == 0;
}
//等待菜单选项状态
void UntilMenuItemState(HWND hq,  UINT item1, UINT item2, UINT item3, bool enable) {
	while (IsMenuItemEnable(hq, item1, item2, item3) != enable) {
		wcout << "UntilMenuItemState" << endl;
		Sleep(100);
	}
}
//尝试获取窗口句柄
bool TryGetWindowsHandle(LPCWSTR name, HWND* hq, bool isClass) {
	if (isClass) {
		*hq = FindWindow(name, NULL);
	}
	else {
		*hq = FindWindow(NULL, name);
	}
	
	if (*hq == NULL) {
		return false;
	}
	return true;
}
//等待窗口开启
void UntilFindWindows(LPCWSTR className, HWND* hq, bool isClass = true) {
	while (!TryGetWindowsHandle(className, hq, isClass)) {
		wcout << "UntilFindWindows" << className << endl;
		Sleep(1000);
	}
	SetForegroundWindow(*hq);
}
//打开文件操作
void OpenFile_AE() {
	HWND hq = NULL;
	UntilFindWindows(L"AE_CApplication_15.0", &hq);
	

	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event('O', 0, 0, 0);
	keybd_event('O', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

	UntilFindWindows(L"打开", &hq, false);
	auto ComboBoxEx32Hq = FindWindowExA(hq, NULL, "ComboBoxEx32", NULL);
	auto ComboBoxHq = FindWindowExA(ComboBoxEx32Hq, NULL, "ComboBox", NULL);
	auto EditHq = FindWindowExA(ComboBoxHq, NULL, "Edit", NULL);
	SendMessage(EditHq, WM_SETTEXT, 0, LPARAM(L"demo.aep"));

	keybd_event(VK_MENU, 0, 0, 0);
	keybd_event('O', 0, 0, 0);
	keybd_event('O', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
}
//导出到Encoder操作
void Export_AE() {

	HWND hq = NULL;
	UntilFindWindows(L"AE_CApplication_15.0", &hq);
	UntilMenuItemState(hq, 0, 15, 2, true);

	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event('P', 0, 0, 0);
	keybd_event('P', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
}
//Encoder执行生成视频操作
void Exe_Encoder() {
	HWND hq = NULL;
	UntilFindWindows(L"Adobe Media Encoder CC 2018", &hq);

	UntilMenuItemState(hq, 0, 10,-1, true);

	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event('P', 0, 0, 0);
	keybd_event('P', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

	UntilMenuItemState(hq, 0, 10, -1, false);

	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event('A', 0, 0, 0);
	keybd_event('A', 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

	keybd_event(VK_DELETE, 0, 0, 0);
	keybd_event(VK_DELETE, 0, KEYEVENTF_KEYUP, 0);
}
//打印菜单项名字
void PrintMuneName(LPCWSTR windowsName) {
	HWND hq = NULL;
	UntilFindWindows(windowsName, &hq);
	auto menu = GetMenu(hq);

	int i = 0;
	int j = 0;
	int k = 0;
	wchar_t ch[100];
	LPMENUITEMINFOA lpmii = new MENUITEMINFOA();
	lpmii->cbSize = sizeof(MENUITEMINFO);
	lpmii->fMask = MIIM_ID;

	while (true) {
		auto subMenu = GetSubMenu(menu, i);
		if (subMenu == NULL) {
			break;
		}
		j = 0;
		while (true) {

			if (GetMenuItemInfoA(subMenu, j, MF_BYPOSITION, lpmii) == 0) {
				break;
			}

			GetMenuStringW(subMenu, j, ch, 1000, MF_BYPOSITION);
			
			wcout << i << L" " << j << L" " << ch << endl;

			auto subsubMenu = GetSubMenu(subMenu, j);
			if (subsubMenu != NULL) {
				k = 0;
				while (true) {
					if (GetMenuItemInfoA(subsubMenu, k, MF_BYPOSITION, lpmii) == 0) {
						break;
					}

					GetMenuStringW(subsubMenu, k, ch, 1000, MF_BYPOSITION);

					wcout << i << L" " << j << L" " << k <<L" "<< ch << endl;
					k++;
				}
			}
			j++;
		}
		wcout << endl;
		i++;
	}
}
//打印该窗口下所有子窗口名字
void PrintChildWindows(HWND parentHq, int layerIndex) {
	layerIndex++;
	auto hq = GetWindow(parentHq, GW_CHILD);
	if (hq == NULL) {
		return;
	}
	wchar_t s[200] = { 0 };
	//int num = 1;
	while (hq != NULL)                    //循环得到所有的子窗口
	{
		memset(s, 0, 200);
		GetWindowText(hq, s, 200);
		wcout << layerIndex << " " << s << endl;
		if (hq != NULL) {
			PrintChildWindows(hq, layerIndex);
		}
		hq = GetNextWindow(hq, GW_HWNDNEXT);
		
		
	}
}
//打印所有窗口名字
void PrintAllWindows(LPCWSTR className) {
	HWND hq = NULL;
	UntilFindWindows(className, &hq);
	int layerIndex = 0;
	PrintChildWindows(hq, layerIndex);

}

void Test() {
	HWND parentHq = NULL;
	UntilFindWindows(L"Adobe Media Encoder CC 2018", &parentHq);
	auto hq = GetWindow(parentHq, GW_CHILD);
	if (hq == NULL) {
		return;
	}
	SendMessage(hq, WM_LBUTTONDOWN, NULL, MAKELPARAM(50, 50));
	//SendMessage(hq, WM_LBUTTONUP, NULL, MAKELPARAM(100, 100));
	//SetActiveWindow(hq);
	//SetFocus(hq);
	/*auto menu = GetMenu(hq);
	auto subMenu = GetSubMenu(menu, 0);
	wchar_t ch[100];
	GetMenuStringW(subMenu, 0, ch, 1000, MF_BYPOSITION);

	Sleep(1000);*/
	/*LPMENUITEMINFOA lpmii = new MENUITEMINFOA();
	lpmii->cbSize = sizeof(MENUITEMINFO);
	lpmii->dwTypeData = NULL;
	lpmii->fMask = MIIM_STRING;
	lpmii->fType = MFT_STRING;
	lpmii->cch = 1023;

	GetMenuItemInfoA(subMenu, 0, MF_BYPOSITION, lpmii);
	cout << lpmii->dwTypeData << endl;*/
	//auto childhq = FindWindowExA(hq, NULL, "ComboBoxEx32", NULL);
	////SendMessage(childhq, WM_SETTEXT, 0, (LPARAM)L"C:\\Documents and Settings\\Blah\\Desktop\\myText.txt");
	//SendMessage(childhq, WM_SETTEXT, 0, LPARAM(L"hello"));
}
int main(int argc, char* argv[])
{
	wcout.imbue(std::locale("chs"));
	//Test();

	//PrintAllWindows(L"Adobe Media Encoder CC 2018");
	//system("pause");
	OpenFile_AE();
	//return 0;
	Export_AE();
	Sleep(1000);
	Exe_Encoder();
	system("pause");
	return 0;
}
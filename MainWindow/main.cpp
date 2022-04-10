

//��� ����, ����� ������� ������� ���� ����������, ����� ��������� 3 ����:
//1. ����������� ������ ����
//2. �������� ����
//3. ����� ����� ���������
#define _CRT_SECURE_NO_WARNINGS
#include <winapifamily.h>
#include <Windows.h>
#include <stdio.h>
#include "resource.h"

#define IDC_MY_STATIC 104 //������ ��� � resource.h �������

CONST CHAR g_szClassName[] = "My Window Class"; //��� ������

//g- global
//sz - string zero

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//1. ����������� ������ ����
	WNDCLASSEX wc; //wc- Window Class
	ZeroMemory(&wc, sizeof(WNDCLASSEX)); //�������� ��������� 'wc'
	//�������������� ���� ��������� 'wc';
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc; //����� ��������� ���� ��� ������� ������.
	wc.style = 0; //����� ����, ���������� ��� �������������� ��������.
					// ����� ��������� ������ ������� �� ������ ����
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)); //������, ������������ � ������ �����
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)); // ������, ������������ � ������ ���������
	
	
	//wc.hIcon = (HICON)LoadImage(hInstance, "OneDrive.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE); //����� ���������������, ����������� ������ ���� � ���� ������������.
	//wc.hIconSm = (HICON)LoadImage(hInstance, "OneDrive.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE); //����� ���������������, ����������� ������ ���� � ���� ������������.
	
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1)); //������ ����
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL; 
	wc.lpszClassName = g_szClassName;
	//����������� ������ ����:
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}



    //2. �������� ����:

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int windowStartX = screenWidth / 8;
	int windowStartY = screenHeight / 8;
	int windowWidth = screenWidth - screenWidth / 4;
	int windowHeight = screenHeight - screenHeight / 4;


	HWND hwnd = CreateWindowEx
	(
		NULL,              //Ex-style- ����������� ����� ����
		g_szClassName,     // ��� ������ ����
		"Main Window",     // ��������� ���� ����� ���� g_szClassName
		WS_OVERLAPPEDWINDOW,//����� ����. � �������� ���� ���������� ����� ������ OverlappedWindow
		windowStartX, windowStartY,  //��������� ���� �� ������
		windowWidth, windowHeight,  // ������ ����
		NULL,              // ������������ ����, ��� ����������� ���� NULL
		NULL,              // ID ���� ����, ���� ���� �������, ��� ID �������, ���� ���� ��������. NULL- ������ ���� �����������
		hInstance,         // ��������� exe
		NULL               // ������ ��� �������� ����, ���� ����� ���-�� �������� ��������� ����
	);

	//������� ����, ������ ���������, ��������� ��

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Info", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);  // ����� ����� ����������� ( ��������� �� ���� �����, ������� � ������ ����� ���
	UpdateWindow(hwnd);          // ���������� ����


	//3. ������ ����� ���������

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)  // GetMessage() ���� ��������� �� ������� ��������� �������� ������
	{
		TranslateMessage(&msg);   // 
		DispatchMessage(&msg);    // ���������� ��������� � ��������� ����
	}



	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:    
		//����� ��������� �������� ����- ������, ����, ������ � �.�.
		//��� ������ ��������� WM_INITDIALOG � ���������� ����
		//��� ��������� ������������ ���� ��� -  ��� �������� ����
		CreateWindowEx
		(
			NULL,
			"Static",
			"This is my static text, where the screen size and its position will be",
			WS_CHILDWINDOW | WS_VISIBLE,
			10,10,
			1000, 50,
			hwnd,
			(HMENU)IDC_MY_STATIC,
			GetModuleHandle(NULL),
			NULL
		);

		break;
	case WM_COMMAND: 
		
		break;
	case WM_MOVE:
	case WM_SIZE:
	{
		CONST int SIZE = 256; //������ ������
		CHAR buffer[SIZE] = {};
		RECT rect; //��������� �������������
		//����� �������� ������������� ����
		GetWindowRect(hwnd, &rect); //winAPI ��� ������� ���� C
		int windowWidth = rect.right - rect.left; //������ ����
		int windowHeight = rect.bottom - rect.top; //������ ����
		sprintf(buffer, "Size: %dx%d, Position: %dx%d" ,windowWidth, windowHeight, rect.left, rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)buffer);
		
		HWND hStatic = GetDlgItem(hwnd, IDC_MY_STATIC);
		SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)buffer);
	}
		break;
			

	case WM_CLOSE: 
		//�������� ��������� DestroyWindow ������ ����
		if (MessageBox(hwnd, "Want to close?", "Exit", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY: 
		//���������� �������� ��������� � ������� ���������
		PostQuitMessage(0);// �������� ��������� � ����������� ������.
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
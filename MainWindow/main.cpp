

//Для того, чтобы создать главное окно приложения, нужно выполнить 3 вещи:
//1. Регистрация класса окна
//2. Создание окна
//3. Зпуск цикла сообщений
#define _CRT_SECURE_NO_WARNINGS
#include <winapifamily.h>
#include <Windows.h>
#include <stdio.h>
#include "resource.h"

#define IDC_MY_STATIC 104 //обычно это в resource.h пишется

CONST CHAR g_szClassName[] = "My Window Class"; //Имя класса

//g- global
//sz - string zero

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//1. Регистрация класса окна
	WNDCLASSEX wc; //wc- Window Class
	ZeroMemory(&wc, sizeof(WNDCLASSEX)); //Зануляем экземпляр 'wc'
	//Инициализируем поля структуры 'wc';
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc; //Задаём процедуру окна для данного класса.
	wc.style = 0; //Стиль окна, определяет его дополнительные свойства.
					// Набор возможных стилей зависит от класса окна
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)); //Иконка, отображаемая в панели задач
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)); // Иконка, отображаемая в строке заголовка
	
	
	//wc.hIcon = (HICON)LoadImage(hInstance, "OneDrive.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE); //менее предпочтительно, подгрузится только если в зоне досигаемости.
	//wc.hIconSm = (HICON)LoadImage(hInstance, "OneDrive.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE); //менее предпочтительно, подгрузится только если в зоне досигаемости.
	
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1)); //курсор окна
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL; 
	wc.lpszClassName = g_szClassName;
	//регистрация класса окна:
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}



    //2. Создание окна:

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int windowStartX = screenWidth / 8;
	int windowStartY = screenHeight / 8;
	int windowWidth = screenWidth - screenWidth / 4;
	int windowHeight = screenHeight - screenHeight / 4;


	HWND hwnd = CreateWindowEx
	(
		NULL,              //Ex-style- расширенный стиль окна
		g_szClassName,     // Имя класса окна
		"Main Window",     // Заголовок окна можно тоже g_szClassName
		WS_OVERLAPPEDWINDOW,//Стиль окна. У главного окна приложения стиль всегда OverlappedWindow
		windowStartX, windowStartY,  //положение окна на экране
		windowWidth, windowHeight,  // размер окна
		NULL,              // родительское окно, оно отсутствует если NULL
		NULL,              // ID меню окна, если окно главное, или ID ресурса, если окно дочернее. NULL- значит меню отсутствует
		hInstance,         // экземпляр exe
		NULL               // Только для дочерних окон, если нужно что-то передать дочернему окну
	);

	//создали окно, теперь проверяем, создалось ли

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Info", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);  // Задаём режим отображения ( развёрнуто на весь экран, свёрнуто в панель задач итд
	UpdateWindow(hwnd);          // Прорисовка окна


	//3. Запуск цикла сообщений

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)  // GetMessage() берёт сообщение из очереди сообщений текущего потока
	{
		TranslateMessage(&msg);   // 
		DispatchMessage(&msg);    // Отправляет сообщение в процедуру окна
	}



	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:    
		//Здесь создаются элементы окна- кнопки, меню, значки и т.д.
		//Это аналог сообщения WM_INITDIALOG в диалоговом окне
		//Это сообщение отрабатывает один раз -  при создании окна
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
		CONST int SIZE = 256; //размер буфера
		CHAR buffer[SIZE] = {};
		RECT rect; //объявляем прямоугольник
		//нужно получить прямоугольник окна
		GetWindowRect(hwnd, &rect); //winAPI это целиком язык C
		int windowWidth = rect.right - rect.left; //ширина окна
		int windowHeight = rect.bottom - rect.top; //высота окна
		sprintf(buffer, "Size: %dx%d, Position: %dx%d" ,windowWidth, windowHeight, rect.left, rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)buffer);
		
		HWND hStatic = GetDlgItem(hwnd, IDC_MY_STATIC);
		SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)buffer);
	}
		break;
			

	case WM_CLOSE: 
		//Посылает сообщение DestroyWindow своему окну
		if (MessageBox(hwnd, "Want to close?", "Exit", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY: 
		//Отправляет выходное сообщение в очередь сообщений
		PostQuitMessage(0);// Посылает сообщение о прекращении работы.
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "resource.h"
#include <cstdio>

CONST CHAR* string[] =
{
	"This", "is","my","first","Combo", "Box"
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// type name(parametrs);
//type calling_convention(paramentrs);
//type- тип возвращаемого значения: bool, char,int....
//calling_convention - конвенция вызовов (соглашение о вызове функции):
//__syscall  - ?
//__stdcall  - WinAPI
//__fastcall - x64
//__cdecl - C++
//конвенция вызовов определяет порядок вызова функции: 
//- кто очищает стек, вызывающая функция (caller) или вызываемая функция (callee)
// - как читается список передаваемых параметров- слева направо или справа налево
//   или же параметры ( первые 4, остальный через стек - он в ОЗУ) передаются через регистры (конвенция __fastcall)

//-------------------------------------------------

//HINSTANCE hInstance- экземпляр исполняемого файла (*.exe). Это загруженный в память exe- файл нашей программы
//HINSTANCE hPrevInst- предыдущий экземпляр *.exe- файла. Этот параметр использовался в Windows 98 и оставлен только для обратной совместимости 
//LPSTRD lpCmdLine - командная строка, из которой была запущена программа. LPSTR: LP- LongPointer, 
//   STR - String => LPSTR - LongPointer to String ( указатель на строку - char*)
//   int cCmdShow - режим отображения окна: свёрнуто в окно, развёрнуто на весь экран, свёрнуто на панель задач итд) Как запустится программа



INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//DialogBoxParam- функция, которая запускает диалоговое окно
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
	//MakeINTResource возвращает по номеру ресурса имя ресурса




	return 0;
}

//HWND - Handler to Window. ОБРАБОТЧИК ОКНА, дескриптор окна.
//HWND - идентификатор окна, через который к нему можно обратиться.
//HWND - это как имя переменной или функции.
//HWND - это окно!
//UINT uMsg - Message (сообщение). UINT - insigned int
//wParam, lParam - параметры сообщения, они зависят от того, какое именно uMsg мы посылаем окну


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:  //Это сообщение отправляется в окно при его создании
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO1);
		//GetDlgItem- возвращает HWND элемента окна по ID- ресурса нужного элемента
	
		
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); ++i)
		{
			SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)string[i]);
			//сообщение CB_ADDSTRING добавляет указанную строку в ComboBox
		}


	}
	break;
	case WM_COMMAND:   //Это сообщение обрабатывает нажатие на кнопки и другие элементы интерфейса
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {}; //в эту строку мы скопируем выделенную строку ComboBox.
			CHAR sz_message[SIZE] = {}; //эту строку мы будем отображать в MessageBox.

			HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO1);
			int index = SendMessage(hComboBox, CB_GETCURSEL, 0, 0); //получаем числовой индекс выделенного элемента ComboBox
			SendMessage(hComboBox, CB_GETLBTEXT, index, (LPARAM)sz_buffer);
			if (index < 0)
			{
				sprintf(sz_message, "Open ComboBox and choose something");
			}
			else 
			
			{
				sprintf(sz_message, "You chose element # %d with the meaning \"%s\".", index, sz_buffer);
			}
			//функция sprintf() выполняет форматирование строк
			//sz_message - это буфер, в который сохранится отформатированная строка
			//"You chose..." - шаблон строки, то есть то, как она должна выглядеть
			//%d - вставить в шаблонную строку десятичное целое число (decimal)
			//%s - вставить в шаблонную строку подстроку
			//все вставляемые значения перечислены далее в передаваемых параметрах: index, sz_buffer....
			//Количество параметров функции sprintf() неограниченно.
			//Функция sprintf() позволяет вставлять в строку какие- угодно значения.

		//	MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}

		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return false;

}


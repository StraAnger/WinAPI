#include <Windows.h>
#include "resource.h"

CHAR sz_login_invitation[] = "Enter login";
CHAR sz_password_invitation[] = "Enter password";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	/*MessageBox(NULL, "HelloWorld", "Info", MB_YESNOCANCEL | MB_ICONERROR | MB_HELP
		| MB_DEFBUTTON4 | MB_SYSTEMMODAL);*/

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);


	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)sz_login_invitation);
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_PASSWORD), WM_SETTEXT, 0, (LPARAM)sz_password_invitation);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			//при выполнении различных действий над каким- либо элементом интерфейса ( окном),
			// этот элемент интерфейса ( окно) получает уведомление. ”ведомлени€, это самые обычные сообщени€.
			// Ќапример, когда мы становимс€ в текстовое поле, то это текстовое поле получает уведомление EN_SETFOCUS
			//  огда мы уходим из текстового пол€, то оно получает уведомление EN_KILLFOCUS. 
			//‘окус - часть окна, котора€ принимает команды клавиатуры.
			switch (HIWORD(wParam))
			{
			case EN_SETFOCUS:SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)"");
				break;
			case EN_KILLFOCUS:
			{
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				if (!GetDlgItemText(hwnd, IDC_EDIT_LOGIN, sz_buffer, SIZE))
					SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)"Enter login");
				break;
			}
			}
		}

		break;
		case IDC_BUTTON_COPY:

		{
			CONST INT SIZE = 256; // размер буфера
			CHAR sz_buffer[SIZE] = {};
			HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN); //получаем ID окна текстового пол€ по имени ресурса
			SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer); // опируем текст из текстового пол€ Login в sz_buffer
			HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer); // опируем текст из текстового пол€ Password в sz_buffer
		}
		break;
		case IDC_BUTTON_SET_TITLE:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			// SendMessage(FindWindow(NULL,"WinAPI - Microsoft Visual Studio"), WM_SETTEXT, 0, (LPARAM)sz_buffer);

		}
		break;
		case IDOK:
			MessageBox(NULL, "OK pressed", "Info", MB_OK | MB_ICONINFORMATION);
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}

	}

	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
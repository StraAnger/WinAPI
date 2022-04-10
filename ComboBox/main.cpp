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
//type- ��� ������������� ��������: bool, char,int....
//calling_convention - ��������� ������� (���������� � ������ �������):
//__syscall  - ?
//__stdcall  - WinAPI
//__fastcall - x64
//__cdecl - C++
//��������� ������� ���������� ������� ������ �������: 
//- ��� ������� ����, ���������� ������� (caller) ��� ���������� ������� (callee)
// - ��� �������� ������ ������������ ����������- ����� ������� ��� ������ ������
//   ��� �� ��������� ( ������ 4, ��������� ����� ���� - �� � ���) ���������� ����� �������� (��������� __fastcall)

//-------------------------------------------------

//HINSTANCE hInstance- ��������� ������������ ����� (*.exe). ��� ����������� � ������ exe- ���� ����� ���������
//HINSTANCE hPrevInst- ���������� ��������� *.exe- �����. ���� �������� ������������� � Windows 98 � �������� ������ ��� �������� ������������� 
//LPSTRD lpCmdLine - ��������� ������, �� ������� ���� �������� ���������. LPSTR: LP- LongPointer, 
//   STR - String => LPSTR - LongPointer to String ( ��������� �� ������ - char*)
//   int cCmdShow - ����� ����������� ����: ������� � ����, ��������� �� ���� �����, ������� �� ������ ����� ���) ��� ���������� ���������



INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//DialogBoxParam- �������, ������� ��������� ���������� ����
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
	//MakeINTResource ���������� �� ������ ������� ��� �������




	return 0;
}

//HWND - Handler to Window. ���������� ����, ���������� ����.
//HWND - ������������� ����, ����� ������� � ���� ����� ����������.
//HWND - ��� ��� ��� ���������� ��� �������.
//HWND - ��� ����!
//UINT uMsg - Message (���������). UINT - insigned int
//wParam, lParam - ��������� ���������, ��� ������� �� ����, ����� ������ uMsg �� �������� ����


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:  //��� ��������� ������������ � ���� ��� ��� ��������
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO1);
		//GetDlgItem- ���������� HWND �������� ���� �� ID- ������� ������� ��������
	
		
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); ++i)
		{
			SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)string[i]);
			//��������� CB_ADDSTRING ��������� ��������� ������ � ComboBox
		}


	}
	break;
	case WM_COMMAND:   //��� ��������� ������������ ������� �� ������ � ������ �������� ����������
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {}; //� ��� ������ �� ��������� ���������� ������ ComboBox.
			CHAR sz_message[SIZE] = {}; //��� ������ �� ����� ���������� � MessageBox.

			HWND hComboBox = GetDlgItem(hwnd, IDC_COMBO1);
			int index = SendMessage(hComboBox, CB_GETCURSEL, 0, 0); //�������� �������� ������ ����������� �������� ComboBox
			SendMessage(hComboBox, CB_GETLBTEXT, index, (LPARAM)sz_buffer);
			if (index < 0)
			{
				sprintf(sz_message, "Open ComboBox and choose something");
			}
			else 
			
			{
				sprintf(sz_message, "You chose element # %d with the meaning \"%s\".", index, sz_buffer);
			}
			//������� sprintf() ��������� �������������� �����
			//sz_message - ��� �����, � ������� ���������� ����������������� ������
			//"You chose..." - ������ ������, �� ���� ��, ��� ��� ������ ���������
			//%d - �������� � ��������� ������ ���������� ����� ����� (decimal)
			//%s - �������� � ��������� ������ ���������
			//��� ����������� �������� ����������� ����� � ������������ ����������: index, sz_buffer....
			//���������� ���������� ������� sprintf() �������������.
			//������� sprintf() ��������� ��������� � ������ �����- ������ ��������.

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


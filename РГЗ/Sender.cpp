//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdlib.h>
#include <queue>
#include <Math.hpp>
#pragma hdrstop

#include "Sender.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

DWORD CALLBACK ThreadFunc1(void* P) //�����, ������� ��������� ��������� �� ���� �� ����,
{                                   //���� ��, �� ������� ���
	for(;;)
	{
			for(int p=0;p<Form1->max;p++)
			{
				if(!Form1->hp.empty())//���� ������� �� �����
				{
					Form1->hh = Form1->hp.front(); //����� ����� �� ������ �������
					GetExitCodeProcess(Form1->hh, &Form1->lpExitCode);//��������� ������ � ��������� ���������� ������ ��������
					if (Form1->lpExitCode != STILL_ACTIVE)//���� �������(����) �� �������
					{

						CloseHandle(Form1->hh); //��������� ����� ��������
						Form1->hp.pop(); //�������� ��� �� �������

						Form1->num1 = String(p);
						Form1->l = RandomRange(3,10); //�������� ����� ����� ����
						Form1->num2 = String(Form1->l);
						Form1->num1 +=";"+Form1->num2;
						Form1->cmdArgs = (LPTSTR)Form1->num1.c_str(); //��������� ��������� ������
						CreateProcess(L"E:\\NSTU\\����\\2 ����\\��\\���\\Win32\\Debug\\Project2.exe",        //��������������� �� ���� ���� !!!!
						Form1->cmdArgs, NULL, NULL, false, 0, NULL, NULL, &Form1->sinfo, &Form1->pinfo); //������� ����
						CloseHandle(Form1->pinfo.hThread); //��������� ����� ������
						Form1->hp.push(Form1->pinfo.hProcess); //��������� � ������� ����� ��������

					}
					else
					{

						Form1->hp.pop(); //�������  ������� �� ������ �������
						Form1->hp.push(Form1->hh); //� ������ ��� � �����
					}

				}

			}



	}

	return 0;
}

void __fastcall TForm1::Button1Click(TObject *Sender) // ������ ������� ������
{
	if( hThread!= INVALID_HANDLE_VALUE)return;   //���� ����� ��������, �� ������ �� ������
	max = StrToInt(Edit1->Text); //��������� ������������ ���-�� ����
	int i=0;
	while(i<max)
	{
		num1 = String(i);
		l = RandomRange(3,10); //�������� ����� ����� ����
		num2 = String(l);
		num1 +=";"+num2;
		cmdArgs = (LPTSTR)num1.c_str(); //��������� ��������� ������
		CreateProcess(L"E:\\NSTU\\����\\2 ����\\��\\���\\Win32\\Debug\\Project2.exe",     //��������������� �� ���� ���� !!!!
		cmdArgs, NULL, NULL, false, 0, NULL, NULL, &sinfo, &pinfo);  //������� ����
		CloseHandle(pinfo.hThread); //��������� ����� ������
		hp.push(pinfo.hProcess);   //��������� � ������� ����� ��������
		i++;
	}
	hThread = CreateThread(0,0,ThreadFunc1,0,0,NULL); //������� �����

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender) //������ ��������� ������
{
	TerminateThread(hThread,1); //���������� ��������� ���� �����
	for(int p=0;p<max;p++)
		{
			if(!hp.empty())//���� ������� �� �����
			{
				hh = hp.front(); //����� ����� �� ������ �������
				GetExitCodeProcess(hh, &lpExitCode); //��������� ������ � ��������� ���������� ������ ��������
				if (lpExitCode == STILL_ACTIVE) //���� �������(����) �������
				{
					TerminateProcess(hh,666); //��������� ���

				}
				CloseHandle(hh); //��������� ����� ��������
				hp.pop(); //������� ������ ������� �������
			}
		}
	CloseHandle( hThread ); //��������� ����� ������
	hThread = INVALID_HANDLE_VALUE;
	max=0; //�������� ������������ ���-�� ����
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Timer1Timer(TObject *Sender)//������, ������� ������ ������
{                                                  //���������� ���� ����� ���������, ��� ��� ������� ������
	for(int p=0;p<max;p++)
	{
		win = String(p);
		cmdArg = (LPTSTR)win.c_str(); //������ ��� ����, �������� �������� ���������
		hWnd = FindWindow(NULL, cmdArg); //���� ���� � �������� ������
		SendMessage(hWnd,WM_USER+1, 200, 0); //���������� ���������
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose) //������� ������������ ��� ���� ��� �������
{                                                                       // �� �������, ���������� ������ ����
	TerminateThread(hThread,1);
	for(int p=0;p<max;p++)
		{
			if(!hp.empty())
			{
				hh = hp.front();
				GetExitCodeProcess(hh, &lpExitCode);
				if (lpExitCode == STILL_ACTIVE)
				{
					TerminateProcess(hh,666);

				}
				CloseHandle(hh);
				hp.pop();
			}
		}
}
//---------------------------------------------------------------------------


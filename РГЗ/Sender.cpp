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

DWORD CALLBACK ThreadFunc1(void* P) //поток, который проверяет закрылось ли одно из окон,
{                                   //если да, то создает его
	for(;;)
	{
			for(int p=0;p<Form1->max;p++)
			{
				if(!Form1->hp.empty())//если очередь не пуста
				{
					Form1->hh = Form1->hp.front(); //берем хендл из начала очереди
					GetExitCodeProcess(Form1->hh, &Form1->lpExitCode);//извлекаем данные о состоянии завершения работы процесса
					if (Form1->lpExitCode != STILL_ACTIVE)//если процесс(окно) не активно
					{

						CloseHandle(Form1->hh); //закрываем хендл процесса
						Form1->hp.pop(); //удалаяем его из очереди

						Form1->num1 = String(p);
						Form1->l = RandomRange(3,10); //рандомим время жизни окна
						Form1->num2 = String(Form1->l);
						Form1->num1 +=";"+Form1->num2;
						Form1->cmdArgs = (LPTSTR)Form1->num1.c_str(); //формируем командную строку
						CreateProcess(L"E:\\NSTU\\АВТФ\\2 курс\\ОС\\РГЗ\\Win32\\Debug\\Project2.exe",        //Отредактировать на свой путь !!!!
						Form1->cmdArgs, NULL, NULL, false, 0, NULL, NULL, &Form1->sinfo, &Form1->pinfo); //создвем окно
						CloseHandle(Form1->pinfo.hThread); //закрываем хендл потока
						Form1->hp.push(Form1->pinfo.hProcess); //добавляем в очередь хендл процесса

					}
					else
					{

						Form1->hp.pop(); //удаляем  элемент из начала очереди
						Form1->hp.push(Form1->hh); //и кладем его в конец
					}

				}

			}



	}

	return 0;
}

void __fastcall TForm1::Button1Click(TObject *Sender) // кнопка запуска работы
{
	if( hThread!= INVALID_HANDLE_VALUE)return;   //если поток работает, то ничего не делаем
	max = StrToInt(Edit1->Text); //считываем максимальное кол-во окон
	int i=0;
	while(i<max)
	{
		num1 = String(i);
		l = RandomRange(3,10); //рандомим время жизни окна
		num2 = String(l);
		num1 +=";"+num2;
		cmdArgs = (LPTSTR)num1.c_str(); //формируем командную строку
		CreateProcess(L"E:\\NSTU\\АВТФ\\2 курс\\ОС\\РГЗ\\Win32\\Debug\\Project2.exe",     //Отредактировать на свой путь !!!!
		cmdArgs, NULL, NULL, false, 0, NULL, NULL, &sinfo, &pinfo);  //создвем окно
		CloseHandle(pinfo.hThread); //закрываем хендл потока
		hp.push(pinfo.hProcess);   //добавляем в очередь хендл процесса
		i++;
	}
	hThread = CreateThread(0,0,ThreadFunc1,0,0,NULL); //создаем поток

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender) //кнопка остановки работы
{
	TerminateThread(hThread,1); //уничтожаем созданный нами поток
	for(int p=0;p<max;p++)
		{
			if(!hp.empty())//если очередь не пуста
			{
				hh = hp.front(); //берем хендл из начала очереди
				GetExitCodeProcess(hh, &lpExitCode); //извлекаем данные о состоянии завершения работы процесса
				if (lpExitCode == STILL_ACTIVE) //если процесс(окно) активно
				{
					TerminateProcess(hh,666); //уничтожем его

				}
				CloseHandle(hh); //закрываем хендл процесса
				hp.pop(); //удаляем первый элемент очереди
			}
		}
	CloseHandle( hThread ); //закрываем хендл потока
	hThread = INVALID_HANDLE_VALUE;
	max=0; //обнуляем максимальное кол-во окон
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Timer1Timer(TObject *Sender)//таймер, который каждую секнду
{                                                  //отправляет всем окнам сообщение, что эта секунда прошла
	for(int p=0;p<max;p++)
	{
		win = String(p);
		cmdArg = (LPTSTR)win.c_str(); //задаем имя окна, которому отправим сообщение
		hWnd = FindWindow(NULL, cmdArg); //ищем окно с заданным именем
		SendMessage(hWnd,WM_USER+1, 200, 0); //отправляем сообщение
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose) //функция закрыввающая все окна при нажатии
{                                                                       // на крестик, аналогична кнопке Стоп
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


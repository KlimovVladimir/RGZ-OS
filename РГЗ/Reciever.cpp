//---------------------------------------------------------------------------

#include <vcl.h>
#include <string.h>
#include <stdio.h>
#pragma hdrstop

#include "Reciever.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	LPTSTR lpCmdLine = GetCommandLine(); //получаем командную строку
	AnsiString num = lpCmdLine;
	char* istr1;
	istr1 = strtok ((char*)num.c_str(),";"); //разделяем эту строку по разделителю ;
	Form2->Caption =  istr1; //первая часть строки - заголовок окна
	istr1 = strtok (NULL,";"); //делим эту строку еще раз
	Label1->Caption =  istr1; //вторая часть строки - время жизни
}
//---------------------------------------------------------------------------
void __fastcall TForm2::WMUSER1(TMessage &msg) //обработчик сообщения
{
	if (msg.WParam==200)//если параметр WParam полученного сообщения = 200
	{
		t = StrToInt(Label1->Caption);//время жизни считываем из  Label1
		t--; //уменьшаем на 1
		Label1->Caption =  IntToStr(t); //и записываем обратно
	}
	if(t <= 0) //если время жизни <= 0
	{
		exit(1);  //то выходим из приложения

	}
}


//---------------------------------------------------------------------------


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
	LPTSTR lpCmdLine = GetCommandLine(); //�������� ��������� ������
	AnsiString num = lpCmdLine;
	char* istr1;
	istr1 = strtok ((char*)num.c_str(),";"); //��������� ��� ������ �� ����������� ;
	Form2->Caption =  istr1; //������ ����� ������ - ��������� ����
	istr1 = strtok (NULL,";"); //����� ��� ������ ��� ���
	Label1->Caption =  istr1; //������ ����� ������ - ����� �����
}
//---------------------------------------------------------------------------
void __fastcall TForm2::WMUSER1(TMessage &msg) //���������� ���������
{
	if (msg.WParam==200)//���� �������� WParam ����������� ��������� = 200
	{
		t = StrToInt(Label1->Caption);//����� ����� ��������� ��  Label1
		t--; //��������� �� 1
		Label1->Caption =  IntToStr(t); //� ���������� �������
	}
	if(t <= 0) //���� ����� ����� <= 0
	{
		exit(1);  //�� ������� �� ����������

	}
}


//---------------------------------------------------------------------------


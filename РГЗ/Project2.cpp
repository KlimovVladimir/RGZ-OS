//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "Reciever.h"
#include <string.h>
#include <stdio.h>
//---------------------------------------------------------------------------
USEFORM("Reciever.cpp", Form2);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR lpCmdLine, int)
{
	//num = (char*)lpCmdLine ";jgf";
	//CopyMemory(lpFileMap,buff, 40);
	//lpCmdLine = L"aizdasds";
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TForm2), &Form2);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

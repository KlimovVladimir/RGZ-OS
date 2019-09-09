//---------------------------------------------------------------------------

#ifndef SenderH
#define SenderH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TTimer *Timer1;
	TEdit *Edit1;
	TButton *Button2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall Button2Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    STARTUPINFO sinfo = {0};
	PROCESS_INFORMATION pinfo= {0};
	std::queue<HANDLE> hp;
	int max;
	int l;
	String num1;
	String num2;
	LPTSTR cmdArgs;
	DWORD lpExitCode = 0;
	HANDLE hh;
	HANDLE hThread = INVALID_HANDLE_VALUE;
	String win;
	LPTSTR cmdArg;
	HWND hWnd;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef RecieverH
#define RecieverH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
private:
BEGIN_MESSAGE_MAP
VCL_MESSAGE_HANDLER(WM_USER+1, TMessage, WMUSER1)
END_MESSAGE_MAP(TForm)
void __fastcall WMUSER1(TMessage & msg);	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
int t=1;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif

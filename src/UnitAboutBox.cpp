//---------------------------------------------------------------------------

#pragma hdrstop

#include <vcl.h>
#include "UnitAboutBox.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAboutBox *FormAboutBox;
//---------------------------------------------------------------------------
__fastcall TFormAboutBox::TFormAboutBox(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormAboutBox::Button1Click(TObject *Sender)
{
Close();	
}
//---------------------------------------------------------------------------

void __fastcall TFormAboutBox::FormDeactivate(TObject *Sender)
{
if(FormAboutBox->Visible == true) {
	Button1->SetFocus();
}
}
//---------------------------------------------------------------------------





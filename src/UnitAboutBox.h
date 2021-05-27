//---------------------------------------------------------------------------

#ifndef UnitAboutBoxH
#define UnitAboutBoxH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Forms.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------

class TFormAboutBox : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TButton *Button1;
	TLabel *Label3;
	TLabel *Label4;
	TMemo *Memo1;
	TLabel *Label6;
	void __fastcall Button1Click(TObject *Sender);
    void __fastcall FormDeactivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormAboutBox(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAboutBox *FormAboutBox;
//---------------------------------------------------------------------------
#endif

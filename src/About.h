//----------------------------------------------------------------------------
#ifndef AboutH
#define AboutH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include <jpeg.hpp>
//----------------------------------------------------------------------------
class TFormAboutBox : public TForm
{
__published:
	TPanel *Panel1;
	TLabel *ProductName;
	TLabel *Version;
	TLabel *Copyright;
	TLabel *Comments;
	TButton *OKButton;
	TImage *Image1;
	void __fastcall OKButtonClick(TObject *Sender);
private:
public:
	virtual __fastcall TFormAboutBox(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TFormAboutBox *FormAboutBox;
//----------------------------------------------------------------------------
#endif    

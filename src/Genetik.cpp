//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------

USEFORM("UnitGenetik.cpp", FormMain);
USEFORM("UnitDialog.cpp", FormDialog);
USEFORM("UnitAboutBox.cpp", FormAboutBox);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
try {
	Application->Initialize();
	Application->Title = "Genetik";
	Application->CreateForm(
		__classid(TFormMain), &FormMain);
	Application->CreateForm(
		__classid(TFormAboutBox), &FormAboutBox);
	Application->CreateForm(
		__classid(TFormDialog), &FormDialog);
	Application->Run();
 }
 catch (Exception &exception) {
	Application->ShowException(&exception);
 }
 catch (...) {
	try {
		throw Exception("");
	}
	catch (Exception &exception) {
		Application->ShowException(&exception);
	}
 }
 return 0;
}
//---------------------------------------------------------------------------

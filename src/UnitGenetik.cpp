//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitGenetik.h"
#include "UnitDialog.h"
#include "UnitAboutBox.h"
#include <fstream.h>
#include <vcl/Clipbrd.hpp>
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"

TFormMain *FormMain;
//---------------------------------------------------------------------------

__fastcall TFormMain::TFormMain(TComponent* Owner):TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCreate(TObject *Sender)
{
VariabelMaksimum = 2;
DataBaru();
FormMain->PageControlGenetik->ActivePage = FormMain->TabSheetVariabel;
isModified = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::NewDataClick(TObject *Sender)
{
if (isModified) {
	int Answer = MessageDlg(
		"Do you want to save the changes you made?",
		mtConfirmation,
		TMsgDlgButtons() << mbYes << mbNo << mbCancel,
		0);
	if (Answer == mrYes) {
		if (SaveData->Enabled == true) {
			SaveDataClick(Sender);
		}
		else {
			SaveAsDataClick(Sender);
		}
		DataBaru();
	}
	else if (Answer == mrNo) {
		DataBaru();
	}
}
else {
	DataBaru();
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::DataBaru()
{
/* Inisialisasi variabel */
const int DefaultJumlahVariabel = 2;
const int JumlahKolomStringGridVariabel = 3;
const int DefaultJumlahData = 30;

/* Tulis judul default pada EditTitle */
EditTitle->Text = "Title";

/* Tulis caption pada form dengan nama databaru */
FormMain->Caption = "Genetik - DataBaru.agd";

/* Kosongkan nama file yang terbuka */
LabelFileTerbuka->Caption = "";

/* Matikan seluruh tombol save */
TombolSaveMati();

/* Kembalikan jumlah variabel ke nilai awal */
EditJumlahVariabel->Text = IntToStr(DefaultJumlahVariabel);

/* Kosongkan tabel variabel */
StringGridVariabel->RowCount = VariabelMaksimum+1;
for (int i = 0; i <= JumlahKolomStringGridVariabel; i++) {
	StringGridVariabel->Cols[i]->Clear();
}

/* Isi tabel variabel dengan format awal */
StringGridVariabel->RowCount = DefaultJumlahVariabel+1;
StringGridVariabel->Cells[0][0] = "No.";
StringGridVariabel->Cells[1][0] = "Name";
StringGridVariabel->Cells[2][0] = "Description";
for (int i = 1; i <= DefaultJumlahVariabel; i++) {
	StringGridVariabel->Cells[1][i] = "Var" + IntToStr(i);
	if (i == 1) {
		StringGridVariabel->Cells[2][i] =
			"Dependent Variable";
	}
	else {
		StringGridVariabel->Cells[2][2] =
			"Independent Variable";
	}
}
UpdateIndeks(StringGridVariabel);

/* Kosongkan tabel data */
for (int i = 0; i <= VariabelMaksimum; i++) {
	StringGridData->Cols[i]->Clear();
}

/* Kembalikan ukuran tabel data ke ukuran awal */
StringGridData->ColCount = DefaultJumlahVariabel+1;
StringGridData->RowCount = DefaultJumlahData+1;

/* Tulis header dan indeks pada tabel data */
UpdateHeaderData();
UpdateIndeks(StringGridData);

/* Update informasi dimensi */
UpdateDimensiData();
UpdateDimensiVariabel();

StringGridResidual->Cells[0][0] = "No.";
StringGridResidual->Cells[1][0] = "Actual";
StringGridResidual->Cells[2][0] = "Fitted";
StringGridResidual->Cells[3][0] = "Residual";
StringGridResidual->Cells[4][0] = "Squared Resuidual";
StringGridOptimasi->Cells[0][0] = "Generation";
StringGridOptimasi->Cells[1][0] = "Worst Fitness";
StringGridOptimasi->Cells[2][0] = "Average Fitness";
StringGridOptimasi->Cells[3][0] = "Best Fitness";
StringGridOptimasi->Cells[4][0] = "Convergence";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::OpenDataClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Membuka Lembar kerja
****************************************************************************/

if (OpenDialog1->Execute()) {
	/* Baca data dari file */
	BacaDariFile();

	/* Tampilkan tabel data */
	PageControlGenetik->ActivePage = TabSheetData;

	/* Hidupkan tombol save */
	TombolSaveHidup();

	/* Tandai bahwa lembar kerja belum dimodifikasi */
	isModified = false;
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::BacaDariFile()
{
/****************************************************************************
  Rutin Membaca Data dari File
****************************************************************************/

/* Inisialisasi variabel */
char   CharBaca[128];
String StringBaca;
String Separator = "========#=";
String StringHasilBaca;

/* Simpan informasi nama file */
LabelFileTerbuka->Caption = OpenDialog1->FileName.c_str();

/* Definisikan ifstream sebagai stream file yang akan dibaca */
ifstream baca(LabelFileTerbuka->Caption.c_str());

/* Baca baris pertama sebagai judul dan tampilkan hasilnya */
StringHasilBaca = "";
do {
	baca >> CharBaca;
	StringBaca = CharBaca;
	if (StringBaca != Separator) {
		StringHasilBaca = StringHasilBaca + StringBaca + " ";
	}
} while (StringBaca != Separator );
EditTitle->Text = StringHasilBaca;

/* Baca jumlah variabel dan tampilkan hasilnya */
baca >> CharBaca;
EditJumlahVariabel->Text = CharBaca;

/* Simpan informasi jumlah variabel maksimum bila jumlah variabel lebih
   besar dari jumlah variabel sebelumnya */
if (VariabelMaksimum < StrToInt(EditJumlahVariabel->Text)) {
	VariabelMaksimum = StrToInt(EditJumlahVariabel->Text);
}

/* Baca nama variabel, keterangan, dan data variabel dan tampilkan
   hasilnya */
int i = 0;
do {
	baca >> CharBaca;
	StringBaca = CharBaca;
	if (StringBaca == "VARIABEL") {
		/* ... Tambahkan jumlah baris untuk menampung data */
		if(StringGridVariabel->RowCount == (i+1)) {
			StringGridVariabel->RowCount ++;
		}
		/* ... Baca nama variabel dan tampilkan hasilnya */
		baca >> CharBaca;
		StringGridVariabel->Cells[1][i+1]= CharBaca;
		/* ... Baca keterangan variabel dan tampilkan hasilnya */
		StringHasilBaca = "";
		do {
			baca >> CharBaca;
			StringBaca = CharBaca;
			if (StringBaca != Separator) {
				StringHasilBaca = StringHasilBaca + StringBaca + " ";
			}
		} while (StringBaca != Separator );
		StringGridVariabel->Cells[2][i+1]= StringHasilBaca;
		i++;
	}
	else if (StringBaca == "DATA") {
		int j = 0;
		do {
			/* ... Tambahkan jumlah baris untuk menampung data */
			if(StringGridData->RowCount == (j+1)) {
				StringGridData->RowCount ++;
			}
			/* ... Baca data variabel dan tampilkan hasilnya */
			baca >> CharBaca;
			StringBaca = CharBaca;
			if (StringBaca != "ENDDATA") {
				StringGridData->Cells[i][j+1]= CharBaca;
			}
		j++;
		} while (StringBaca != "ENDDATA");
	}
}while (! baca.eof());

/* Tutup file */
baca.close();

/* Update tabel data dan variabel */
UpdateHeaderData();
UpdateDimensiData();
UpdateDimensiVariabel();
UpdateIndeks(StringGridData);

/* Tulis nama aplikasi dan nama file pada caption Form */
FormMain->Caption = "Genetik - " + ExtractFileName(OpenDialog1->FileName);

/* Hidupkan tombol Save */
TombolSaveHidup();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SaveDataClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Menyimpan Lembar Kerja
****************************************************************************/

/* Tentukan nama file */
SaveDialog1->FileName = LabelFileTerbuka->Caption;

/* Simpan data ke file */
SimpanKeFile();

/* Tandai bahwa lembar kerja sudah disimpan */
isModified = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SaveAsDataClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Menyimpan Lembar Kerja ke File Baru
****************************************************************************/

if (SaveDialog1->Execute()) {
	/* Simpan data ke file */
	SimpanKeFile();

	/* Tampilkan nama file */
	FormMain->Caption = "Genetik - " + ExtractFileName(SaveDialog1->FileName);

	/* Simpan nama file */
	LabelFileTerbuka->Caption = SaveDialog1->FileName.c_str();

	/* Hidupkan tombol save */
	TombolSaveHidup();
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SimpanKeFile()
{
/****************************************************************************
  Rutin untuk Menyimpan Lembar Kerja
****************************************************************************/

/* Inisialisasi variabel */
String Separator = "========#=";

/* Kosongkan MemoSave */
MemoSave->Clear();

/* Tulis judul pada MemoSave */
MemoSave->Lines->Add(EditTitle->Text);

/* Tulis Separator pada MemoSave */
MemoSave->Lines->Add(Separator);

/* Tulis jumlah variabel pada MemoSave */
MemoSave->Lines->Add(EditJumlahVariabel->Text);

/* Tulis data StringGridVariabel pada MemoSave */
for (int i = 0; i < StrToInt(EditJumlahVariabel->Text); i++) {
	/* ... Tulis VARIABEL pada MemoSave */
	MemoSave->Lines->Add("VARIABEL");
	/* ... Tulis nama variabel pada MemoSave */
	MemoSave->Lines->Add(StringGridVariabel->Cells[1][i+1]);
	/* ... Tulis keterangan variabel pada MemoSave */
	MemoSave->Lines->Add(StringGridVariabel->Cells[2][i+1]);
	/* ... Tulis Separator pada MemoSave */
	MemoSave->Lines->Add(Separator);
	/* ... Tulis DATA pada MemoSave */
	MemoSave->Lines->Add("DATA");
	/* ... Tulis data variabel pada MemoSave */
	int j = 0;
	while (j <= StringGridData->RowCount) {
		MemoSave->Lines->Add(StringGridData->Cells[i+1][j+1]);
		j++;
	};
	/* ... Tulis ENDDATA pada MemoSave */
	MemoSave->Lines->Add("ENDDATA");
}

/* Pindahkan data pada MemoSave ke File */
MemoSave->Lines->SaveToFile(SaveDialog1->FileName);

/* Kosongkan MemoSave */
MemoSave->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TombolSaveMati()
{
/****************************************************************************
  Rutin untuk Mematikan Tombol Save
****************************************************************************/

SaveData->Enabled = false;
SaveDataPopUpMenuVariabel->Enabled = false;
SaveDataPopUpMenuData->Enabled = false;
SpeedButtonSaveDataPanelData->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TombolSaveHidup()
{
/****************************************************************************
  Rutin untuk Menghidupkan Tombol Save
****************************************************************************/

SaveData->Enabled = true;
SaveDataPopUpMenuVariabel->Enabled = true;
SaveDataPopUpMenuData->Enabled = true;
SpeedButtonSaveDataPanelData->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PrintDataClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Mencetak Data
****************************************************************************/
int X1, X2, Y1, Y2;
TRect TR;

if (PrintDialog1->Execute()) {
	Printer()->Title = EditTitle->Text;
	Printer()->BeginDoc();
	Printer()->Canvas->TextOutA(0,100, Printer()->Title);
	for (int baris=1; baris < StringGridData->RowCount; baris=baris+40) {
		if (StringGridData->Cells[1][baris] != "") {
			for(int i = 0; i < StringGridData->ColCount; i++) {
				X1=150;
				for(int j = 0; j < i; j++) {
					X1 = X1 + 5 * StringGridData->ColWidths[j];
				}
				Y1=300;
				X2=150;
				for(int j = 0; j < i+1 ; j++) {
					X2 = X2 + 5 * StringGridData->ColWidths[j];
				}
				Y2 = 450;
				TR = Rect(X1, Y1, X2-30, Y2);
				Printer()->Canvas->Font->Style = TFontStyles() << fsBold;
				Printer()->Canvas->Font->Size = 7;
				Printer()->Canvas->TextRect(
					TR, X1+50, 350, StringGridData->Cells[i][0]);

				Printer()->Canvas->Font->Style = TFontStyles();
				for (int j = baris; j<baris+40; j++) {
					Y1 = 150*(j-baris+1)+300;
					Y2 = 150*(j-baris+2)+300;
					TR = Rect(X1, Y1, X2-30, Y2);
					Printer()->Canvas->TextRect(
						TR, X1+50, Y1+50, StringGridData->Cells[i][j]
					);
				}
			}
			Printer()->Canvas->TextOutA(
				2300,6500,"Page " + IntToStr(Printer()->PageNumber));
		}
		if (StringGridData->Cells[1][baris+40] != "") {
		Printer()->NewPage();
		}
	}
	Printer()->EndDoc();     
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::CloseDataClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Menutup Data
****************************************************************************/

/* Periksa apakah lembar kerja sebelumnya sudah dimodifikasi */
if (isModified) {
	int Jawaban = MessageDlg(
		"Do you want to save the changes?",
		mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
	if (Jawaban == mrYes) {
		if (SaveData->Enabled == true) {
			SaveDataClick(Sender);
	  	}
		else {
			SaveAsDataClick(Sender);
		}
		/* ... Matikan tombol save*/
		TombolSaveMati();
		/* ... Buat data baru */
		DataBaru();
		/* ... Kosongkan nama file */
		LabelFileTerbuka->Caption = "";
	}
	else if (Jawaban == mrNo) {
		/* ... Matikan tombol save */
		TombolSaveMati();
		/* ... Buat data baru */
		DataBaru();
		/* ... Kosongkan nama file */
		LabelFileTerbuka->Caption = "";
	}
}
else {
	/* ... Matikan tombol save */
	TombolSaveMati();
	/* ... Buat data baru */
	DataBaru();
	/* ... Kosongkan nama file */
	LabelFileTerbuka->Caption = "";
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SaveLaporanClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Menyimpan Report ke File
****************************************************************************/

RichEditHasil->Lines->SaveToFile(LabelRichEditTerbuka->Caption);
RichEditHasil->Modified = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SaveLaporanAsClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Menyimpan Report ke File Baru
****************************************************************************/

if(SaveDialogRichEditHasil->Execute()) {
	RichEditHasil->Lines->SaveToFile(SaveDialogRichEditHasil->FileName);
	LabelRichEditTerbuka->Caption = SaveDialogRichEditHasil->FileName.c_str();
	SaveLaporan->Enabled = true;
	SavePopUpMenuReport->Enabled = true;
	SavePopUpMenuReport->Enabled = true;
	RichEditHasil->Modified = false;
	String NamaFile = SaveDialogRichEditHasil->FileName;
	String Dummy = "";
	int Panjang = NamaFile.Length();
	for (int i = 0; i < Panjang-4; i++) {
		Dummy = Dummy+NamaFile.c_str()[i] ;
    }
	NamaFile = Dummy;
	String ChartOptimasiName = NamaFile + ".opt.emf";
	ChartOptimasi->SaveToMetafileEnh(ChartOptimasiName);
	String ChartResiduName = NamaFile + ".res.emf";
	ChartResidu->SaveToMetafileEnh(ChartResiduName);
	String ChartHistogramName = NamaFile + ".his.emf";
	ChartHistogram->SaveToMetafileEnh(ChartHistogramName);

	String VariabelCSVName = NamaFile + ".var.csv";
	MemoClipBoard->Clear();
	for (int i = 0; i <= StringGridVariabel->RowCount; i++) {
		String Tulisan;
		for (int j = 0; j <= StringGridVariabel->ColCount; j++) {
			if (j != StringGridVariabel->ColCount) {
				Tulisan = Tulisan + StringGridVariabel->Cells[j][i] + ",";
			}
			else {
				Tulisan = Tulisan + StringGridVariabel->Cells[j][i];
			}
		}
		MemoClipBoard->Lines->Add(Tulisan);
	}
	MemoClipBoard->SelectAll();
	MemoClipBoard->Lines->SaveToFile(VariabelCSVName);
	MemoClipBoard->Clear();

	String DataCSVName = NamaFile + ".dat.csv";
	MemoClipBoard->Clear();
	for (int i = 0; i <= StringGridData->RowCount; i++) {
		String Tulisan;
		for (int j = 0; j <= StringGridData->ColCount; j++) {
			if (j != StringGridData->ColCount) {
				Tulisan = Tulisan + StringGridData->Cells[j][i] + ",";
			}
			else {
				Tulisan = Tulisan + StringGridData->Cells[j][i];
			}
		}
		MemoClipBoard->Lines->Add(Tulisan);
	}
	MemoClipBoard->SelectAll();
	MemoClipBoard->Lines->SaveToFile(DataCSVName);
	MemoClipBoard->Clear();

	String ResidualCSVName = NamaFile + ".res.csv";
	MemoClipBoard->Clear();
	for (int i = 0; i <= StringGridResidual->RowCount; i++) {
		String Tulisan;
		for (int j = 0; j <= StringGridResidual->ColCount; j++) {
			if (j != StringGridResidual->ColCount) {
				Tulisan = Tulisan + StringGridResidual->Cells[j][i] + ",";
			}
			else {
				Tulisan = Tulisan + StringGridResidual->Cells[j][i];
			}
		}
		MemoClipBoard->Lines->Add(Tulisan);
	}
	MemoClipBoard->SelectAll();
	MemoClipBoard->Lines->SaveToFile(ResidualCSVName);
	MemoClipBoard->Clear();

	String OptimasiCSVName = NamaFile + ".opt.csv";
	MemoClipBoard->Clear();
	for (int i = 0; i <= StringGridOptimasi->RowCount; i++) {
		String Tulisan;
		for (int j = 0; j <= StringGridOptimasi->ColCount; j++) {
			if (j != StringGridOptimasi->ColCount) {
				Tulisan = Tulisan + StringGridOptimasi->Cells[j][i] + ",";
			}
			else {
				Tulisan = Tulisan + StringGridOptimasi->Cells[j][i];
			}
		}
		MemoClipBoard->Lines->Add(Tulisan);
	}
	MemoClipBoard->SelectAll();
	MemoClipBoard->Lines->SaveToFile(OptimasiCSVName);
	MemoClipBoard->Clear();

	String TitleName = NamaFile + ".txt";
	MemoClipBoard->Clear();

	MemoClipBoard->Lines->Add("GENETIK");
	MemoClipBoard->Lines->Add("PARAMETER ESTIMATION WITH GENETIC ALGORITHM METHOD IN NON LINEAR EQUATION");
	MemoClipBoard->Lines->Add("CREATED BY YOHAN NAFTALI 2007-2009");
	MemoClipBoard->Lines->Add(" ");
	MemoClipBoard->Lines->Add("OUTPUT FILES");
	MemoClipBoard->Lines->Add("Title                : "+EditTitle->Text);
	MemoClipBoard->Lines->Add("Variable List        : "+VariabelCSVName);
	MemoClipBoard->Lines->Add("Data Table           : "+DataCSVName);
	MemoClipBoard->Lines->Add("Report               : "+NamaFile+".rtf");
	MemoClipBoard->Lines->Add("Residual Plot vs Obs : "+ChartResiduName);
	MemoClipBoard->Lines->Add("Histogram Residual   : "+ChartHistogramName);
	MemoClipBoard->Lines->Add("Residual Table       : "+ResidualCSVName);
	MemoClipBoard->Lines->Add("Optimization Chart   : "+ChartOptimasiName);
	MemoClipBoard->Lines->Add("Optimization History : "+OptimasiCSVName);

	MemoClipBoard->SelectAll();
	MemoClipBoard->Lines->SaveToFile(TitleName);
	MemoClipBoard->Clear();
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PrintLaporanClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Mencetak Report
****************************************************************************/

if (PrintDialog1->Execute()) {
	TPrinter *Prntr = Printer();
	Prntr->Canvas->Font->Name = "Courier New";
	Prntr->Canvas->Font->Size = 8;
	Prntr->BeginDoc();
	int j = 0;
	for( int i = 0; i < RichEditHasil->Lines->Count; i++) {
	if(j * Prntr->Canvas->TextHeight(RichEditHasil->Lines->Strings[i]) >=
		Prntr->PageHeight-800) {
		j = 0;
		Prntr->NewPage();
	}
	Prntr->Canvas->TextOut(
	  500,
	  400+(j*Prntr->Canvas->TextHeight(RichEditHasil->Lines->Strings[i])),
	  RichEditHasil->Lines->Strings[i]);
	j++;
	}
	Prntr->EndDoc();
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PrintHistorisClick(TObject *Sender)
{
if (PrintDialog1->Execute()) {
	ChartOptimasi->Print();
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PrintResidualClick(TObject *Sender)
{
if (PrintDialog1->Execute()) {
	ChartResidu->Print();
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PrintHistogramClick(TObject *Sender)
{
if (PrintDialog1->Execute()) {
	ChartHistogram->Print();
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::EditTitleChange(TObject *Sender)
{
/****************************************************************************
  Rutin yang dijalankan setelah Judul diganti
****************************************************************************/

/* Tandai bahwa lembar kerja sudah dimodifikasi */
isModified = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::EditJumlahVariabelChange(TObject *Sender)
{
/****************************************************************************
  Rutin yang dijalankan setelah Jumlah Variabel diganti
****************************************************************************/

/* Tandai bahwa lembar kerja sudah dimodifikasi */
isModified = true;

/* Sesuaikan jumlah baris tabel variabel setelah jumlah variabel diganti */
StringGridVariabel->RowCount = StrToInt(EditJumlahVariabel->Text) + 1;

/* Tulis indeks baris pada tabel variabel */
UpdateIndeks(StringGridVariabel);

/* Tulis nama variabel dan keterangannya */
for(int i = 1; i <= StringGridVariabel->RowCount-1 ; i++) {
	if (StringGridVariabel->Cells[1][i] == "" ) {
		StringGridVariabel->Cells [1][i] = "Var" + IntToStr(i);
	}
	if (StringGridVariabel->Cells[2][i] == "" ) {
		StringGridVariabel->Cells [2][i] = "Independent Variable";
	}
}

/* Sesuaikan jumlah kolom tabel data dengan jumlah variabel */
StringGridData->ColCount = StrToInt(EditJumlahVariabel->Text)+1;

/* Tulis header pada tabel data */
UpdateHeaderData();

/* Tulis informasi dimensi StringGridVariabel */
UpdateDimensiVariabel();

/* Catat jumlah variabel maksimum bila jumlah variabel lebih besar dari
   pada jumlah variabel maksimum sebelumnya */
if (VariabelMaksimum < StrToInt(EditJumlahVariabel->Text)) {
	VariabelMaksimum = StrToInt(EditJumlahVariabel->Text);
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridVariabelMouseDown(TObject *Sender,
	  TMouseButton Button, TShiftState Shift, int X, int Y)
{
/****************************************************************************
  Rutin untuk Menulis Informasi Posisi Cell pada Tabel Variabel
****************************************************************************/

TGridCoord GC=StringGridVariabel->MouseCoord(X,Y);
StatusBarVariabel->Panels->operator [](2)->Text = AnsiString(GC.X);
StatusBarVariabel->Panels->operator [](4)->Text = AnsiString(GC.Y);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridVariabelSetEditText(TObject *Sender,
      int ACol, int ARow, const AnsiString Value)
{
/****************************************************************************
  Rutin yang Menulis Informasi Posisi Cell pada Tabel Variabel
****************************************************************************/

/* Update no data sesuai dengan no baris */
StringGridVariabel->Cells[0]
	[StrToInt(StatusBarVariabel->Panels->operator [](4)->Text)]
	= StrToInt(StatusBarVariabel->Panels->operator [](4)->Text);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridVariabelMouseWheelDown(TObject *Sender,
	  TShiftState Shift, TPoint &MousePos, bool &Handled)
{
/****************************************************************************
  Rutin yang Mengatur Status Tabel Variabel ketika Mouse Wheel ke Bawah
****************************************************************************/

/* Bila Mouse Wheel digeser ke bawah, maka posisi kursor akan turun ke baris
   berikutnya, kecuali bila pada pada posisi baris terbawah maka kursor tidak
   akan bergerak lagi */
if (StrToInt(StatusBarVariabel->Panels->operator [](4)->Text) !=
	(StringGridVariabel->RowCount - 1)) {
	StatusBarVariabel->Panels->operator [](4)->Text = IntToStr(StrToInt(
		StatusBarVariabel->Panels->operator [](4)->Text)+1);
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridVariabelMouseWheelUp(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
/****************************************************************************
  Rutin yang Mengatur Status Tabel Variabel ketika Mouse Wheel ke Atas
****************************************************************************/

/* Bila Mouse Wheel digeser ke atas, maka posisi kursor akan naik ke baris
   sebelumnya, kecuali bila pada pada posisi baris teratas maka kursor
   tidak akan bergerak lagi */
if (StatusBarVariabel->Panels->operator [](4)->Text != "1") {
	StatusBarVariabel->Panels->operator [](4)->Text = IntToStr(StrToInt(
		StatusBarVariabel->Panels->operator [](4)->Text)-1);
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridVariabelKeyDown(TObject *Sender,
  WORD &Key,TShiftState Shift)
{
/****************************************************************************
  Rutin yang Mengatur Status Tabel Variabel ketika Sebuah Tombol Ditekan
****************************************************************************/

/* Tombol Shift ditekan, pananda shift menjadi 1 */
if (Key == 16) {
	LabelShift->Caption = 1;
}

/* Bila tombol panah ke atas ditekan, maka posisi kursor akan naik ke baris
  sebelumnya, kecuali bila pada pada posisi baris teratas maka kursor tidak
  akan bergerak lagi */
if (Key == 38) {
	if (StatusBarVariabel->Panels->operator [](4)->Text != "1") {
		StatusBarVariabel->Panels->operator [](4)->Text = IntToStr(StrToInt(
		StatusBarVariabel->Panels->operator [](4)->Text)-1);
	}
}

/* Bila tombol panah ke bawah ditekan, maka posisi kursor akan turun ke
   baris selanjutnya, bila kursor berada pada posisi baris terbawah maka
   jumlah baris akan ditambah */
if (Key == 40) {
	if (StrToInt(StatusBarVariabel->Panels->operator [](4)->Text) !=
		(StringGridVariabel->RowCount - 1)) {
		StatusBarVariabel->Panels->operator [](4)->Text = IntToStr(
			StrToInt(StatusBarVariabel->Panels->operator [](4)->Text)+1);
	}
	else {
		StringGridVariabel->RowCount++;
		UpdateIndeks(StringGridVariabel);
		UpdateDimensiVariabel();
		StatusBarVariabel->Panels->operator [](4)->Text =
		IntToStr(StrToInt(StatusBarVariabel->Panels->operator [](4)->Text)+1);
	}
}

/* Bila tombol panah ke kiri ditekan, maka posisi kursor akan bergeser ke
   kiri, kecuali bila pada pada posisi kolom pertama maka kursor tidak akan
   bergerak lagi */
if (Key == 37) {
	if (StatusBarVariabel->Panels->operator [](2)->Text != "1") {
		StatusBarVariabel->Panels->operator [](2)->Text = IntToStr(
			StrToInt(StatusBarVariabel->Panels->operator [](2)->Text)-1);
	}
}

/* Bila tombol panah ke kanan ditekan, maka posisi kursor akan bergeser ke
   kanan, kecuali bila pada pada posisi kolom pertama maka kursor tidak akan
   bergerak lagi */
if (Key == 39) {
	if (StrToInt(StatusBarVariabel->Panels->operator [](2)->Text) !=
		(StringGridVariabel->ColCount - 1)) {
		StatusBarVariabel->Panels->operator [](2)->Text = IntToStr(
			StrToInt(StatusBarVariabel->Panels->operator [](2)->Text)+1);
	}
}

/* Bila tombol Tab ditekan */
if (Key == 9) {
	/* ... Bila bukan Shift Tab yang ditekan (artinya hanya tombol tab saja
		 yang ditekan, apabila hanya tombol tab yang ditekan maka kursor
		 akan bergerak ke kanan dan pada ujung kolom kursor akan bergerak ke
		 baris berikutnya */
	if (LabelShift->Caption !=1) {
		/* ... Update status posisi baris sekaligus kolom bila posisi kursor
		   bukan pada kolom terakhir maka posisi kolom ditambah dengan 1 */
		if (StrToInt(StatusBarVariabel->Panels->operator [](2)->Text)
			!= (StringGridVariabel->ColCount - 1)) {
			StatusBarVariabel->Panels->operator [](2)->Text = IntToStr(
			StrToInt(StatusBarVariabel->Panels->operator [](2)->Text)+1);
		}
		/* ... Bila posisi kursor pada kolom terakhir tetapi bukan pada baris
		   terakhir maka posisi baris ditambah dengan 1, dan posisi kolom
		   menjadi kolom 1 */
		else if (StrToInt(StatusBarVariabel->Panels->operator [](4)->Text)
			!= (StringGridVariabel->RowCount-1)) {
			StatusBarVariabel->Panels->operator [](2)->Text = IntToStr(1);
			StatusBarVariabel->Panels->operator [](4)->Text = IntToStr(
				StrToInt(StatusBarVariabel->Panels->operator [](4)->Text)+1);
		}
		/* ... Bila posisi kursor pada kolom terakhir dan baris terakhir maka
		   setelah tombol tab ditekan maka posisi baris menjadi baris 1 dan
		   posisi kolom menjadi kolom 1 */
		else {
			StatusBarVariabel->Panels->operator [](2)->Text = IntToStr(1);
			StatusBarVariabel->Panels->operator [](4)->Text = IntToStr(1);
		}
	}
	/* ... Bila Shift Tab yang ditekan, maka kursor akan bergerak ke kiri, bila
		 pada awal kolom maka kolom akan berpindah ke baris sebelumnya */
	else {
		/* ... Update status posisi baris sekaligus kolom bila posisi kursor
		   bukan pada kolom 1, karena tombol shift tab ditekan, posisi kolom
		   dikurangi 1 */
		if (StatusBarVariabel->Panels->operator [](2)->Text != "1") {
			StatusBarVariabel->Panels->operator [](2)->Text = IntToStr(
				StrToInt(StatusBarVariabel->Panels->operator [](2)->Text)-1);
		}
		/* ... Bila posisi kursor pada kolom 1, dan posisi kursor bukan pada
			baris 1, karena tombol shift tab ditekan, posisi kursor berpindah
			ke baris sebelumnya, dan posisi kursor berpindah pada kolom
			terakhir */
		else if (StatusBarVariabel->Panels->operator [](4)->Text != "1") {
			StatusBarVariabel->Panels->operator [](2)->Text =
				StringGridVariabel->ColCount - 1;
			StatusBarVariabel->Panels->operator [](4)->Text = IntToStr(
				StrToInt(StatusBarVariabel->Panels->operator [](4)->Text) - 1);
		}
		/* ... Bila posisi kursor pada kolom pertama baris pertama, karena
			tombol shift tab ditekan maka posisi kursor akan berpindah ke
			kolom terakhir baris terakhir */
		else {
			StatusBarVariabel->Panels->operator [](2)->Text =
				StringGridVariabel->ColCount - 1;
			StatusBarVariabel->Panels->operator [](4)->Text =
				StringGridVariabel->RowCount - 1;
		}
	}
}

/* Bila tombol enter ditekan, posisi kursor pindah ke baris berikutnya */
if (Key == 13) {
	StatusBarVariabel->Panels->operator [](10)->Text = "";
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridVariabelKeyUp(TObject *Sender, WORD &Key,
	  TShiftState Shift)
{
/****************************************************************************
  Rutin yang dijalankan setelah Sebuah Tombol dilepas
****************************************************************************/

/* Bila tombol Shift yang dilepas, berikan statusnya */
if (Key == 16) {
	LabelShift->Caption = 0;
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridVariabelGetEditText(TObject *Sender,
	  int ACol, int ARow, AnsiString &Value)
{
/****************************************************************************
  Rutin yang dijalankan ketika Edit Text Aktif pada Tabel Variabel
****************************************************************************/

/* Tandai bahwa lembar kerja sudah dimodifikasi */
isModified = true;

/* Beri status editing variabel saat melakukan edit */
StatusBarVariabel->Panels->operator [](10)->Text = "Editing Variabel...";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridVariabelSelectCell(TObject *Sender,
	  int ACol, int ARow, bool &CanSelect)
{
/****************************************************************************
  Rutin yang dijalankan ketika Memilih Cell pada Tabel Variabel
****************************************************************************/

/* Status Editing dimatikan */
StatusBarVariabel->Panels->operator [](10)->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::UpdateDimensiVariabel()
{
/****************************************************************************
  Rutin untuk Memperbaharui Informasi Dimensi pada Tabel Variabel
****************************************************************************/

StatusBarVariabel->Panels->operator [](7)->Text = IntToStr(
	StringGridVariabel->ColCount - 1);
StatusBarVariabel->Panels->operator [](9)->Text = IntToStr(
	StringGridVariabel->RowCount - 1);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::CopyVariabelClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Menyalin Text pada Tabel Variabel
****************************************************************************/
int atas = StringGridVariabel->Selection.Top;
int bawah = StringGridVariabel->Selection.Bottom;
int kiri = StringGridVariabel->Selection.Left;
int kanan = StringGridVariabel->Selection.Right;

MemoClipBoard->Clear();
for (int i = atas; i <= bawah; i++) {
	String Tulisan;
	for (int j = kiri; j <= kanan; j++) {
		if (j != kanan) {
			Tulisan = Tulisan + StringGridVariabel->Cells[j][i] + '\t';
		}
		else {
			Tulisan = Tulisan + StringGridVariabel->Cells[j][i];
		}
	}
	MemoClipBoard->Lines->Add(Tulisan);
}
MemoClipBoard->SelectAll();
MemoClipBoard->CopyToClipboard();
MemoClipBoard->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PasteVariabelClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Paste Text dari Tabel Variabel
****************************************************************************/

MemoClipBoard->Clear();
MemoClipBoard->PasteFromClipboard();

int PosisiBaris = StrToInt(StatusBarVariabel->Panels->operator [](4)->Text);
int JumlahBaris = MemoClipBoard->Lines->Count;
for (int i = 0; i < JumlahBaris; i++) {
	int PosisiKolom = StrToInt(
		StatusBarVariabel->Panels->operator [](2)->Text);
	String Tulisan = MemoClipBoard->Lines->operator [](i);
	int j = 0;
	while (j < Tulisan.Length()) {
		String Dummy = "";
		while (Tulisan.c_str()[j] != '\t' &&
			Tulisan.c_str()[j] != '\n' &&
			j < Tulisan.Length()) {
			Dummy = Dummy+Tulisan.c_str()[j] ;
			j++;
		}
		j++;
		StringGridVariabel->Cells[PosisiKolom][PosisiBaris] = Dummy;
		PosisiKolom++;
	}

	PosisiBaris++;
}
MemoClipBoard->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridDataMouseDown(TObject *Sender,
	  TMouseButton Button, TShiftState Shift, int X, int Y)
{
/****************************************************************************
  Rutin untuk Menulis Informasi Posisi Cell pada Tabel Data
****************************************************************************/

TGridCoord GC=StringGridData->MouseCoord(X,Y);
StatusBarData->Panels->operator [](2)->Text = AnsiString(GC.X);
StatusBarData->Panels->operator [](4)->Text = AnsiString(GC.Y);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridDataSetEditText(TObject *Sender,
  int ACol, int ARow, const AnsiString Value)
{
/****************************************************************************
  Rutin untuk Menulis Informasi Posisi Cell pada Tabel Data
****************************************************************************/

/* Update no data sesuai dengan no baris */
StringGridData->Cells[0][StrToInt(StatusBarData->Panels->operator [](4)->
	Text)] = StrToInt(StatusBarData->Panels->operator [](4)->Text);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridDataMouseWheelDown(TObject *Sender,
	  TShiftState Shift, TPoint &MousePos, bool &Handled)
{
/****************************************************************************
  Rutin yang Mengatur Status Tabel Data ketika Mouse Wheel ke Bawah
****************************************************************************/

/* Bila Mouse Wheel digeser ke bawah, maka posisi kursor akan turun ke baris
   berikutnya, kecuali bila pada pada posisi baris terbawah maka kursor tidak
   akan bergerak lagi */
if (StrToInt(StatusBarData->Panels->operator [](4)->Text) !=
	(StringGridData->RowCount - 1)) {
	StatusBarData->Panels->operator [](4)->Text = (
	IntToStr (
		StrToInt(StatusBarData->Panels->operator [](4)->Text)+1));
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridDataMouseWheelUp(TObject *Sender,
	  TShiftState Shift, TPoint &MousePos, bool &Handled)
{
/****************************************************************************
  Rutin yang Mengatur Status Tabel Data ketika Mouse Wheel ke Atas
****************************************************************************/

/* Bila Mouse Wheel digeser ke atas, maka posisi kursor akan naik ke baris
   sebelumnya, kecuali bila pada pada posisi baris teratas maka kursor
   tidak akan bergerak lagi */
if (StatusBarData->Panels->operator [](4)->Text != "1") {
	StatusBarData->Panels->operator [](4)->Text = (IntToStr(StrToInt(
		StatusBarData->Panels->operator [](4)->Text)-1));
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridDataKeyDown(TObject *Sender, WORD &Key,
	  TShiftState Shift)
{
/****************************************************************************
  Rutin yang Mengatur Status Tabel Data ketika Sebuah Tombol Ditekan
****************************************************************************/

/* Tombol Shift ditekan, pananda shift menjadi 1 */
if (Key == 16) {
	LabelShift->Caption = 1;
}

/* Bila tombol panah ke atas ditekan, maka posisi kursor akan naik ke baris
   sebelumnya, kecuali bila pada pada posisi baris teratas maka kursor tidak
   akan bergerak lagi */
if (Key == 38) {
	if (StatusBarData->Panels->operator [](4)->Text != "1") {
		StatusBarData->Panels->operator [](4)->Text = (IntToStr(StrToInt(
			StatusBarData->Panels->operator [](4)->Text)-1));
	}
}

/* Bila tombol panah ke bawah ditekan, maka posisi kursor akan turun ke baris
   selanjutnya, bila kursor berada pada posisi baris terbawah maka jumlah
   baris akan ditambah */
if (Key == 40) {
	if (StrToInt(StatusBarData->Panels->operator [](4)->Text) !=
		(StringGridData->RowCount-1)) {
		StatusBarData->Panels->operator [](4)->Text = (IntToStr(StrToInt(
			StatusBarData->Panels->operator [](4)->Text)+1));
	}
	else {
		StringGridData->RowCount++;
		UpdateIndeks(StringGridData);
		UpdateDimensiData();
		StatusBarData->Panels->operator [](4)->Text = (IntToStr(StrToInt(
			StatusBarData->Panels->operator [](4)->Text)+1));
	}
}

/* Bila tombol panah ke kiri ditekan, maka posisi kursor akan bergeser ke
   kiri, kecuali bila pada pada posisi kolom pertama maka kursor tidak
   akan bergerak lagi */
if (Key == 37) {
	if (StatusBarData->Panels->operator [](2)->Text != "1") {
		StatusBarData->Panels->operator [](2)->Text = (IntToStr(StrToInt(
			StatusBarData->Panels->operator [](2)->Text)-1));
	}
}

/* Bila tombol panah ke kanan ditekan, maka posisi kursor akan bergeser ke
   kanan, kecuali bila pada pada posisi kolom pertama maka kursor tidak
   akan bergerak lagi */
if (Key == 39) {
	if (StrToInt(StatusBarData->Panels->operator [](2)->Text) !=
		(StringGridData->ColCount - 1)) {
		StatusBarData->Panels->operator [](2)->Text = (IntToStr(StrToInt(
			StatusBarData->Panels->operator [](2)->Text)+1));
	}
}

/* Bila tombol Tab ditekan */
if (Key == 9) {
	/* ... Bila bukan Shift Tab yang ditekan (artinya hanya tombol tab saja
		   yang ditekan, apabila hanya tombol tab yang ditekan maka kursor
		   akan bergerak ke kanan dan pada ujung kolom kursor akan bergerak
		   ke baris berikutnya */
	if (LabelShift->Caption !=1) {
	/* ... Update status posisi baris sekaligus kolom bila posisi kursor
		   bukan pada kolom terakhir maka posisi kolom ditambah dengan 1 */
		if (StrToInt(StatusBarData->Panels->operator [](2)->Text)!=
			(StringGridData->ColCount - 1)) {
			StatusBarData->Panels->operator [](2)->Text = (IntToStr(StrToInt
				(StatusBarData->Panels->operator [](2)->Text)+1));
		}
		/* ... Bila posisi kursor pada kolom terakhir tetapi bukan pada
			   baris terakhir maka posisi baris ditambah dengan 1, dan
			   posisi kolom menjadi kolom 1 */
		else if (StrToInt(StatusBarData->Panels->operator [](4)->Text)
			!= (StringGridData->RowCount - 1)) {
			StatusBarData->Panels->operator [](2)->Text = IntToStr(1);
			StatusBarData->Panels->operator [](4)->Text = (IntToStr(StrToInt
				(StatusBarData->Panels->operator [](4)->Text)+1));
		}
		/* ... Bila posisi kursor pada kolom terakhir dan baris terakhir
			   maka setelah tombol tab ditekan maka posisi baris menjadi
			   baris 1 dan posisi kolom menjadi kolom 1 */
		else {
			StatusBarData->Panels->operator [](2)->Text = IntToStr(1);
			StatusBarData->Panels->operator [](4)->Text = IntToStr(1);
		}
	}
	/* ... Bila Shift Tab yang ditekan, maka kursor akan bergerak ke kiri,
		   bila pada awal kolom maka kolom akan berpindah ke baris
		   sebelumnya */
	else {
		/* ... Update status posisi baris sekaligus kolom bila posisi kursor
			   bukan pada kolom 1, karena tombol shift tab ditekan, posisi
			   kolom dikurangi 1 */
		if (StatusBarData->Panels->operator [](2)->Text != "1") {
			StatusBarData->Panels->operator [](2)->Text = (IntToStr(StrToInt
				(StatusBarData->Panels->operator [](2)->Text)-1));
		}
		/* ... Bila posisi kursor pada kolom 1, dan posisi kursor bukan pada
			   baris 1, karena tombol shift tab ditekan, posisi kursor
			   berpindah ke baris sebelumnya, dan posisi kursor berpindah
			   pada kolom terakhir */
		else if (StatusBarData->Panels->operator [](4)->Text != "1") {
			StatusBarData->Panels->operator [](2)->Text
				= StringGridData->ColCount - 1;
			StatusBarData->Panels->operator [](4)->Text = IntToStr(StrToInt(
				StatusBarData->Panels->operator [](4)->Text)-1);
		}
		/* ... Bila posisi kursor pada kolom pertama baris pertama, karena
			   tombol shift tab ditekan maka posisi kursor akan berpindah ke
			   kolom terakhir baris terakhir */
		else {
			StatusBarData->Panels->operator [](2)->Text
				= StringGridData->ColCount-1;
			StatusBarData->Panels->operator [](4)->Text
				= StringGridData->RowCount-1;
		}
	}
}

/* Bila tombol enter ditekan, posisi kursor pindah ke baris berikutnya */
if (Key == 13) {
	StatusBarData->Panels->operator [](10)->Text = "";
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridDataKeyUp(TObject *Sender, WORD &Key,
	  TShiftState Shift)
{
/****************************************************************************
  Rutin yang dijalankan setelah Sebuah Tombol Dilepas
****************************************************************************/

/* Bila tombol Shift yang dilepas, berikan statusnya */
if (Key == 16) {
	LabelShift->Caption = 0;
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridDataGetEditText(TObject *Sender,
  int ACol, int ARow, AnsiString &Value)
{
/****************************************************************************
  Rutin yang dijalankan ketika Edit Text Aktif pada Tabel Data
****************************************************************************/

/* Tandai bahwa lembar kerja sudah dimodifikasi */
isModified = true;

/* Beri status editing data saat melakukan edit */
StatusBarData->Panels->operator [](10)->Text = "Editing Data...";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridDataSelectCell(TObject *Sender,
  int ACol, int ARow, bool &CanSelect)
{
/****************************************************************************
  Rutin yang dijalankan ketika Memilih Cell pada Tabel Data
****************************************************************************/

/* Status Editing dimatikan */
StatusBarData->Panels->operator [](10)->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::CopyDataClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Menyalin Text pada Tabel Data
****************************************************************************/

int atas  = StringGridData->Selection.Top;
int bawah = StringGridData->Selection.Bottom;
int kiri  = StringGridData->Selection.Left;
int kanan = StringGridData->Selection.Right;

MemoClipBoard->Clear();
for (int i = atas; i <= bawah; i++) {
	String Tulisan;
	for (int j = kiri; j <= kanan; j++) {
		if (j != kanan) {
			Tulisan = Tulisan + StringGridData->Cells[j][i] + '\t';
		}
		else {
			Tulisan = Tulisan + StringGridData->Cells[j][i];
		}
	}
	MemoClipBoard->Lines->Add(Tulisan);
}
MemoClipBoard->SelectAll();
MemoClipBoard->CopyToClipboard();
MemoClipBoard->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PasteDataClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Paste Text dari Tabel Variabel
****************************************************************************/

MemoClipBoard->Clear();
MemoClipBoard->PasteFromClipboard();

int PosisiBaris = StrToInt(StatusBarData->Panels->operator [](4)->Text);
int JumlahBaris = MemoClipBoard->Lines->Count;
for (int i = 0; i < JumlahBaris; i++) {
	int PosisiKolom = StrToInt(StatusBarData->Panels->operator [](2)->Text);
	String Tulisan = MemoClipBoard->Lines->operator [](i);
	int j = 0;
	while (j < Tulisan.Length()) {
		String Dummy = "";
		while (Tulisan.c_str()[j] != '\t' &&
			Tulisan.c_str()[j] != '\n' &&
			j < Tulisan.Length()) {
			Dummy = Dummy+Tulisan.c_str()[j] ;
			j++;
		}
		j++;
		StringGridData->Cells[PosisiKolom][PosisiBaris] = Dummy;
		PosisiKolom++;
	}
	PosisiBaris++;
}
MemoClipBoard->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AddRowClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Menambah Baris Baru pada Tabel Data
****************************************************************************/

StringGridData->RowCount ++;
UpdateDimensiData();
UpdateIndeks(StringGridData);

/* Tandai bahwa lembar kerja sudah dimodifikasi */
isModified = true;

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::InsertRowClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Menyisipkan Baris Baru pada Tabel Data
****************************************************************************/

StringGridData->RowCount ++;

for(int i = StringGridData->RowCount - 1;
	i >= StrToInt(StatusBarData->Panels->operator [](4)->Text) ; i--) {
	for (int j = 1; j <= StringGridData->ColCount - 1; j++) {
		if(i == StrToInt(StatusBarData->Panels->operator [](4)->Text)) {
			StringGridData->Cells[j][i] = "";
		}
		else {
			StringGridData->Cells[j][i] = StringGridData->Cells[j][i-1];
		}
	}
}
UpdateDimensiData();
UpdateIndeks(StringGridData);

/* Tandai bahwa lembar kerja sudah dimodifikasi */
isModified = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::DeleteEndRowClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Menghapus Baris Terakhir pada Tabel Data
****************************************************************************/

StringGridData->RowCount --;
UpdateDimensiData();
if(StrToInt(StatusBarData->Panels->operator [](4)->Text)
	> StrToInt(StatusBarData->Panels->operator [](9)->Text)) {
	StatusBarData->Panels->operator [](4)->Text
		= StatusBarData->Panels->operator [](9)->Text;
}

/* Tandai bahwa lembar kerja sudah dimodifikasi */
isModified = true;
}
//---------------------------------------------------------------------------
   
void __fastcall TFormMain::DeleteRowClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Menghapus Baris pada Tabel Data
****************************************************************************/

for(int i = StrToInt(StatusBarData->Panels->operator [](4)->Text);
	i <= StringGridData->RowCount - 1; i++) {
	for (int j = 1; j <= StringGridData->ColCount - 1; j++) {
		StringGridData->Cells[j][i] = StringGridData->Cells[j][i+1];
	}
}
StringGridData->RowCount --;
UpdateDimensiData();
UpdateIndeks(StringGridData);

/* Tandai bahwa lembar kerja sudah dimodifikasi */
isModified = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::UpdateDimensiData()
{
/****************************************************************************
  Rutin untuk Memperbaharui Informasi Dimensi pada Tabel Data
****************************************************************************/

StatusBarData->Panels->operator [](7)->Text
	= IntToStr(StringGridData->ColCount - 1);
StatusBarData->Panels->operator [](9)->Text
	= IntToStr(StringGridData->RowCount - 1);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::UpdateHeaderData()
{
/****************************************************************************
  Rutin untuk Menulis Header pada Tabel Data
****************************************************************************/

StringGridData->Cells[0][0] = "Obs.";
for (int i = 1; i <= StringGridData->ColCount; i++) {
	StringGridData->Cells[i][0] = StringGridVariabel->Cells[1][i];
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PageControlGenetikChange(TObject *Sender)
{
/****************************************************************************
  Rutin yang Dipanggil saat Berpindah Halaman
****************************************************************************/

StringGridData->ColCount = StrToInt(EditJumlahVariabel->Text) + 1;
UpdateHeaderData();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::UpdateIndeks(TStringGrid *SG)
{
/****************************************************************************
  Rutin untuk Memperbaharui Indeks Baris pada Tabel
****************************************************************************/

for(int i = 1; i <= SG->RowCount - 1 ; i++) {
	SG->Cells [0][i] = i;
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::KosongSG(TStringGrid *SG)
{
/****************************************************************************
  Rutin untuk Menghapus Tabel
****************************************************************************/

for (int i = 0; i <= SG->ColCount; i++) {
	SG->Cols[i]->Clear();
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::CopyReportClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Menyalin Text dari Report
****************************************************************************/

RichEditHasil->CopyToClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::CutReportClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Cut Text dari Report
****************************************************************************/

RichEditHasil->CutToClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PasteReportClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Paste Text ke Report
****************************************************************************/

RichEditHasil->PasteFromClipboard();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::SelectAllReportClick(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Select Seluruh Text pada Report
****************************************************************************/

RichEditHasil->SelectAll();	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::DataMode()
{
MenuEditData->Visible = true;
MenuEditReport->Visible = false;
MenuEditVariabel->Visible = false;
//PanelReport->Visible = false;
//PanelData->Visible = true;
PanelJudul->Top = 154;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ReportMode()
{
MenuEditData->Visible = false;
MenuEditVariabel->Visible = false;
MenuEditReport->Visible = true;
//PanelData->Visible = false;
//PanelReport->Visible = true;
PanelJudul->Top = 154;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::VariabelMode()
{
MenuEditData->Visible = false;
MenuEditVariabel->Visible = true;
MenuEditReport->Visible = false;
//PanelData->Visible = true;
//PanelReport->Visible = false;
PanelJudul->Top = 154;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabSheetVariabelShow(TObject *Sender)
{
VariabelMode();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabSheetDataShow(TObject *Sender)
{
DataMode();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabSheetHasilShow(TObject *Sender)
{
ReportMode();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabSheetTabelOptimasiShow(TObject *Sender)
{
ReportMode();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabSheetGrafikHistorisOptimasiShow(TObject *Sender)
{
ReportMode();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabSheetTabelResidualShow(TObject *Sender)
{
ReportMode();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabSheetGrafikResidualShow(TObject *Sender)
{
ReportMode();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::TabSheetHistogramShow(TObject *Sender)
{
ReportMode();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::OptimasiAlgoritmaGenetik1Click(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Menampilkan Dialog Optimasi
****************************************************************************/

#define VariabelBox FormDialog->ListBoxVariabel->Items
#define VariabelBebasBox FormDialog->ListBoxVariabelBebas->Items
#define VariabelTakBebasBox FormDialog->ComboBoxVariabelTakBebas

FormDialog->ProgressBarTotal->Position = 0;
FormDialog->ComboBoxVariabelTakBebas->Items->Clear();
VariabelBebasBox->Clear();
VariabelBox->Clear();
VariabelTakBebasBox->Text = StringGridVariabel->Cells[1][1];

for (int i = 0; i < StrToInt(EditJumlahVariabel->Text); i++) {
	if (i == 0) {
		VariabelTakBebasBox->Items->Add(StringGridVariabel->Cells[1][i+1]);
	}
	else if (i != 0) {
		VariabelBebasBox->Add(StringGridVariabel->Cells[1][i+1]);
	}
}
FormMain->Visible = false;
FormDialog->Show();
SaveLaporan->Enabled = false;
SavePopUpMenuReport->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::About1Click(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Memanggil About Box
****************************************************************************/

FormAboutBox->Show();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
/****************************************************************************
  Rutin yang dijalankan ketika Program akan Ditutup
****************************************************************************/

/*---------------------------------------------------------------------------
  Berikan peringatan untuk menyimpan lembar kerja saat aplikasi ditutup
---------------------------------------------------------------------------*/
if (isModified) {
	int Jawaban = MessageDlg(
		"Do you want to save the changes the data?",
		mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0);
	if (Jawaban == mrYes) {
		if (SaveData->Enabled == true) {
			SaveDataClick(Sender);
		}
		else {
			SaveAsDataClick(Sender);
		}
	}
	else if (Jawaban == mrNo) {
		CanClose = true;
	}
	else if (Jawaban == mrCancel) {
		CanClose = false;
	}
}

/*---------------------------------------------------------------------------
  Berikan peringatan untuk menyimpan hasil optimasi saat aplikasi ditutup
---------------------------------------------------------------------------*/
if (RichEditHasil->Modified) {
	int Jawaban = MessageDlg(
		"Do you want to save the changes the result?",
		mtConfirmation, TMsgDlgButtons() << mbYes << mbNo << mbCancel,0);
	if (Jawaban == mrYes) {
		if (SaveLaporan->Enabled == true) {
			SaveLaporanClick(Sender);
		}
		else {
			SaveLaporanAsClick(Sender);
		}
	}
	else if (Jawaban == mrNo) {
		CanClose = true;
	}
	else if (Jawaban == mrCancel) {
		CanClose = false;
	}
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Exit1Click(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Menutup Program
****************************************************************************/

Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Copy1Click(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Menyalin Text pada Tabel Residual
****************************************************************************/

int atas  = StringGridResidual->Selection.Top;
int bawah = StringGridResidual->Selection.Bottom;
int kiri  = StringGridResidual->Selection.Left;
int kanan = StringGridResidual->Selection.Right;

MemoClipBoard->Clear();
for (int i = atas; i <= bawah; i++) {
	String Tulisan;
	for (int j = kiri; j <= kanan; j++) {
		if (j != kanan) {
			Tulisan = Tulisan + StringGridResidual->Cells[j][i] + '\t';
		}
		else {
			Tulisan = Tulisan + StringGridResidual->Cells[j][i];
		}
	}
	MemoClipBoard->Lines->Add(Tulisan);
}
MemoClipBoard->SelectAll();
MemoClipBoard->CopyToClipboard();
MemoClipBoard->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Copy2Click(TObject *Sender)
{
/****************************************************************************
  Rutin untuk Menyalin Text pada Tabel Optimasi
****************************************************************************/

int atas  = StringGridOptimasi->Selection.Top;
int bawah = StringGridOptimasi->Selection.Bottom;
int kiri  = StringGridOptimasi->Selection.Left;
int kanan = StringGridOptimasi->Selection.Right;

MemoClipBoard->Clear();
for (int i = atas; i <= bawah; i++) {
	String Tulisan;
	for (int j = kiri; j <= kanan; j++) {
		if (j != kanan) {
			Tulisan = Tulisan + StringGridOptimasi->Cells[j][i] + '\t';
		}
		else {
			Tulisan = Tulisan + StringGridOptimasi->Cells[j][i];
		}
	}
	MemoClipBoard->Lines->Add(Tulisan);
}
MemoClipBoard->SelectAll();
MemoClipBoard->CopyToClipboard();
MemoClipBoard->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridDataDblClick(TObject *Sender)
{
if (isEditing) {
	isEditing = false;
	StringGridData->Options = TGridOptions()
	<< goFixedVertLine
	<< goFixedHorzLine
	<< goVertLine
	<< goHorzLine
	<< goColSizing
	<< goTabs
	<< goRangeSelect;
}
else {
	isEditing = true;
	StringGridData->Options = TGridOptions()
	<< goFixedVertLine
	<< goFixedHorzLine
	<< goVertLine
	<< goHorzLine
	<< goRangeSelect
	<< goColSizing
	<< goTabs
	<< goEditing;
}



}
//---------------------------------------------------------------------------

void __fastcall TFormMain::StringGridDataClick(TObject *Sender)
{
if (isEditing) {
	StringGridData->Options = TGridOptions()
	<< goFixedVertLine
	<< goFixedHorzLine
	<< goVertLine
	<< goHorzLine
	<< goRangeSelect
	<< goColSizing
	<< goTabs
	<< goEditing;
}
else {
 StringGridData->Options = TGridOptions()
	<< goFixedVertLine
	<< goFixedHorzLine
	<< goVertLine
	<< goHorzLine
	<< goColSizing
	<< goTabs
	<< goRangeSelect;
}


}
//---------------------------------------------------------------------------


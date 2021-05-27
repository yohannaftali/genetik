//---------------------------------------------------------------------------

#ifndef UnitGenetikH
#define UnitGenetikH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ExtDlgs.hpp>
#include <Tabs.hpp>
#include "perfgrap.h"
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TEdit           *EditTitle;
	TEdit           *EditJumlahVariabel;  
	TImageList      *ImageList1;
	TLabel          *LabelFileTerbuka;
	TLabel          *LabelShift;
	TLabel          *LabelJumlahVariabel;
	TLabel          *LabelRichEditTerbuka;
	TMainMenu       *MainMenu1;
	TMenuItem       *File1;
	TMenuItem       *MenuEditData;
	TMenuItem       *MenuEditVariabel;
	TMenuItem       *MenuEditReport;
	TMenuItem       *Help1;	
	TMenuItem       *CopyData;
	TMenuItem       *PasteData;
	TMenuItem       *NewData;
	TMenuItem       *OpenData;
	TMenuItem       *SaveData;
	TMenuItem       *SaveAsData;
	TMenuItem       *CloseData;
	TMenuItem       *About1;
	TMenuItem       *Exit1;
	TMenuItem       *CopyPopUpMenuData;
	TMenuItem       *PastePopUpMenuData;
	TMenuItem       *Run1;
	TMenuItem       *AddRow;
	TMenuItem       *InsertRow;
	TMenuItem       *DeleteEndRow;
	TMenuItem       *SaveLaporanAs;
	TMenuItem       *PrintData;
	TMenuItem       *PrintLaporan;
	TMenuItem       *SaveLaporan;
	TMenuItem       *CopyVariabel;
	TMenuItem       *DeleteRow;
	TMenuItem       *OptimasiAlgoritmaGenetik1;
	TMenuItem       *CopyPopUpMenuReport;
	TMenuItem       *CutPopUpMenuReport;
	TMenuItem       *PastePopUpMenuReport;
	TMenuItem       *SelectAllPopUpMenuReport;
	TMenuItem       *AddRowPopUpMenuData;
	TMenuItem       *InsertRowPopUpMenuData;
	TMenuItem       *DeleteRowPopUpMenuData;
	TMenuItem       *DeleteEndRowPopUpMenuData;
	TMenuItem       *N1;
	TMenuItem       *N2;
	TMenuItem       *N3;
	TMenuItem       *N4;
	TMenuItem       *N5;
	TMenuItem       *N6;
	TMenuItem       *N7;
	TMenuItem       *N8;
	TMenuItem       *N9;
	TMenuItem       *N10;  
	TMenuItem       *N11;
	TMenuItem       *N12;
	TMenuItem       *N13;
	TMenuItem       *N14;
	TMenuItem       *N15;
	TMenuItem       *N16;
	TMenuItem       *N17;
	TMenuItem       *SavePopUpMenuReport;
	TMenuItem       *SaveAsPopUpMenuReport;
	TMenuItem       *CopyReport;
	TMenuItem       *CutReport;
	TMenuItem       *PasteReport;
	TMenuItem       *SelectAllReport;
	TMenuItem       *SaveDataPopUpMenuVariabel;
	TMenuItem       *SaveDataAsPopUpMenuVariabel;
	TMenuItem       *PrintDataPopUpMenuVariabel;
	TMenuItem       *SaveDataPopUpMenuData;
	TMenuItem       *SaveDataAsPopUpMenuData;
	TMenuItem       *PrintData2;
	TMenuItem       *PrintPopUpMenuReport;
	TMenuItem       *CopyPopUpMenuVariabel;
	TMenuItem       *PastePopUpMenuVariabel;
	TMenuItem       *PasteVariabel;
	TMemo           *MemoClipBoard;
	TMemo           *MemoSave;
	TOpenDialog     *OpenDialog1;
	TPanel          *PanelJudul;
	TPanel          *PanelData;
	TPanel          *PanelVariabel;
	TLabel          *LabelJudul;
	TPanel          *PanelReport;
	TPanel          *PanelEditData;
	TPopupMenu      *PopupMenuVariabel;
	TPopupMenu      *PopupMenuData;
	TPopupMenu      *PopupMenuReport;
	TPrintDialog    *PrintDialog1;
	TPageControl    *PageControlGenetik;
	TRichEdit       *RichEditHasil;
	TSaveDialog     *SaveDialog1;
	TSpeedButton    *SpeedButtonCopyData;
	TSpeedButton    *SpeedButtonPaste;
	TSpeedButton    *SpeedButtonAddRow;
	TSpeedButton    *SpeedButtonInsertRow;
	TSpeedButton    *SpeedButtonDeleteEndRow;
	TSpeedButton    *SpeedButtonDeleteRow;
	TSpeedButton    *SpeedButtonPrintReportPanelReport;
	TSpeedButton    *SpeedButtonSaveReportAsPanelReport;
	TSpeedButton    *SpeedButtonSavePanelReport;
	TSpeedButton    *SpeedButtonSaveDataPanelData;
	TSpeedButton    *SpeedButtonPanelData;
	TSpeedButton    *SpeedButtonPrintDataPanelData;
	TSpeedButton    *SpeedButtonSaveDataAsPanelData;
	TSpeedButton    *SpeedButtonOpenDataPanelData;
	TSpeedButton    *SpeedButtonNewDataPanelData;
	TSpeedButton    *SpeedButtonCloseDataPanelData;
	TStringGrid     *StringGridData;
	TStringGrid     *StringGridVariabel;
	TStatusBar      *StatusBarData;
	TStatusBar      *StatusBarVariabel;
	TSaveDialog     *SaveDialogRichEditHasil;
	TTabSheet       *TabSheetVariabel;
	TTabSheet       *TabSheetData;
	TTabSheet       *TabSheetHasil;
    TTabSheet *TabSheetGrafikHistorisOptimasi;
    TPanel *PanelGrafik;
    TChart *ChartOptimasi;
    TLineSeries *SeriesBestFitness;
    TLineSeries *SeriesAvgFitness;
    TLineSeries *SeriesWorstFitness;
    TTabSheet *TabSheetGrafikResidual;
    TPanel *PanelResidu;
    TChart *ChartResidu;
    TLineSeries *SeriesResidual;
    TSpeedButton *SpeedButtonPrintHistorisPanelReport;
    TSpeedButton *SpeedButtonPrintResidualPanelReport;
    TMenuItem *PrintHistoris;
    TMenuItem *PrintResidual;
	TTabSheet *TabSheetHistogram;
    TPanel *Panel1;
    TChart *ChartHistogram;
    TBarSeries *SeriesHistogram;
    TSpeedButton *SpeedButtonPrintHistogram;
    TMenuItem *PrintHistogram;
	TTabSheet *TabSheetTabelResidual;
	TStringGrid *StringGridResidual;
	TTabSheet *TabSheetTabelOptimasi;
	TStringGrid *StringGridOptimasi;
	TPopupMenu *PopupMenuResTable;
	TMenuItem *Copy1;
	TPopupMenu *PopupMenuTabelOptimasi;
	TMenuItem *Copy2;
	void __fastcall CopyDataClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall PasteDataClick(TObject *Sender);
	void __fastcall StringGridDataMouseWheelDown(TObject *Sender,
					TShiftState Shift, TPoint &MousePos, bool &Handled);
	void __fastcall StringGridDataMouseWheelUp(TObject *Sender,
					TShiftState Shift, TPoint &MousePos, bool &Handled);
	void __fastcall StringGridDataMouseDown(TObject *Sender,
					TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall AddRowClick(TObject *Sender);
	void __fastcall DeleteEndRowClick(TObject *Sender);
	void __fastcall About1Click(TObject *Sender);
	void __fastcall InsertRowClick(TObject *Sender);
	void __fastcall StringGridDataSetEditText(TObject *Sender, int ACol,
	                int ARow, const AnsiString Value);
	void __fastcall SaveAsDataClick(TObject *Sender);
	void __fastcall OpenDataClick(TObject *Sender);
	void __fastcall CloseDataClick(TObject *Sender);
	void __fastcall NewDataClick(TObject *Sender);
	void __fastcall SaveDataClick(TObject *Sender);
	void __fastcall StringGridDataKeyDown(TObject *Sender, WORD &Key,
					TShiftState Shift);
	void __fastcall StringGridDataKeyUp(TObject *Sender, WORD &Key,
					TShiftState Shift);   
	void __fastcall SaveLaporanClick(TObject *Sender);
	void __fastcall PrintDataClick(TObject *Sender);
	void __fastcall StringGridDataGetEditText(TObject *Sender, int ACol,
					int ARow, AnsiString &Value);
	void __fastcall StringGridDataSelectCell(TObject *Sender, int ACol,
					int ARow, bool &CanSelect);
	void __fastcall DeleteRowClick(TObject *Sender);
	void __fastcall EditJumlahVariabelChange(TObject *Sender);
	void __fastcall PageControlGenetikChange(TObject *Sender);
	void __fastcall OptimasiAlgoritmaGenetik1Click(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall StringGridVariabelMouseDown(TObject *Sender,
					TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall StringGridVariabelSetEditText(TObject *Sender, int ACol,
					int ARow, const AnsiString Value);
	void __fastcall StringGridVariabelMouseWheelDown(TObject *Sender,
					TShiftState Shift, TPoint &MousePos, bool &Handled);
	void __fastcall StringGridVariabelMouseWheelUp(TObject *Sender,
					TShiftState Shift, TPoint &MousePos, bool &Handled);
	void __fastcall StringGridVariabelKeyDown(TObject *Sender, WORD &Key,
					TShiftState Shift);
	void __fastcall StringGridVariabelKeyUp(TObject *Sender, WORD &Key,
					TShiftState Shift);
	void __fastcall StringGridVariabelGetEditText(TObject *Sender, int ACol,
					int ARow, AnsiString &Value);
	void __fastcall StringGridVariabelSelectCell(TObject *Sender, int ACol,
                    int ARow, bool &CanSelect);
	void __fastcall CopyVariabelClick(TObject *Sender);
	void __fastcall PasteVariabelClick(TObject *Sender);
	void __fastcall PrintLaporanClick(TObject *Sender);
	void __fastcall SaveLaporanAsClick(TObject *Sender);
	void __fastcall SelectAllReportClick(TObject *Sender);
	void __fastcall CopyReportClick(TObject *Sender);
	void __fastcall CutReportClick(TObject *Sender);
	void __fastcall PasteReportClick(TObject *Sender);
	void __fastcall EditTitleChange(TObject *Sender);
    void __fastcall TabSheetGrafikHistorisOptimasiShow(TObject *Sender);
    void __fastcall TabSheetGrafikResidualShow(TObject *Sender);
    void __fastcall PrintHistorisClick(TObject *Sender);
    void __fastcall PrintResidualClick(TObject *Sender);
    void __fastcall PrintHistogramClick(TObject *Sender);
	void __fastcall Copy1Click(TObject *Sender);
	void __fastcall Copy2Click(TObject *Sender);
	void __fastcall TabSheetVariabelShow(TObject *Sender);
	void __fastcall TabSheetDataShow(TObject *Sender);
	void __fastcall TabSheetHasilShow(TObject *Sender);
	void __fastcall TabSheetHistogramShow(TObject *Sender);
	void __fastcall TabSheetTabelOptimasiShow(TObject *Sender);
	void __fastcall TabSheetTabelResidualShow(TObject *Sender);
	void __fastcall StringGridDataDblClick(TObject *Sender);
	void __fastcall StringGridDataClick(TObject *Sender);
private:
	bool isModified;
	bool isEditing;
	int VariabelMaksimum;
	void __fastcall DataBaru();
	void __fastcall UpdateDimensiData();
	void __fastcall UpdateDimensiVariabel();
	void __fastcall UpdateHeaderData();
	void __fastcall SimpanKeFile();
	void __fastcall BacaDariFile();
	void __fastcall TombolSaveMati();
	void __fastcall TombolSaveHidup();
	void __fastcall UpdateIndeks(TStringGrid *SG);
	void __fastcall KosongSG(TStringGrid *SG);
	void __fastcall DataMode();
	void __fastcall VariabelMode();
	void __fastcall ReportMode();  

public:
	__fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif

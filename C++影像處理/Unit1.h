//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.FileCtrl.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>

#include "ImgProc.h"
#include "cc.h"
#include "Morphology.h"
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TStatusBar *StatusBar1;
	TPanel *Panel2;
	TImage *Image1;
	TDriveComboBox *DriveComboBox1;
	TFileListBox *FileListBox1;
	TDirectoryListBox *DirectoryListBox1;
	TMainMenu *MainMenu1;
	TMenuItem *F1;
	TMenuItem *Filter1;
	TMenuItem *g1;
	TMenuItem *oBinary1;
	TMenuItem *MeanFilter1;
	TMenuItem *MeanFilter2;
	TMenuItem *MedianFilter1;
	TMenuItem *RGBMeanFi1;
	TMenuItem *RGBMedian1;
	TMenuItem *N1;
	TMenuItem *SharpenFilter1;
	TMenuItem *RGBSharpenFilter1;
	TButton *Button2;
	TOpenDialog *OpenDialog1;
	TMenuItem *N2;
	TMenuItem *Difference1;
	TButton *Button1;
	TPageControl *PageControl1;
	TTabSheet *Orignal;
	TImage *Image2;
	TTabSheet *TabSheet2;
	TImage *Image3;
	TTabSheet *TabSheet3;
	TImage *Image4;
	TScrollBar *ScrollBar1;
	TTabSheet *TabSheet4;
	TImage *Image5;
	TTabSheet *TabSheet5;
	TImage *Image6;
	TTabSheet *TabSheet6;
	TImage *Image7;
	TTabSheet *TabSheet7;
	TImage *Image8;
	TTabSheet *TabSheet8;
	TImage *Image9;
	TImage *Image10;
	TImage *Image11;
	TTabSheet *TabSheet9;
	TImage *Image12;
	TImage *Image13;
	TMenuItem *HProjection1;
	TMemo *Memo1;
	TMenuItem *VProjection1;
	TTabSheet *TabSheet10;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TImage *Image14;
	TImage *Image15;
	TMenuItem *N3;
	TMenuItem *Sobel1;
	TTabSheet *TabSheet11;
	TImage *Image16;
	TImage *Image17;
	TImage *Image18;
	TImage *Image19;
	TButton *Button4;
	TButton *Button3;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	void __fastcall FileListBox1Click(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall Image2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall g1Click(TObject *Sender);
	void __fastcall oBinary1Click(TObject *Sender);
	void __fastcall ScrollBar1Change(TObject *Sender);
	void __fastcall MeanFilter2Click(TObject *Sender);
	void __fastcall MedianFilter1Click(TObject *Sender);
	void __fastcall RGBMeanFi1Click(TObject *Sender);
	void __fastcall RGBMedian1Click(TObject *Sender);
	void __fastcall SharpenFilter1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Difference1Click(TObject *Sender);
	void __fastcall RGBSharpenFilter1Click(TObject *Sender);
	void __fastcall HProjection1Click(TObject *Sender);
	void __fastcall VProjection1Click(TObject *Sender);
	void __fastcall Sobel1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);



private:	// User declarations
	bool fgImgLoad;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
		Graphics::TBitmap *Bmp;
		int *HProjection;
		int *VProjection;

		ConntdCompnt CC;
		MorphyObj Morphy;
		void MorphoInitial();
		void InitCC();
		void FillBlack();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

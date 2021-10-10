//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FileListBox1Click(TObject *Sender)
{
	Image1->Picture->LoadFromFile(FileListBox1->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1Click(TObject *Sender)
{
	//Image2->Picture->LoadFromFile(FileListBox1->FileName);
	Bmp=LoadImage(FileListBox1->FileName);
	Image2->Picture->Assign(Bmp);
	Image2->Width=Bmp->Width;
	Image2->Height=Bmp->Height;

	Image3->Width=Bmp->Width;
	Image3->Height=Bmp->Height;
	Image3->Picture->Bitmap=new Graphics::TBitmap();
	Image3->Picture->Bitmap->Width=Bmp->Width;
	Image3->Picture->Bitmap->Height=Bmp->Height;
	Image3->Picture->Bitmap->PixelFormat=pf24bit;

	Image4->Width=Bmp->Width;
	Image4->Height=Bmp->Height;
	Image4->Picture->Bitmap=new Graphics::TBitmap();
	Image4->Picture->Bitmap->Width=Bmp->Width;
	Image4->Picture->Bitmap->Height=Bmp->Height;
	Image4->Picture->Bitmap->PixelFormat=pf24bit;
//--------------------------------for Blur ------------------------------
	Image5->Width=Bmp->Width;
	Image5->Height=Bmp->Height;
	Image5->Picture->Bitmap=new Graphics::TBitmap();
	Image5->Picture->Bitmap->Width=Bmp->Width;
	Image5->Picture->Bitmap->Height=Bmp->Height;
	Image5->Picture->Bitmap->PixelFormat=pf24bit;
//--------------------------------for RGB Blur ------------------------------
	Image6->Width=Bmp->Width;
	Image6->Height=Bmp->Height;
	Image6->Picture->Bitmap=new Graphics::TBitmap();
	Image6->Picture->Bitmap->Width=Bmp->Width;
	Image6->Picture->Bitmap->Height=Bmp->Height;
	Image6->Picture->Bitmap->PixelFormat=pf24bit;
//--------------------------------for Sharpen ----------------------------------
	Image7->Width=Bmp->Width;
	Image7->Height=Bmp->Height;
	Image7->Picture->Bitmap=new Graphics::TBitmap();
	Image7->Picture->Bitmap->Width=Bmp->Width;
	Image7->Picture->Bitmap->Height=Bmp->Height;
	Image7->Picture->Bitmap->PixelFormat=pf24bit;
//--------------------------------for RGB Sharpen ------------------------------
	Image8->Width=Bmp->Width;
	Image8->Height=Bmp->Height;
	Image8->Picture->Bitmap=new Graphics::TBitmap();
	Image8->Picture->Bitmap->Width=Bmp->Width;
	Image8->Picture->Bitmap->Height=Bmp->Height;
	Image8->Picture->Bitmap->PixelFormat=pf24bit;
//--------------------------------for projection--------------------------------
	Image12->Width=Bmp->Width;
	Image12->Height=Bmp->Height;
	Image12->Picture->Bitmap=new Graphics::TBitmap();
	Image12->Picture->Bitmap->Width=Bmp->Width;
	Image12->Picture->Bitmap->Height=Bmp->Height;
	Image12->Picture->Bitmap->PixelFormat=pf24bit;
//--------------------------for horizontal projection---------------------------
	Image13->Width=100;
	Image13->Height=Bmp->Height;
	Image13->Picture->Bitmap=new Graphics::TBitmap();
	Image13->Picture->Bitmap->Width=Bmp->Width;
	Image13->Picture->Bitmap->Height=Bmp->Height;
	Image13->Picture->Bitmap->PixelFormat=pf24bit;
	Image13->Left=Image12->Left+Image7->Width+50;
//--------------------------for vertical projection----------------------------
	Image14->Width=Bmp->Width;
	Image14->Height=100;
	Image14->Picture->Bitmap=new Graphics::TBitmap();
	Image14->Picture->Bitmap->Width=Bmp->Width;
	Image14->Picture->Bitmap->Height=Bmp->Height;
	Image14->Picture->Bitmap->PixelFormat=pf24bit;
	Image14->Left=Image12->Left;
	Image14->Top=Image12->Top+Image12->Height+10;
//--------------------------for Edge Detection----------------------------------
	Image15->Width=100;
	Image15->Height=Bmp->Height;
	Image15->Picture->Bitmap=new Graphics::TBitmap();
	Image15->Picture->Bitmap->Width=Bmp->Width;
	Image15->Picture->Bitmap->Height=Bmp->Height;
	Image15->Picture->Bitmap->PixelFormat=pf24bit;

   	fgImgLoad=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image2MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	int r, g, b;
    int h, s, v;
	String str;

	if(/*!fgImgLoad*/Image2->Picture->Bitmap==NULL)
		return;

	GetRGB(Image2->Picture->Bitmap, X, Y, &r, &g, &b);

	str="R="+IntToStr(r)+",G="+IntToStr(g)+",B="+IntToStr(b);
	StatusBar1->Panels->Items[0]->Text=str;

	RGBToHSV(r, g, b, &h, &s, &v);

	str="H="+IntToStr(h)+",S="+IntToStr(s)+",V="+IntToStr(v);
	StatusBar1->Panels->Items[1]->Text=str;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	fgImgLoad=false;
    Bmp=NULL;
	HProjection=NULL;
	Form1->Width=1150;
	Form1->Height=800;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::g1Click(TObject *Sender)
{
	if(!fgImgLoad)
		return;
	ToGray(Bmp,Image3->Picture->Bitmap);
	TabSheet2->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::oBinary1Click(TObject *Sender)
{
	ToBinary_B(Bmp,Image4->Picture->Bitmap,80);
	TabSheet3->Repaint();

	Image12->Picture->Assign(Image4->Picture->Bitmap);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar1Change(TObject *Sender)
{
	int v;

	if(!fgImgLoad)
		return;

	v=ScrollBar1->Position;
	//Label1->Caption=IntToStr(ScrollBar1->Position);
	if(RadioButton1->Checked == true)
	{
		ToBinary_B(Bmp,Image4->Picture->Bitmap,v);
	}
	else if(RadioButton2->Checked == true)
	{
    	ToBinary_S(Bmp,Image4->Picture->Bitmap,v);
    }
	Image4->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MeanFilter2Click(TObject *Sender)
{
	ToGray(Bmp,Image5->Picture->Bitmap);
	MeanFilter(Image5->Picture->Bitmap,Image5->Picture->Bitmap);
	TabSheet4->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MedianFilter1Click(TObject *Sender)
{
	MedianFilter(Image5->Picture->Bitmap,Image5->Picture->Bitmap);
	TabSheet4->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RGBMeanFi1Click(TObject *Sender)
{
	RGBMean(Bmp,Image6->Picture->Bitmap);
	TabSheet5->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RGBMedian1Click(TObject *Sender)
{
	RGBMedian(Bmp,Image6->Picture->Bitmap);
	TabSheet5->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SharpenFilter1Click(TObject *Sender)
{
	SharpenFilter(Image3->Picture->Bitmap,Image7->Picture->Bitmap);
	TabSheet6->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if(OpenDialog1->Execute())
	{
		Graphics::TBitmap* BMP = new Graphics::TBitmap();
		BMP->PixelFormat = pf24bit;
		BMP->LoadFromFile(OpenDialog1->FileName);
		Image9->Picture->Assign(BMP);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	if(OpenDialog1->Execute())
	{
		Graphics::TBitmap* BMP = new Graphics::TBitmap();
		BMP->PixelFormat = pf24bit;
		BMP->LoadFromFile(OpenDialog1->FileName);
		Image10->Picture->Assign(BMP);

		Image11->Width=Image10->Width;
		Image11->Height=Image10->Height;
		Image11->Picture->Bitmap=new Graphics::TBitmap();
		Image11->Picture->Bitmap->Width=Image10->Width;
		Image11->Picture->Bitmap->Height=Image10->Height;
		Image11->Picture->Bitmap->PixelFormat=pf24bit;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Difference1Click(TObject *Sender)
{
	if(Image9->Width!=Image10->Width || Image9->Height!=Image10->Height)
	{
		ShowMessage("圖片大小不同");
        return;
    }
	ToGray(Image9->Picture->Bitmap,Image9->Picture->Bitmap);
	ToGray(Image10->Picture->Bitmap,Image10->Picture->Bitmap);
	Ddifference(Image9->Picture->Bitmap,Image10->Picture->Bitmap,Image11->Picture->Bitmap);
	//ToGray(Image11->Picture->Bitmap,Image11->Picture->Bitmap);
	TabSheet8->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RGBSharpenFilter1Click(TObject *Sender)
{
	RGBSharpenFilter(Bmp,Image8->Picture->Bitmap);
	TabSheet7->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::HProjection1Click(TObject *Sender)
{
	float scale;

	if(HProjection!=NULL)
	{
		delete [] HProjection;
		HProjection=NULL;
	}
	else
	{
		try{
			HProjection = new int [Image12->Height];
			for(int i=0;i<Image13->Height;i++)
				HProjection[i]=0;
		}
		catch(...)
		{   ShowMessage("Allocate Memory error");
			return;
        }
	}

	H_Projection(Image12->Picture->Bitmap,&HProjection[0]);

	Memo1->Clear();
	for(int i=0;i<Image12->Height;i++)
		Memo1->Lines->Add(HProjection[i]);

	Image13->Canvas->Brush->Color=clGreen;
	Image13->Height=Image12->Height;
    Image13->Canvas->FillRect(TRect(0,0,Image13->Width,Image13->Height));

	scale=(float)Image12->Width/(float)Image13->Width;
	DrawHProjection(&HProjection[0], Image13, Image13->Height, scale);

	if(HProjection!=NULL)
	{
		delete HProjection;
        HProjection=NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::VProjection1Click(TObject *Sender)
{
	float scale;

	if(VProjection!=NULL)
	{
		delete [] VProjection;
		VProjection=NULL;
	}
	else
	{
		try
		{
			VProjection=new int [Image12->Width];

			for(int i=0;i<Image14->Width;i++)
				VProjection[i]=0;
		}
		catch (...)
		{
			ShowMessage("error1");
			return;
		}
	}

	V_Projection(Image12->Picture->Bitmap,&VProjection[0]);

	Memo1->Clear();

	for(int i=0;i<Image12->Width;i++)
	Memo1->Lines->Add(VProjection[i]);

	Image13->Canvas->Brush->Color=clWhite;
	Image13->Canvas->FillRect(TRect(0,0,Image14->Width,Image14->Height));

	scale=(float)Image12->Height/(float)Image14->Height;

	DrawVProjection(&VProjection[0],Image14,Image14->Width,scale);
  	//Image15->Repaint();

	if(VProjection!=NULL)
	{
		delete VProjection;
		VProjection=NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Sobel1Click(TObject *Sender)
{
	SobelFilter(Image3->Picture->Bitmap,Image15->Picture->Bitmap);
	TabSheet10->Repaint();
}
//---------------------------------------------------------------------------
void TForm1::InitCC()
{
	//指定輸出影像
	CC.Initial(Image17->Width,Image17->Height,Image17->Picture->Bitmap,20000);
	CC.SetRemovalSize(20);
	//指定一補洞的影像來源
	CC.Connection(Image16->Picture->Bitmap);
	//可以不用此行
	CC.ShowComponents();
}
//---------------------------------------------------------------------------
void TForm1::MorphoInitial()
{
	//指定影像長寬
	Morphy.Inital(Image17->Picture->Bitmap->Width,Image17->Picture->Bitmap->Height);
	//指定要補洞的來源影像
	Morphy.AssignSource(Image17->Picture->Bitmap);
	//指定輸出的影像
	Morphy.AssignOutput(Image18->Picture->Bitmap);
}
//---------------------------------------------------------------------------
void TForm1::FillBlack()
{
	Byte *ptr;
	int width;

	width=Image17->Picture->Bitmap->Width*3;

	for(int y=0;y<Image17->Picture->Bitmap->Height;y++)
	{
		ptr=(Byte *)Image17->Picture->Bitmap->ScanLine[y];
		for(int x=0;x<width;x+=3)
		{
			if(ptr[x]!=255)
			{
				ptr[x]=0;
				ptr[x+1]=0;
				ptr[x+2]=0;
            }
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	//Image16->Picture->LoadFromFile("1.bmp");
    Image16->Picture->Assign(Image4->Picture->Bitmap);
	Image16->Width=Image1->Picture->Bitmap->Width;
	Image16->Height=Image1->Picture->Bitmap->Height;

	Image17->Width=Image1->Picture->Bitmap->Width;
	Image17->Height=Image1->Picture->Bitmap->Height;
	Image17->Picture->Bitmap=new Graphics::TBitmap();
	Image17->Picture->Bitmap->Width=Image1->Picture->Bitmap->Width;
	Image17->Picture->Bitmap->Height=Image1->Picture->Bitmap->Height;
	Image17->Picture->Bitmap->PixelFormat=pf24bit;;

	Image18->Width=Image1->Picture->Bitmap->Width;
	Image18->Height=Image1->Picture->Bitmap->Height;
	Image18->Picture->Bitmap=new Graphics::TBitmap();
	Image18->Picture->Bitmap->Width=Image1->Picture->Bitmap->Width;
	Image18->Picture->Bitmap->Height=Image1->Picture->Bitmap->Height;
	Image18->Picture->Bitmap->PixelFormat=pf24bit;

	Image19->Width=Image1->Picture->Bitmap->Width;
	Image19->Height=Image1->Picture->Bitmap->Height;
	Image19->Picture->Bitmap=new Graphics::TBitmap();
	Image19->Picture->Bitmap->Width=Image1->Picture->Bitmap->Width;
	Image19->Picture->Bitmap->Height=Image1->Picture->Bitmap->Height;
	Image19->Picture->Bitmap->PixelFormat=pf24bit;

	InitCC();

	MorphoInitial();	//補洞演算法初始化
	FillBlack();      	//把背景以外的顏色,都塗成黑色才能進行物體補洞
	Morphy.Opening();  	//進行物體補洞

    //在一次利用 connect conpoment進行去雜訊
	CC.Initial(Image18->Width,Image19->Height,Image19->Picture->Bitmap,20000);
	CC.SetRemovalSize(70);
	CC.Connection(Image18->Picture->Bitmap);
	CC.ShowComponents();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	Bmp=new Graphics::TBitmap();
	Bmp->Assign(Image19->Picture->Bitmap);

	Image16->Picture->Assign(Bmp);
}
//---------------------------------------------------------------------------


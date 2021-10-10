//---------------------------------------------------------------------------

#pragma hdrstop

#include "12.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

int compare(const void *a, const void *b)
{
	int aa = *(int *)a;
	int bb = *(int *)b;

	if(aa<bb) return -1;
	if(aa>bb) return 1;

	else
		return 0;
}

int min(int  a,int b)
{
	if(a>=b)
		return b;
	else
		return a;
}
int max(int  a,int b)
{
	if(a>=b)
		return a;
	else
		return b;
}

Graphics::TBitmap *LoadImage(AnsiString Str)
{
	AnsiString ext;
	Graphics::TBitmap *Pic;
	TJPEGImage *Jpeg = new TJPEGImage;

	Pic=new Graphics::TBitmap();

	ext = ExtractFileExt(Str).LowerCase();

	if(ext==".bmp")
	{
		Pic->LoadFromFile(Str);
	}
	else
	{
		Jpeg->LoadFromFile(Str);
		Pic->Assign(Jpeg);
		delete Jpeg;
	}
	return Pic;
}
//------------------------------------------------------------------------------
void GetRGB(Graphics::TBitmap *Bmp,int x, int y, int *r, int *g, int *b)
{
	Byte *ptr;
	ptr=(Byte *)Bmp->ScanLine[y];
	int x1;
	x1=(x<<1)+x;

	*r=ptr[x1+2];
	*g=ptr[x1+1];
	*b=ptr[x1];
}
//------------------------------------------------------------------------------
void ToGray(Graphics::TBitmap *Source, Graphics::TBitmap *Target)
{
	Byte *s_ptr, *t_ptr;
	int r, g, b;
	int width, height;
	int gray;

	width=Source->Width*3;
	height=Source->Height;
	for(int y=0;y<height;y++)
	{
		s_ptr=(Byte *)Source->ScanLine[y];
		t_ptr=(Byte *)Target->ScanLine[y];

		for(int x=0;x<width;x+=3)
		{
			r=s_ptr[x+2];
			g=s_ptr[x+1];
			b=s_ptr[x];

			gray = b*0.114+g*0.587+r*0.299;

			t_ptr[x+2]=gray;
			t_ptr[x+1]=gray;
			t_ptr[x]=gray;
		}
	}
}
//-----------------------------------------------------------------------------
void RGBToHSV(int r, int g, int b, int *ch, int *cs, int *cv)
{
  BYTE *ptr;
  float temp,mi,delta;
  int inter,c;
  float h,s,v;

  mi=min(min(r,g),b);
  v=max(max(r,g),b);
  delta=v-mi;

  if(delta==0)
	h=0;
  else
    {
      if(r==v)
        h = 60.0 * (g - b) / delta;
	  if(g==v)
		h = 120.0 + 60.0 * (b - r) / delta;
      if(b==v)
        h = 240.0 + 60.0 * (r - g) / delta;
      if(h<0.0)
		h = h + 360.0;
	}

  if(v==0.0)
    s=0;
  else
    s=delta/v;

  s*=255.0;

  *ch=h;
  *cs=s;
  *cv=v;
}
//-----------------------------------------------------------------------------
void ToBinary_B(Graphics::TBitmap *Source, Graphics::TBitmap *Target,int th)
{
	Byte *s_ptr, *t_ptr;
	int r, g, b;
	int width, height;

	width=Source->Width*3;
	height=Source->Height;

	for(int y=0;y<height;y++)
	{
		s_ptr=(Byte *)Source->ScanLine[y];
		t_ptr=(Byte *)Target->ScanLine[y];

		for(int x=0;x<width;x+=3)
		{
			b=s_ptr[x];

			if(b >= th)
			{
				t_ptr[x+2]=BINARY_FOREGROUND;
				t_ptr[x+1]=BINARY_FOREGROUND;
				t_ptr[x]=BINARY_FOREGROUND;
			}
			else
			{
				t_ptr[x+2]=BINARY_BACKGROUND;
				t_ptr[x+1]=BINARY_BACKGROUND;
				t_ptr[x]=BINARY_BACKGROUND;
			}
		}
	}
}
//------------------------------------------------------------------------------
void MeanFilter(Graphics::TBitmap *Source, Graphics::TBitmap *Target)
{
	Byte *sptr1, *sptr2, *sptr3, *tptr;
	int avg;
	int width, height;

	width=(Source->Width-2)*3;
	height=Source->Height-2;

	for(int y=0;y<height;y++)
	{
		sptr1=(Byte *)Source->ScanLine[y];
		sptr2=(Byte *)Source->ScanLine[y+1];
		sptr3=(Byte *)Source->ScanLine[y+2];
		tptr=(Byte *)Target->ScanLine[y+1];

		for(int x=0;x<width;x+=3)
		{
			avg=(sptr1[x]+sptr1[x+3]+sptr1[x+6]+
				 sptr2[x]+sptr2[x+3]+sptr2[x+6]+
				 sptr3[x]+sptr3[x+3]+sptr3[x+6])/9;

			tptr[x+3]=avg;
			tptr[x+4]=avg;
			tptr[x+5]=avg;
		}
	}
}
//------------------------------------------------------------------------------
void MedianFilter(Graphics::TBitmap *Source, Graphics::TBitmap *Target)
{
	Byte *sptr1, *sptr2, *sptr3, *tptr;
	int data[9];
	int width, height;

	width=(Source->Width-2)*3;
	height=Source->Height-2;

	for(int y=0;y<height;y++)
	{
		sptr1=(Byte *)Source->ScanLine[y];
		sptr2=(Byte *)Source->ScanLine[y+1];
		sptr3=(Byte *)Source->ScanLine[y+2];
		tptr=(Byte *)Target->ScanLine[y+1];

		for(int x=0;x<width;x+=3)
		{
			data[0]=sptr1[x]; data[1]=sptr1[x+3]; data[2]=sptr1[x+6];
			data[3]=sptr2[x]; data[4]=sptr2[x+3]; data[5]=sptr2[x+6];
			data[6]=sptr3[x]; data[7]=sptr3[x+3]; data[8]=sptr3[x+6];

			qsort(data, 9, sizeof(int), compare);

			tptr[x+3]=data[4];
			tptr[x+4]=data[4];
			tptr[x+5]=data[4];
		}
	}
}
//------------------------------------------------------------------------------
void RGBMean(Graphics::TBitmap *Source, Graphics::TBitmap *Target)
{
	Byte *sptr1,*sptr2,*sptr3,*tptr;
	int w,h;
	int avg1,avg2,avg3;

	w=(Source->Width-2)*3;
	h=Source->Height-2;

	for(int y=0;y<h;y++)
	{
	   sptr1=(Byte *)Source->ScanLine[y];
	   sptr2=(Byte *)Source->ScanLine[y+1];
	   sptr3=(Byte *)Source->ScanLine[y+2];
	   tptr=(Byte *)Target->ScanLine[y+1];

		for(int x=0;x<w;x+=3)
		{
		  avg1=(sptr1[x]+sptr1[x+3]+sptr1[x+6]+
				sptr2[x]+sptr2[x+3]+sptr2[x+6]+
				sptr3[x]+sptr3[x+3]+sptr3[x+6])/9;

		  avg2=(sptr1[x+1]+sptr1[x+4]+sptr1[x+7]+
				sptr2[x+1]+sptr2[x+4]+sptr2[x+7]+
				sptr3[x+1]+sptr3[x+4]+sptr3[x+7])/9;

		  avg3=(sptr1[x+2]+sptr1[x+5]+sptr1[x+8]+
				sptr2[x+2]+sptr2[x+5]+sptr2[x+8]+
				sptr3[x+2]+sptr3[x+5]+sptr3[x+8])/9;

		  tptr[x+3]=avg1;
		  tptr[x+4]=avg2;
		  tptr[x+5]=avg3;
		}
	}
}
//------------------------------------------------------------------------------
void RGBMedian(Graphics::TBitmap *Source, Graphics::TBitmap *Target)
{
	Byte *sptr1,*sptr2,*sptr3,*tptr;
	int w,h;
	int data1[9],data2[9],data3[9];

	w=(Source->Width-2)*3;
	h=Source->Height-2;

	for(int y=0;y<h;y++)
	{
		sptr1=(Byte *)Source->ScanLine[y];
		sptr2=(Byte *)Source->ScanLine[y+1];
		sptr3=(Byte *)Source->ScanLine[y+2];
		tptr=(Byte *)Target->ScanLine[y+1];

		for(int x=0;x<w;x+=3)
		{
			data1[0]=sptr1[x]; data1[1]=sptr1[x+3]; data1[2]=sptr1[x+6];
			data1[3]=sptr2[x]; data1[4]=sptr2[x+3]; data1[5]=sptr2[x+6];
			data1[6]=sptr3[x]; data1[7]=sptr3[x+3]; data1[8]=sptr3[x+6];

			qsort(data1,9,sizeof(int),compare);

			data2[0]=sptr1[x+1]; data2[1]=sptr1[x+4]; data2[2]=sptr1[x+7];
			data2[3]=sptr2[x+1]; data2[4]=sptr2[x+4]; data2[5]=sptr2[x+7];
			data2[6]=sptr3[x+1]; data2[7]=sptr3[x+4]; data2[8]=sptr3[x+7];

			qsort(data2,9,sizeof(int),compare);

			data3[0]=sptr1[x+2]; data3[1]=sptr1[x+5]; data3[2]=sptr1[x+8];
			data3[3]=sptr2[x+2]; data3[4]=sptr2[x+5]; data3[5]=sptr2[x+8];
			data3[6]=sptr3[x+2]; data3[7]=sptr3[x+5]; data3[8]=sptr3[x+8];

			qsort(data3,9,sizeof(int),compare);

			tptr[x+3]=data1[4];
			tptr[x+4]=data2[4];
			tptr[x+5]=data3[4];
		}
	}
}
//------------------------------------------------------------------------------
void SharpenFilter(Graphics::TBitmap *Source, Graphics::TBitmap *Target)
{
	float Mask[9] = {-1.0, -1.0, -1.0,
					 -1.0,  8.0, -1.0,
					 -1.0, -1.0, -1.0
					};
	HeighBoostFilter(Source, Target, Mask);
}
//------------------------------------------------------------------------------
void HeighBoostFilter(Graphics::TBitmap *Source, Graphics::TBitmap *Target, float *Mask)
{
	float value;
	int height, width;
	Byte *spt0, *spt1, *spt2, *tptr;

	width=(Source->Width-2)*3;
	height=Source->Height-2;

	for(int y=0;y<height;y++)
	{
		spt0=(Byte *)Source->ScanLine[y];
		spt1=(Byte *)Source->ScanLine[y+1];
		spt2=(Byte *)Source->ScanLine[y+2];
		tptr=(Byte *)Target->ScanLine[y+1];

		for(int x=0;x<width;x+=3)
		{
			value=(spt0[x]*Mask[0]+spt0[x+3]*Mask[1]+spt0[x+6]*Mask[2]+
				   spt1[x]*Mask[3]+spt1[x+3]*Mask[4]+spt1[x+6]*Mask[5]+
				   spt2[x]*Mask[6]+spt2[x+3]*Mask[7]+spt2[x+6]*Mask[8])/9;

			tptr[x+3]=spt1[x+3]+value;
			tptr[x+4]=spt1[x+4]+value;
			tptr[x+5]=spt1[x+5]+value;
		}
	}
}
//------------------------------------------------------------------------------
void RGBSharpenFilter(Graphics::TBitmap *Source, Graphics::TBitmap *Target)
{
	float Mask[9] = {-1.0, -1.0, -1.0,
					 -1.0,  8.0, -1.0,
					 -1.0, -1.0, -1.0
					};
	RGBBoostFilter(Source, Target, Mask);
}
//------------------------------------------------------------------------------
void RGBBoostFilter(Graphics::TBitmap *Source, Graphics::TBitmap *Target, float *Mask)
{
	float value;
	int height, width;
	Byte *spt0, *spt1, *spt2, *tptr;

	width=(Source->Width-2)*3;
	height=Source->Height-2;
}
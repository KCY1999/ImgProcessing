//---------------------------------------------------------------------------

#ifndef ImgProcH
#include <vcl.h>
#include <jpeg.hpp>
#include <algorithm>

#define ImgProcH
#define BINARY_FOREGROUND 0
#define BINARY_BACKGROUND 255

Graphics::TBitmap *LoadImage(AnsiString);
void GetRGB(Graphics::TBitmap *, int, int, int *, int *, int *);
void ToGray(Graphics::TBitmap *, Graphics::TBitmap *);
void RGBToHSV(int , int , int , int *, int *, int *);
void ToBinary_B(Graphics::TBitmap *, Graphics::TBitmap *,int);
void ToBinary_S(Graphics::TBitmap *, Graphics::TBitmap *,int);
void MeanFilter(Graphics::TBitmap *, Graphics::TBitmap *);
void MedianFilter(Graphics::TBitmap *, Graphics::TBitmap *);
void RGBMean(Graphics::TBitmap *, Graphics::TBitmap *);
void RGBMedian(Graphics::TBitmap *, Graphics::TBitmap *);
void SharpenFilter(Graphics::TBitmap *, Graphics::TBitmap *);
void HeighBoostFilter(Graphics::TBitmap *, Graphics::TBitmap *,float Mask[]);
void RGBSharpenFilter(Graphics::TBitmap *, Graphics::TBitmap *);
void RGBBoostFilter(Graphics::TBitmap *, Graphics::TBitmap *,float Mask[]);
void Ddifference(Graphics::TBitmap *,Graphics::TBitmap *,Graphics::TBitmap *);
void H_Projection(Graphics::TBitmap *,int[]);
void V_Projection(Graphics::TBitmap *,int[]);
void DrawHProjection(int[],TImage *,int,float);
void DrawVProjection(int[],TImage *,int,float);
void SobelFilter(Graphics::TBitmap *, Graphics::TBitmap *);
void Converlution2Times(Graphics::TBitmap *,Graphics::TBitmap *,int *,int *,int);

//---------------------------------------------------------------------------
#endif

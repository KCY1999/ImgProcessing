//-------------------------------------------------------------------------
//                         Morphology.h
//     Using on binary image, objects' colors are defined 0(black),
//     background's colors are defined 255(white).
//     The square of size 3x3 structuring element is adopted, it's origin is
//     up-left, coordinate is (1,1). 
//-------------------------------------------------------------------------

#ifndef MORPHOLOGY1H
#define MORPHOLOGY1H
//-------------------------------------------------------------------------

#include <vcl.h>

#define OBJECT_COLOR 0
#define BG_COLOR 255

class MorphyObj
{
private:
      Graphics::TBitmap *BmpSource; // 指向原來的影像
      Graphics::TBitmap *BmpOutput; // 指向輸出的影像
      Graphics::TBitmap *BmpTmp;    // 暫存影像
      int MorphoW,MorphoH;  
      int MorphoTotalWidth;
      int TotalWidth;
      int SEsize;  // structuring element's size
      int Center;  // the original of SE
      int x,y,k;  // free
      void ReBmpAllocation(Graphics::TBitmap *, int, int, TPixelFormat);
      inline void ClearBitmap(Graphics::TBitmap *,int);
      BYTE *Sptr, *SptrU, *SptrD, *Tptr, *TptrU, *TptrD;

public:
      MorphyObj();
      ~MorphyObj();
      void AssignOutput(Graphics::TBitmap *);
      void Inital(int,int);
      void Erosion(Graphics::TBitmap *,Graphics::TBitmap *);
      void Dilation(Graphics::TBitmap *,Graphics::TBitmap *);
      inline void SetEroObject(BYTE *, int);
      inline void SetDilaObject(BYTE *, BYTE *,BYTE *,int);
      inline void SetEroBG(BYTE *, int);
      inline int EroMask(BYTE *,BYTE *,BYTE *,int);
      inline BYTE DilaMask(BYTE *,int);
      void AssignSource(Graphics::TBitmap *);
      void Opening();
};

//---------------------------------------------------------------------------
#endif

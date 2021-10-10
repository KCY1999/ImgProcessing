/*=========================================================================
    Erosion & Dialation on binary image
    square structuring element 3x3

=======================================================================*/
#include "Morphology.h"

//---------------------------------------------------------------------
MorphyObj::MorphyObj()
{
  SEsize=3;
  Center=1;
  BmpTmp=NULL;

}

//---------------------------------------------------------------------
void MorphyObj::Inital(int width, int height)
{


  if(BmpTmp!=NULL)
    ReBmpAllocation(BmpTmp,width, height, pf24bit);
  else
    {
      BmpTmp = new Graphics::TBitmap;
      BmpTmp->Width = width;
      BmpTmp->Height = height;
      BmpTmp->PixelFormat = pf24bit;
    }
    
  MorphoW=width-1;
  MorphoH=height-1;
  TotalWidth = width*3;
  MorphoTotalWidth = MorphoW * 3; // three color channels
}

//---------------------------------------------------------------------
MorphyObj::~MorphyObj()
{

  if( BmpTmp!=NULL)
    delete BmpTmp;

  BmpTmp=NULL;

}

//-----------------------------------------------------------------------
void MorphyObj::AssignOutput(Graphics::TBitmap *Output)
{
  BmpOutput = Output;

} 

//-----------------------------------------------------------------------
void MorphyObj::AssignSource(Graphics::TBitmap *Source)
{

  BmpSource = Source;

}

//-----------------------------------------------------------------------
void MorphyObj::Dilation(Graphics::TBitmap *Source, Graphics::TBitmap *Output)
{ 

  for(y=1;y<MorphoH; y++)
    {
      Sptr =(Byte *)Source->ScanLine[y];
      Tptr =(Byte *)Output->ScanLine[y];
      TptrU =(Byte *)Output->ScanLine[y-1];
      TptrD =(Byte *)Output->ScanLine[y+1];

      for(x=4; x<MorphoTotalWidth; x+=3)
        {
          if( DilaMask(Sptr,x)==OBJECT_COLOR )
            SetDilaObject(Tptr,TptrU,TptrD,x);

        }
    }
}

//----------------------------------------------------------------------
void MorphyObj::Erosion(Graphics::TBitmap *Source, Graphics::TBitmap *Output)
{

  for(y=1;y<MorphoH; y++)
    {
      Sptr = (Byte *)Source->ScanLine[y];
      SptrU = (Byte *)Source->ScanLine[y-1];
      SptrD = (Byte *)Source->ScanLine[y+1];

      Tptr = (Byte *)Output->ScanLine[y];

      for(x=4; x<MorphoTotalWidth; x+=3)
        {
          if( EroMask(Sptr,SptrU,SptrD,x)==OBJECT_COLOR )
            SetEroObject(Tptr,x);
          else
            SetEroBG(Tptr,x);
        }
    }
}

//-----------------------------------------------------------------------
void MorphyObj::Opening()
{

 /*
  ClearBitmap(BmpTmp,BG_COLOR);
  ClearBitmap(BmpOutput,BG_COLOR);
  Erosion(BmpSource,BmpTmp);
  Dilation(BmpTmp,BmpOutput);
 */


  ClearBitmap(BmpTmp,BG_COLOR);
  ClearBitmap(BmpOutput,BG_COLOR);
  Dilation(BmpSource,BmpTmp);
  Erosion(BmpTmp,BmpOutput);
  
}

//-----------------------------------------------------------------------
inline int MorphyObj::EroMask(BYTE *ptr, BYTE *ptrU,BYTE *ptrD,int x)
{
  return ptrU[x-3] | ptr[x-3] | ptrD[x-3] |
         ptrU[x]   | ptr[x]   | ptrD[x]   |
         ptrU[x+3] | ptr[x+3] | ptrD[x+3];

}

//-----------------------------------------------------------------------
inline BYTE MorphyObj::DilaMask(BYTE *ptr, int x)
{

  return ptr[x];

}

//-----------------------------------------------------------------------
inline void MorphyObj::SetDilaObject(BYTE *ptr, BYTE *ptrU,BYTE *ptrD,int Index)
{

  ptrU[Index-4] = ptrU[Index-3] = ptrU[Index-2] = OBJECT_COLOR;
  ptrU[Index-1] = ptrU[Index]   = ptrU[Index+1] = OBJECT_COLOR;
  ptrU[Index+2] = ptrU[Index+3] = ptrU[Index+4] = OBJECT_COLOR;

  ptr[Index-4] = ptr[Index-3] = ptr[Index-2] = OBJECT_COLOR;
  ptr[Index-1] = ptr[Index]   = ptr[Index+1] = OBJECT_COLOR;
  ptr[Index+2] = ptr[Index+3] = ptr[Index+4] = OBJECT_COLOR;

  ptrD[Index-4] = ptrD[Index-3] = ptrD[Index-2] = OBJECT_COLOR;
  ptrD[Index-1] = ptrD[Index]   = ptrD[Index+1] = OBJECT_COLOR;
  ptrD[Index+2] = ptrD[Index+3] = ptrD[Index+4] = OBJECT_COLOR;

}

//-----------------------------------------------------------------------
inline void MorphyObj::SetEroObject(BYTE *ptr, int Index)
{
  ptr[Index-1] = OBJECT_COLOR;
  ptr[Index] = OBJECT_COLOR;
  ptr[Index+1] = OBJECT_COLOR;
}

//-----------------------------------------------------------------------
inline void MorphyObj::SetEroBG(BYTE *ptr, int Index)
{
  ptr[Index-1] = BG_COLOR;
  ptr[Index] = BG_COLOR;
  ptr[Index+1] = BG_COLOR;

}

//-----------------------------------------------------------------------
void MorphyObj::ReBmpAllocation(Graphics::TBitmap *Bmp, int w, int h, TPixelFormat pf)
{

 Bmp->FreeImage();
 Bmp = new Graphics::TBitmap();
 Bmp->PixelFormat=pf;
 Bmp->Width=w;
 Bmp->Height=h;

 ClearBitmap(Bmp,BG_COLOR);
}

//-------------------------------------------------
inline void MorphyObj::ClearBitmap(Graphics::TBitmap *Bmp,int color)
{
  BYTE *ptr;
  
  for( int y=0;y<Bmp->Height;y++)
    {
      ptr = (Byte *)Bmp->ScanLine[y];

      for( int x=0;x <TotalWidth ; x+=3)
        {
          ptr[x]=color;
          ptr[x+1]=color;
          ptr[x+2]=color;
        }
    }

}
//----------------------------------------------------------------------

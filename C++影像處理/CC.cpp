//---------------------------------------------------------------------
#include "CC.h"
#include <time.h>
#include "unit1.h"


//---------------------------------------------------------------------
ConntdCompnt::ConntdCompnt()
{
  NewLabel=0;
  ERRORMSG=0;
  Width=0;
  Height=0;
  MaxLabel=DEFAULT_MAX_LABEL;
  LabelMatrix=NULL;
  ConnectSet=NULL;
  Buf=NULL;
  F=NULL;
  Show=NULL;
  CompntPos=NULL;
  CompntNum=0;
  
  RemovalSize=REMOVAL_SIZE;
}

//--------------------------------------------------------------------
ConntdCompnt::ConntdCompnt(int w, int h,int num,int size)
{
  NewLabel=0;
  ERRORMSG=0;
  MaxLabel=DEFAULT_MAX_LABEL;
  LabelMatrix=NULL;
  ConnectSet=NULL;
  Buf=NULL;
  F=NULL;
  CompntPos=NULL;
  CompntNum=0;

  Show=NULL;
  SetRemovalSize(size);
  Initial(w,h,NULL, num);
}

//---------------------------------------------------------------------
ConntdCompnt::~ConntdCompnt()
{
  Show=NULL;
  DeleteMatrix();
  DeleteConnectSet();
  DeleteBuf();
  DeleteCompntPos();
  

}

//--------------------------------------------------------------------
bool ConntdCompnt::Initial(int w, int h, Graphics::TBitmap *bmp,int num)
{

  DeleteMatrix();
  DeleteConnectSet();
  DeleteBuf();
  DeleteCompntPos();


  NewLabel=0;
  ERRORMSG=0;
  Width=w;
  Height=h;
  TotalWidth=Width*3;
  
  if(num>=0)
    if (SetMaxLabel(num)==false)
      {
        ERRORMSG=1;
        return false;
      }

  if(AllocateLabelMatrix()==false)
     {
       ERRORMSG=1;
       return false;
     } 

  SetShow(bmp);
  return true;
}

//--------------------------------------------------------------------
bool ConntdCompnt::AllocateLabelMatrix()
{
  if(LabelMatrix!=NULL)
    {
      DeleteMatrix();
      DeleteConnectSet();
      DeleteBuf();
      DeleteCompntPos();

    }

  LabelMatrix = new  int* [Height+2];

  for(int i = 0; i < Height+2; ++i)
    {
       LabelMatrix[i] = new  int [Width+2];

       if(LabelMatrix[i]==NULL)
         {
           for(int j=0;j<i;j++)
             delete LabelMatrix[j];
           delete LabelMatrix;
           LabelMatrix==NULL;
           return false;
         }

       for(int j=0;j<Width+2;j++)  // initialization
         LabelMatrix[i][j]=0;
    }
 //----------------------------------------------------
  if(AllocateSet()==false)
    {
      DeleteMatrix();
      return false;
    }

  if(AllocateBuf()==false)
    {
      DeleteMatrix();
      DeleteConnectSet();
      return false;
    }

  return true;

}

//-----------------------------------------------------------------
bool ConntdCompnt::AllocateSet()
{
  ConnectSet = new  int [MaxLabel+1];

  if(ConnectSet==NULL)
    return false;

  F= new char [MaxLabel+1];

  InitialSet();

  return true;
}

//----------------------------------------------------------------
bool ConntdCompnt::AllocateBuf()
{
  Buf = new  unsigned char* [Height+2];

  for(int i = 0; i < Height+2; ++i)
    {
       Buf[i] = new  unsigned char [Width+2];

       if(Buf[i]==NULL)
         {
           for(int j=0;j<i;j++)
             delete Buf[j];
           delete Buf;
           Buf==NULL;
           return false;
         }

       for(int j=0;j<Width+2;j++)  // initialization
         Buf[i][j]=BACKGROUND_COLOR;
    }
  return true;
}

//----------------------------------------------------------------
inline bool ConntdCompnt::AllocateCompntPos()
{

  if(NewLabel<1)
    return false;

  if(CompntPos!=NULL)
    DeleteCompntPos();  

  CompntPos = new  COO [NewLabel+1];
  
  if(CompntPos==NULL)
    return false;
  else
    {
      for(int i=0;i<NewLabel+1;i++)
        {
          CompntPos[i].x1=MAX_X;
          CompntPos[i].x2=-1;
          CompntPos[i].y1=MAX_Y;
          CompntPos[i].y2=-1;

        }
      return true;
    }

}

//----------------------------------------------------------------
inline void ConntdCompnt::InitialMatrix()
{
  // LabelMatrix的w和h比真實的image的w和h個多出2個byte
  //而圖像資料會擺在LabelMatrix的[1,1]開始處。即會留下一個寬為1 byte的框，
  //使得背景的編號永遠為0，而物體的編號則從1開始。

  for(i=0;i<Height+2;i++)
    for(j=0;j<Width+2;j++)
      LabelMatrix[i][j]=0;

}

//-----------------------------------------------------------------
inline void ConntdCompnt::InitialSet()
{
  //ConnectSet的大小為使用者預留的，通常會比真正找到的label數還要多很多
  //由於元件最後的編號，不一定是有順序的，例如可能最後找到三個物體，
  //但其編號為1, 4, 10。因此，在ConnectSet中有物體的編號位置，才會有值。

  for(i=0;i<MaxLabel+1;i++)
    {
      ConnectSet[i]=i;
      F[i]=1;
    }  
}

//----------------------------------------------------------------
inline void ConntdCompnt::InitialBuf(Graphics::TBitmap *Bmp)
{
  for(y=0,y1=1;y<Height;y++,y1++)
    {
      ptr = (Byte *)Bmp->ScanLine[y];
      for(x=0,x1=1;x<TotalWidth;x+=3,x1++)
        {
          Buf[y1][x1]=ptr[x];
        }
    }

}

//-----------------------------------------------------------------
bool ConntdCompnt::SetMaxLabel(int num)
{
  if(num > MAX_LABEL_LIMIT)
    return false;
  else
    MaxLabel=num;

  return true;  

}

//-----------------------------------------------------------------
void ConntdCompnt::DeleteMatrix()
{
  if(LabelMatrix==NULL)
    return;

  for(i=0;i<Height+2;i++)
    delete LabelMatrix[i];

  delete LabelMatrix;
  LabelMatrix=NULL;

}

//------------------------------------------------------------------
void ConntdCompnt::DeleteConnectSet()
{
  if(ConnectSet==NULL)
    return;

  delete ConnectSet;
  ConnectSet=NULL;

  delete F;
  F=NULL;

}

//-----------------------------------------------------------------
void ConntdCompnt::DeleteBuf()
{
  if(Buf==NULL)
    return;

  for(i=0;i<Height+2;i++)
    delete Buf[i];

  delete Buf;
  LabelMatrix=NULL;

}

//-----------------------------------------------------------------
inline void ConntdCompnt::DeleteCompntPos()
{
  if(CompntPos==NULL)
    return;

  delete [] CompntPos;
  CompntPos=NULL;
}    

//------------------------------------------------------------------
void ConntdCompnt::Connection(Graphics::TBitmap *Bmp)
{

  //TLargeInteger rFreq,rStart,rEnd;
  //float t;
  //QueryPerformanceFrequency(&rFreq);
  //QueryPerformanceCounter(&rStart);

  FirstScan(Bmp);
  SecondScan();
  LabelIgnoredComponents();
  
 // QueryPerformanceCounter(&rEnd);
 // t=float(rEnd.QuadPart-rStart.QuadPart)/float(rFreq.QuadPart/1000);
 // t=t;
}

//-----------------------------------------------------------------
//          modified version 2
//-----------------------------------------------------------------
inline void ConntdCompnt::FirstScan(Graphics::TBitmap *Bmp)
{
  NewLabel = 0;
  CompntNum=0;
  InitialMatrix();
  InitialSet();
  InitialBuf(Bmp);

  for(y=1; y<=Height;y++)
    {
      for(x=1;x<=Width;x++)
        {
          if(Buf[y][x] == FOREGROUND_COLOR)
            {
              up = Buf[y-1][x];
              left = Buf[y][x-1];

              if(up == BACKGROUND_COLOR && left == BACKGROUND_COLOR)
                {
                  NewLabel++;
                  lx = NewLabel;
                }
              else
                if ((LabelMatrix[y-1][x]!=LabelMatrix[y][x-1]) &&
                    (up!=BACKGROUND_COLOR) && (left!=BACKGROUND_COLOR))
                  {
                    if(F[ConnectSet[LabelMatrix[y][x-1]]]==1)
                        {
                          ConnectSet[LabelMatrix[y][x-1]]=ConnectSet[LabelMatrix[y-1][x]];
                          F[ConnectSet[LabelMatrix[y-1][x]]]=0;
                        }
                    else
                      if(F[ConnectSet[LabelMatrix[y-1][x]]]==1)
                        {
                          ConnectSet[LabelMatrix[y-1][x]]=ConnectSet[LabelMatrix[y][x-1]];
                          F[ConnectSet[LabelMatrix[y][x-1]]]=0;
                        }
                      else
                        for(k=0;k<NewLabel;k++)
                          if(ConnectSet[k]==ConnectSet[LabelMatrix[y-1][x]])
                             ConnectSet[k]=ConnectSet[LabelMatrix[y][x-1]];

                    lx=LabelMatrix[y][x-1];
                  }
                else
                  if(left!=BACKGROUND_COLOR)
                    lx=LabelMatrix[y][x-1];
                  else
                    if(up!=BACKGROUND_COLOR)
                      lx=LabelMatrix[y-1][x];

              LabelMatrix[y][x]=lx;
            }
        }// end for x
    } // end for y

}

//-----------------------------------------------------------------
inline void ConntdCompnt::SecondScan()
{
  for(y=1; y<=Height;y++)
    for(x=1; x<=Width;x++)
      if(LabelMatrix[y][x]!=0)
        LabelMatrix[y][x]=ConnectSet[LabelMatrix[y][x]];

}

//---------------------------------------------------------------
inline void ConntdCompnt::LabelIgnoredComponents()
{
  // here the variable 'ConnectSet' is temporarily used for recording the count of every component.
  // and variable 'F' is also temporarily used for recording which components are small and can be ignored.

  for(i=0;i<NewLabel+1;i++)
    {
      F[i]=0;  // stand for the component is big enough for reserving.
      ConnectSet[i]=0;
    }

  // counting every components' number
  for(y=1;y<Height;y++)
    for(x=1;x<Width;x++)  //原來 for(x=0;x<Width;x++)
      ConnectSet[LabelMatrix[y][x]]++;

  // Label the ignored components
  for(i=0;i<NewLabel+1;i++)
    if(ConnectSet[i]<RemovalSize)
      F[i]=1;   // label this component is ignored.

}

//---------------------------------------------------------------
void ConntdCompnt::SetRemovalSize(int size)
{
  if(size<1)
    return;

  RemovalSize=size;

}

//---------------------------------------------------------------------------
void ConntdCompnt::ShowComponents()
{

  for(y=0,y1=1;y<Height;y++,y1++)
    {
      ptr = (Byte *)Show->ScanLine[y];
      for(x=0,x1=1;x<TotalWidth;x+=3,x1++)
        {

          if(LabelMatrix[y1][x1]!=0 && F[LabelMatrix[y1][x1]]==0)
            {
              ptr[x] = (ConnectSet[LabelMatrix[y1][x1]] * 624 )&0xff;
              ptr[x+1] = (ConnectSet[LabelMatrix[y1][x1]] *371) & 0xff;
              ptr[x+2] = (ConnectSet[LabelMatrix[y1][x1]] * 923) &0xff;

            }
          else
            {
              ptr[x]=BACKGROUND_COLOR;
              ptr[x+1]=BACKGROUND_COLOR;
              ptr[x+2]=BACKGROUND_COLOR;
            }
     

        }
    }
}

//--------------------------------------------------------------------
 void ConntdCompnt::SetShow(Graphics::TBitmap *Bmp)
{
  Show=Bmp;

}

//---------------------------------------------------------------------
//找最大的那一個component，以及他的編號
int ConntdCompnt::FindMaxCompnt(int *x1, int *y1, int *x2, int *y2, int *No)
{
  int MaxSize=-1;
  *No=-1;

  for(int i=1;i<NewLabel+1;i++)  //若i從0開始，則ConnectSet[0]即是背景
    if(ConnectSet[i]>MaxSize)
      {
        MaxSize=ConnectSet[i];
        *No=i;
      }

  return MaxSize;

}

//----------------------------------------------------------------------
//找出所有的component的數量
int ConntdCompnt::GetCompntNum(bool fg)
{
  CompntNum=0; 

  if(fg==1) //省略面積小於設定大小的compnent
    {
      for(i=1;i<NewLabel+1;i++)  //若i從0開始，則ConnectSet[0]即是背景的size
        if(ConnectSet[i]!=0 && F[i]==0)
          CompntNum++;
    }
  else //不管面積大小，全部統計
    {
      for(i=1;i<NewLabel+1;i++)
        if(ConnectSet[i]!=0)
          CompntNum++;
    }

  return CompntNum;
}

//---------------------------------------------------------------------

COO *ConntdCompnt::GetCompntPos()
{
  int x1,x2,y1,y2;

  AllocateCompntPos();

  for(int y=1;y<Height+1; y++)
    for(int x=1;x<Width+1;x++)
      {
        if(LabelMatrix[y][x]!=0)  //不是背景
          {
            if (CompntPos[LabelMatrix[y][x]].x1>x)
               CompntPos[LabelMatrix[y][x]].x1=x;
            if (CompntPos[LabelMatrix[y][x]].x2<x)
               CompntPos[LabelMatrix[y][x]].x2=x;
            if (CompntPos[LabelMatrix[y][x]].y1>y)
               CompntPos[LabelMatrix[y][x]].y1=y;
            if (CompntPos[LabelMatrix[y][x]].y2<y)
               CompntPos[LabelMatrix[y][x]].y2=y;
          }
      }

  return CompntPos;
}

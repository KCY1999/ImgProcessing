//===========================================================================
//          Binary Image Connected Components      2006/07/03
//                            Cite from:
//   "A simple and efficient connected components labeling algorithm"
//   Di Stefano, L.; Bulgarelli, A.; Image Analysis and Processing, 1999.
//   Proceedings. International Conference on 27-29 Sept. 1999 Page(s):322 - 327
//===========================================================================

//---------------------------------------------------------------------------
//  This program is only used for C++ Builder 6.0 enviornment,
//  the images of input and output are 24 bits of bi-color in which only
//  containing black 0 and white 255 two colors.
//---------------------------------------------------------------------------
#ifndef CC1H
#define CC1H

#define BACKGROUND_COLOR 255    //背景色的預設值
#define FOREGROUND_COLOR 0      //前景色的預設值
#define MAX_LABEL_LIMIT 30000   //允許一張影像中的label的最大數量, 請勿任意更改.
                                //若要更改,需搭配更改 LabelMatrix, ConnectSet,
                                //Buf, F 這些變數的資料型態, 以及相關的functions.
#define DEFAULT_MAX_LABEL 1000  //預設一張影像中最多可包含的label數目, 不得大於
                                //MAX_LABEL_LIMIT
#define REMOVAL_SIZE 0          //預設的雜訊大小=0, 即不處理雜訊.
#define MAX_X 9999999
#define MAX_Y 9999999
//---------------------------------------------------------------------------
#include <vcl.h>

typedef struct _COO{
        int x1,x2,y1,y2;
        }COO;

//---------------------------------------------------------------------------
class ConntdCompnt
{
private:
        int NewLabel; // 指向目前新增的label編號, 即component的總數
        int Width, Height,TotalWidth; //影像的寬與高, TotalWidth=Width*3 (R,G,B三個chennels)
        int MaxLabel;      //一張影像中最多可包含的label數目,可由 ConntdCompnt(),
                           //及 Initial()設定. 請視狀況而設定, 此值越大會浪費記憶體空間,
                           //及拖慢執行的速度.
        int up,left,lx;
        int RemovalSize;   // 雜訊的大小, 可由SetRemovalSize()設定.
        int x,y,x1,i,j,k,y1;
        BYTE *ptr,*Upptr;
        Graphics::TBitmap *Show; // 指向欲輸出結果的影像的指標, 可由SetShow()設定.
        int **LabelMatrix;  // 儲存影像的labels. label的編號不一定有順序性
        int *ConnectSet;   //儲存每個找到的label的size，有可能某個label的size=0
        unsigned char **Buf;
        char *F;
        COO *CompntPos; //用來儲存每個元件的座標
        int CompntNum;

        bool AllocateLabelMatrix();
        inline void FirstScan(Graphics::TBitmap *);
        inline void SecondScan();
        void DeleteConnectSet();
        void DeleteMatrix();
        void DeleteBuf();
        inline void DeleteCompntPos();
        bool SetMaxLabel(int);
        bool AllocateSet();
        bool AllocateBuf();
        inline bool AllocateCompntPos();
        inline void InitialSet();
        inline void InitialMatrix();
        inline void InitialBuf(Graphics::TBitmap*);
        inline void LabelIgnoredComponents();

public:
        unsigned char ERRORMSG;
        // ERROTMSG: 1: allocate label matrix failure.
        //

        ConntdCompnt();
        ConntdCompnt(int , int, int ,int); //傳入: 影像寬, 影像高, 最大的label數目, 雜訊的size.
        ~ConntdCompnt();
        bool Initial(int,int,Graphics::TBitmap *,int); // 初始化, 傳入: 影像寬, 影像高, 輸出影像的指標, 最大的label數目.
        void Connection(Graphics::TBitmap *);  //呼叫Connected Components程序進行處理,
                                               //預被處理的影像指標.
        int **GetLabelMatrix(){ return LabelMatrix; }; //傳回Label table的陣列指標.
        void SetShow(Graphics::TBitmap *); // 搭配ShowComponents使用.
        void ShowComponents();     //以隨機的顏色顯示每一個components, 須先
                                   // 以SetShow()設定欲輸出的畫面的指標.
        void SetRemovalSize(int);  // 設定欲移除的雜訊的size(以pixels為單位).
                                   //並不影響 label table陣列的內容, 只影響輸出的影像. 預設值為不處理雜訊.
        int FindMaxCompnt(int *, int *, int *, int *, int *); //找出最大的component，傳回size及座標
        int GetCompntNum(bool); //傳回object的數量。 參數=1表示忽略面積小於設定的，則不算
        int *GetConnectSet(){ return ConnectSet; };
        int GetLabels(){ return NewLabel; };
        COO *GetCompntPos();  //注意：必須先使用GetCompntNum()算出物件的數量

};

//---------------------------------------------------------------------------

#endif
 
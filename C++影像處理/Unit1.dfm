object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 571
  ClientWidth = 878
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 635
    Height = 571
    Align = alLeft
    TabOrder = 0
    object StatusBar1: TStatusBar
      Left = 1
      Top = 547
      Width = 633
      Height = 23
      Panels = <
        item
          Width = 150
        end
        item
          Width = 150
        end
        item
          Width = 150
        end>
    end
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 633
      Height = 546
      ActivePage = TabSheet9
      Align = alClient
      TabOrder = 1
      object Orignal: TTabSheet
        Caption = 'Orignal'
        object Image2: TImage
          Left = 0
          Top = 16
          Width = 121
          Height = 121
          AutoSize = True
          Stretch = True
          OnMouseMove = Image2MouseMove
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'Gray'
        ImageIndex = 1
        object Image3: TImage
          Left = 3
          Top = 16
          Width = 121
          Height = 121
          AutoSize = True
          Stretch = True
        end
      end
      object TabSheet3: TTabSheet
        Caption = 'Binary'
        ImageIndex = 2
        object Image4: TImage
          Left = 3
          Top = 16
          Width = 121
          Height = 121
          AutoSize = True
          Stretch = True
        end
        object ScrollBar1: TScrollBar
          Left = 0
          Top = 494
          Width = 625
          Height = 24
          Align = alBottom
          Max = 255
          PageSize = 0
          TabOrder = 0
          OnChange = ScrollBar1Change
        end
        object RadioButton1: TRadioButton
          Left = 192
          Top = 16
          Width = 113
          Height = 17
          Caption = #26368#22823
          Checked = True
          TabOrder = 1
          TabStop = True
        end
        object RadioButton2: TRadioButton
          Left = 192
          Top = 56
          Width = 113
          Height = 17
          Caption = #26368#23567
          TabOrder = 2
        end
      end
      object TabSheet4: TTabSheet
        Caption = 'Blur'
        ImageIndex = 3
        object Image5: TImage
          Left = 3
          Top = 16
          Width = 121
          Height = 121
          AutoSize = True
          Stretch = True
        end
      end
      object TabSheet5: TTabSheet
        Caption = 'RGBBlur'
        ImageIndex = 4
        object Image6: TImage
          Left = 3
          Top = 16
          Width = 121
          Height = 121
          AutoSize = True
          Stretch = True
        end
      end
      object TabSheet6: TTabSheet
        Caption = 'Sharpen'
        ImageIndex = 5
        object Image7: TImage
          Left = 3
          Top = 16
          Width = 121
          Height = 121
          AutoSize = True
          Stretch = True
        end
      end
      object TabSheet7: TTabSheet
        Caption = 'RGBSharpen'
        ImageIndex = 6
        object Image8: TImage
          Left = 3
          Top = 16
          Width = 121
          Height = 121
          AutoSize = True
          Stretch = True
        end
      end
      object TabSheet8: TTabSheet
        Caption = 'Difference'
        ImageIndex = 7
        object Image9: TImage
          Left = 25
          Top = 30
          Width = 109
          Height = 106
          AutoSize = True
          Stretch = True
        end
        object Image10: TImage
          Left = 323
          Top = 30
          Width = 109
          Height = 106
          AutoSize = True
          Stretch = True
        end
        object Image11: TImage
          Left = 171
          Top = 272
          Width = 121
          Height = 121
          AutoSize = True
          Stretch = True
        end
        object Button1: TButton
          Left = 25
          Top = 296
          Width = 75
          Height = 25
          Caption = #22294#19968
          TabOrder = 0
          OnClick = Button1Click
        end
        object Button2: TButton
          Left = 25
          Top = 385
          Width = 75
          Height = 25
          Caption = #22294#20108
          TabOrder = 1
          OnClick = Button2Click
        end
      end
      object TabSheet9: TTabSheet
        Caption = 'Projection'
        ImageIndex = 8
        object Image12: TImage
          Left = 3
          Top = 16
          Width = 121
          Height = 121
          AutoSize = True
          Stretch = True
        end
        object Image13: TImage
          Left = 154
          Top = 16
          Width = 87
          Height = 121
        end
        object Image14: TImage
          Left = 3
          Top = 366
          Width = 87
          Height = 121
          OnMouseMove = Image2MouseMove
        end
        object Memo1: TMemo
          Left = 509
          Top = 16
          Width = 113
          Height = 400
          ScrollBars = ssVertical
          TabOrder = 0
        end
      end
      object TabSheet10: TTabSheet
        Caption = 'Edge Detection'
        ImageIndex = 9
        object Image15: TImage
          Left = 3
          Top = 16
          Width = 121
          Height = 121
          AutoSize = True
          Stretch = True
        end
      end
      object TabSheet11: TTabSheet
        Caption = 'noise removal'
        ImageIndex = 10
        object Image16: TImage
          Left = 27
          Top = 56
          Width = 121
          Height = 121
          AutoSize = True
          Stretch = True
        end
        object Image17: TImage
          Left = 243
          Top = 56
          Width = 121
          Height = 121
          AutoSize = True
          Stretch = True
        end
        object Image18: TImage
          Left = 456
          Top = 56
          Width = 121
          Height = 121
          AutoSize = True
          Stretch = True
        end
        object Image19: TImage
          Left = 27
          Top = 264
          Width = 121
          Height = 121
          AutoSize = True
          Stretch = True
        end
        object Label1: TLabel
          Left = 72
          Top = 16
          Width = 38
          Height = 23
          Caption = #21407#22294
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object Label2: TLabel
          Left = 270
          Top = 16
          Width = 57
          Height = 23
          Caption = #21435#38620#35338
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object Label3: TLabel
          Left = 499
          Top = 16
          Width = 38
          Height = 23
          Caption = #35036#27934
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object Label4: TLabel
          Left = 40
          Top = 235
          Width = 95
          Height = 23
          Caption = #20108#27425#21435#38620#35338
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object Button4: TButton
          Left = 392
          Top = 448
          Width = 75
          Height = 25
          Caption = 'Button4'
          TabOrder = 0
          OnClick = Button4Click
        end
        object Button3: TButton
          Left = 270
          Top = 448
          Width = 75
          Height = 25
          Caption = 'Button3'
          TabOrder = 1
          OnClick = Button3Click
        end
      end
    end
  end
  object Panel2: TPanel
    Left = 635
    Top = 0
    Width = 243
    Height = 571
    Align = alClient
    TabOrder = 1
    object Image1: TImage
      Left = 16
      Top = 346
      Width = 217
      Height = 201
      Stretch = True
      OnClick = Image1Click
    end
    object DriveComboBox1: TDriveComboBox
      Left = 16
      Top = 16
      Width = 217
      Height = 19
      DirList = DirectoryListBox1
      TabOrder = 0
    end
    object FileListBox1: TFileListBox
      Left = 16
      Top = 183
      Width = 217
      Height = 138
      ItemHeight = 13
      Mask = '*.bmp;*.jpg'
      TabOrder = 1
      OnClick = FileListBox1Click
    end
    object DirectoryListBox1: TDirectoryListBox
      Left = 16
      Top = 41
      Width = 217
      Height = 136
      FileList = FileListBox1
      TabOrder = 2
    end
  end
  object MainMenu1: TMainMenu
    Left = 592
    Top = 104
    object F1: TMenuItem
      Caption = 'File'
    end
    object Filter1: TMenuItem
      Caption = 'Filter'
      object g1: TMenuItem
        Caption = 'ToGray'
        OnClick = g1Click
      end
      object oBinary1: TMenuItem
        Caption = 'ToBinary'
        OnClick = oBinary1Click
      end
      object MeanFilter1: TMenuItem
        Caption = '-'
      end
      object MeanFilter2: TMenuItem
        Caption = 'MeanFilter'
        OnClick = MeanFilter2Click
      end
      object MedianFilter1: TMenuItem
        Caption = 'MedianFilter'
        OnClick = MedianFilter1Click
      end
      object RGBMeanFi1: TMenuItem
        Caption = 'RGBMean'
        OnClick = RGBMeanFi1Click
      end
      object RGBMedian1: TMenuItem
        Caption = 'RGBMedian'
        OnClick = RGBMedian1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object SharpenFilter1: TMenuItem
        Caption = 'SharpenFilter'
        OnClick = SharpenFilter1Click
      end
      object RGBSharpenFilter1: TMenuItem
        Caption = 'RGBSharpenFilter'
        OnClick = RGBSharpenFilter1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Difference1: TMenuItem
        Caption = 'Difference'
        OnClick = Difference1Click
      end
      object HProjection1: TMenuItem
        Caption = 'HProjection'
        OnClick = HProjection1Click
      end
      object VProjection1: TMenuItem
        Caption = 'VProjection'
        OnClick = VProjection1Click
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object Sobel1: TMenuItem
        Caption = 'Sobel'
        OnClick = Sobel1Click
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 592
    Top = 40
  end
end

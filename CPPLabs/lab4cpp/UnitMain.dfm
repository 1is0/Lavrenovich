object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Stacked'
  ClientHeight = 200
  ClientWidth = 727
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 16
    Width = 32
    Height = 25
    Caption = 'r ='
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 64
    Width = 36
    Height = 25
    Caption = 'a ='
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 160
    Top = 64
    Width = 36
    Height = 25
    Caption = 'b ='
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 296
    Top = 64
    Width = 34
    Height = 25
    Caption = 'c ='
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label5: TLabel
    Left = 424
    Top = 64
    Width = 36
    Height = 25
    Caption = 'd ='
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label6: TLabel
    Left = 552
    Top = 64
    Width = 35
    Height = 25
    Caption = 'e ='
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label7: TLabel
    Left = 8
    Top = 112
    Width = 78
    Height = 25
    Caption = 'Answer'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label8: TLabel
    Left = 8
    Top = 152
    Width = 134
    Height = 25
    Caption = 'Postfix Form'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object FormulaInput: TEdit
    Left = 46
    Top = 18
    Width = 515
    Height = 27
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
  end
  object aInput: TEdit
    Left = 50
    Top = 68
    Width = 79
    Height = 21
    TabOrder = 1
  end
  object bInput: TEdit
    Left = 202
    Top = 68
    Width = 79
    Height = 21
    TabOrder = 2
  end
  object cInput: TEdit
    Left = 336
    Top = 68
    Width = 79
    Height = 21
    TabOrder = 3
  end
  object dInput: TEdit
    Left = 466
    Top = 68
    Width = 79
    Height = 21
    TabOrder = 4
  end
  object eInput: TEdit
    Left = 593
    Top = 68
    Width = 79
    Height = 21
    TabOrder = 5
  end
  object ExecButton: TButton
    Left = 576
    Top = 21
    Width = 129
    Height = 25
    Caption = #1056#1072#1089#1089#1095#1080#1090#1072#1090#1100
    TabOrder = 6
    OnClick = ExecButtonClick
  end
  object ansEdit: TEdit
    Left = 102
    Top = 114
    Width = 515
    Height = 27
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 7
  end
  object PostfixFormEdit: TEdit
    Left = 160
    Top = 154
    Width = 457
    Height = 27
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 8
  end
end

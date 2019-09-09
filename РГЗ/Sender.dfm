object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Sender'
  ClientHeight = 224
  ClientWidth = 194
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 56
    Top = 82
    Width = 75
    Height = 25
    Caption = #1057#1090#1072#1088#1090
    TabOrder = 0
    OnClick = Button1Click
  end
  object Edit1: TEdit
    Left = 56
    Top = 36
    Width = 75
    Height = 21
    TabOrder = 1
  end
  object Button2: TButton
    Left = 56
    Top = 111
    Width = 75
    Height = 25
    Caption = #1057#1090#1086#1087
    TabOrder = 2
    OnClick = Button2Click
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 88
    Top = 152
  end
end

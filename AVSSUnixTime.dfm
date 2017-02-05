object frmUnixTime: TfrmUnixTime
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1050#1086#1085#1074#1077#1088#1090#1077#1088' '#1102#1085#1080#1082#1089'-'#1074#1088#1077#1084#1077#1085#1080
  ClientHeight = 153
  ClientWidth = 280
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Segoe UI'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 17
  object eDateTimeWin: TLabeledEdit
    Left = 8
    Top = 24
    Width = 264
    Height = 25
    EditLabel.Width = 158
    EditLabel.Height = 17
    EditLabel.Caption = #1058#1077#1082#1091#1097#1080#1081' '#1092#1086#1088#1084#1072#1090' Windows'
    TabOrder = 0
    OnChange = eDateTimeWinChange
  end
  object eDateTimeSQL: TLabeledEdit
    Left = 8
    Top = 72
    Width = 264
    Height = 25
    EditLabel.Width = 73
    EditLabel.Height = 17
    EditLabel.Caption = #1060#1086#1088#1084#1072#1090' SQL'
    TabOrder = 1
    OnChange = eDateTimeWinChange
  end
  object eUnixTime: TLabeledEdit
    Left = 8
    Top = 120
    Width = 264
    Height = 25
    EditLabel.Width = 75
    EditLabel.Height = 17
    EditLabel.Caption = #1060#1086#1088#1084#1072#1090' Unix'
    TabOrder = 2
    OnChange = eDateTimeWinChange
  end
end

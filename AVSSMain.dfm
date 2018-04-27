object Main: TMain
  Left = 0
  Top = 0
  Caption = #1056#1072#1073#1086#1090#1072' '#1089' '#1080#1085#1090#1077#1075#1088#1072#1094#1080#1086#1085#1085#1099#1084' '#1089#1077#1088#1074#1077#1088#1086#1084' '#1074#1077#1089#1086#1074#1099#1093' '#1089#1080#1089#1090#1077#1084
  ClientHeight = 555
  ClientWidth = 750
  Color = clBtnFace
  Constraints.MinHeight = 450
  Constraints.MinWidth = 750
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Segoe UI'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyUp = FormKeyUp
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 17
  object DBGrid: TDBGrid
    Left = 0
    Top = 307
    Width = 750
    Height = 134
    Align = alClient
    DataSource = DataSource
    Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -13
    TitleFont.Name = 'Segoe UI'
    TitleFont.Style = []
  end
  object pnlTop: TPanel
    Left = 0
    Top = 0
    Width = 750
    Height = 307
    Align = alTop
    BevelOuter = bvNone
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    DesignSize = (
      750
      307)
    object lblScales: TLabel
      Left = 70
      Top = 142
      Width = 48
      Height = 17
      Caption = 'scales ='
    end
    object lblFrom: TLabel
      Left = 16
      Top = 81
      Width = 36
      Height = 17
      Caption = 'FROM'
      FocusControl = cboxTable
    end
    object lblDate: TLabel
      Left = 70
      Top = 172
      Width = 69
      Height = 17
      Caption = 'datetime>='
    end
    object lblDateAnd: TLabel
      Left = 278
      Top = 172
      Width = 95
      Height = 17
      Caption = 'and datetime<='
    end
    object lblSelect: TLabel
      Left = 16
      Top = 51
      Width = 42
      Height = 17
      Caption = 'SELECT'
      FocusControl = cboxFields
    end
    object lblWhere: TLabel
      Left = 16
      Top = 111
      Width = 43
      Height = 17
      Caption = 'WHERE'
      FocusControl = eWhere
    end
    object lblOrder: TLabel
      Left = 16
      Top = 263
      Width = 42
      Height = 17
      Caption = 'ORDER'
      FocusControl = eOrder
    end
    object lblWhereAdd: TLabel
      Left = 70
      Top = 233
      Width = 22
      Height = 17
      Caption = 'and'
      FocusControl = eWhereAdd
    end
    object btnPerform: TButton
      Left = 638
      Top = 48
      Width = 96
      Height = 32
      Anchors = [akTop, akRight]
      Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
      Default = True
      TabOrder = 10
      OnClick = btnPerformClick
    end
    object eFull: TEdit
      Left = 16
      Top = 18
      Width = 718
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      AutoSelect = False
      TabOrder = 0
    end
    object eOrder: TEdit
      Left = 72
      Top = 260
      Width = 548
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 9
      OnChange = eOrderChange
    end
    object cboxScales: TComboBox
      Left = 126
      Top = 138
      Width = 247
      Height = 25
      AutoComplete = False
      Style = csDropDownList
      DropDownCount = 20
      TabOrder = 4
      OnChange = cboxScalesChange
    end
    object cboxTable: TComboBox
      Left = 72
      Top = 78
      Width = 200
      Height = 25
      AutoComplete = False
      DropDownCount = 20
      TabOrder = 2
      OnChange = cboxTableChange
    end
    object dtpDateFrom: TDateTimePicker
      Left = 146
      Top = 168
      Width = 123
      Height = 25
      Date = 29674.494996238430000000
      Format = 'yyyy-MM-dd'
      Time = 29674.494996238430000000
      TabOrder = 5
      OnChange = dtpDateFromChange
    end
    object dtpDateTo: TDateTimePicker
      Left = 382
      Top = 168
      Width = 123
      Height = 25
      Date = 29674.494996238430000000
      Format = 'yyyy-MM-dd'
      Time = 29674.494996238430000000
      Enabled = False
      TabOrder = 6
      OnChange = dtpDateFromChange
    end
    object cboxFields: TComboBox
      Left = 72
      Top = 48
      Width = 548
      Height = 25
      AutoComplete = False
      AutoCompleteDelay = 100500
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 1
      OnChange = cboxFieldsChange
    end
    object eWhere: TEdit
      Left = 72
      Top = 108
      Width = 548
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      AutoSelect = False
      TabOrder = 3
      OnChange = cboxFieldsChange
    end
    object cboxDateDay: TCheckBox
      Left = 512
      Top = 172
      Width = 97
      Height = 17
      Caption = #1047#1072' '#1089#1091#1090#1082#1080
      Checked = True
      State = cbChecked
      TabOrder = 7
      OnClick = cboxDateDayClick
    end
    object btnClose: TButton
      Left = 638
      Top = 256
      Width = 96
      Height = 32
      Anchors = [akTop, akRight]
      Caption = #1047#1072#1082#1088#1099#1090#1100
      TabOrder = 13
      OnClick = btnCloseClick
    end
    object btnAbout: TButton
      Left = 638
      Top = 208
      Width = 96
      Height = 32
      Anchors = [akTop, akRight]
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
      TabOrder = 12
      OnClick = btnAboutClick
    end
    object btnUnixTime: TButton
      Left = 638
      Top = 96
      Width = 96
      Height = 32
      Anchors = [akTop, akRight]
      Caption = #1070#1085#1080#1082#1089'-'#1074#1088#1077#1084#1103
      TabOrder = 11
      OnClick = btnUnixTimeClick
    end
    object eWhereAdd: TEdit
      Left = 100
      Top = 230
      Width = 520
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 8
      OnChange = cboxScalesChange
    end
    object dtpTimeTo: TDateTimePicker
      Left = 382
      Top = 199
      Width = 123
      Height = 25
      Date = 29674.999988425930000000
      Format = 'HH:mm:ss'
      Time = 29674.999988425930000000
      Enabled = False
      Kind = dtkTime
      TabOrder = 14
      OnChange = dtpDateFromChange
    end
    object dtpTimeFrom: TDateTimePicker
      Left = 146
      Top = 199
      Width = 123
      Height = 25
      Date = 29674.000000000000000000
      Format = 'HH:mm:ss'
      Time = 29674.000000000000000000
      Kind = dtkTime
      TabOrder = 15
      OnChange = dtpDateFromChange
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 536
    Width = 750
    Height = 19
    Panels = <
      item
        Text = #169' '#1055'3'#1090#1088'0'#1074#1080#1063#1098
        Width = 150
      end
      item
        Text = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1079#1072#1087#1080#1089#1077#1081': %d'
        Width = 200
      end
      item
        Text = #1053#1086#1084#1077#1088' '#1079#1072#1087#1080#1089#1080': %d'
        Width = 50
      end>
  end
  object DBNavigator: TDBNavigator
    Left = 0
    Top = 441
    Width = 750
    Height = 25
    DataSource = DataSource
    VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbPost, nbCancel]
    Align = alBottom
    TabOrder = 3
  end
  object pnlBottom: TPanel
    Left = 0
    Top = 466
    Width = 750
    Height = 70
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 4
    object lblServerHost: TLabel
      Left = 16
      Top = 10
      Width = 36
      Height = 17
      Caption = #1040#1076#1088#1077#1089
      FocusControl = cboxServerHost
    end
    object eServerPort: TLabeledEdit
      Left = 144
      Top = 30
      Width = 70
      Height = 25
      EditLabel.Width = 30
      EditLabel.Height = 17
      EditLabel.Caption = #1055#1086#1088#1090
      TabOrder = 0
    end
    object eDataBase: TLabeledEdit
      Left = 220
      Top = 30
      Width = 120
      Height = 25
      EditLabel.Width = 74
      EditLabel.Height = 17
      EditLabel.Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
      TabOrder = 1
    end
    object eUser: TLabeledEdit
      Left = 346
      Top = 30
      Width = 120
      Height = 25
      EditLabel.Width = 85
      EditLabel.Height = 17
      EditLabel.Caption = #1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1100
      TabOrder = 2
    end
    object ePass: TLabeledEdit
      Left = 472
      Top = 30
      Width = 120
      Height = 25
      EditLabel.Width = 46
      EditLabel.Height = 17
      EditLabel.Caption = #1055#1072#1088#1086#1083#1100
      PasswordChar = '#'
      TabOrder = 3
    end
    object cboxPassSave: TCheckBox
      Left = 598
      Top = 33
      Width = 97
      Height = 17
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      TabOrder = 4
    end
    object cboxServerHost: TComboBox
      Left = 16
      Top = 30
      Width = 122
      Height = 25
      TabOrder = 5
      OnChange = cboxServerHostChange
    end
  end
  object ADOConnection: TADOConnection
    LoginPrompt = False
    Left = 56
    Top = 280
  end
  object DataSource: TDataSource
    DataSet = ADODataSet
    OnDataChange = DataSourceDataChange
    Left = 136
    Top = 280
  end
  object ADODataSet: TADODataSet
    Connection = ADOConnection
    AfterScroll = ADODataSetAfterScroll
    Parameters = <>
    Left = 208
    Top = 280
  end
end

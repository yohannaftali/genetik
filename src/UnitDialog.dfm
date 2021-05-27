object FormDialog: TFormDialog
  Left = 0
  Top = 0
  AlphaBlendValue = 200
  BorderStyle = bsDialog
  Caption = 'Genetics Algorithm for Parameter Estimation - Yohan Naftali'
  ClientHeight = 680
  ClientWidth = 641
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  ScreenSnap = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object ButtonPolyOptimasi: TButton
    Left = 8
    Top = 577
    Width = 482
    Height = 57
    Caption = '&Estimate'
    TabOrder = 0
    OnClick = ButtonPolyOptimasiClick
  end
  object ButtonCancelPolyOptimasi: TButton
    Left = 496
    Top = 577
    Width = 137
    Height = 57
    Caption = '&Cancel'
    TabOrder = 1
    OnClick = ButtonCancelPolyOptimasiClick
  end
  object PanelProgress: TPanel
    Left = 0
    Top = 640
    Width = 641
    Height = 40
    Align = alBottom
    BevelOuter = bvLowered
    TabOrder = 2
    object LabelStatus: TLabel
      Left = 16
      Top = 10
      Width = 46
      Height = 13
      Caption = 'Progress:'
    end
    object ProgressBarTotal: TProgressBar
      Left = 72
      Top = 14
      Width = 553
      Height = 9
      Max = 1500
      Smooth = True
      Step = 1
      TabOrder = 0
    end
  end
  object PanelEquation: TPanel
    Left = 0
    Top = 0
    Width = 641
    Height = 42
    Align = alTop
    BevelKind = bkFlat
    BevelOuter = bvLowered
    TabOrder = 3
    object LabelEquation: TLabel
      Left = 96
      Top = 14
      Width = 285
      Height = 13
      Caption = 'Y'#39' = B0 + B1*(X1)^C1 + B2*(X2)^C2 + ... + BN*(XN)^CN '
    end
    object LabelModelPolynomial: TLabel
      Left = 21
      Top = 14
      Width = 46
      Height = 13
      Caption = 'Equation:'
    end
  end
  object PanelVariable: TPanel
    Left = 0
    Top = 42
    Width = 641
    Height = 359
    Align = alTop
    BevelKind = bkFlat
    BevelOuter = bvLowered
    TabOrder = 4
    object LabelDepVar: TLabel
      Left = 336
      Top = 13
      Width = 103
      Height = 13
      Caption = 'Dependent Variables:'
    end
    object LabelIndepVar: TLabel
      Left = 336
      Top = 85
      Width = 112
      Height = 13
      Caption = 'Independent Variables:'
    end
    object LabelVar: TLabel
      Left = 17
      Top = 13
      Width = 47
      Height = 13
      Caption = 'Variables:'
    end
    object ComboBoxVariabelTakBebas: TComboBox
      Left = 336
      Top = 35
      Width = 281
      Height = 21
      DragMode = dmAutomatic
      ItemHeight = 13
      TabOrder = 1
      OnChange = ComboBoxVariabelTakBebasChange
    end
    object ListBoxVariabelBebas: TListBox
      Left = 336
      Top = 104
      Width = 281
      Height = 233
      DragMode = dmAutomatic
      ItemHeight = 13
      MultiSelect = True
      TabOrder = 2
      OnClick = ListBoxVariabelBebasClick
    end
    object ListBoxVariabel: TListBox
      Left = 17
      Top = 35
      Width = 260
      Height = 302
      DragMode = dmAutomatic
      ItemHeight = 13
      MultiSelect = True
      TabOrder = 0
      OnClick = ListBoxVariabelClick
    end
    object BitBtnTambah: TBitBtn
      Left = 289
      Top = 135
      Width = 33
      Height = 33
      TabOrder = 4
      Visible = False
      OnClick = BitBtnTambahClick
      Glyph.Data = {
        36030000424D3603000000000000360000002800000010000000100000000100
        1800000000000003000000000000000000000000000000000000C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C05090
        50305030C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0809080C0
        C0C0C0C0C0C0C0C0C0C0C080B09070C080509050305030C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0809080202020C0C0C0C0C0C0C0C0C0C0C0C090B8
        A060A070C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C080908040
        7850202020C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        809880202820303830304030404840509060407850202020C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C080A090B0E8C070B08070A88060A07060
        987060A870407850202020C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        90A890B0F0C090E0B090D8A080D0A070C09070B88060A870509060607860C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C090B8A0B0F0D0B0F0C0B0E8C0A0E8C0A0
        E0B070C09070B080809880C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        90C0A090B8A090A89080A090809880B0E8C080C890809880C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C080A090A0
        E0C0809880C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C090A890809880C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C090B8A0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0}
      Layout = blGlyphTop
    end
    object BitBtnKurang: TBitBtn
      Left = 289
      Top = 135
      Width = 33
      Height = 33
      TabOrder = 3
      OnClick = BitBtnKurangClick
      Glyph.Data = {
        36030000424D3603000000000000360000002800000010000000100000000100
        18000000000000030000C40E0000C40E00000000000000000000C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C06F80F4C0C0C0C0C0C00020901038B02040
        D06078D0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C06078D031
        49F0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C06078D07983FF6078D0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C06078D03149F05562FF31
        49F06078D03149F06F80F498A4F8C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C06078D03048F03048F01527FF5562FF7983FF979EFFA0A8FF6F80F4C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C01038B01038B02040D03048F0566AF315
        27FF5562FF7983FF979EFF5569F2C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C00020901038B02048F01531EE3149F0566AF33048F07983FF3149F0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C00020901038B02040D000
        20900020900020900020906078D0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C00020901038B06078D0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000209060
        78D0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C06078D0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0}
      Layout = blGlyphTop
    end
  end
  object PanelParameter: TPanel
    Left = 0
    Top = 401
    Width = 641
    Height = 170
    Align = alTop
    BevelKind = bkFlat
    BevelOuter = bvLowered
    TabOrder = 5
    object GroupBox3: TGroupBox
      Left = 16
      Top = 16
      Width = 185
      Height = 105
      Caption = 'Population Parameter'
      TabOrder = 0
      object LabelJumlahPopulasi: TLabel
        Left = 10
        Top = 28
        Width = 87
        Height = 13
        Caption = 'No. of Population:'
      end
      object LabelJumlahGenerasi: TLabel
        Left = 10
        Top = 55
        Width = 90
        Height = 13
        Caption = 'No. of Generation:'
      end
      object EditJumlahPopulasi: TEdit
        Left = 106
        Top = 24
        Width = 65
        Height = 21
        TabOrder = 0
        Text = '80'
      end
      object EditJumlahGenerasi: TEdit
        Left = 106
        Top = 51
        Width = 65
        Height = 21
        TabOrder = 1
        Text = '100000'
      end
    end
    object GroupBox1: TGroupBox
      Left = 207
      Top = 16
      Width = 146
      Height = 105
      Caption = 'Search Space'
      TabOrder = 1
      object LabelRVD: TLabel
        Left = 9
        Top = 28
        Width = 60
        Height = 13
        Caption = 'Upper Limit :'
      end
      object Label6: TLabel
        Left = 9
        Top = 55
        Width = 57
        Height = 13
        Caption = 'Lower Limit:'
      end
      object EditRuangAtas: TEdit
        Left = 75
        Top = 51
        Width = 62
        Height = 21
        TabOrder = 1
        Text = '100'
      end
      object EditRuangBawah: TEdit
        Left = 75
        Top = 24
        Width = 62
        Height = 21
        TabOrder = 0
        Text = '-100'
      end
    end
    object GroupBox2: TGroupBox
      Left = 496
      Top = 16
      Width = 129
      Height = 105
      Caption = 'Mutation Probability'
      TabOrder = 2
      object LabelMutasi1: TLabel
        Left = 14
        Top = 28
        Width = 30
        Height = 13
        Caption = 'Begin:'
      end
      object LabelMutasi2: TLabel
        Left = 14
        Top = 55
        Width = 22
        Height = 13
        Caption = 'End:'
      end
      object EditStartProbMutasi: TEdit
        Left = 50
        Top = 24
        Width = 41
        Height = 21
        TabOrder = 0
        Text = '0.01'
      end
      object EditEndProbMutasi: TEdit
        Left = 50
        Top = 51
        Width = 41
        Height = 21
        TabOrder = 1
        Text = '0.01'
      end
    end
    object CheckBoxBest: TCheckBox
      Left = 17
      Top = 135
      Width = 240
      Height = 17
      Caption = 'Use previous Optimatization Result'
      Checked = True
      State = cbChecked
      TabOrder = 3
    end
    object CheckBoxInteger: TCheckBox
      Left = 216
      Top = 94
      Width = 97
      Height = 17
      Caption = 'Integer Only'
      Checked = True
      State = cbChecked
      TabOrder = 4
    end
    object GroupBox4: TGroupBox
      Left = 359
      Top = 16
      Width = 131
      Height = 105
      Caption = 'Cross Over Probability'
      TabOrder = 5
      object LabelEndProbXO: TLabel
        Left = 14
        Top = 55
        Width = 22
        Height = 13
        Caption = 'End:'
      end
      object LabelStartProbXO: TLabel
        Left = 14
        Top = 28
        Width = 30
        Height = 13
        Caption = 'Begin:'
      end
      object EditStartProbXO: TEdit
        Left = 50
        Top = 24
        Width = 41
        Height = 21
        TabOrder = 0
        Text = '0.45'
      end
      object EditEndProbXO: TEdit
        Left = 50
        Top = 51
        Width = 41
        Height = 21
        TabOrder = 1
        Text = '0.45'
      end
    end
  end
end

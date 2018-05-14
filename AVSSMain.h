// ---------------------------------------------------------------------------

#ifndef AVSSMainH
#define AVSSMainH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>

#include "AVSSTConnectionInfo.h"

// ---------------------------------------------------------------------------
class TMain : public TForm {
__published:
	TDBGrid *DBGrid;
	TPanel *pnlTop;
	TLabel *lblScales;
	TLabel *lblFrom;
	TLabel *lblDate;
	TLabel *lblDateAnd;
	TLabel *lblSelect;
	TLabel *lblWhere;
	TButton *btnPerform;
	TEdit *eFull;
	TEdit *eOrder;
	TComboBox *cboxScales;
	TComboBox *cboxTable;
	TDateTimePicker *dtpDateFrom;
	TDateTimePicker *dtpDateTo;
	TComboBox *cboxFields;
	TEdit *eWhere;
	TCheckBox *cboxDateDay;
	TButton *btnClose;
	TButton *btnAbout;
	TStatusBar *StatusBar;
	TDBNavigator *DBNavigator;
	TPanel *pnlBottom;
	TLabeledEdit *eServerPort;
	TLabeledEdit *eDataBase;
	TLabeledEdit *eUser;
	TLabeledEdit *ePass;
	TCheckBox *cboxPassSave;
	TADOConnection *ADOConnection;
	TDataSource *DataSource;
	TADODataSet *ADODataSet;
	TButton *btnUnixTime;
	TLabel *lblOrder;
	TEdit *eWhereAdd;
	TLabel *lblWhereAdd;
	TDateTimePicker *dtpTimeTo;
	TDateTimePicker *dtpTimeFrom;
	TComboBox *cboxServerHost;
	TLabel *lblServerHost;

	void __fastcall btnCloseClick(TObject *Sender);
	void __fastcall btnAboutClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall cboxFieldsChange(TObject *Sender);
	void __fastcall cboxDateDayClick(TObject *Sender);
	void __fastcall cboxScalesChange(TObject *Sender);
	void __fastcall btnPerformClick(TObject *Sender);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cboxTableChange(TObject *Sender);
	void __fastcall btnUnixTimeClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall DataSourceDataChange(TObject *Sender, TField *Field);
	void __fastcall ADODataSetAfterScroll(TDataSet *DataSet);
	void __fastcall eOrderChange(TObject *Sender);
	void __fastcall dtpDateFromChange(TObject *Sender);
	void __fastcall cboxServerHostChange(TObject *Sender);

private:
	TConnectionInfoList * ConnectionInfoList;

	TStringList * ScaleNamesList;
	TStringList * ScaleTablesList;
	TStringList * TablesList;
	TStringList * FieldsList;
	TStringList * OrderByList;
	TStringList * DateTimeFieldList;

	String Decrypt(String Text);
	String Encrypt(String Text);

	bool MakeInProcess;

	void UpdateRecordCount(int RecordCount);
	void UpdateRecordNo(int RecordNo);

	void UpdateQuery();
	void UpdateWhere();

public:
	__fastcall TMain(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
// ---------------------------------------------------------------------------
#endif

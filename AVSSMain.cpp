// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AVSSMain.h"
#include "AVSSUnixTime.h"

#include "AVSSEncKey.h"

#include "AVSSStrings.h"

#include "AboutFrm.h"

#include "UtilsFileIni.h"
#include "UtilsStr.h"
#include "UtilsMisc.h"
#include "UtilsBase64.h"
#include "UtilsCryptoPP.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMain *Main;

// ---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner) : TForm(Owner) {
	UpdateRecordCount(-1);
	UpdateRecordNo(-1);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnCloseClick(TObject *Sender) {
	Close();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnAboutClick(TObject *Sender) {
	ShowAbout(18, MAXBYTE, MAXBYTE, MAXBYTE, NULL, NULL, NULL, NULL, NULL,
		LoadStr(IDS_COPYRIGHT));
}

// ---------------------------------------------------------------------------
void TMain::UpdateRecordCount(int RecordCount) {
	if (RecordCount > -1) {
		StatusBar->Panels->Items[1]->Text =
			Format(IDS_TEXT_RECORD_COUNT, RecordCount);
	}
	else {
		StatusBar->Panels->Items[1]->Text = "";
	}
}

// ---------------------------------------------------------------------------
void TMain::UpdateRecordNo(int RecordNo) {
	if (RecordNo > 0) {
		StatusBar->Panels->Items[2]->Text =
			Format(IDS_TEXT_RECORD_NUM, RecordNo);
	}
	else {
		StatusBar->Panels->Items[2]->Text = "";
	}
}

// ---------------------------------------------------------------------------
String TMain::Decrypt(String Text) {
	if (IsEmpty(Text)) {
		return "";
	}

	try {
		return DecryptAES(Text, ENC_KEY);
	}
	catch (...) {
		return "";
	}
}

// ---------------------------------------------------------------------------
String TMain::Encrypt(String Text) {
	if (IsEmpty(Text)) {
		return "";
	}

	try {
		return EncryptAES(Text, ENC_KEY);
	}
	catch (...) {
		return "";
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender) {
	ConnectionInfoList = new TConnectionInfoList();

	ScaleNamesList = new TStringList;
	ScaleTablesList = new TStringList;
	TablesList = new TStringList;
	FieldsList = new TStringList;
	OrderByList = new TStringList;
	DateTimeFieldList = new TStringList;

	Caption = Format(IDS_MAIN_CAPTION,
		ARRAYOFCONST((Application->Title, GetFileVer(Application->ExeName))));
	StatusBar->Panels->Items[0]->Text = LoadStr(IDS_COPYRIGHT_STATUS);

	MakeInProcess = true;

	dtpDateFrom->Date = Now();
	dtpDateTo->Date = dtpDateFrom->Date;

	TFileIni * FileIni = TFileIni::GetNewInstance();

	try {
		FileIni->ReadFormBounds(this);

		eWhere->Text = FileIni->ReadString("Query", "Where", "");

		eWhereAdd->Text = FileIni->ReadString("Query", "WhereAdd", "");

		eOrder->Text = FileIni->ReadString("Query", "Order", "");

		cboxServerHost->Text = FileIni->ReadString("Connection", "Host", "");
		eServerPort->Text = FileIni->ReadString("Connection", "Port", "");
		eDataBase->Text = FileIni->ReadString("Connection", "DB", "");
		eUser->Text = FileIni->ReadString("Connection", "User", "");

		cboxPassSave->Checked = FileIni->ReadBool("Connection",
			"PassSave", false);

		ePass->Text = Decrypt(FileIni->ReadString("Connection", "Pass", ""));

		TConnectionInfo * ConnectionInfo;

		String Section;

		int Count = FileIni->ReadInteger("Connections", "Count", 0);

		for (int i = 0; i < Count; i++) {
			Section = "Connection_" + IntToStr(i);

			if (!FileIni->SectionExists(Section)) {
				continue;
			}

			ConnectionInfo = new TConnectionInfo();

			ConnectionInfo->Host = FileIni->ReadString(Section, "Host", "");
			ConnectionInfo->Port = FileIni->ReadString(Section, "Port", "");
			ConnectionInfo->Database =
				FileIni->ReadString("Connection", "DB", "");
			ConnectionInfo->User = FileIni->ReadString(Section, "User", "");
			ConnectionInfo->Password =
				Decrypt(FileIni->ReadString(Section, "Pass", ""));

			ConnectionInfoList->Add(ConnectionInfo);
		}

		for (int i = 0; i < ConnectionInfoList->Count; i++) {
			if (IsEmpty(ConnectionInfoList->Items[i]->Host)) {
				continue;
			}

			cboxServerHost->Items->Add(ConnectionInfoList->Items[i]->Host);
		}

		FileIni->ReadSectionValues("ScaleNames", ScaleNamesList);

		cboxScales->Items->Add("Все");
		for (int i = 0; i < ScaleNamesList->Count; i++) {
			cboxScales->Items->Add(ScaleNamesList->Names[i] + " - " +
				ScaleNamesList->ValueFromIndex[i]);
		}
		ScaleNamesList->Insert(0, "");
		cboxScales->ItemIndex = 0;

		FileIni->ReadSectionValues("ScaleTables", ScaleTablesList);

		FileIni->ReadSectionValues("Tables", TablesList);

		for (int i = 0; i < TablesList->Count; i++) {
			cboxTable->Items->Add(TablesList->Names[i]);
		}

		cboxTable->Text = FileIni->ReadString("Query", "Table", "");

		FileIni->ReadSectionValues("Fields", FieldsList);

		cboxFields->Items->Add("*");
		for (int i = 0; i < FieldsList->Count; i++) {
			String Fields = FieldsList->ValueFromIndex[i];

			if (cboxFields->Items->IndexOf(Fields) < 0) {
				cboxFields->Items->Add(Fields);
			}
		}

		cboxFields->Text = FileIni->ReadString("Query", "Fields", "");

		FileIni->ReadSectionValues("OrderBy", OrderByList);
		FileIni->ReadSectionValues("DateTimeField", DateTimeFieldList);
	}
	__finally {
		delete FileIni;
	}

	MakeInProcess = false;

	UpdateQuery();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormDestroy(TObject * Sender) {
	TFileIni * FileIni = TFileIni::GetNewInstance();

	try {
		FileIni->WriteFormBounds(this);

		FileIni->WriteString("Query", "Fields", cboxFields->Text);
		FileIni->WriteString("Query", "Table", cboxTable->Text);
		FileIni->WriteString("Query", "Where", eWhere->Text);
		FileIni->WriteString("Query", "WhereAdd", eWhereAdd->Text);
		FileIni->WriteString("Query", "Order", eOrder->Text);

		FileIni->WriteString("Connection", "Host", cboxServerHost->Text);
		FileIni->WriteString("Connection", "Port", eServerPort->Text);
		FileIni->WriteString("Connection", "DB", eDataBase->Text);
		FileIni->WriteString("Connection", "User", eUser->Text);

		FileIni->WriteBool("Connection", "PassSave", cboxPassSave->Checked);
		if (cboxPassSave->Checked) {
			FileIni->WriteString("Connection", "Pass", Encrypt(ePass->Text));
		}
		else {
			FileIni->WriteString("Connection", "Pass", "");
		}
	}
	__finally {
		delete FileIni;
	}

	DateTimeFieldList->Free();
	OrderByList->Free();
	FieldsList->Free();
	TablesList->Free();
	ScaleTablesList->Free();
	ScaleNamesList->Free();

	ConnectionInfoList->Free();
}

// ---------------------------------------------------------------------------
void TMain::UpdateQuery() {
	if (MakeInProcess) {
		return;
	}

	String Select, From, Where, Order;

	if (!IsEmpty(cboxFields->Text)) {
		Select = cboxFields->Text;
	}
	else {
		Select = "*";
	}

	Select = ConcatStrings("SELECT", Select, SPACE);

	if (!IsEmpty(cboxTable->Text)) {
		From = ConcatStrings("FROM", cboxTable->Text, SPACE);
	}
	if (!IsEmpty(eWhere->Text)) {
		Where = ConcatStrings("WHERE", eWhere->Text, SPACE);
	}
	if (!IsEmpty(eOrder->Text)) {
		Order = ConcatStrings("ORDER BY", eOrder->Text, SPACE);
	}

	eFull->Text = ConcatStrings(ConcatStrings(ConcatStrings(Select, From,
		SPACE), Where, SPACE), Order, SPACE);
}

// ---------------------------------------------------------------------------
void TMain::UpdateWhere() {
	MakeInProcess = true;

	String Where;

	if (cboxScales->ItemIndex == 0) {
		Where = "";
	}
	else {
		if (ScaleNamesList->Count > 0) {
			Where = "scales=" + ScaleNamesList->Names[cboxScales->ItemIndex];
		}
	}

	String DateTimeField =
		DateTimeFieldList->ValueFromIndex[DateTimeFieldList->IndexOfName
		("default")];

	if (cboxTable->ItemIndex > -1) {
		int DateTimeFieldIndex =
			DateTimeFieldList->IndexOfName
			(cboxTable->Items->Strings[cboxTable->ItemIndex]);

		if (DateTimeFieldIndex > -1) {
			DateTimeField =
				DateTimeFieldList->ValueFromIndex[DateTimeFieldIndex];
		}
	}

	if (!IsEmpty(DateTimeField)) {
		if (cboxDateDay->Checked) {
			dtpDateTo->Date = dtpDateFrom->Date;
			dtpTimeTo->Time = StrToTime("23:59:59");
		}

		dtpDateFrom->Time = dtpTimeFrom->Time;
		dtpDateTo->Time = dtpTimeTo->Time;

		String D1, D2;

		DateTimeToString(D1, "yyyy-MM-dd HH:mm:ss", dtpDateFrom->DateTime);
		DateTimeToString(D2, "yyyy-MM-dd HH:mm:ss", dtpDateTo->DateTime);

		D1 = "\"" + D1 + "\"";
		D2 = "\"" + D2 + "\"";

		Where = ConcatStrings(Where, DateTimeField + ">=" + D1 + " and " +
			DateTimeField + "<=" + D2, " and ");
	}

	Where = ConcatStrings(Where, eWhereAdd->Text, " and ");

	eWhere->Text = Where;

	MakeInProcess = false;

	UpdateQuery();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::cboxFieldsChange(TObject * Sender) {
	if (MakeInProcess) {
		return;
	}

	UpdateQuery();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::cboxTableChange(TObject * Sender) {
	if (MakeInProcess) {
		return;
	}

	MakeInProcess = true;

	if (cboxTable->ItemIndex > -1) {
		String TableName = TablesList->Names[cboxTable->ItemIndex];

		String FieldsName = TablesList->ValueFromIndex[cboxTable->ItemIndex];

		if (!IsEmpty(FieldsName)) {
			String Fields =
				FieldsList->ValueFromIndex[FieldsList->IndexOfName(FieldsName)];

			if (!IsEmpty(Fields)) {
				cboxFields->Text = Fields;
			}
		}

		String OrderBy =
			OrderByList->ValueFromIndex[OrderByList->IndexOfName("default")];

		int OrderByNameIndex = OrderByList->IndexOfName(TableName);
		if (OrderByNameIndex > -1) {
			OrderBy = OrderByList->ValueFromIndex[OrderByNameIndex];

		}

		eOrder->Text = OrderBy;
	}

	MakeInProcess = false;

	UpdateWhere();

	UpdateQuery();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::cboxDateDayClick(TObject * Sender) {
	if (MakeInProcess) {
		return;
	}

	dtpDateTo->Enabled = !cboxDateDay->Checked;
	dtpTimeTo->Enabled = dtpDateTo->Enabled;

	cboxScalesChange(Sender);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::cboxScalesChange(TObject * Sender) {
	if (MakeInProcess) {
		return;
	}

	MakeInProcess = true;

	if (cboxScales->ItemIndex > -1) {
		String ScaleNum = ScaleNamesList->Names[cboxScales->ItemIndex];
		String TableName =
			ScaleTablesList->ValueFromIndex[ScaleTablesList->IndexOfName
			(ScaleNum)];

		if (!IsEmpty(TableName)) {
			int Index = cboxTable->Items->IndexOf(TableName);

			if (Index > -1) {
				cboxTable->ItemIndex = Index;
				cboxTableChange(this);
			}
		}
	}

	MakeInProcess = false;

	UpdateWhere();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormKeyUp(TObject * Sender, WORD & Key,
	TShiftState Shift) {
	if (Shift.Empty() && (Key == VK_F9)) {
		btnPerform->Click();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnPerformClick(TObject * Sender) {
	ShowWaitCursor();

	UpdateRecordCount(-1);
	UpdateRecordNo(-1);

	try {
		ADOConnection->Close();

		ADOConnection->ConnectionString =
			Format(IDS_MYSQL_CONNECTION,
			ARRAYOFCONST((cboxServerHost->Text, eServerPort->Text,
			eDataBase->Text, eUser->Text, ePass->Text)));

		ADOConnection->Open();

		ADODataSet->Close();
		ADODataSet->CommandText = eFull->Text;
		ADODataSet->Open();
	}
	__finally {
		RestoreCursor();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnUnixTimeClick(TObject * Sender) {
	frmUnixTime->Visible = !frmUnixTime->Visible;
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormShow(TObject * Sender) {
	// frmUnixTime->Show();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::DataSourceDataChange(TObject * Sender, TField * Field) {
	UpdateRecordCount(ADODataSet->RecordCount);
	UpdateRecordNo(-1);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::ADODataSetAfterScroll(TDataSet * DataSet) {
	UpdateRecordNo(ADODataSet->RecNo);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::eOrderChange(TObject * Sender) {
	if (MakeInProcess) {
		return;
	}

	UpdateQuery();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::dtpDateFromChange(TObject * Sender) {
	if (MakeInProcess) {
		return;
	}

	UpdateWhere();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::cboxServerHostChange(TObject * Sender) {
	if (MakeInProcess) {
		return;
	}

	if (cboxServerHost->ItemIndex < 0) {
		return;
	}

	for (int i = 0; i < ConnectionInfoList->Count; i++) {
		if (ConnectionInfoList->Items[i]->Host == cboxServerHost->Text) {
			eServerPort->Text = ConnectionInfoList->Items[i]->Port;
			eDataBase->Text = ConnectionInfoList->Items[i]->Database;
			eUser->Text = ConnectionInfoList->Items[i]->User;
			ePass->Text = ConnectionInfoList->Items[i]->Password;
		}
	}
}
// ---------------------------------------------------------------------------

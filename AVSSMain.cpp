// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AVSSMain.h"
#include "AVSSUnixTime.h"

#include "AboutFrm.h"
#include "UtilsFileIni.h"
#include "UtilsStr.h"
#include "UtilsMisc.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMain *Main;

// ---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnCloseClick(TObject *Sender) {
	Close();
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnAboutClick(TObject *Sender) {
	ShowAbout(18);
}

// ---------------------------------------------------------------------------
String EncryptDecrypt(String S) {
	Char key[3] = {'V', 'Y', 'P'};
	String output = S;

	for (int i = 1; i <= S.Length(); i++) {
		output[i] = S[i] ^ key[i % (sizeof(key) / sizeof(Char))];
	}

	return output;
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject *Sender) {
	ScaleNamesList = new TStringList;
	ScaleTablesList = new TStringList;
	TablesList = new TStringList;
	FieldsList = new TStringList;

	dtpDateFrom->DateTime = Now();
	dtpDateTo->DateTime = dtpDateFrom->DateTime + 1;

	TFileIni* FileIni = TFileIni::GetNewInstance();

	try {
		FileIni->ReadFormBounds(this);

		eWhere->Text = FileIni->ReadString("Query", "Where", "");
		eOrder->Text = FileIni->ReadString("Query", "Order", "");

		eServerIP->Text = FileIni->ReadString("Connection", "IP", "");
		eServerPort->Text = FileIni->ReadString("Connection", "Port", "");
		eDataBase->Text = FileIni->ReadString("Connection", "DB", "");
		eUser->Text = FileIni->ReadString("Connection", "User", "");

		cboxPassSave->Checked = FileIni->ReadBool("Connection",
			"PassSave", false);

		ePass->Text = EncryptDecrypt(FileIni->ReadString("Connection",
			"Pass", ""));

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
			cboxFields->Items->Add(FieldsList->ValueFromIndex[i]);
		}

		cboxFields->Text = FileIni->ReadString("Query", "Fields", "");
	}
	__finally {
		delete FileIni;
	}

	cboxFieldsChange(this);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormDestroy(TObject *Sender) {
	TFileIni* FileIni = TFileIni::GetNewInstance();

	try {
		FileIni->WriteFormBounds(this);

		FileIni->WriteString("Query", "Fields", cboxFields->Text);
		FileIni->WriteString("Query", "Table", cboxTable->Text);
		FileIni->WriteString("Query", "Where", eWhere->Text);
		FileIni->WriteString("Query", "Order", eOrder->Text);

		FileIni->WriteString("Connection", "IP", eServerIP->Text);
		FileIni->WriteString("Connection", "Port", eServerPort->Text);
		FileIni->WriteString("Connection", "DB", eDataBase->Text);
		FileIni->WriteString("Connection", "User", eUser->Text);

		FileIni->WriteBool("Connection", "PassSave", cboxPassSave->Checked);
		if (cboxPassSave->Checked) {
			FileIni->WriteString("Connection", "Pass",
				EncryptDecrypt(ePass->Text));
		}
		else {
			FileIni->WriteString("Connection", "Pass", "");
		}
	}
	__finally {
		delete FileIni;
	}

	delete FieldsList;
	delete TablesList;
	delete ScaleTablesList;
	delete ScaleNamesList;
}

// ---------------------------------------------------------------------------
void __fastcall TMain::cboxFieldsChange(TObject *Sender) {
	String ASelect, AFrom, AWhere, AOrder;

	if (cboxFields->Text != "") {
		ASelect = cboxFields->Text;
	}
	else {
		ASelect = "*";
	}

	ASelect = ConcatStrings("SELECT", ASelect, SPACE);

	if (cboxTable->Text != "") {
		AFrom = ConcatStrings("FROM", cboxTable->Text, SPACE);
	}
	if (eWhere->Text != "") {
		AWhere = ConcatStrings("WHERE", eWhere->Text, SPACE);
	}
	if (eOrder->Text != "") {
		AOrder = ConcatStrings("ORDER BY", eOrder->Text, SPACE);
	}

	eFull->Text = ConcatStrings(ConcatStrings(ConcatStrings(ASelect, AFrom,
		SPACE), AWhere, SPACE), AOrder, SPACE);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::cboxTableChange(TObject *Sender) {
	if (cboxTable->ItemIndex > -1) {
		String FieldsName = TablesList->ValueFromIndex[cboxTable->ItemIndex];

		if (!FieldsName.IsEmpty()) {
			String Fields =
				FieldsList->ValueFromIndex[FieldsList->IndexOfName(FieldsName)];

			if (!Fields.IsEmpty()) {
				cboxFields->Text = Fields;
			}
		}
	}

	cboxFieldsChange(this);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::cboxDateDayClick(TObject *Sender) {
	dtpDateTo->Enabled = !cboxDateDay->Checked;
	cboxScalesChange(this);
}

// ---------------------------------------------------------------------------
void __fastcall TMain::cboxScalesChange(TObject *Sender) {
	if (cboxScales->ItemIndex > -1) {
		String ScaleNum = ScaleNamesList->Names[cboxScales->ItemIndex];
		String TableName =
			ScaleTablesList->ValueFromIndex[ScaleTablesList->IndexOfName
			(ScaleNum)];

		if (!TableName.IsEmpty()) {
			int Index = cboxTable->Items->IndexOf(TableName);
			if (Index > -1) {
				cboxTable->ItemIndex = Index;
				cboxTableChange(this);
			}
		}
	}

	String S, D1, D2;

	if (cboxScales->ItemIndex == 0) {
		S = "";
	}
	else {
		S = "scales=" + ScaleNamesList->Names[cboxScales->ItemIndex];
	}

	if (cboxDateDay->Checked) {
		dtpDateTo->DateTime = dtpDateFrom->DateTime + 1;
	}

	DateTimeToString(D1, "yyyyMMdd000000", dtpDateFrom->Date);
	DateTimeToString(D2, "yyyyMMdd000000", dtpDateTo->Date);

	S = ConcatStrings(S, "bdatetime>=" + D1 + " and bdatetime<" + D2, " and ");

	eWhere->Text = S;
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Shift.Empty() && (Key == VK_F9)) {
		btnPerform->Click();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnPerformClick(TObject *Sender) {
	ShowWaitCursor();

	try {
		ADOConnection->Close();

		ADOConnection->ConnectionString =
			Format("DRIVER={MySQL ODBC 3.51 Driver}; SERVER=%s; PORT=%s; DATABASE=%s; USER=%s; PASSWORD=%s; OPTION=3;",
			ARRAYOFCONST((eServerIP->Text, eServerPort->Text, eDataBase->Text,
			eUser->Text, ePass->Text)));

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
void __fastcall TMain::btnUnixTimeClick(TObject *Sender) {
	frmUnixTime->Visible = !frmUnixTime->Visible;
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormShow(TObject *Sender) {
	// frmUnixTime->Show();
}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#pragma hdrstop

#include "AVSSUnixTime.h"

#include "UtilsMisc.h"
#include "UtilsStr.h"
#include "UtilsFileIni.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmUnixTime *frmUnixTime;

// ---------------------------------------------------------------------------
__fastcall TfrmUnixTime::TfrmUnixTime(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TfrmUnixTime::FormCreate(TObject *Sender) {
	TFileIni* FileIni = TFileIni::GetNewInstance();

	try {
		FileIni->ReadFormPosition(this);
	}
	__finally {
		delete FileIni;
	}

	eDateTimeWin->Tag = etWin;
	eDateTimeSQL->Tag = etSQL;
	eUnixTime->Tag = etUnix;

	SelfChange = false;

	eDateTimeWin->Text = DateTimeToStr(Now());
}

// ---------------------------------------------------------------------------
void __fastcall TfrmUnixTime::FormDestroy(TObject *Sender) {
	TFileIni* FileIni = TFileIni::GetNewInstance();

	try {
		FileIni->WriteFormPosition(this);
	}
	__finally {
		delete FileIni;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmUnixTime::FormKeyPress(TObject *Sender,
	System::WideChar &Key)

{
	if (Key == 27) {
		Key = 0;
		Close();
	}
}

static String DTToSQLStr(TDateTime ADateTime) {
	return FormatDateTime("yyyy'-'mm'-'dd' 'hh':'nn':'ss", ADateTime);
}

static TDateTime SQLStrToDT(String ASQLDateTime) {
	if (IsEmpty(ASQLDateTime)) {
		throw EConvertError("Bad format");
	}

	String Year, Month, Day, Hour, Min, Sec;

	if (ASQLDateTime.Length() == 14) { // YYYYMMDDHHMMSS
		Year = ASQLDateTime.SubString(1, 4);
		Month = ASQLDateTime.SubString(5, 2);
		Day = ASQLDateTime.SubString(7, 2);
		Hour = ASQLDateTime.SubString(9, 2);
		Min = ASQLDateTime.SubString(11, 2);
		Sec = ASQLDateTime.SubString(13, 2);
	}
	else {
		if (ASQLDateTime.Length() == 19) { // YYYY-MM-DD HH:MM:SS
			SplitStr(ASQLDateTime, '-', 0, Year, ASQLDateTime);
			SplitStr(ASQLDateTime, '-', 0, Month, ASQLDateTime);
			SplitStr(ASQLDateTime, ' ', 0, Day, ASQLDateTime);
			SplitStr(ASQLDateTime, ':', 0, Hour, ASQLDateTime);
			SplitStr(ASQLDateTime, ':', 0, Min, Sec);

			Year = Trim(Year);
			Month = Trim(Month);
			Day = Trim(Day);
			Hour = Trim(Hour);
			Min = Trim(Min);
			Sec = Trim(Sec);
		}
		else {
			throw EConvertError("Bad format");
		}
	}

	if (Year.Length() != 4 || Month.Length() != 2 || Day.Length() != 2 ||
		Hour.Length() != 2 || Min.Length() != 2 || Sec.Length() != 2) {
		throw EConvertError("Bad format");
	}

	return EncodeDateTime(StrToInt(Year), StrToInt(Month), StrToInt(Day),
		StrToInt(Hour), StrToInt(Min), StrToInt(Sec), 0);
}

static int DTToWTime(TDateTime ADateTime) {
	return int(DateTimeToUnix(IncHour(ADateTime, -3)));
}

static TDateTime WTimeToDT(int AWTime) {
	return IncHour(UnixToDateTime(AWTime), 3);
}

static void LabeledEditSetError(TLabeledEdit * LabeledEdit, bool HasError) {
	LabeledEdit->Font->Color = HasError ? clRed : clWindowText;
	LabeledEdit->EditLabel->Font->Color = LabeledEdit->Font->Color;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmUnixTime::eDateTimeWinChange(TObject *Sender) {
	if (SelfChange) {
		return;
	}

	SelfChange = true;
	try {
		TLabeledEdit *AEdit = dynamic_cast<TLabeledEdit*>(Sender);

		LabeledEditSetError(eDateTimeWin, false);
		LabeledEditSetError(eDateTimeSQL, false);
		LabeledEditSetError(eUnixTime, false);

		String Value = AEdit->Text;

		TDateTime DT;

		try {
			switch (AEdit->Tag) {
			case etWin:
				DT = StrToDateTime(Value);

				eDateTimeSQL->Text = DTToSQLStr(DT);
				eUnixTime->Text = DTToWTime(DT);
				break;
			case etSQL:
				DT = SQLStrToDT(Value);

				eDateTimeWin->Text = DateTimeToStr(DT);
				eUnixTime->Text = DTToWTime(DT);
				break;
			case etUnix:
				DT = WTimeToDT(StrToInt(Value));

				eDateTimeWin->Text = DateTimeToStr(DT);
				eDateTimeSQL->Text = DTToSQLStr(DT);
				break;
			}
		}
		catch (...) {
			LabeledEditSetError(AEdit, true);
		}
	}
	__finally {
		SelfChange = false;
	}
}
// ---------------------------------------------------------------------------

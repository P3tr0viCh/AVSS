// ---------------------------------------------------------------------------

#ifndef AVSSUnixTimeH
#define AVSSUnixTimeH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

enum TEditTag {
	etWin, etSQL, etUnix
};

// ---------------------------------------------------------------------------
class TfrmUnixTime : public TForm {
__published:
	TLabeledEdit *eDateTimeWin;
	TLabeledEdit *eDateTimeSQL;
	TLabeledEdit *eUnixTime;

	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall eDateTimeWinChange(TObject *Sender);
	void __fastcall eDateTimeWinSubLabelMouseDown(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y);

private:
	bool SelfChange;

public:
	__fastcall TfrmUnixTime(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmUnixTime *frmUnixTime;
// ---------------------------------------------------------------------------
#endif

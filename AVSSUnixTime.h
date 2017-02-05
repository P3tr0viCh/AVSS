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
__published: // IDE-managed Components

	TLabeledEdit *eDateTimeWin;
	TLabeledEdit *eDateTimeSQL;
	TLabeledEdit *eUnixTime;

	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall eDateTimeWinChange(TObject *Sender);

private: // User declarations

	bool SelfChange;

public: // User declarations

	__fastcall TfrmUnixTime(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmUnixTime *frmUnixTime;
// ---------------------------------------------------------------------------
#endif

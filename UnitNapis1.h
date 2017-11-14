//---------------------------------------------------------------------------
#ifndef UnitNapis1H
#define UnitNapis1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormNapisy : public TForm
{
__published:	// IDE-managed Components
        TLabel *LabelNapis1;
        TLabel *LabelNapis2;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TFormNapisy(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormNapisy *FormNapisy;
//---------------------------------------------------------------------------
#endif

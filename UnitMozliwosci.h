//---------------------------------------------------------------------------
#ifndef UnitMozliwosciH
#define UnitMozliwosciH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormMozliwosci : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TPanel *Panel1;
        TMemo *Memo1;
        TLabel *LabelTytul;
        TLabel *Label1;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMozliwosci(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMozliwosci *FormMozliwosci;
//---------------------------------------------------------------------------
#endif

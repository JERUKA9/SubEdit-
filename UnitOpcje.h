//---------------------------------------------------------------------------
#ifndef UnitOpcjeH
#define UnitOpcjeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormOpcje : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TButton *Button2;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TTabSheet *TabSheet3;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormOpcje(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOpcje *FormOpcje;
//---------------------------------------------------------------------------
#endif

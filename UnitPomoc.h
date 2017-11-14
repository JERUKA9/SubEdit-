//---------------------------------------------------------------------------
#ifndef UnitPomocH
#define UnitPomocH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormPomoc : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TRichEdit *RichEdit;
        TRichEdit *RichEdit2;
        TTabSheet *TabSheet3;
        TRichEdit *RichEdit1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall RichEditSelectionChange(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormPomoc(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPomoc *FormPomoc;
//---------------------------------------------------------------------------
#endif

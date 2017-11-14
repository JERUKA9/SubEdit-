//---------------------------------------------------------------------------
#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormInformacje : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label6;
        TButton *Button1;
        TLabel *Label7;
        TPanel *Panel1;
        TLabel *LabelDate;
        TLabel *LabelTytul;
        TLabel *LabelVersion;
        TPanel *Panel2;
        TLabel *Label3;
        TLabel *Label5;
        TLabel *Label8;
        TPanel *Panel3;
        TLabel *Label12;
        TPanel *Panel4;
        TLabel *Label1;
        TLabel *Label4;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Label4Click(TObject *Sender);
        void __fastcall Label8Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormInformacje(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormInformacje *FormInformacje;
//---------------------------------------------------------------------------
#endif

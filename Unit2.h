//---------------------------------------------------------------------------
#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormPytanie : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TButton *Button2;
        TPanel *Panel1;
        TLabel *Label1;
        TPanel *Panel2;
        TEdit *EditFrm;
        TLabel *Label2;
        TCheckBox *CheckBoxTo;
        TCheckBox *CheckBoxFrom;
        TPanel *Panel3;
        TCheckBox *CheckBoxOverwrite;
        TCheckBox *CheckBoxNa100;
        TCheckBox *CheckBoxNieWieksze;
        TEdit *EditShowFrm;
        TLabel *Label3;
        TComboBox *ComboBoxFps;
        TPanel *Panel4;
        TLabel *Label4;
        TEdit *EditGotoFrm;
        TLabel *Label5;
        TLabel *LabelMaxFrm;
        TGroupBox *GroupBoxTime;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TLabel *Label6;
        TLabel *LabelFps;
        TPanel *Panel5;
        TLabel *Label8;
        TLabel *LabelFps2;
        TGroupBox *GroupBox1;
        TComboBox *ComboBoxFpsAct;
        TLabel *Label7;
        TComboBox *ComboBoxFpsDest;
        TLabel *Label9;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormPytanie(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPytanie *FormPytanie;
//---------------------------------------------------------------------------
#endif

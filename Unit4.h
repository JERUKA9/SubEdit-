//---------------------------------------------------------------------------
#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include "CSPIN.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormUstawienia : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TButton *Button2;
        TGroupBox *GroupBox4;
        TGroupBox *GroupBox1;
        TCheckBox *CheckBoxOgniskoNaRichEdit;
        TEdit *EditSzybkoscReakcji;
        TLabel *Label1;
        TCheckBox *CheckBoxKoncowaReakcja;
        TCheckBox *CheckBoxReakcjaPrzyOpoznieniu;
        TCheckBox *CheckBoxAutoPlay;
        TGroupBox *GroupBox2;
        TCheckBox *CheckBoxAutoSub;
        TGroupBox *GroupBox3;
        TCheckBox *CheckBoxToolBar;
        TLabel *Label2;
        TEdit *EditEditorFontSize;
        TLabel *Label3;
        TTreeView *TreeView1;
        TEdit *EditDlugoscWyswietlaniaNapisu;
        TLabel *Label6;
        TBevel *Bevel1;
        TEdit *Edit1;
        TLabel *Label4;
        TEdit *Edit2;
        TLabel *Label5;
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall TreeView1Change(TObject *Sender, TTreeNode *Node);
        void __fastcall FormCreate(TObject *Sender);
private:
	//Powoduje, ¿e wszystkie sekcje ustawieñ s¹ niewidoczne.
        void __fastcall UnvisibleAreas();
        //Tak ustawia obszar tematyczny opcji, zawarty wewn¹trz komponentu
        //GroupBox, aby wypelnial cale okno - wysokosc taka jak TreeView.
        void __fastcall DesignComponents(TGroupBox *GroupBox);
public:		// User declarations
        __fastcall TFormUstawienia(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormUstawienia *FormUstawienia;
//---------------------------------------------------------------------------
#endif

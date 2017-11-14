//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitPomoc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPomoc *FormPomoc;
//---------------------------------------------------------------------------
__fastcall TFormPomoc::TFormPomoc(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormPomoc::Button1Click(TObject *Sender)
{
  ModalResult = 1;
}
//---------------------------------------------------------------------------
void __fastcall TFormPomoc::RichEditSelectionChange(TObject *Sender)
{
  if (RichEdit->SelLength>0)
    RichEdit->SelLength = 0;
}
//---------------------------------------------------------------------------
// event on show
void __fastcall TFormPomoc::FormShow(TObject *Sender)
{//
  PageControl1->ActivePage = TabSheet1;
}
//---------------------------------------------------------------------------





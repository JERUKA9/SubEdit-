//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitMozliwosci.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMozliwosci *FormMozliwosci;
//---------------------------------------------------------------------------
__fastcall TFormMozliwosci::TFormMozliwosci(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMozliwosci::Button1Click(TObject *Sender)
{
  ModalResult = mrCancel;        
}
//---------------------------------------------------------------------------

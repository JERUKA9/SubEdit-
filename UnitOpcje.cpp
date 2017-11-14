//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitOpcje.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormOpcje *FormOpcje;
//---------------------------------------------------------------------------
__fastcall TFormOpcje::TFormOpcje(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormOpcje::FormShow(TObject *Sender)
{
  Left = Screen->Width / 2 - Width / 2;
  Top = Screen->Height / 2 - Height / 2;
}
//---------------------------------------------------------------------------
void __fastcall TFormOpcje::Button1Click(TObject *Sender)
{
  ModalResult = mrOk;        
}
//---------------------------------------------------------------------------
void __fastcall TFormOpcje::Button2Click(TObject *Sender)
{
  ModalResult = mrCancel;        

}
//---------------------------------------------------------------------------

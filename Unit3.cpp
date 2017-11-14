//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormInformacje *FormInformacje;
//---------------------------------------------------------------------------
__fastcall TFormInformacje::TFormInformacje(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormInformacje::Button1Click(TObject *Sender)
{
  ModalResult = 1;
}
//---------------------------------------------------------------------------
#include <stdlib.h>
// uruchami adomyslny program pocztowy
void __fastcall TFormInformacje::Label8Click(TObject *Sender)
{
  ShellExecute(Handle, "open", "mailto:artur@alfa.imi.pcz.czest.pl", "", "", SW_NORMAL);
}
//---------------------------------------------------------------------------
// uruchami adomyslna przegladarke
void __fastcall TFormInformacje::Label4Click(TObject *Sender)
{
  ShellExecute(Handle, "open", "http://alfa.imi.pcz.czest.pl/~artur", "", "", SW_NORMAL);
}
//---------------------------------------------------------------------------


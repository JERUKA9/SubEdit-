//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPytanie *FormPytanie;
//---------------------------------------------------------------------------
__fastcall TFormPytanie::TFormPytanie(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
#include <stdlib.h>
// Wcisnieto OK
void __fastcall TFormPytanie::Button1Click(TObject *Sender)
{
  if (Panel1->Visible) // czas-->klatka  klatka-->czas
  {
    float fps = atof (ComboBoxFpsAct->Text.c_str());
    if (fps<=0)
    {
      Application->MessageBox ("Nieprawid³owa iloœæ klatek na sekundê", "Ostrze¿enie", 48);
      ComboBoxFps->SetFocus();
      return;
    }
    ModalResult = mrOk;
  }
  if (Panel2->Visible) // dodaj/odejmij klatki
  {
    int ile = StrToInt(FormPytanie->EditFrm->Text);
    if (ile==0)
    { Application->MessageBox("Zerowa wartoœæ przesuniêcia","Ostrze¿enie", 48);
      EditFrm->SetFocus();
      return;
    }
    if ( (!FormPytanie->CheckBoxFrom->Checked) && (!FormPytanie->CheckBoxTo->Checked) )
    { Application->MessageBox("Nie ma czego przesuwaæ", "Ostrze¿enie", 48);
      CheckBoxFrom->SetFocus();
      return;
    }
    ModalResult = mrOk;
  }
  if (Panel3->Visible) // czas wyswietlania tekstu
  {
    int ile = StrToInt(FormPytanie->EditShowFrm->Text);
    if (ile<=0)
    { Application->MessageBox("Nieprawid³owa iloœæ klatek","Ostrze¿enie", 48);
      EditShowFrm->SetFocus();
      return;
    }
    ModalResult = mrOk;
  }
  if (Panel4->Visible) // skok do wybranej klatki filmu
  {
    int ile = StrToInt(FormPytanie->EditGotoFrm->Text);
    if (ile<0)
    { Application->MessageBox("Nieprawid³owa wartoœæ klatki","Ostrze¿enie", 48);
      EditGotoFrm->SetFocus();
      return;
    }
    ModalResult = mrOk;
  }
  if (Panel5->Visible) // Zmiana ilosci klatek na sekunde
  {
    float fpsact  = atof (ComboBoxFpsAct->Text.c_str());
    float fpsdest = atof (ComboBoxFpsDest->Text.c_str());
    if (fpsact<=0)
    {
      Application->MessageBox ("Nieprawid³owa iloœæ klatek na sekundê", "Ostrze¿enie", 48);
      ComboBoxFpsAct->SetFocus();
      return;
    }
    if (fpsdest<=0)
    {
      Application->MessageBox ("Nieprawid³owa iloœæ klatek na sekundê", "Ostrze¿enie", 48);
      ComboBoxFpsDest->SetFocus();
      return;
    }
    if (fpsdest==fpsact)
    {
      Application->MessageBox ("Równe wartoœci! Nie ma czego zamieniaæ", "Ostrze¿enie", 48);
      ComboBoxFpsAct->SetFocus();
      return;
    }
    ModalResult = mrOk;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPytanie::Button2Click(TObject *Sender)
{
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TFormPytanie::FormCreate(TObject *Sender)
{
  Width = 204;
  Height = 200;
  Panel1->Left = 5;
  Panel1->Top  = 5;
  Panel2->Left = 5;
  Panel2->Top  = 5;
  Panel3->Left = 5;
  Panel3->Top  = 5;
  Panel4->Left = 5;
  Panel4->Top  = 5;
  Panel5->Left = 5;
  Panel5->Top  = 5;
}
//---------------------------------------------------------------------------

void __fastcall TFormPytanie::FormShow(TObject *Sender)
{
  if (Panel1->Visible) // czas-->klatka  klatka-->czas
  {
      RadioButton1->Enabled = FormPytanie->GroupBoxTime->Enabled;
      RadioButton2->Enabled = FormPytanie->GroupBoxTime->Enabled;
      RadioButton3->Enabled = FormPytanie->GroupBoxTime->Enabled;
      FormPytanie->ComboBoxFps->SetFocus();
      FormPytanie->ComboBoxFps->SelectAll();
  }
  if (Panel2->Visible) // dodaj/odejmij klatki
  {
      FormPytanie->EditFrm->SetFocus();
      FormPytanie->EditFrm->SelectAll();
  }
  if (Panel3->Visible) // czas wyswietlania tekstu
  {
      FormPytanie->EditShowFrm->SetFocus();
      FormPytanie->EditShowFrm->SelectAll();
  }
  if (Panel4->Visible) // skok do wybranej klatki filmu
  {
      FormPytanie->EditGotoFrm->SetFocus();
      FormPytanie->EditGotoFrm->SelectAll();
  }
  if (Panel5->Visible) // skok do wybranej klatki filmu
  {
      FormPytanie->ComboBoxFpsAct->SetFocus();
      FormPytanie->ComboBoxFpsAct->SelectAll();
  }
}
//---------------------------------------------------------------------------



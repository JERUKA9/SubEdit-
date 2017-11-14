//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
// #pragma link "CSPIN"
#pragma resource "*.dfm"
TFormUstawienia *FormUstawienia;

//---------------------------------------------------------------------------
// Metody u¿ytkownika
//---------------------------------------------------------------------------

//---private

void __fastcall TFormUstawienia::UnvisibleAreas()
{
  GroupBox1->Visible = False;
  GroupBox2->Visible = False;
  GroupBox3->Visible = False;
  GroupBox4->Visible = False;
}

void __fastcall TFormUstawienia::DesignComponents(TGroupBox *GroupBox)
{
  //Szerokosc okna glownego.
//  Width = 600;
  GroupBox->Width = ClientWidth - TreeView1->Width - 15;
  GroupBox->Height = TreeView1->Height;
  GroupBox->Left = TreeView1->Left + TreeView1->Width + 5;
  GroupBox->Top = TreeView1->Top;
  //Rozmieszczenie przyciskow.
  Button2->Left = ClientWidth - Button2->Width - 10;
  Button2->Top = TreeView1->Top + TreeView1->Height + 5;
  Button1->Left = Button2->Left - Button2->Width - 10;
  Button1->Top = Button2->Top;
  //Wysokosc okna glownego.
//  ClientHeight = Button1->Top + Button1->Height + 10;
}

//---public


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TFormUstawienia::TFormUstawienia(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormUstawienia::Button2Click(TObject *Sender)
{
  ModalResult = IDCANCEL;
}
//---------------------------------------------------------------------------
void __fastcall TFormUstawienia::Button1Click(TObject *Sender)
{
  if (
    (atoi(EditEditorFontSize->Text.c_str()) < 6) ||
    (atoi(EditEditorFontSize->Text.c_str()) > 22) )
    {
      Application->MessageBox ("Wartoœæ wielkoœci czcionki musi byæ z zakresu 6 do 22.", "B³¹d", 16);
      EditEditorFontSize->SetFocus();
      return;
    }
  ModalResult = IDYES;
}
//---------------------------------------------------------------------------
void __fastcall TFormUstawienia::TreeView1Change(TObject *Sender,
      TTreeNode *Node)
{
  if (TreeView1->Selected != NULL)
  {
    UnvisibleAreas();
    switch(TreeView1->Selected->Index)
    {
      case 0:
        GroupBox1->Visible = True;
        DesignComponents(GroupBox1);
        break;
      case 1:
        GroupBox3->Visible = True;
        DesignComponents(GroupBox3);
        break;
      case 2:
        GroupBox2->Visible = True;
        DesignComponents(GroupBox2);
        break;
      case 3:
        GroupBox4->Visible = True;
        DesignComponents(GroupBox4);
        break;
    };
  }
}
//---------------------------------------------------------------------------



void __fastcall TFormUstawienia::FormCreate(TObject *Sender)
{
  Width = 600;
  Height = 310;
}
//---------------------------------------------------------------------------


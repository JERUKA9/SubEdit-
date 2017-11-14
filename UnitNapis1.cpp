//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "UnitNapis1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormNapisy *FormNapisy;
//---------------------------------------------------------------------------
__fastcall TFormNapisy::TFormNapisy(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormNapisy::FormShow(TObject *Sender)
{
  int maxwid;
  if (LabelNapis1->Width>LabelNapis2->Width)
    maxwid = LabelNapis1->Width;
  else
    maxwid = LabelNapis2->Width;
  LabelNapis1->Width = maxwid;
  FormNapisy->Width = maxwid;
  if (LabelNapis2->Caption == "")
    FormNapisy->Height = LabelNapis1->Height;
  else
  {
    LabelNapis2->Top = LabelNapis1->Height;
    LabelNapis2->Width = maxwid;
    FormNapisy->Height = LabelNapis1->Height << 1;
  }
  Top = Screen->Height - FormNapisy->Height;
  Left = int( (Screen->Width>>1) -
              (maxwid>>1) + .5 );
}
//---------------------------------------------------------------------------

void __fastcall TFormNapisy::FormCreate(TObject *Sender)
{
  // ustawia dialog fontow na fonty zgodne z napisem
  FormNapisy->FormShow(Sender);
  FormNapisy->FormStyle = fsStayOnTop;
}
//---------------------------------------------------------------------------

void __fastcall TFormNapisy::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
/*  int s = Shift.Contains(ssShift);
  int c = Shift.Contains(ssCtrl);
  int a = Shift.Contains(ssAlt);*/
//  if ( s && !c && !a && (Key==76) ) Form1->ZatrzymajOdtwarzaj1Click(Sender);
//  Application->MessageBox("Napisy","",0);
  if (Key==78) Form1->Wywietlajnapisy1Click(Sender); // 'N' // wlacz/wylacz wyswietlanie napisow
  if (Key==32) Form1->ZatrzymajOdtwarzaj1Click(Sender); // spacja // pause/play
  if (Key==27) Form1->MediaPlayerNew1->DisplaySize = 4; // escape // tryb normalnokranowy
}
//---------------------------------------------------------------------------


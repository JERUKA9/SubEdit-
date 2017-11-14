//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "UnitPomoc.h"
#include "UnitNapis1.h"
#include "UnitOpcje.h"
#include "UnitMozliwosci.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "MediaPlayer_OCX"
#pragma resource "*.dfm"

const AnsiString ver = "1.0";
const AnsiString build = "859";
const AnsiString ldate = "2000-12-16";

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <inifiles.hpp>
#include <stdlib>
#include "functions.cpp"
#include "strcut.h"
#include "subtitle_fun.cpp"
#include "getposline.h"
int frf1=0, frf2=0, frn1=0, frn2=0; // do geometrycznej zmiany klatek napisow
AnsiString frnapis1, frnapis2; // napis z tej linii
int frnrlin1, frnrlin2; // numer linii z napisem
bool GeomPocz=false, GeomKon=false; // potwierdzenie wykonania pomiaru
int xvsize=0, yvsize=0; // rozmiar poczatkowy filmu
int nowytekst=1; // jezeli zostal wgrany nowy tekst lub zostal przesuniety film
int pokazywany = 0; // czy tekst jest pokazywany
int dlugoscfilmu; // dlugosc filmu w sekundach
int movielength; // dlugosc filmu w klatkach
//int lastwindowstate; // przy powrocie z fullskrina
bool isvideofile = false; // czy jest otwarty plik wideo
int line_num; // aktualnie obrabiana linia
bool pelnyekran;
struct Ini
{
  bool firststart;
  bool AutoSub;
  int iloscklatekwysw;
  bool AutoPlay;
  bool RichEditFocus;
  int szybkoscreakcji;
  bool uwzglczasreakcjinaendfrm;
  bool uwzglreakcjeprzyopoznieniu;
} ini;
TIniFile *inifile; // plik   SubEdit.ini
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void opentextfile(char *filename);
int formquestion (int questnum);
void showsub (char *tekstnapisu);
void hidesub (void);
bool zamknijaktualnypliktekstowy ();
bool checkfileext (char *file, char *ext); // sprawdza czy podany plik ma takie rozszezenie jak podane :)) oki, nie umiem wytlumaczyc :)))
void WOknieChange (bool WOknie); // zmienia ustawienia programu zaleznie czy film wyswietlany w osobnym oknie czy w oknie programu
void openvideofile (char *filename);
void zamknijplikwideo (); // ustala zmienne tak jakby nie bylo zadnego pliku wideo
int getnextline(int &n_od, int &n_do, char *tekstnapisu); // pobiera dane o nastepnej linii z napisem

//-------------- OBSLUGA PLIKU  INI -----------------------------------------
//-------------- OBSLUGA PLIKU  INI -----------------------------------------
//-------------- OBSLUGA PLIKU  INI -----------------------------------------
//-------------- OBSLUGA PLIKU  INI -----------------------------------------
//-------------- OBSLUGA PLIKU  INI -----------------------------------------
//-------------- OBSLUGA PLIKU  INI -----------------------------------------
void readinifile(TIniFile *inifile)
{
 // FONTY NAPISUF
  FormNapisy->LabelNapis1->Font->Name = // AnsiString
    inifile->ReadString("Fonts", "Name", "Arial"); // odczytaj kolor
  FormNapisy->LabelNapis1->Font->Size = // int
    inifile->ReadInteger("Fonts", "Size", 16); // odczytaj kolor
  FormNapisy->LabelNapis1->Font->Color = // TColor;
    TColor(inifile->ReadInteger("Fonts", "Color", clWhite)); // odczytaj kolor
      // font style
   FormNapisy->LabelNapis1->Font->Style.Clear();
  if (inifile->ReadInteger("Fonts", "Bold", 1)) // odczytaj styl czcionki
    FormNapisy->LabelNapis1->Font->Style = FormNapisy->LabelNapis1->Font->Style << fsBold; // TFontStyle: fsBold
  if (inifile->ReadInteger("Fonts", "Italic", 0)) // odczytaj styl czcionki
    FormNapisy->LabelNapis1->Font->Style = FormNapisy->LabelNapis1->Font->Style << fsItalic; // TFontStyle: fsBold
  if (inifile->ReadInteger("Fonts", "Underline", 0)) // odczytaj styl czcionki
    FormNapisy->LabelNapis1->Font->Style = FormNapisy->LabelNapis1->Font->Style << fsUnderline; // TFontStyle: fsBold
  if (inifile->ReadInteger("Fonts", "StrikeOut", 0)) // odczytaj styl czcionki
    FormNapisy->LabelNapis1->Font->Style = FormNapisy->LabelNapis1->Font->Style << fsStrikeOut; // TFontStyle: fsBold
   FormNapisy->LabelNapis2->Font = FormNapisy->LabelNapis1->Font;

 // ROZMIAR I STATUS OKNA GLOWNEGO PROGRAMU
  Form1->Left   = inifile->ReadInteger("Window", "Left"  , 100);
  Form1->Top    = inifile->ReadInteger("Window", "Top"   , 100);
  Form1->Height = inifile->ReadInteger("Window", "Height", 400);
  Form1->Width  = inifile->ReadInteger("Window", "Width" , 600);
  Form1->WindowState = TWindowState( inifile->ReadInteger("Window", "WindowState" , wsMaximized) );

 // USTAWIENIA PROGRAMU
  ini.firststart = inifile->ReadInteger("Settings", "FirstStart"  , 1);
  Form1->ToolBar1->Visible = inifile->ReadInteger("Settings", "ShowToolBar"  , 1);
  ini.AutoSub = inifile->ReadInteger("Settings", "AutoShowSubtitles"  , 0);
  ini.iloscklatekwysw = inifile->ReadInteger("Settings", "ShowSubtitleFrames"  , 110);
  ini.AutoPlay = inifile->ReadInteger("Settings", "AutoPlayMovie"  , 0);
  ini.RichEditFocus = inifile->ReadInteger("Settings", "RichEditFocus"  , 1);
  Form1->RichEdit->Font->Size = inifile->ReadInteger("Settings", "EditorFontSize"  , 9);
  ini.szybkoscreakcji = inifile->ReadInteger("Settings", "ReactionSpeed"  , 8);
  ini.uwzglczasreakcjinaendfrm = inifile->ReadInteger("Settings", "ReactionForEndFrameToo"  , 0);
  ini.uwzglreakcjeprzyopoznieniu = inifile->ReadInteger("Settings", "ReactionForDelayCheckToo"  , 0);
}
//---------------------------------------------------------------------------
void writeinifile(TIniFile *inifile)
{
 // FONTY NAPISUF
  inifile->WriteString ("Fonts", "Name", FormNapisy->LabelNapis1->Font->Name);
  inifile->WriteInteger("Fonts", "Size", FormNapisy->LabelNapis1->Font->Size);
  inifile->WriteInteger("Fonts", "Color", FormNapisy->LabelNapis1->Font->Color);
     // font style
  inifile->WriteInteger("Fonts", "Bold", FormNapisy->LabelNapis1->Font->Style.Contains (fsBold));
  inifile->WriteInteger("Fonts", "Italic", FormNapisy->LabelNapis1->Font->Style.Contains (fsItalic));
  inifile->WriteInteger("Fonts", "Underline", FormNapisy->LabelNapis1->Font->Style.Contains (fsUnderline));
  inifile->WriteInteger("Fonts", "StrikeOut", FormNapisy->LabelNapis1->Font->Style.Contains (fsStrikeOut));

 // ROZMIAR I STATUS OKNA GLOWNEGO PROGRAMU
  if (Form1->WindowState==wsNormal)
  {
    inifile->WriteInteger("Window", "Left"  , Form1->Left);
    inifile->WriteInteger("Window", "Top"   , Form1->Top);
    inifile->WriteInteger("Window", "Height", Form1->Height);
    inifile->WriteInteger("Window", "Width" , Form1->Width);
  }
  inifile->WriteInteger("Window", "WindowState" , Form1->WindowState);

 // USTAWIENIA PROGRAMU
  inifile->WriteInteger("Settings", "FirstStart"  , 0);
  inifile->WriteInteger("Settings", "ShowToolBar"  , Form1->ToolBar1->Visible);
  inifile->WriteInteger("Settings", "AutoShowSubtitles"  , ini.AutoSub);
  inifile->WriteInteger("Settings", "ShowSubtitleFrames"  , ini.iloscklatekwysw);
  inifile->WriteInteger("Settings", "AutoPlayMovie"  , ini.AutoPlay);
  inifile->WriteInteger("Settings", "RichEditFocus"  , ini.RichEditFocus);
  inifile->WriteInteger("Settings", "EditorFontSize"  , Form1->RichEdit->Font->Size);
  inifile->WriteInteger("Settings", "ReactionSpeed"  , ini.szybkoscreakcji);
  inifile->WriteInteger("Settings", "ReactionForEndFrameToo"  , ini.uwzglczasreakcjinaendfrm);
  inifile->WriteInteger("Settings", "ReactionForDelayCheckToo"  , ini.uwzglreakcjeprzyopoznieniu);
}

//------------- MOJE  FUNKCJE -----------------------------------------------
//------------- MOJE  FUNKCJE -----------------------------------------------
//------------- MOJE  FUNKCJE -----------------------------------------------
//------------- MOJE  FUNKCJE -----------------------------------------------
//------------- MOJE  FUNKCJE -----------------------------------------------
//------------- MOJE  FUNKCJE -----------------------------------------------
bool zamknijaktualnypliktekstowy ()//char *filename)
{
  if (!Form1->RichEdit->Modified) return true;
  int odp = Application->MessageBox ("Aktualny plik tekstowy jest zmodyfikowany\n"
    "\nCzy zachowaæ zmiany?", "Pytanie", 36);
  if (odp == IDCANCEL) return false;
  if (odp == IDYES)
    Form1->Zapisz1Click(NULL);
//    Form1->RichEdit->Lines->SaveToFile (filename);
  return true;
}
//---------------------------------------------------------------------------
void modifiedfalse ()
{
  Form1->RichEdit->Modified = false;
  Form1->Zapisz1->Enabled = false; // MENU save
  Form1->SpeedButtonSave->Enabled = false;
  Form1->LabelFileName->Font->Style = Form1->LabelFileName->Font->Style >> fsBold;
}
//---------------------------------------------------------------------------
bool checkfileext (char *file, char *ext) // sprawdza czy podany plik ma takie rozszezenie jak podane :)) oki, nie umiem wytlumaczyc :)))
{
  int filechlen = strlen (file);
  int extchlen = strlen (ext);
  if (filechlen <= extchlen) return false; // na pewno inne rozszerzenie bo by sie nie zmiescilo
  if ( file[filechlen-extchlen-1] != '.' ) return false; // napewno inne bo kropka nie pasi. niech spierdala
  char extfromfile[10];                                         //       9        3
  strcut (file, extfromfile, filechlen-extchlen, extchlen);      //  "12345.txt" "txt"
//  for (int i=0; i<extchlen; i++)      // to jest do dupy bo uwzglednia wielkosc liter
//    if ( file[filechlen-extchlen+i] != ext[i] ) return false;
  if (stricmp(ext, extfromfile)) return false; // sama tresc rozszerzenia nie pasuje :(
  return true; // wszystkie probby przeszedl pomyslnie :))
}
//---------------------------------------------------------------------------
void dlugoscfilmuczas (float seccount) // wpisuje czasowa dlugosc filmu
{
  int hh, mm;
  AnsiString h, m, s, ms;
    h = IntToStr( hh=int(seccount/3600) );
      if (h.Length()==1) s = "0"+h;
    m = IntToStr( mm=int((seccount - hh*3600) /60) );
      if (m.Length()==1) m = "0"+m;
    s = IntToStr( int(seccount - hh*3600 - mm*60) );
      if (s.Length()==1) s = "0"+s;
  Form1->StatusBar->Panels->Items[2]->Text = h+":"+m+":"+s;
}
void aktualnyczasfilmu (float seccount) // wpisuje czas trwania filmu
{
  int hh, mm;
  AnsiString h, m, s, ms;
    h = IntToStr( hh=int(seccount/3600) );
      if (h.Length()==1) s = "0"+h;
    m = IntToStr( mm=int((seccount - hh*3600) /60) );
      if (m.Length()==1) m = "0"+m;
    s = IntToStr( int(seccount - hh*3600 - mm*60) );
      if (s.Length()==1) s = "0"+s;
  Form1->StatusBar->Panels->Items[1]->Text = h+":"+m+":"+s;
}
//---------------------------------------------------------------------------
void czasowadlugoscfilmu() // czas trwania filmu w godzinach min i sek
{
  Form1->MediaPlayerNew1->DisplayMode = 0; // format czasu - sekundy
  dlugoscfilmu = Form1->MediaPlayerNew1->Duration;
  dlugoscfilmuczas (dlugoscfilmu);
}
//---------------------------------------------------------------------------
void filmmenu(bool wlacznik)
{
  Form1->Skokdowybranejklatkifilmu1->Enabled = wlacznik;
  Form1->Wstawklatkfilmudoliniijakoklatkpoczrkow1->Enabled = wlacznik;
  Form1->Wstawklatkfilmudoliniijakoklatkkocow1->Enabled = wlacznik;
  Form1->Wstawklatkinnyskrt1->Enabled = wlacznik;
  Form1->Skokdoliniizaktualnklatkfilmu1->Enabled = wlacznik;
  Form1->Odtwarzajfilmodklatki1->Enabled = wlacznik;
  Form1->PauzaOdtwarzaj1->Enabled = wlacznik;
  Form1->Stop1->Enabled = wlacznik;
//  Form1->Przewijanie1->Enabled = wlacznik;
   Form1->Skokdoprzoduo50klatek1->Enabled = wlacznik;
   Form1->Skokwsteczo50klatek1->Enabled = wlacznik;
   Form1->Skokdopocztkufilmu1->Enabled = wlacznik;
   Form1->Skoknakoniecfilmu1->Enabled = wlacznik;
//  Form1->Opnieniegeometryczne1->Enabled = wlacznik;
   Form1->Zmierzopnienielinii1->Enabled = wlacznik;
   Form1->Zmierzpocztkoweopnienienapisw1->Enabled = wlacznik;
   Form1->Zmierzkocoweopnienienapisw1->Enabled = wlacznik;
//   Form1->GeometryczneOp->Enabled = wlacznik; // <<---
        Form1->GeometryczneOp->Enabled = false;
  Form1->Trybpe1->Enabled = wlacznik;
  Form1->Wywietlajnapisy1->Enabled = wlacznik;
}
//---------------------------------------------------------------------------
void zamknijplikwideo () // ustala zmienne tak jakby nie bylo zadnego pliku wideo
{
  Form1->Timer->Enabled = false;
  Form1->MediaPlayerNew1->FileName = "";
//    Form1->Splitter->Visible = false;
//  Form1->MediaPlayerNew1->Visible = false;
//  Form1->Obraz1->Enabled = false;
  filmmenu(false);
  FormPytanie->LabelFps->Caption = "N/A";
  FormPytanie->LabelFps2->Caption = "N/A";
    hidesub();
    if (Form1->Wywietlajnapisy1->Checked) // jezeli napisy wlaczone
      Form1->Wywietlajnapisy1Click(NULL); // wylacz napisy przy otwarciu nowego pliku
    isvideofile = false;
    FormNapisy->Visible = false;
    Screen->Cursor = crHourGlass; // kursor na hourgalss
    Form1->StatusBar->Panels->Items[3]->Text = "";
    Form1->StatusBar->Panels->Items[0]->Text = "{0}{0}";
    dlugoscfilmuczas (0); // "00:00:00"
    aktualnyczasfilmu (0); // "00:00:00"
    Form1->MediaPlayerNew1->FileName = "";
    Form1->Zamknijplikwideo1->Enabled = false;
    xvsize=0; yvsize=0; // wielkosc filmiku
    Screen->Cursor = crDefault; // kursor na default
    Form1->SpeedButtonShowSubTit->Enabled=false;
    Form1->SpeedButtonFullScreen->Enabled = false;
    Form1->GeometryczneOp->Enabled = false;
    Form1->MediaPlayerNew1->Height = 150;
    GeomPocz=false; GeomKon=false;
}
//---------------------------------------------------------------------------
void openvideofile (char *filename)
{
    zamknijplikwideo ();
    if (ini.AutoPlay) Form1->MediaPlayerNew1->AutoStart = true;
    else Form1->MediaPlayerNew1->AutoStart = false;
    Form1->MediaPlayerNew1->FileName = filename; // nazwa filmiku do media playera
//    Form1->Refresh();
//    Screen->Cursor = crDefault; // zmienia kursor na domyslny
    if (!Form1->MediaPlayerNew1->OpenState) // pewnie jebniety plik
    {
      Application->MessageBox ("Plik nie zosta³ otwarty pomyœlnie!","B³¹d", 16);
      return;
    }
    Form1->StatusBar->Panels->Items[3]->Text = filename; // pokazuje na labelu nazwe pliku filmu

    Form1->MediaPlayerNew1->Visible = true;
//    Form1->MediaPlayerNew1->Height = Form1->MediaPlayerNew1->ImageSourceWidth;
    isvideofile = true;
    Form1->Splitter->Visible = true;
    Form1->SpeedButtonShowSubTit->Enabled=true;
    Form1->SpeedButtonFullScreen->Enabled = true;
    int addtoheight=0;

    if (FormUstawienia->CheckBoxToolBar->Checked) addtoheight=Form1->ToolBar1->Height; // dodaje wysokosc toolbara jezeli toolbar jest pokazywany
  int MPHeight = Form1->MediaPlayerNew1->ImageSourceHeight + 46 + addtoheight;
   if (MPHeight>400) MPHeight=400; // jezeli wysokosc > 400 to zmiejsz do 400
      Form1->MediaPlayerNew1->Height = MPHeight;

//    xvsize = Form1->MediaPlayer->DisplayRect.Width(); // szerokosc filmu  //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//    yvsize = Form1->MediaPlayer->DisplayRect.Height(); // wysokosc filmu  //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//      Form1->Obraz1->Enabled = true;
        filmmenu(true);
    czasowadlugoscfilmu(); // zapisuje maksymalny czas trwania filmu
    Form1->MediaPlayerNew1->DisplayMode = 1; // format czasu - klatki
    movielength = Form1->MediaPlayerNew1->Duration; // ustala ilosc klatek calego filmu
    FormPytanie->LabelFps->Caption = FloatToStr(float(float(movielength)/float(dlugoscfilmu)));
    FormPytanie->LabelFps2->Caption = FormPytanie->LabelFps->Caption;
    Form1->Zamknijplikwideo1->Enabled = true;
    // zmienia max wielkosc framesa
      FormPytanie->LabelMaxFrm->Caption = IntToStr(movielength);
      // automatyczne otwieranie pliku tekstowego o tej samej nazwie
      char *fmovie, ftext[512];
      fmovie = Form1->StatusBar->Panels->Items[3]->Text.c_str();
      int fmovlen = strlen (fmovie);
      int lastpointpos=0;
      for (int i=0; i<fmovlen; i++)
        if (fmovie[i]=='.') lastpointpos=i+1;
       strcut (fmovie, ftext, 0, lastpointpos);
       strcat (ftext, "txt");
      if (FileExists(ftext))
      {
        if (zamknijaktualnypliktekstowy ())
          opentextfile(ftext);
      }
  Form1->Timer->Enabled = true;
}
//---------------------------------------------------------------------------
// DO menu open tekst
void opentextfile(char *filename)
{
  if (Form1->Wywietlajnapisy1->Checked) // jezeli napisy wlaczone
   Form1->Wywietlajnapisy1Click(NULL); // wylacz napisy przy otwarciu nowego pliku
//    zamknijaktualnypliktekstowy (Form1->LabelFileName->Caption.c_str());
    nowytekst = 1; // wgrany nowy tekst (do napisuf)
    Form1->RichEdit->Lines->LoadFromFile(filename);
    Form1->LabelFileName->Caption = filename;
    bool modify = true;
    if (checktimelineerr (Form1->RichEdit->Lines->Strings[0].c_str())) // sprawdza czy linia jest w zapisie czasowym
    {
      if (
      Application->MessageBox("Plik wydaje siê byæ zapisany w formacie czasowym\n"
        "Program obs³uguje wy³¹cznie format klatkowy napisów\n"
        "\nPrzekonwertowaæ plik na wymagany format?", "Ostrze¿enie", 52)
      == IDYES)
      {
          Form1->CzasKlatkaClick(NULL);
          modify = false;
      }
    }
  if ((ini.AutoSub)&&(isvideofile))
//    if (!Form1->Wywietlajnapisy1->Checked) // jezeli napisy wylaczone
      Form1->Wywietlajnapisy1Click(NULL); // wlacz napisy przy otwarciu nowego pliku
    if (modify) modifiedfalse();
    if (Form1->RichEdit->CanFocus()) Form1->RichEdit->SetFocus();
}
//---------------------------------------------------------------------------
// wywolanie okna zapytania
int formquestion (int questnum)
{
  FormPytanie->Panel1->Visible = false;
  FormPytanie->Panel2->Visible = false;
  FormPytanie->Panel3->Visible = false;
  FormPytanie->Panel4->Visible = false;
  FormPytanie->Panel5->Visible = false;
  switch(questnum)
  {
    case 1: // zmiana: czas --> klatki
      FormPytanie->GroupBoxTime->Enabled = false;
        if (timeformat==1) FormPytanie->RadioButton1->Checked=true;
        if (timeformat==2) FormPytanie->RadioButton2->Checked=true;
        if (timeformat==3) FormPytanie->RadioButton3->Checked=true;
      FormPytanie->Caption = "Czas --> Klatka";
      FormPytanie->Panel1->Visible = true;
      break;
    case 2: // zmiana: klatki --> czas
      FormPytanie->GroupBoxTime->Enabled = true;
        if (timeformat==1) FormPytanie->RadioButton1->Checked=true;
        if (timeformat==2) FormPytanie->RadioButton2->Checked=true;
        if (timeformat==3) FormPytanie->RadioButton3->Checked=true;
      FormPytanie->Caption = "Klatka --> Czas";
      FormPytanie->Panel1->Visible = true;
      break;
    case 3: // dodanie framesuf
      FormPytanie->Caption = "Przesuñ klatki";
      FormPytanie->Panel2->Visible = true;
      break;
    case 4: // zmiana czasu wyswietlania tekstu
      FormPytanie->Caption = "Czas wyœwietlania napisu";
      FormPytanie->Panel3->Visible = true;
      break;
    case 5: // skok do wybranej klatki filmu
      FormPytanie->Caption = "Skok do klatki filmu";
      FormPytanie->Panel4->Visible = true;
      break;
    case 6: // Zmiana ilosci klatek na sekunde
      FormPytanie->Caption = "Zmiana iloœci klatek na sekunde";
      FormPytanie->Panel5->Visible = true;
      break;

    default:
      Application->MessageBox ("Nieprawod³owe wywo³anie okna zapytania", "Errorus", 16);
  }
  if (FormPytanie->ShowModal()==mrOk)
  {
      if (FormPytanie->RadioButton1->Checked) timeformat=1;
      if (FormPytanie->RadioButton2->Checked) timeformat=2;
      if (FormPytanie->RadioButton3->Checked) timeformat=3;
    Form1->Refresh();
    return 1; // wcisniete OK
  }
  else
  {
    Form1->Refresh();
    return 0; // wcisniete Anuluj
  }
}
//---------------------------------------------------------------------------
//   do Apply przy zmianie fontuf
void ZmienCzcionke (TObject *Sender)
{
    FormNapisy->LabelNapis1->Font = Form1->FontDialog->Font;
    FormNapisy->LabelNapis2->Font = Form1->FontDialog->Font;
    FormNapisy->FormShow(Sender); // zmiana okna napisow
}

//------------- OBSLUGA MENU ------------------------------------------------
//------------- OBSLUGA MENU ------------------------------------------------
//------------- OBSLUGA MENU ------------------------------------------------
//------------- OBSLUGA MENU ------------------------------------------------
//------------- OBSLUGA MENU ------------------------------------------------
//------------- OBSLUGA MENU ------------------------------------------------

// MENU ->PLIK-> nowy
void __fastcall TForm1::Nowy1Click(TObject *Sender)
{
  if (zamknijaktualnypliktekstowy ())
  {
    LabelFileName->Caption = "Subtitle.txt";
    RichEdit->Clear();
    modifiedfalse();
  }
}
//---------------------------------------------------------------------------
// MENU ->PLIK-> open wideo
void __fastcall TForm1::Otwrzplikwideo1Click(TObject *Sender)
{
  if (OpenVideo->Execute())
    openvideofile (OpenVideo->FileName.c_str());
}
//---------------------------------------------------------------------------
// MENU ->PLIK-> open
void __fastcall TForm1::Open1Click(TObject *Sender)
{
  if (zamknijaktualnypliktekstowy ())
    if (Open->Execute())
      opentextfile(Open->FileName.c_str());
  Form1->Refresh();
}
//---------------------------------------------------------------------------
// MENU ->PLIK-> zamknij plik Wideo
void __fastcall TForm1::Zamknijplikwideo1Click(TObject *Sender)
{//
  zamknijplikwideo ();
}
//---------------------------------------------------------------------------
// MENU ->PLIK-> save
void __fastcall TForm1::Zapisz1Click(TObject *Sender)
{
  if (LabelFileName->Caption=="Subtitle.txt")// jezeli nazwa defaultowa
  {
    TForm1::ZapiszJako1Click(Sender); // nie rob save tylko save as
    return; // i spierdalaj
  }
  RichEdit->Lines->SaveToFile(LabelFileName->Caption);
    modifiedfalse();
  if (RichEdit->CanFocus()) RichEdit->SetFocus();
}
//---------------------------------------------------------------------------
// MENU ->PLIK-> save as
void __fastcall TForm1::ZapiszJako1Click(TObject *Sender)
{
  Save->FileName = LabelFileName->Caption;
  if (Save->Execute())
  {
    if ( FileExists(Save->FileName) )
      if (Application->MessageBox("Plik o podanej nazwie istnieje\n"
          "Zast¹piæ istniej¹cy plik?", "Pytanie", 36) !=IDYES ) return;
    {
      RichEdit->Lines->SaveToFile(Save->FileName);
      LabelFileName->Caption = Save->FileName;
      modifiedfalse();
      if (RichEdit->CanFocus()) RichEdit->SetFocus();
    }
  }
}
//---------------------------------------------------------------------------
// MENU ->PLIK-> exit
void __fastcall TForm1::Exit1Click(TObject *Sender)
{
  Form1->Close();
}
//---------------------------------------------------------------------------
// MENU ->EDYCJA-> Znajdz tekst
void __fastcall TForm1::ZnajdzTekst1Click(TObject *Sender)
{//
  Find->Execute();
}
//---------------------------------------------------------------------------
// MENU ->EDYCJA-> znajdz ramke
void __fastcall TForm1::Znajdramk1Click(TObject *Sender)
{//

}
//---------------------------------------------------------------------------
// MENU ->EDYCJA-> Kopiuj
void __fastcall TForm1::Kopiuj1Click(TObject *Sender)
{//
  RichEdit->CopyToClipboard();
}
//---------------------------------------------------------------------------
// MENU ->EDYCJA-> wklej
void __fastcall TForm1::Wklej1Click(TObject *Sender)
{//
  RichEdit->PasteFromClipboard();
}
//---------------------------------------------------------------------------
// MENU ->EDYCJA-> Ustawienia programu
void __fastcall TForm1::Ustawieniaprogramu1Click(TObject *Sender)
{
  FormUstawienia->CheckBoxToolBar->Checked = Form1->ToolBar1->Visible;
  FormUstawienia->CheckBoxAutoSub->Checked = ini.AutoSub;
  if (ini.iloscklatekwysw == 9999999)
    FormUstawienia->EditDlugoscWyswietlaniaNapisu->Text = "0";
  else
    FormUstawienia->EditDlugoscWyswietlaniaNapisu->Text = IntToStr(ini.iloscklatekwysw);
  FormUstawienia->CheckBoxAutoPlay->Checked = ini.AutoPlay;
  FormUstawienia->CheckBoxOgniskoNaRichEdit->Checked = ini.RichEditFocus;
  FormUstawienia->EditEditorFontSize->Text = IntToStr(Form1->RichEdit->Font->Size);
  FormUstawienia->EditSzybkoscReakcji->Text = IntToStr(ini.szybkoscreakcji);
  FormUstawienia->CheckBoxKoncowaReakcja->Checked = ini.uwzglczasreakcjinaendfrm;
  FormUstawienia->CheckBoxReakcjaPrzyOpoznieniu->Checked = ini.uwzglreakcjeprzyopoznieniu;

  if (FormUstawienia->ShowModal()==IDCANCEL) return; // wcisniete anuluj

  Form1->ToolBar1->Visible = FormUstawienia->CheckBoxToolBar->Checked;
  ini.AutoSub = FormUstawienia->CheckBoxAutoSub->Checked;
  ini.iloscklatekwysw = atoi(FormUstawienia->EditDlugoscWyswietlaniaNapisu->Text.c_str());
    if (ini.iloscklatekwysw==0) ini.iloscklatekwysw = 9999999;
  ini.AutoPlay = FormUstawienia->CheckBoxAutoPlay->Checked;
  ini.RichEditFocus = FormUstawienia->CheckBoxOgniskoNaRichEdit->Checked;
  Form1->RichEdit->Font->Size = atoi(FormUstawienia->EditEditorFontSize->Text.c_str());
  ini.szybkoscreakcji = atoi(FormUstawienia->EditSzybkoscReakcji->Text.c_str());
  ini.uwzglczasreakcjinaendfrm = FormUstawienia->CheckBoxKoncowaReakcja->Checked;
  ini.uwzglreakcjeprzyopoznieniu = FormUstawienia->CheckBoxReakcjaPrzyOpoznieniu->Checked;
}
//---------------------------------------------------------------------------
// MENU ->EDYCJA-> opcje napisow
void __fastcall TForm1::Opcjenapisw1Click(TObject *Sender)
{
  bool wlaczonenapisy = Form1->Wywietlajnapisy1->Checked;
  if (wlaczonenapisy) // jezeli napisy wlaczone
    Form1->Wywietlajnapisy1Click(Sender); // wylacz napisy

  showsub ("Próbny tekst napisu... 0123456|A tutaj polskie krzaki: ¥¹ÆæÊê£³¯¿");
  if (FontDialog->Execute())
    ZmienCzcionke (Sender);
  hidesub ();

  if (wlaczonenapisy) // jezeli napisy byly wlaczone
    Form1->Wywietlajnapisy1Click(Sender); // wlacz napisy
}
//---------------------------------------------------------------------------
// MENU ->TEKST-> Czas --> Klatki
void __fastcall TForm1::CzasKlatkaClick(TObject *Sender)
{
  if (!formquestion(1)) return;
  int wyswietlajnapisy = Wywietlajnapisy1->Checked;
    if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wylacz napisy jezeli wlaczone

     float fps = atof (FormPytanie->ComboBoxFps->Text.c_str());
     int strtline=0; // poczatkowa linia
     int endline=RichEdit->Lines->Count; // koncowa linia
     if (RichEdit->SelLength>0) // jezeli jest cos zaznaczone
     { strtline = getstartposline(RichEdit->Lines, RichEdit->SelStart); // zmien poczatkowa linie
       endline  = getendposline(RichEdit->Lines, RichEdit->SelStart+RichEdit->SelLength)+1; // i koncowa
     }
   Screen->Cursor = crHourGlass;
    time2frm (RichEdit->Lines, fps, strtline, endline);
   Screen->Cursor = crDefault;
    if (RichEdit->CanFocus()) RichEdit->SetFocus();

  if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wlacz napisy jezeli wczesniej byly wlaczone
}
//---------------------------------------------------------------------------
// MENU ->TEKST-> Klatka --> Czas
void __fastcall TForm1::KlatkaCzasClick(TObject *Sender)
{
  if (!formquestion(2)) return;
  int wyswietlajnapisy = Wywietlajnapisy1->Checked;
    if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wylacz napisy jezeli wlaczone

     float fps = atof (FormPytanie->ComboBoxFps->Text.c_str());
     int strtline=0; // poczatkowa linia
     int endline=RichEdit->Lines->Count; // koncowa linia
     if (RichEdit->SelLength>0) // jezeli jest cos zaznaczone
     { strtline = getstartposline(RichEdit->Lines, RichEdit->SelStart); // zmien poczatkowa linie
       endline  = getendposline(RichEdit->Lines, RichEdit->SelStart+RichEdit->SelLength)+1; // i koncowa
     }
   Screen->Cursor = crHourGlass;
    frm2time (RichEdit->Lines, fps, strtline, endline);
   Screen->Cursor = crDefault;
    if (RichEdit->CanFocus()) RichEdit->SetFocus();

  if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wlacz napisy jezeli wczesniej byly wlaczone
}
//---------------------------------------------------------------------------
// MENU ->TEKST-> Dodaj klatki
void __fastcall TForm1::DodajKlatkiClick(TObject *Sender)
{
 if (!formquestion(3)) return;

 int wyswietlajnapisy = Wywietlajnapisy1->Checked;
    if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wylacz napisy jezeli wlaczone

//   SendMessage(Form1->RichEdit->Handle, WM_SETREDRAW, false, 0);
     int ile = atoi(FormPytanie->EditFrm->Text.c_str());
     int strtline=0; // poczatkowa linia
     int endline=RichEdit->Lines->Count; // koncowa linia
     if (RichEdit->SelLength>0) // jezeli jest cos zaznaczone
     { strtline = getstartposline(RichEdit->Lines, RichEdit->SelStart); // zmien poczatkowa linie
       endline  = getendposline(RichEdit->Lines, RichEdit->SelStart+RichEdit->SelLength)+1; // i koncowa
     }
   Screen->Cursor = crHourGlass;
    addfrm (RichEdit->Lines, ile, FormPytanie->CheckBoxFrom->Checked, FormPytanie->CheckBoxTo->Checked, strtline, endline);
   Screen->Cursor = crDefault;
//   SendMessage(Form1->RichEdit->Handle, WM_SETREDRAW, true, 0);

  if (RichEdit->CanFocus()) RichEdit->SetFocus();
  nowytekst = 1; // klatki zostaly zmienione (do napisuf)

  if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wlacz napisy jezeli wczesniej byly wlaczone
}
//---------------------------------------------------------------------------
// MENU ->TEKST-> Zmien czas wyswietlania tekstu
void __fastcall TForm1::ZmienIloscKlatekClick(TObject *Sender)
{
  if (!formquestion(4)) return;

  int wyswietlajnapisy = Wywietlajnapisy1->Checked;
    if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wylacz napisy jezeli wlaczone

     int ile = atoi(FormPytanie->EditShowFrm->Text.c_str());
       FormPytanie->EditShowFrm->Text = IntToStr(ile);
     int strtline=0; // poczatkowa linia
     int endline=RichEdit->Lines->Count; // koncowa linia
     if (RichEdit->SelLength>0) // jezeli jest cos zaznaczone
     { strtline = getstartposline(RichEdit->Lines, RichEdit->SelStart); // zmien poczatkowa linie
       endline  = getendposline(RichEdit->Lines, RichEdit->SelStart+RichEdit->SelLength)+1; // i koncowa
     }    
   Screen->Cursor = crHourGlass;
  changeshowtime(RichEdit->Lines, ile, FormPytanie->CheckBoxOverwrite->Checked,
      FormPytanie->CheckBoxNa100->Checked, FormPytanie->CheckBoxNieWieksze->Checked,
                                strtline, endline);
   Screen->Cursor = crDefault;
  if (RichEdit->CanFocus()) RichEdit->SetFocus();

  if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wlacz napisy jezeli wczesniej byly wlaczone
}
//---------------------------------------------------------------------------
// MENU ->TEKST-> zmiana ilosci klatek na sekunde
void __fastcall TForm1::Zmianailociklateknasekund1Click(TObject *Sender)
{//
  if (!formquestion(6)) return;

  int wyswietlajnapisy = Wywietlajnapisy1->Checked;
    if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wylacz napisy jezeli wlaczone

     int ile = atoi(FormPytanie->EditShowFrm->Text.c_str());
       FormPytanie->EditShowFrm->Text = IntToStr(ile);
     int strtline=0; // poczatkowa linia
     int endline=RichEdit->Lines->Count; // koncowa linia
     if (RichEdit->SelLength>0) // jezeli jest cos zaznaczone
     { strtline = getstartposline(RichEdit->Lines, RichEdit->SelStart); // zmien poczatkowa linie
       endline  = getendposline(RichEdit->Lines, RichEdit->SelStart+RichEdit->SelLength)+1; // i koncowa
     }
   Screen->Cursor = crHourGlass;
  fpsratechange(RichEdit->Lines, atof(FormPytanie->ComboBoxFpsAct->Text.c_str()),
                                 atof(FormPytanie->ComboBoxFpsDest->Text.c_str()),
                                strtline, endline);
   Screen->Cursor = crDefault;
  if (RichEdit->CanFocus()) RichEdit->SetFocus();

  if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wlacz napisy jezeli wczesniej byly wlaczone
}
//---------------------------------------------------------------------------
// MENU ->TEKST-> posortuj linie
void __fastcall TForm1::PosortujNapisyClick(TObject *Sender)
{//
  if ( !
      (Application->MessageBox ("Posortowaæ napisy rosn¹co?", "Pytanie", 36)
      == IDYES)) return;

  int wyswietlajnapisy = Wywietlajnapisy1->Checked;
    if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wylacz napisy jezeli wlaczone

     int strtline=0; // poczatkowa linia
     int endline=RichEdit->Lines->Count; // koncowa linia
     if (RichEdit->SelLength>0) // jezeli jest cos zaznaczone
     { strtline = getstartposline(RichEdit->Lines, RichEdit->SelStart); // zmien poczatkowa linie
       endline  = getendposline(RichEdit->Lines, RichEdit->SelStart+RichEdit->SelLength)+1; // i koncowa
     }
   Screen->Cursor = crHourGlass;
  sortlines (RichEdit->Lines, strtline, endline);
   Screen->Cursor = crDefault;
  if (RichEdit->CanFocus()) RichEdit->SetFocus();

  if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wlacz napisy jezeli wczesniej byly wlaczone
}
//---------------------------------------------------------------------------
// MENU ->TEKST-> wytnij entery
void __fastcall TForm1::WyczyscPusteLinieClick(TObject *Sender)
{
  if ( !
      (Application->MessageBox ("Usun¹æ puste linie tekstu?", "Pytanie", 36)
      == IDYES)) return;

  int wyswietlajnapisy = Wywietlajnapisy1->Checked;
    if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wylacz napisy jezeli wlaczone

     int strtline=0; // poczatkowa linia
     int endline=RichEdit->Lines->Count; // koncowa linia
     if (RichEdit->SelLength>0) // jezeli jest cos zaznaczone
     { strtline = getstartposline(RichEdit->Lines, RichEdit->SelStart); // zmien poczatkowa linie
       endline  = getendposline(RichEdit->Lines, RichEdit->SelStart+RichEdit->SelLength)+1; // i koncowa
     }
   Screen->Cursor = crHourGlass;
  delenters (RichEdit->Lines, strtline, endline);
   Screen->Cursor = crDefault;
  if (RichEdit->CanFocus()) RichEdit->SetFocus();

  if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wlacz napisy jezeli wczesniej byly wlaczone
}
//---------------------------------------------------------------------------
// MENU ->TEKST-> przesuniecie tekstu do przodu o 5 klatek
void __fastcall TForm1::PrzesunTekst5DoPrzoduClick(TObject *Sender)
{//
 int wyswietlajnapisy = Wywietlajnapisy1->Checked;
    if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wylacz napisy jezeli wlaczone
  int startsel = RichEdit->SelStart;
  int endsel = RichEdit->SelLength;
    SendMessage(Form1->RichEdit, WM_SETREDRAW, 0, 0);
     int strtline=RichEdit->CaretPos.y; // poczatkowa linia
     int endline=strtline+1; // koncowa linia
     if (RichEdit->SelLength>0) // jezeli jest cos zaznaczone
     { strtline = getstartposline(RichEdit->Lines, startsel); // zmien poczatkowa linie
       endline  = getendposline(RichEdit->Lines, startsel+RichEdit->SelLength)+1; // i koncowa
     }
   Screen->Cursor = crHourGlass;
    addfrm (RichEdit->Lines, 5, true, true, strtline, endline);
   Screen->Cursor = crDefault;
  if (RichEdit->CanFocus()) RichEdit->SetFocus();
  nowytekst = 1; // klatki zostaly zmienione (do napisuf)
  RichEdit->SelStart = startsel;
  RichEdit->SelLength = endsel;

  if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wlacz napisy jezeli wczesniej byly wlaczone
}
//---------------------------------------------------------------------------
// MENU ->TEKST-> przesuniecie tekstu do tylu o 5 klatek
void __fastcall TForm1::PrzesunTekst5DoTyluClick(
      TObject *Sender)
{//
 int wyswietlajnapisy = Wywietlajnapisy1->Checked;
    if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wylacz napisy jezeli wlaczone
  int startsel = RichEdit->SelStart;
  int endsel = RichEdit->SelLength;
    SendMessage(Form1->RichEdit, WM_SETREDRAW, 0, 0);
     int strtline=RichEdit->CaretPos.y; // poczatkowa linia
     int endline=strtline+1; // koncowa linia
     if (RichEdit->SelLength>0) // jezeli jest cos zaznaczone
     { strtline = getstartposline(RichEdit->Lines, startsel); // zmien poczatkowa linie
       endline  = getendposline(RichEdit->Lines, startsel+RichEdit->SelLength)+1; // i koncowa
     }
   Screen->Cursor = crHourGlass;
    addfrm (RichEdit->Lines, -5, true, true, strtline, endline);
   Screen->Cursor = crDefault;
  if (RichEdit->CanFocus()) RichEdit->SetFocus();
  nowytekst = 1; // klatki zostaly zmienione (do napisuf)
  RichEdit->SelStart = startsel;
  RichEdit->SelLength = endsel;

  if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wlacz napisy jezeli wczesniej byly wlaczone
}
//---------------------------------------------------------------------------
// MENU ->TEKST->INNE-> usun podwojne spacje
void __fastcall TForm1::UsunPodwjneSpacje1Click(TObject *Sender)
{//
  if ( !
      (Application->MessageBox ("Usun¹æ podwójne spacje?", "Pytanie", 36)
      == IDYES)) return;
  int wyswietlajnapisy = Wywietlajnapisy1->Checked;
    if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wylacz napisy jezeli wlaczone
     int strtline=0; // poczatkowa linia
     int endline=RichEdit->Lines->Count; // koncowa linia
     if (RichEdit->SelLength>0) // jezeli jest cos zaznaczone
     { strtline = getstartposline(RichEdit->Lines, RichEdit->SelStart); // zmien poczatkowa linie
       endline  = getendposline(RichEdit->Lines, RichEdit->SelStart+RichEdit->SelLength)+1; // i koncowa
     }
   Screen->Cursor = crHourGlass;
  deldoublespaces (RichEdit->Lines, strtline, endline);
   Screen->Cursor = crDefault;
  if (RichEdit->CanFocus()) RichEdit->SetFocus();
  if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wlacz napisy jezeli wczesniej byly wlaczone
}
//---------------------------------------------------------------------------
// MENU ->TEKST->INNE->  ' | '  --->  '|'
void __fastcall TForm1::UsuSpacjeZaiPrzedClick(TObject *Sender)
{//
  if ( !
      (Application->MessageBox ("Usuñ spacje na koñcu wiersza?\n\n"
                                "Je¿eli dooko³a | jest wiêcej spacji wywo³aj funkcjê kilka razy.", "Pytanie", 36)
      == IDYES)) return;
  int wyswietlajnapisy = Wywietlajnapisy1->Checked;
    if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wylacz napisy jezeli wlaczone
     int strtline=0; // poczatkowa linia
     int endline=RichEdit->Lines->Count; // koncowa linia
     if (RichEdit->SelLength>0) // jezeli jest cos zaznaczone
     { strtline = getstartposline(RichEdit->Lines, RichEdit->SelStart); // zmien poczatkowa linie
       endline  = getendposline(RichEdit->Lines, RichEdit->SelStart+RichEdit->SelLength)+1; // i koncowa
     }
   Screen->Cursor = crHourGlass;
  delvertspaces (RichEdit->Lines, strtline, endline);
   Screen->Cursor = crDefault;
  if (RichEdit->CanFocus()) RichEdit->SetFocus();
  if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wlacz napisy jezeli wczesniej byly wlaczone
}
//---------------------------------------------------------------------------
// MENU ->TEKST->INNE->  1 0  --->  10
void __fastcall TForm1::UsunSpacjemiClickiedzyCyframi(TObject *Sender)
{//
  if ( !
      (Application->MessageBox ("Usun¹æ spacje miêdzy cyframi?", "Pytanie", 36)
      == IDYES)) return;
  int wyswietlajnapisy = Wywietlajnapisy1->Checked;
    if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wylacz napisy jezeli wlaczone
     int strtline=0; // poczatkowa linia
     int endline=RichEdit->Lines->Count; // koncowa linia
     if (RichEdit->SelLength>0) // jezeli jest cos zaznaczone
     { strtline = getstartposline(RichEdit->Lines, RichEdit->SelStart); // zmien poczatkowa linie
       endline  = getendposline(RichEdit->Lines, RichEdit->SelStart+RichEdit->SelLength)+1; // i koncowa
     }
   Screen->Cursor = crHourGlass;
  delnumspaces (RichEdit->Lines, strtline, endline);
   Screen->Cursor = crDefault;
  if (RichEdit->CanFocus()) RichEdit->SetFocus();
  if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wlacz napisy jezeli wczesniej byly wlaczone
}
//---------------------------------------------------------------------------
// MENU ->TEKST->INNE-> wytnij informacje o kolorze tekstu
void __fastcall TForm1::Wyczyinformacjeokolorze1Click(TObject *Sender)
{
  if ( !
      (Application->MessageBox ("Usuniêcie informacji o kolorze\n"
       "spowoduje wyczyszczenie wszystkich napisów w nawiasach klamrowych\n"
       "(wy³¹czaj¹c dwie pierwsze pary nawiasów)\n\n"
       "Usun¹æ informacje o kolorach?", "Pytanie", 36)
      == IDYES)) return;

  int wyswietlajnapisy = Wywietlajnapisy1->Checked;
    if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wylacz napisy jezeli wlaczone

     int strtline=0; // poczatkowa linia
     int endline=RichEdit->Lines->Count; // koncowa linia
     if (RichEdit->SelLength>0) // jezeli jest cos zaznaczone
     { strtline = getstartposline(RichEdit->Lines, RichEdit->SelStart); // zmien poczatkowa linie
       endline  = getendposline(RichEdit->Lines, RichEdit->SelStart+RichEdit->SelLength)+1; // i koncowa
     }
   Screen->Cursor = crHourGlass;
  cutcolorinfo (RichEdit->Lines, strtline, endline);
   Screen->Cursor = crDefault;
  if (RichEdit->CanFocus()) RichEdit->SetFocus();

  if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wlacz napisy jezeli wczesniej byly wlaczone
}
//---------------------------------------------------------------------------
// MENU ->OBRAZ-> skok do wybranej klatki filmu
void __fastcall TForm1::Przewidowybranejklatki1Click(TObject *Sender)
{
  if (!formquestion(5)) return;
//    SBPause->Enabled = false;
//    SBStop ->Enabled = false;
//    SBPlay->Enabled = true;
    int frm = atoi (FormPytanie->EditGotoFrm->Text.c_str());
    if (frm>movielength) frm = movielength;
    FormPytanie->EditGotoFrm->Text = IntToStr(frm);
    MediaPlayerNew1->CurrentPosition = frm;
  nowytekst = 1;
  if (RichEdit->CanFocus()) RichEdit->SetFocus();
}
//---------------------------------------------------------------------------
// MENU ->OBRAZ-> Wstaw klatkê filmu do linii (jako klatkê poczatkowa)
void __fastcall TForm1::Wstawklatkfilmudolinii1Click(TObject *Sender)
{
  int pos = MediaPlayerNew1->CurrentPosition;
    pos -= ini.szybkoscreakcji; // odejmuje szybkosc reakcji (patrz USTAWIENIA)
  int cursorpos = RichEdit->CaretPos.y;
  char buf[1024];
  char linia[1024];
    strcpy (linia, RichEdit->Lines->Strings[cursorpos].c_str());
  char wynik[1024];
  if (checkfrmlineerr(linia)&&(strlen(linia)))
  {  // linia jest juz w zapisie klatkowym
    getendfrm (linia, buf);
    int endfrm = atoi(buf); // klatka koncowa
    getfrmtext (linia, buf); // odczytanie tekstu
    putfrmline (pos, endfrm, buf, wynik); // utworzenie nowej linii
  }
  else
    putfrmline (pos, 0, linia, wynik); // utworzenie nowej linii
//  RichEdit->Lines->Delete(cursorpos); // usuniecie starej linii
//  RichEdit->Lines->Insert(cursorpos, wynik); // wpisanie nowej linii
  RichEdit->Lines->Strings[cursorpos] = wynik;
  nowytekst = true; ////////////////////////////////////////////////////////////////////2000-07-22//
}
//---------------------------------------------------------------------------
// MENU ->OBRAZ-> Wstaw klatkê filmu do linii (jako klatkê koñcow¹)
void __fastcall TForm1::Wstawjakokocowklatkfilmudoliniijako1Click(
      TObject *Sender)
{
  int pos = MediaPlayerNew1->CurrentPosition;
  if (ini.uwzglczasreakcjinaendfrm)
    pos -= ini.szybkoscreakcji; // odejmuje szybkosc reakcji (patrz USTAWIENIA)
  int cursorpos = RichEdit->CaretPos.y;
  char buf[1024];
  char linia[1024];
    strcpy (linia, RichEdit->Lines->Strings[cursorpos].c_str());
  char wynik[1024];
  if (checkfrmlineerr(linia)&&(strlen(linia)))
  {  // linia jest juz w zapisie klatkowym
    getstartfrm (linia, buf);
    int startfrm = atoi(buf); // klatka poczatkowa
    getfrmtext (linia, buf); // odczytanie tekstu
    putfrmline (startfrm, pos, buf, wynik); // utworzenie nowej linii
  }
  else
    putfrmline (0, pos, linia, wynik); // utworzenie nowej linii
//  RichEdit->Lines->Delete(cursorpos); // usuniecie starej linii
//  RichEdit->Lines->Insert(cursorpos, wynik); // wpisanie nowej linii
  RichEdit->Lines->Strings[cursorpos] = wynik;
  nowytekst = true; ////////////////////////////////////////////////////////////////////2000-07-22//
}
//---------------------------------------------------------------------------
// MENU ->OBRAZ-> Skok do linii z aktualn¹ klatk¹ &filmu
void __fastcall TForm1::Skokdoliniizaktualnklatkfilmu1Click(
      TObject *Sender)
{
  if (Wywietlajnapisy1->Checked)
  {
    RichEdit->Lines->Strings[line_num-2] = RichEdit->Lines->Strings[line_num-2];
  }
  else
  {
    int a_poz = MediaPlayerNew1->CurrentPosition; // aktualna pozycja filu
    int a_od, a_do, n_od, n_do;
    char tekstnapisu [1024]; // aktualny napis
    line_num = 0;
    for (;;)
    {
        getnextline (a_od, a_do, tekstnapisu);
      int linenum_bak = line_num; // stary nr nastepnej linii
        getnextline (n_od, n_do, tekstnapisu); // odczyt nastepnej linii
      line_num = linenum_bak; // przywrocenie nru linii
      if ((a_do==0)||(a_do<=a_od)) a_do = a_od + ini.iloscklatekwysw; // dlugosc wyswietlania klatek nieokreslonych
      if (a_do>=n_od) a_do=n_od-1; // na wypadek gdyby czas pokazywania byl wiekszy niz czas nastepnego

      if ( ( a_od>=a_poz ) || // poczatkowa klatka wieksza niz pozycja w filmie
           ( a_do>a_poz ) || // koncowa klatka wieksza niz pozycja w filmie ale i nastepna poczatkowa klatka tez musi byc wieksza
           ( a_do==0 ) || // koncowa klatka pusta (zerowa) ale i nastepna poczatkowa klatka tez musi byc wieksza
           ( a_od==9999999 )   ) // koniec pliku
                                 break;
    }
    RichEdit->Lines->Strings[line_num-1] = RichEdit->Lines->Strings[line_num-1];
  }
/*   to jest stary kod ktory okazal sie troche do dupy  wyremowany  2000-07-28
  char buf[1024];
  int startfrm; // poczatkowa klatka
  char linia[1024];
  int i;
  for (i=0; i<RichEdit->Lines->Count; i++)
  { strcpy (linia, RichEdit->Lines->Strings[i].c_str());
    if (!checkfrmlineerr(linia)) continue; // sprawdzenie poprawnosci linii
    if (strlen(linia)==0) continue; // pusta linia
     getstartfrm(linia, buf); // odczyt klatki poczatkowej
     startfrm = atoi(buf);
     if (startfrm > MediaPlayerNew1->CurrentPosition)
     {
       if (i>0) i--;
       RichEdit->Lines->Strings[i] = RichEdit->Lines->Strings[i];
       break;
     }
  }*/
}
//---------------------------------------------------------------------------
// MENU ->OBRAZ-> Odtwarzaj od klatki z aktualnej linii
void __fastcall TForm1::Skokdoklatkizaktualnejlinii1Click(TObject *Sender)
{
  int cursorpos = RichEdit->CaretPos.y;
  char linia[1024];
    strcpy (linia, RichEdit->Lines->Strings[cursorpos].c_str());
  if (!(checkfrmlineerr(linia)&&(strlen(linia)))) return;
  char buf[1024];
    getstartfrm (linia, buf);
    int startfrm = atoi(buf); // klatka poczatkowa
  if (startfrm>movielength) return;
  MediaPlayerNew1->CurrentPosition = startfrm;
  MediaPlayerNew1->Play();
}
//---------------------------------------------------------------------------
// MENU ->OBRAZ-> Pauza / play
void __fastcall TForm1::ZatrzymajOdtwarzaj1Click(TObject *Sender)
{
  // 0-stop; 1-pause; 2-play
  switch (MediaPlayerNew1->PlayState)
  {
    case 0: // zastopowany
      if (MediaPlayerNew1->CurrentPosition==movielength)
        MediaPlayerNew1->CurrentPosition = 0;
      MediaPlayerNew1->Play();
      break;
    case 1: // spauzowany
      MediaPlayerNew1->Play();
      break;
    case 2: // playowany
      MediaPlayerNew1->Pause();
      break;
  }
}
//---------------------------------------------------------------------------
// MENU ->OBRAZ-> stop
void __fastcall TForm1::Zatrzymaj1Click(TObject *Sender)
{
  MediaPlayerNew1->Stop(); // klik na stop
}
//---------------------------------------------------------------------------
// MENU ->OBRAZ-> do przodu o 50 frm
void __fastcall TForm1::DoPrzodu1Click(TObject *Sender)
{//
  MediaPlayerNew1->CurrentPosition += 200; // do przodu o 50 klatek
//  MediaPlayerNew1->Play(); // i kliknij na playu
}
//---------------------------------------------------------------------------
// MENU ->OBRAZ-> do tylu o 50 frm
void __fastcall TForm1::Wsteczo501Click(TObject *Sender)
{
  if (MediaPlayerNew1->CurrentPosition-200<0)
    MediaPlayerNew1->CurrentPosition = 0;
  else
    MediaPlayerNew1->CurrentPosition -= 200; // do tylu o 50 klatek
//  MediaPlayerNew1->Play(); // i kliknij na playu
}
//---------------------------------------------------------------------------
// MENU ->OBRAZ-> skok na poczatek filmu
void __fastcall TForm1::Skokdopocztkufilmu1Click(TObject *Sender)
{//
  MediaPlayerNew1->CurrentPosition = 0;
}
//---------------------------------------------------------------------------
// MENU ->OBRAZ-> skok na koniec filmu
void __fastcall TForm1::Skoknakoniecfilmu1Click(TObject *Sender)
{//
  MediaPlayerNew1->CurrentPosition = movielength;
}
//---------------------------------------------------------------------------
// MENU ->OBRAZ-> Opoznienie filmu wzgledem aktualnej linii
void __fastcall TForm1::Opnieniefilmuwzgl1Click(TObject *Sender)
{
  char linia[1024];
  strcpy ( linia, RichEdit->Lines->Strings[RichEdit->CaretPos.y].c_str() );
  if (!checkfrmlineerr(linia)) return; // blad w aktualnej linii tekstowej
  if (linia[0] == NULL) return; // pusta linia
  getstartfrm (linia, linia);
  int frm = atoi (linia);
    if (ini.uwzglreakcjeprzyopoznieniu) frm -= ini.szybkoscreakcji;
  int pos = MediaPlayerNew1->CurrentPosition;
  strcpy (linia, "OpóŸnienie filmu wzglêdem aktualnej linii wynosi:\n\n");
  char op[15];
  itoa (pos-frm, op, 10);
  strcat (linia, op);
  FormPytanie->EditFrm->Text = op; // wpisuje ta wartosc jako domyslne przesuniecie tekstu
  strcat (linia, "\n\nU¿yj \"Edycja -> Dodaj/Odejmij klatki\" do zniwelowania opóŸnienia.");
  Application->MessageBox (linia, "OpóŸnienie filmu", 64);
}
//---------------------------------------------------------------------------
// MENU ->OBRAZ-> poczatkowe przesuniecie geometryczne
void __fastcall TForm1::Zbadajpoczatkoweopnienietekstu1Click(TObject *Sender)
{//
// frf1, frf2, frn1, frn2
//frnapis1, frnapis2; // napis z tej linii
//frnrlin1, frnrlin2; // numer linii z napisem
// GeomPocz=false, GeomKon=false;
  char linia[1024];
  strcpy ( linia, RichEdit->Lines->Strings[frnrlin1=RichEdit->CaretPos.y].c_str() );
  frnrlin1++;
  if (!checkfrmlineerr(linia)) return; // blad w aktualnej linii tekstowej
  if (linia[0] == NULL) return; // pusta linia
  GeomPocz=true;
  frnapis1=linia;
  getstartfrm (linia, linia);
  frn1 = atoi (linia);
    if (ini.uwzglreakcjeprzyopoznieniu) frn1 -= ini.szybkoscreakcji;
  frf1 = MediaPlayerNew1->CurrentPosition;
  if ( (GeomKon)&&(frn2>frn1)&&(frf2>frf1) )
    Form1->GeometryczneOp->Enabled = true;
  else
    Form1->GeometryczneOp->Enabled = false;
}
//---------------------------------------------------------------------------
// MENU ->OBRAZ-> koncowe przesuniecie geometryczne
void __fastcall TForm1::Zbadajkocoweopnienietekstu1Click(TObject *Sender)
{//
  char linia[1024];
  strcpy ( linia, RichEdit->Lines->Strings[frnrlin2=RichEdit->CaretPos.y].c_str() );
  frnrlin2++;
  if (!checkfrmlineerr(linia)) return; // blad w aktualnej linii tekstowej
  if (linia[0] == NULL) return; // pusta linia
  GeomKon=true;
  frnapis2=linia;
  getstartfrm (linia, linia);
  frn2 = atoi (linia);
    if (ini.uwzglreakcjeprzyopoznieniu) frn2 -= ini.szybkoscreakcji;
  frf2 = MediaPlayerNew1->CurrentPosition;
  if ( (GeomPocz)&&(frn2>frn1)&&(frf2>frf1) )
    Form1->GeometryczneOp->Enabled = true;
  else
    Form1->GeometryczneOp->Enabled = false;
}
//---------------------------------------------------------------------------
// MENU ->OBRAZ-> zmien klatki w sposob geometryczny
void __fastcall TForm1::GeometryczneOpClick(TObject *Sender)
{//
// frf1, frf2, frn1, frn2
//frnapis1, frnapis2; // napis z tej linii
//frnrlin1, frnrlin2; // numer linii z napisem
  AnsiString pytanie;
  pytanie = "Przesun¹æ napisy w sposób geometryczny?\n\n";
  pytanie+= "Przesuniêcia napisów wzglêdem filmu:\n  ";
  pytanie+= "#"+IntToStr(frnrlin1);
  pytanie+= ":\t"+frnapis1+"\t"+IntToStr(frn1-frf1)+"\n  ";
  pytanie+= "#"+IntToStr(frnrlin2);
  pytanie+= ":\t"+frnapis2+"\t"+IntToStr(frn2-frf2)+"\n  ";
  if ( !
        (Application->MessageBox (pytanie.c_str(), "Pytanie", 36)
      == IDYES)) return;

  int wyswietlajnapisy = Wywietlajnapisy1->Checked;
    if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wylacz napisy jezeli wlaczone

    SendMessage(Form1->RichEdit, WM_SETREDRAW, 0, 0);
     int strtline=0; // poczatkowa linia
     int endline=RichEdit->Lines->Count; // koncowa linia
     if (RichEdit->SelLength>0) // jezeli jest cos zaznaczone
     { strtline = getstartposline(RichEdit->Lines, RichEdit->SelStart); // zmien poczatkowa linie
       endline  = getendposline(RichEdit->Lines, RichEdit->SelStart+RichEdit->SelLength)+1; // i koncowa
     }
    geomchange (RichEdit->Lines, strtline, endline,
                frf1, frf2, frn1, frn2);
  //  SendMessage(RichEdit, WM_SETREDRAW, 1, 0);
  if (RichEdit->CanFocus()) RichEdit->SetFocus();
  nowytekst = 1; // klatki zostaly zmienione (do napisuf)

  if (wyswietlajnapisy) TForm1::Wywietlajnapisy1Click(Sender); // wlacz napisy jezeli wczesniej byly wlaczone
}
//---------------------------------------------------------------------------
// MENU tryb pelnoekranowy
void __fastcall TForm1::Trybpe1Click(TObject *Sender)
{ //
  MediaPlayerNew1->DisplaySize = mpFullScreen;
  MediaPlayerNew1->Play();
//  MediaPlayerNew1->contr
}
//---------------------------------------------------------------------------
// MENU wyswietlaj napisy
void __fastcall TForm1::Wywietlajnapisy1Click(TObject *Sender)
{
  Wywietlajnapisy1->Checked = !Wywietlajnapisy1->Checked;
  TimerNapisy->Enabled = Wywietlajnapisy1->Checked;
  if (Wywietlajnapisy1->Checked)
  { // wlaczone napisy
    SpeedButtonShowSubTit->Hint =
      "Nie wyœwietlaj napisów (Shift+Ctrl+N)";
    PanelShowSubStatus->Color = clRed;
    SpeedButtonShowSubTit->Down = true;
  }
  else
  { // wylaczone napisy
    SpeedButtonShowSubTit->Hint =
      "Wyœwietlaj napisy (Shift+Ctrl+N)";
    FormNapisy->Visible= false;
    PanelShowSubStatus->Color = clBtnFace;
    SpeedButtonShowSubTit->Down = false;
  }
//  SpeedButtonShowSubStatus->Enabled = Wywietlajnapisy1->Checked;
  nowytekst = 1;
}
//---------------------------------------------------------------------------
// MENU ->POMOC-> mo¿liwosci programu
void __fastcall TForm1::Moliwociprogramu1Click(TObject *Sender)
{//
  FormMozliwosci->ShowModal();
}
//---------------------------------------------------------------------------
// MENU ->POMOC-> pomoc
void __fastcall TForm1::Pomoc2Click(TObject *Sender)
{
  FormPomoc->ShowModal();
}
//---------------------------------------------------------------------------
// MENU ->POMOC-> about
void __fastcall TForm1::Informacjeoprogramie1Click(TObject *Sender)
{
  FormInformacje->ShowModal();
}

//------------- OBSLUGA PRZYCISKOE NA TOOLBARZE -----------------------------
//------------- OBSLUGA PRZYCISKOE NA TOOLBARZE -----------------------------
//------------- OBSLUGA PRZYCISKOE NA TOOLBARZE -----------------------------
//------------- OBSLUGA PRZYCISKOE NA TOOLBARZE -----------------------------
//------------- OBSLUGA PRZYCISKOE NA TOOLBARZE -----------------------------
//------------- OBSLUGA PRZYCISKOE NA TOOLBARZE -----------------------------
// nowy
void __fastcall TForm1::SpeedButtonNewClick(TObject *Sender)
{
  TForm1::Nowy1Click(Sender);
}
//---------------------------------------------------------------------------
// open wideo
void __fastcall TForm1::SpeedButtonOpenVideoClick(TObject *Sender)
{
  TForm1::Otwrzplikwideo1Click(Sender);
}
//---------------------------------------------------------------------------
// open
void __fastcall TForm1::SpeedButtonOpenClick(TObject *Sender)
{
  TForm1::Open1Click(Sender);
}
//---------------------------------------------------------------------------
// saveas
void __fastcall TForm1::SpeedButtonSaveasClick(TObject *Sender)
{
  TForm1::ZapiszJako1Click(Sender);
}
//---------------------------------------------------------------------------
// save
void __fastcall TForm1::SpeedButtonSaveClick(TObject *Sender)
{
  TForm1::Zapisz1Click(Sender);
}
//---------------------------------------------------------------------------
// find
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
  TForm1::ZnajdzTekst1Click(Sender);
}
//---------------------------------------------------------------------------
// addfrm
void __fastcall TForm1::SpeedButtonAddFramesClick(TObject *Sender)
{
  TForm1::DodajKlatkiClick(Sender);//
}
//---------------------------------------------------------------------------
// changeshowtime
void __fastcall TForm1::SpeedButtonChangeShowTimeClick(TObject *Sender)
{
  TForm1::ZmienIloscKlatekClick(Sender);//
}
//---------------------------------------------------------------------------
// zmiana wsp. fps napisow
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{//
  Form1->Zmianailociklateknasekund1Click(Sender);
}
//---------------------------------------------------------------------------
// Time2Frm
void __fastcall TForm1::SpeedButtonTime2FrmClick(TObject *Sender)
{
  TForm1::CzasKlatkaClick(Sender);//
}
//---------------------------------------------------------------------------
// frm2time
void __fastcall TForm1::SpeedButtonFrm2TimeClick(TObject *Sender)
{
  TForm1::KlatkaCzasClick(Sender);//
}
//---------------------------------------------------------------------------
// wyczysc puste linie
void __fastcall TForm1::SpeedButtonCutEntersClick(TObject *Sender)
{
  TForm1::WyczyscPusteLinieClick(Sender);
}
//---------------------------------------------------------------------------
// sortuj linia
void __fastcall TForm1::SpeedButtonSortClick(TObject *Sender)
{//
  TForm1::PosortujNapisyClick(Sender);
}
//---------------------------------------------------------------------------
// show subtitles
void __fastcall TForm1::SpeedButtonShowSubTitClick(TObject *Sender)
{
  TForm1::Wywietlajnapisy1Click(Sender);
}
//---------------------------------------------------------------------------
// fullscreen
void __fastcall TForm1::SpeedButtonFullScreenClick(TObject *Sender)
{//
  Form1->Trybpe1Click(Sender);
}

//---------- OBSLUGA ZDARZEN ------------------------------------------------
//---------- OBSLUGA ZDARZEN ------------------------------------------------
//---------- OBSLUGA ZDARZEN ------------------------------------------------
//---------- OBSLUGA ZDARZEN ------------------------------------------------
//---------- OBSLUGA ZDARZEN ------------------------------------------------
//---------- OBSLUGA ZDARZEN ------------------------------------------------
// EVENT on show dla formatki
void __fastcall TForm1::FormCreate(TObject *Sender)
{
  Application->HintHidePause = 5000;

  // ustawienia mediaplayera
  MediaPlayerNew1->EnableFullScreenControls = true; // wlacza panel na pelnym ekranie
  MediaPlayerNew1->AutoRewind = true; // automatyczne przewijanie na poczatek

  AnsiString inifilename;
//  inifilename = ExtractFilePath (Application->ExeName)+"SubEdit.ini";
  inifilename = "SubEdit.ini";
  inifile = new TIniFile(inifilename); // przydziela pamiec dla pliku SubTitle.ini

  pelnyekran = MediaPlayerNew1->DisplaySize==mpFullScreen;
}
//---------------------------------------------------------------------------
bool ininieczytane = true;
void __fastcall TForm1::FormShow(TObject *Sender)
{//
    if (ininieczytane) // odczytuje tylko raz
    {
      FormInformacje->LabelVersion->Caption = "v."+ver+"  build "+build;
      FormInformacje->LabelDate->Caption = "2000-07-14  -  "+ldate;
      readinifile (inifile); // odczytuje plik ini
//      lastwindowstate = Form1->WindowState;
      ininieczytane = false;
      Form1->FontDialog->Font = FormNapisy->LabelNapis1->Font; //////////////////

        zamknijplikwideo();

        // AUTOMATYCZNE WCZYTYWANIE PLIKOW PODANYCH JAKO PARAMETRY
        bool movie = false; // czy juz wgrany plik wideo
        bool txt = false; // czy juz wgrany plik txt
        const int numofmov = 13;
        const int numoftxt = 2;
        char emov[numofmov][5] = // pliki z filmami
          {"avi","mpg","mpe","mpeg","mov","asf","m1v","mp2","ivf","mp2v","mpa","mpv2","qt"};
        char etxt[numoftxt][4] = {"sub", "txt"}; // pliki z podpisami
        for (int i=0; i<ParamCount(); i++)
        {
          char filename[1024];
          strcpy (filename, ParamStr(i+1).c_str());
          if (!movie) // jezeli nie zostal juz wczytany plik wideo
            for (int j=0; j<numofmov; j++) // pliki wideo
              if (checkfileext(filename, emov[j]))
              {
                movie = true;
                openvideofile (filename);
                break;
              }
          if (!txt) // jezeli nie zostal znaleziony plik tekstowy
            for (int j=0; j<numoftxt; j++) // pliki tekstowe
              if (checkfileext(filename, etxt[j]))
              {
                txt = true;
                opentextfile(filename);
                break;
              }
        }
      if (Form1->RichEdit->CanFocus()) RichEdit->SetFocus();
      if (ini.firststart) FormMozliwosci->ShowModal();
    }
}
//---------------------------------------------------------------------------
// EVENT on close
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
  writeinifile(inifile);
}
//---------------------------------------------------------------------------
// EVENT on close query
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  CanClose = zamknijaktualnypliktekstowy ();
/*  if (Application->MessageBox ("Are You Sure?","Exit Program",36) == IDYES)
    CanClose = True;
  else CanClose = False;
*/
}
//---------------------------------------------------------------------------
// EVENT on destroy
void __fastcall TForm1::FormDestroy(TObject *Sender)
{//
  delete inifile;
}
//---------------------------------------------------------------------------
// EVENT Po przesunieciu traka na Playerze.
void __fastcall TForm1::MediaPlayerNew1PositionChange(TObject *Sender,
      double oldPosition, double newPosition)
{
  nowytekst = true;
}
//---------------------------------------------------------------------------
// EVENT ON TIMER
//int oldpos=0;
void __fastcall TForm1::TimerTimer(TObject *Sender)
{
  int pos = MediaPlayerNew1->CurrentPosition;
  Form1->StatusBar->Panels->Items[0]->Text = "{"+IntToStr(pos)+"}{"+IntToStr(movielength)+"}";
// obsluga czasu
    aktualnyczasfilmu (float(dlugoscfilmu)/float(movielength)*float(pos));

// sprawdza, czy tryb pelnoekranowy czy nie
  bool temp_pelnyekran = MediaPlayerNew1->DisplaySize == mpFullScreen;

  if (pelnyekran)
    if (!temp_pelnyekran)
    { // zmiana: fullscreen -> normalscreen
      Form1->Show();
//      Form1->WindowState = TWindowState(lastwindowstate);
      pelnyekran = false;
      Trybpe1->Checked = pelnyekran;
      SpeedButtonFullScreen->Down = pelnyekran;
      try{RichEdit->SetFocus();}catch(...){};
    }
  if (!pelnyekran)
    if (temp_pelnyekran)
    { // zmiana: normalscreen -> fullscreen
      Form1->Hide();
//      lastwindowstate = Form1->WindowState;
//      Form1->WindowState = wsMinimized;
      pelnyekran = true;
      Trybpe1->Checked = pelnyekran;
      SpeedButtonFullScreen->Down = pelnyekran;
    }
}
//---------------------------------------------------------------------------
// EVENT on Find dla FindDialogu
void __fastcall TForm1::FindFind(TObject *Sender)
{//

  TSearchTypes opcje;  // stWholeWord  stMatchCase
  if (  Find->Options.Contains(frWholeWord) ) // tylko cale wyrazy
    opcje = opcje << stWholeWord;
  if (  Find->Options.Contains(frMatchCase) ) // uwzglednia wielkosc liter
    opcje = opcje << stMatchCase;

  int ZnalezionyNa, SzukajOd, SzukajDlugosc;

  if (RichEdit->SelLength)
    SzukajOd = RichEdit->SelStart + RichEdit->SelLength;
  else
    SzukajOd = 0;
  SzukajDlugosc = RichEdit->Text.Length() - SzukajOd;

  ZnalezionyNa = RichEdit->FindText(Find->FindText, SzukajOd, SzukajDlugosc, opcje);
  if (ZnalezionyNa != -1)
  {
//    RichEdit->SetFocus();
    RichEdit->SelStart = ZnalezionyNa;
    RichEdit->SelLength = Find->FindText.Length();
  }
  else
    Application->MessageBox ("Przeszukiwanie zakoñczone", "Szukaj tekstu", 64);
}
//---------------------------------------------------------------------------
// EVENT po wywolaniu finda wlacz pokazywanie zaznaczenia kiedy richedit nie ma fokusa
void __fastcall TForm1::FindShow(TObject *Sender)
{
  RichEdit->HideSelection = false;
}
//---------------------------------------------------------------------------
// EVENT a tu wylacz
void __fastcall TForm1::FindClose(TObject *Sender)
{
  RichEdit->HideSelection = true;
}
//---------------------------------------------------------------------------
// EVENT on key down dla media playera
void __fastcall TForm1::MediaPlayerNew1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
//  Application->MessageBox("MP","",0);
  FormNapisy->FormKeyDown(Sender, Key, Shift);
}
//------------------ INNE FUNKCJE DODANE PRZEZ BUILDERA ---------------------
//------------------ INNE FUNKCJE DODANE PRZEZ BUILDERA ---------------------
//------------------ INNE FUNKCJE DODANE PRZEZ BUILDERA ---------------------
//------------------ INNE FUNKCJE DODANE PRZEZ BUILDERA ---------------------
//------------------ INNE FUNKCJE DODANE PRZEZ BUILDERA ---------------------
//------------------ INNE FUNKCJE DODANE PRZEZ BUILDERA ---------------------
// obsluga polozenia kursora i ilosci linii
void __fastcall TForm1::RichEditEnter(TObject *Sender)
{
  char buf[20];
  char buf2[10];
  itoa (RichEdit->CaretPos.y+1, buf, 10);
  itoa (RichEdit->Lines->Count+1, buf2, 10);
  strcat( strcat( strcat (buf, ":"), buf2), " ");
  LabelCursorPos->Caption = buf;
}
void __fastcall TForm1::RichEditKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{ TForm1::RichEditEnter(Sender);}
void __fastcall TForm1::RichEditMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{ TForm1::RichEditEnter(Sender); }
int starailosclinii = -2; // ilosc linii tekstu przed wywolaniem tej funkcji
void __fastcall TForm1::RichEditChange(TObject *Sender)
{
  Zapisz1->Enabled = RichEdit->Modified; // MENU save
  SpeedButtonSave->Enabled = RichEdit->Modified; // Button SAVE
  Form1->LabelFileName->Font->Style = Form1->LabelFileName->Font->Style << fsBold; // fonty z nazwa pliku

  TForm1::RichEditEnter(Sender);
  if (starailosclinii!=RichEdit->Lines->Count)
  {
    nowytekst = 1; // odczytaj na nowo tekst
    starailosclinii = RichEdit->Lines->Count;
  }
}
//---------------------------------------------------------------------------
//  Zmiana fontuf  -  APPLY
void __fastcall TForm1::FontDialogApply(TObject *Sender, HWND Wnd)
{//
  ZmienCzcionke (Sender);
}

//----------- TIMER DO WYSWIETLANIA NAPISUF ---------------------------------
//----------- TIMER DO WYSWIETLANIA NAPISUF ---------------------------------
//----------- TIMER DO WYSWIETLANIA NAPISUF ---------------------------------
//----------- TIMER DO WYSWIETLANIA NAPISUF ---------------------------------
//----------- TIMER DO WYSWIETLANIA NAPISUF ---------------------------------
//----------- TIMER DO WYSWIETLANIA NAPISUF ---------------------------------
// timer od napisuf   // TimerNapisy
  void showsub (char *tekstnapisu) // pokazuje napisy
  { // do pokazaniu subtitla
    pokazywany = 1;
    showsubtitle (FormNapisy->LabelNapis1,
             FormNapisy->LabelNapis2, tekstnapisu);
    FormNapisy->Visible = true;
//    if (!Form1->CheckBoxWOknie->Checked) Form1->RichEdit->SetFocus(); // dawaj fokusa na rich edita tylko jak film jest wyswietlany w oknie programu
    if (ini.RichEditFocus && (Form1->MediaPlayerNew1->DisplaySize!=mpFullScreen))
    {
      try
      {Form1->RichEdit->SetFocus(); // dawaj fokusa na rich edita (z USTAWIENIA)
      }
      catch(...){}
    }
  }
  void hidesub (void) // chowa napisy
  {
    pokazywany = 0;
    FormNapisy->Visible = false;
  }

  int getnextline(int &n_od, int &n_do, char *tekstnapisu)
  {
//    Form1->RichEdit->selatrib
    char linia [1024];
    for (line_num; line_num<Form1->RichEdit->Lines->Count; line_num++)
    {
      strcpy(linia, Form1->RichEdit->Lines->Strings[line_num].c_str());
      if (checkfrmlineerr(linia)&&(strlen(linia)>0)) break; // linia jest OK
    }
    if (line_num>=Form1->RichEdit->Lines->Count) // koniec linii z napisami
    {
      n_od = 9999999; // max duzy zeby nigdy nie byl wyswietlony
      strcpy (tekstnapisu, "TEN TEKST NIE POWINIEN|SIÊ WYŒWIETLIÆ");
      return 0; // napisy siem skoniczyly
    }
    getstartfrm(linia, tekstnapisu);
      n_od = atoi (tekstnapisu); // poczatkowa klatka
    getendfrm(linia, tekstnapisu);
      n_do = atoi (tekstnapisu); // koncowa klatka
    getfrmtext (linia, tekstnapisu); // napis
    line_num++;
    return 1; // wsjo oki
  }
//////////////////////////////////////////////////////////////////////////////
  char tekstnapisu [1024]; // aktualny napis
  char n_tekstnapisu [1024]; // nastepny napis
int a_poz;      // aktualna pozycja filmu;
int old_poz;    // stara pozycja filmu;
int a_od, a_do; // aktualne klatki
int n_od, n_do; // nastepne klatki
//int nowytekst=1;
void __fastcall TForm1::TimerNapisyTimer(TObject *Sender)
{//
  a_poz = MediaPlayerNew1->CurrentPosition; // aktualna pozycja filu
  if (nowytekst) // trza znalezc nowa pozycje aktualnego tekstu
  {
    line_num = 0;
    for (;;)
    {
        getnextline (a_od, a_do, tekstnapisu);
//      if ((a_od>=a_poz)||(a_od==9999999))
//      if ( (a_od>=a_poz) || (a_do>a_poz) || (a_od==9999999) )
//      if ( (a_od>=a_poz) || ((a_od<=a_poz)&&(a_do>a_poz)) || (a_od==9999999) )
//      if ( (a_od>=a_poz) || ((a_od<=a_poz)&&((a_do>a_poz)||(a_do==0))) || (a_od==9999999) )
//      if ( (a_od>=a_poz) || ((a_od<=a_poz)&&((a_do>a_poz)||((a_do==0)&&(a_od+200>a_poz)))) || (a_od==9999999) )
//      if ( (a_od>=a_poz) || (a_do>a_poz) || ((a_do==0)&&(a_od+200>a_poz)) || (a_od==9999999) )
//      if ( (a_od>=a_poz) || ((a_do>a_poz)&&(n_od>a_poz)) || ((a_do==0)&&(n_od>a_poz)) || (a_od==9999999) )

      int linenum_bak = line_num; // stary nr nastepnej linii
        getnextline (n_od, n_do, n_tekstnapisu); // odczyt nastepnej linii
      line_num = linenum_bak; // przywrocenie nru linii
//                 /   dodane   \ 2000-07-25
      if ((a_do==0)||(a_do<=a_od)) a_do = a_od + ini.iloscklatekwysw; // dlugosc wyswietlania klatek nieokreslonych
      if (a_do>=n_od) a_do=n_od-1; // na wypadek gdyby czas pokazywania byl wiekszy niz czas nastepnego

      if ( ( a_od>=a_poz ) || // poczatkowa klatka wieksza niz pozycja w filmie
           ( a_do>a_poz ) || // koncowa klatka wieksza niz pozycja w filmie ale i nastepna poczatkowa klatka tez musi byc wieksza
           ( a_do==0 ) || // koncowa klatka pusta (zerowa) ale i nastepna poczatkowa klatka tez musi byc wieksza
           ( a_od==9999999 )   ) // koniec pliku
      {
        getnextline (n_od, n_do, n_tekstnapisu); // odczyt nastepnej linii
        break;
      }
    }
    nowytekst = 0; // aktualna linia znaleziona
    hidesub (); // pokazywany = 0;
  }

  if (!pokazywany) // ten tekst jest jusz pokazywany
  {
    if (a_poz>=a_od) // zaczal sie czas pokazywania
    {
      showsub (tekstnapisu);
      if ((a_do==0)||(a_do<=a_od)) a_do = a_od + ini.iloscklatekwysw; // dlugosc wyswietlania klatek nieokreslonych
      if (a_do>=n_od) a_do=n_od-1; // na wypadek gdyby czas pokazywania byl wiekszy niz czas nastepnego
    }
  }
  else // ten tekst jest jusz pokazywany
  {
    if ((a_poz>a_do)||(a_poz>=movielength)) // skonczyl sie czas pokazywania
    {
      hidesub ();
      a_od = n_od;
      a_do = n_do;
      strcpy (tekstnapisu, n_tekstnapisu);
      getnextline(n_od, n_do, n_tekstnapisu);
    }
  }

   // tu powtorka tego samego, tak na wszelki wypadek gdyby trza bylo od razu po schowaniu pokazac nowy
  if (!pokazywany) // ten tekst jest jusz pokazywany
  {
    if (a_poz>=a_od) // zaczal sie czas pokazywania
    {
      showsub (tekstnapisu);
      if ((a_do==0)||(a_do<=a_od)) a_do = a_od + ini.iloscklatekwysw; // dlugosc wyswietlania klatek nieokreslonych
      if (a_do>=n_od) a_do=n_od-1; // na wypadek gdyby czas pokazywania byl wiekszy niz czas nastepnego
    }
  }
}
//---------------------------------------------------------------------------


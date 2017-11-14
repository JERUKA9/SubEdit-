//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//#include <MPlayer.hpp>
//#include <OleCtnrs.hpp>
//#include <ImgList.hpp>
#include "MediaPlayer_OCX.h"
#include <OleCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TOpenDialog *Open;
        TSaveDialog *Save;
        TMenuItem *Plik1;
        TMenuItem *ZapiszJako1;
        TMenuItem *Zapisz1;
        TMenuItem *Open1;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *Exit1;
        TMenuItem *Edycja1;
        TToolBar *ToolBar1;
        TSpeedButton *SpeedButtonOpen;
        TSpeedButton *SpeedButtonSave;
        TSpeedButton *SpeedButtonTime2Frm;
        TToolButton *ToolButton1;
        TSpeedButton *SpeedButtonFrm2Time;
        TToolButton *ToolButton2;
        TSpeedButton *SpeedButtonAddFrames;
        TSpeedButton *SpeedButtonChangeShowTime;
        TSpeedButton *SpeedButtonNew;
        TSpeedButton *SpeedButtonCutEnters;
        TMenuItem *N6;
        TMenuItem *Nowy1;
        TMenuItem *Pomoc1;
        TMenuItem *Informacjeoprogramie1;
        TMenuItem *Otwrzplikwideo1;
        TSpeedButton *SpeedButtonOpenVideo;
        TOpenDialog *OpenVideo;
        TTimer *Timer;
        TMenuItem *Pomoc2;
        TMenuItem *Opcjenapisw1;
        TFontDialog *FontDialog;
        TTimer *TimerNapisy;
        TToolButton *ToolButton3;
        TSpeedButton *SpeedButtonShowSubTit;
        TMenuItem *N1;
        TMenuItem *Ustawieniaprogramu1;
        TMenuItem *N10;
        TMenuItem *ZnajdzTekst1;
        TFindDialog *Find;
        TToolButton *ToolButton4;
        TSpeedButton *SpeedButton1;
        TMenuItem *N11;
        TMenuItem *Zamknijplikwideo1;
        TSpeedButton *SpeedButtonSort;
        TPanel *PanelText;
        TRichEdit *RichEdit;
        TPanel *PanelTitle;
        TLabel *LabelFileName;
        TLabel *LabelCursorPos;
        TPanel *PanelShowSubStatus;
        TMenuItem *Tekst1;
        TMenuItem *Obraz1;
        TMenuItem *CzasKlatka1;
        TMenuItem *KlatkaCzas1;
        TMenuItem *N5;
        TMenuItem *Dodajodejmijklatki1;
        TMenuItem *Zmieiloklatekwywietlanianapisu1;
        TMenuItem *Usuinformacjeokolorzenapisu1;
        TMenuItem *Posortujnapisyrosnco1;
        TMenuItem *Wyczypustelinieentery1;
        TMenuItem *Przesuteksto5klatekdoprzodu1;
        TMenuItem *Przesuteksto5klatekdotyu1;
        TMenuItem *Inne1;
        TMenuItem *Ususpacjezaiprzed1;
        TMenuItem *Ususpacjemidzycyframi10101;
        TMenuItem *Usupodwjnespacje1;
        TMenuItem *Skokdowybranejklatkifilmu1;
        TMenuItem *N2;
        TMenuItem *Wstawklatkfilmudoliniijakoklatkpoczrkow1;
        TMenuItem *Wstawklatkfilmudoliniijakoklatkkocow1;
        TMenuItem *Wstawklatkinnyskrt1;
        TMenuItem *Skokdoliniizaktualnklatkfilmu1;
        TMenuItem *N7;
        TMenuItem *PauzaOdtwarzaj1;
        TMenuItem *Stop1;
        TMenuItem *Skokdoprzoduo50klatek1;
        TMenuItem *Skokwsteczo50klatek1;
        TMenuItem *N8;
        TMenuItem *Zmierzopnienielinii1;
        TMenuItem *Zmierzpocztkoweopnienienapisw1;
        TMenuItem *Zmierzkocoweopnienienapisw1;
        TMenuItem *GeometryczneOp;
        TMenuItem *N12;
        TMenuItem *Wywietlajnapisy1;
        TMenuItem *Znajdramk1;
        TMenuItem *Kopiuj1;
        TMenuItem *Wklej1;
        TStatusBar *StatusBar;
        TSplitter *Splitter;
        TMediaPlayerNew *MediaPlayerNew1;
        TSpeedButton *SpeedButtonFullScreen;
        TMenuItem *Skokdopocztkufilmu1;
        TMenuItem *Skoknakoniecfilmu1;
        TMenuItem *Przewijanie1;
        TMenuItem *Opnieniegeometryczne1;
        TMenuItem *N13;
        TMenuItem *N9;
        TMenuItem *Trybpe1;
        TMenuItem *Odtwarzajfilmodklatki1;
        TMenuItem *Zmianailociklateknasekund1;
        TMenuItem *Moliwociprogramu1;
        TSpeedButton *SpeedButton2;
        void __fastcall SpeedButtonOpenClick(TObject *Sender);
        void __fastcall Open1Click(TObject *Sender);
        void __fastcall SpeedButtonSaveasClick(TObject *Sender);
        void __fastcall ZapiszJako1Click(TObject *Sender);
        void __fastcall Zapisz1Click(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall SpeedButtonAddFramesClick(TObject *Sender);
        void __fastcall SpeedButtonSaveClick(TObject *Sender);
        void __fastcall RichEditEnter(TObject *Sender);
        void __fastcall RichEditKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall RichEditChange(TObject *Sender);
        void __fastcall RichEditMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall SpeedButtonChangeShowTimeClick(TObject *Sender);
        void __fastcall SpeedButtonTime2FrmClick(TObject *Sender);
        void __fastcall SpeedButtonFrm2TimeClick(TObject *Sender);
        void __fastcall CzasKlatkaClick(TObject *Sender);
        void __fastcall KlatkaCzasClick(TObject *Sender);
        void __fastcall DodajKlatkiClick(TObject *Sender);
        void __fastcall ZmienIloscKlatekClick(TObject *Sender);
        void __fastcall Wyczyinformacjeokolorze1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall SpeedButtonNewClick(TObject *Sender);
        void __fastcall SpeedButtonCutEntersClick(TObject *Sender);
        void __fastcall Nowy1Click(TObject *Sender);
        void __fastcall Informacjeoprogramie1Click(TObject *Sender);
        void __fastcall Otwrzplikwideo1Click(TObject *Sender);
        void __fastcall SpeedButtonOpenVideoClick(TObject *Sender);
        void __fastcall TimerTimer(TObject *Sender);
        void __fastcall Przewidowybranejklatki1Click(TObject *Sender);
        void __fastcall Skokdoklatkizaktualnejlinii1Click(TObject *Sender);
        void __fastcall Skokdoliniizaktualnklatkfilmu1Click(
          TObject *Sender);
        void __fastcall Wstawklatkfilmudolinii1Click(TObject *Sender);
        void __fastcall Wstawjakokocowklatkfilmudoliniijako1Click(
          TObject *Sender);
        void __fastcall Pomoc2Click(TObject *Sender);
        void __fastcall ZatrzymajOdtwarzaj1Click(TObject *Sender);
        void __fastcall Wywietlajnapisy1Click(TObject *Sender);
        void __fastcall Opcjenapisw1Click(TObject *Sender);
        void __fastcall TimerNapisyTimer(TObject *Sender);
        void __fastcall SpeedButtonShowSubTitClick(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Ustawieniaprogramu1Click(TObject *Sender);
        void __fastcall Zatrzymaj1Click(TObject *Sender);
        void __fastcall DoPrzodu1Click(TObject *Sender);
        void __fastcall Wsteczo501Click(TObject *Sender);
        void __fastcall Opnieniefilmuwzgl1Click(TObject *Sender);
        void __fastcall ZnajdzTekst1Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall FindFind(TObject *Sender);
        void __fastcall FindShow(TObject *Sender);
        void __fastcall FindClose(TObject *Sender);
        void __fastcall Zamknijplikwideo1Click(TObject *Sender);
        void __fastcall FontDialogApply(TObject *Sender, HWND Wnd);
        void __fastcall PrzesunTekst5DoPrzoduClick(TObject *Sender);
        void __fastcall PrzesunTekst5DoTyluClick(
          TObject *Sender);
        void __fastcall WyczyscPusteLinieClick(TObject *Sender);
        void __fastcall PosortujNapisyClick(TObject *Sender);
        void __fastcall SpeedButtonSortClick(TObject *Sender);
        void __fastcall Zbadajpoczatkoweopnienietekstu1Click(TObject *Sender);
        void __fastcall Zbadajkocoweopnienietekstu1Click(TObject *Sender);
        void __fastcall GeometryczneOpClick(TObject *Sender);
        void __fastcall UsunSpacjemiClickiedzyCyframi(TObject *Sender);
        void __fastcall UsuSpacjeZaiPrzedClick(TObject *Sender);
        void __fastcall UsunPodwjneSpacje1Click(TObject *Sender);
        void __fastcall Znajdramk1Click(TObject *Sender);
        void __fastcall Kopiuj1Click(TObject *Sender);
        void __fastcall Wklej1Click(TObject *Sender);
        void __fastcall MediaPlayerNew1PositionChange(TObject *Sender,
          double oldPosition, double newPosition);
        void __fastcall SpeedButtonFullScreenClick(TObject *Sender);
        void __fastcall Skokdopocztkufilmu1Click(TObject *Sender);
        void __fastcall Skoknakoniecfilmu1Click(TObject *Sender);
        void __fastcall Trybpe1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall MediaPlayerNew1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Zmianailociklateknasekund1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall Moliwociprogramu1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

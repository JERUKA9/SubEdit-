#include <string.h>
#include <stdlib.h>
// do zapisu klatkowego
int checkfrmlineerr (char *linia); // sprawdza czy linia jest poprawna
int getstartfrm (char *linia, char *wynik); // zwraca ramke startowa z wyslanej linii
int getendfrm (char *linia, char *wynik); // zwraca ramke koncowa z wyslanej linii
int getfrmtext (char *linia, char *wynik); // zwraca tekst linii
int cutcolor (char *linia); // obcina tekst z informacji o kolorze
int putfrmline (int start, int end, char *text, char *wynik); // tworzy linie z podanych danych
// do formatu czasowego
int gettimeformat (char *linia); // sprawdza w jakim formacie jest zapis czasu
int checktimelineerr (char *linia); // sprawdza czy linia jest poprawna
int lasttimeline (char *linia); // sprawdza czy linia jest == "0:00:00:"
int getstarttime (char *linia, int &h, int &m, int &s); // zwraca godzine, minute i sekunde z danej linii
int gettimetext (char *linia, char *wynik); // zwraca tekst linii
int puttimeline (int h, int m, int s, char *tekst, char *linia); // utworzenie nowej linii

// foramt zapisu czasowego
int timeformat = 0;
/*
0 = zaden z ponizszych
1 = '0:00:00:'
2 = '00:00:13:'
3 = '00:00:13 '
*/
////////////////////////////////////////////////////////////////////////////////
// funkcje do operacji na TString'u
int addfrm(TStrings *Lines, int ile, bool from, bool to, int strtline, int endline); // dodaje/odejmuje framesy (mo¿e odejmowac od poczatkowego, koncowego lub obu)
int fpsratechange(TStrings *Lines, float aktualna, float docelowy, int strtline, int endline); // zmienia napisy z jednego fps na inny
int cutcolorinfo (TStrings *Lines, int strtline, int endline); // obcina informacje o kolorze (wszystkie nawiasy klamrowe)
int changeshowtime(TStrings *Lines, int ile, bool overwrite, bool na100znakuf, bool blokujwielkosc, int strtline, int endline); // zmienia ilosc klatek przez ktore jest pokazywany tekst.
int time2frm (TStrings *Lines, float fps, int strtline, int endline); // zamienia zapis czasowy na klatkowy
int frm2time (TStrings *Lines, float fps, int strtline, int endline); // zamienia zapis klatkowy na czasowy
int delenters (TStrings *Lines, int strtline, int endline); // wycina puste linie
int sortlines (TStrings *Lines, int strtline, int endline); // sortuje napisy
int geomchange (TStrings *Lines, int strtline, int endline,
                int frf1, int frf2, int frn1, int frn2); // likwiduje przesuniecie geometryczne
int delnumspaces (TStrings *Lines, int strtline, int endline); // 1 0  --->  10
int delvertspaces (TStrings *Lines, int strtline, int endline); // ' | '  --->  '|'
int deldoublespaces (TStrings *Lines, int strtline, int endline); // '   '  --->  ' '
void delendspc (char *linia); // usuwa wszystkie koncowe spacje z linii

#ifndef MOJEFUNKCJE
 #define MOJEFUNKCJE

 #include "strcut.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int frm2time (TStrings *Lines, float fps, int strtline, int endline) // zamienia zapis klatkowy na czasowy
{
  char buf[1024];
  char linia[1024];
  char tekst[1024]; // opis tekstowy w klatce
  int oldh=0, oldm=0, olds=0;
  int i; // do indeksowania
  for (i=strtline; i<endline; i++)
  { strcpy (linia, Lines->Strings[i].c_str());
    if (!checkfrmlineerr(linia)) // sprawdzenie poprawnosci linii
    { strcpy(buf, "B³¹d w linii : ");
      char istr[20];
      itoa(i+1, istr, 10);
      strcat( strcat( strcat(buf, istr), "\n"), linia);
      strcat( buf, "\n\nKontynuowaæ zamianê");
      if (Application->MessageBox (buf,"B³¹d", 35)==IDNO)
        break;
      else
        continue;
    }
    if (strlen(linia)==0) continue; // pusta linia

    int startfrm; // poczatkowa klatka
    getstartfrm(linia, buf); // odczyt klatki poczatkowej
    startfrm = atoi(buf);

    getfrmtext (linia, tekst); // odczytanie tekstu

    int h, m, s;

    float frmfps = int(startfrm/fps +.5);
    h = int(frmfps/3600);
    m = int((frmfps - h*3600) /60);
    s = int(frmfps - h*3600 - m*60);

    if (i) // sprawdza czy czasem aktualna linia jest rozna od poprzedniaj
    {
      if (s==olds)
        if (m==oldm)
          if (h==oldh) // linia taka sama jak poprzednia :(
          {
            char a[255] = "Linia nr ";
            char b[5]; itoa(i+1, b, 10);
            strcat (a, b); strcat (a, " ma taki sam czas jak linia poprzednia\n"
              "Tekst linii poprzedniej nie bêdzie wyœwietlany");
            Application->MessageBox(a,"Uwaga", 48);
          }
    }
    olds=s; oldm=m; oldh=h;

    puttimeline (h, m, s, tekst, linia); // utworzenie nowej linii

    Lines->Delete(i); // usuniecie starej linii
    Lines->Insert(i, linia); // wpisanie nowej linii
  }
  if ((i==Lines->Count)&&(timeformat==1))  // wpisuje na koniec 0:00:00:
  {
      //  utworzenie linii 0:00:00:
    puttimeline (0, 0, 0, "", linia); // utworzenie nowej linii
    Lines->Insert(i, linia); // wpisanie nowej linii
  } 

  return 0;
}
////////////////////////////////////////////////////////////////////////////////
int time2frm (TStrings *Lines, float fps, int strtline, int endline) // zamienia zapis czasowy na klatkowy
{
  char buf[1024];
  char linia[1024];
  char tekst[1024]; // opis tekstowy w klatce
  for (int i=strtline; i<endline; i++)
  { strcpy (linia, Lines->Strings[i].c_str());
    if (!checktimelineerr(linia)) // sprawdzenie poprawnosci linii
    { strcpy(buf, "B³¹d w linii : ");
      char istr[20];
      itoa(i+1, istr, 10);
      strcat( strcat( strcat(buf, istr), "\n"), linia);
      strcat( buf, "\n\nKontynuowaæ zamianê");
      if (Application->MessageBox (buf,"B³¹d", 35)==IDNO)
        break;
      else
        continue;
    }
    if (strlen(linia)==0) continue; // pusta linia

    int h, m, s;
    getstarttime (linia,h,m,s);
    int startfrm; // poczatkowa klatka
    startfrm = int(((h*3600+m*60+s)*fps)+.5);
    gettimetext (linia, tekst);
    putfrmline (startfrm, 0, tekst, linia); // utworzenie nowej linii

    Lines->Delete(i); // usuniecie starej linii
    if (!((strlen(tekst)==0)&&(startfrm==0))) // opuszcza koncowa, zerowa linie (jesli istnieje)
      Lines->Insert(i, linia); // wpisanie nowej linii
    else
    {
      i--;
      endline--;
    }
  }
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
int changeshowtime(TStrings *Lines, int ile, bool overwrite, bool na100znakuf, bool blokujwielkosc, int strtline, int endline) // zmienia ilosc klatek przez ktore jest pokazywany tekst.
{
  char buf[1024];
  int startfrm, endfrm; // poczatkowa i koncowa klatka
  char tekst[1024]; // opis tekstowy w klatce
  char linia[1024];
  for (int i=strtline; i<endline; i++)
  { strcpy (linia, Lines->Strings[i].c_str());
    if (!checkfrmlineerr(linia)) // sprawdzenie poprawnosci linii
    { strcpy(buf, "B³¹d w linii : ");
      char istr[20];
      itoa(i+1, istr, 10);
      strcat( strcat( strcat(buf, istr), "\n"), linia);
      strcat( buf, "\n\nKontynuowaæ zamianê");
      if (Application->MessageBox (buf,"B³¹d", 35)==IDNO)
        break;
      else
        continue;
    }
    if (strlen(linia)==0) continue; // pusta linia

    getstartfrm(linia, buf); // odczyt klatki poczatkowej
    startfrm = atoi(buf);

    getendfrm(linia, buf); // odczyt klatki koncowej
    endfrm = atoi(buf);

    getfrmtext (linia, tekst); // odczytanie tekstu

    //  nadpisanie               puste miejsce {}
    if ((overwrite) || (((startfrm>=endfrm)&&(endfrm==0))))
    {
      if (na100znakuf)
        endfrm = startfrm + (((float)strlen(tekst)/50.0)*ile)+20; // opcja "ile klatek na 50 znakow"
      else
        endfrm = startfrm + ile; // stala ilosc klatek
    }

    if (blokujwielkosc) // endfrm nie moze byc wiekszy niz strtfrm nastepnego wiersza
      if (i<endline)
        if (checkfrmlineerr(Lines->Strings[i+1].c_str()))
        {
          getstartfrm(Lines->Strings[i+1].c_str(), buf); // odczyt klatki poczatkowej
          int nextstartfrm = atoi(buf);
          if ((nextstartfrm<=endfrm)&&(nextstartfrm)) endfrm = nextstartfrm-1; // nowa wartosc
        }

    putfrmline (startfrm, endfrm, tekst, linia); // utworzenie nowej linii

    Lines->Delete(i); // usuniecie starej linii
    Lines->Insert(i, linia); // wpisanie nowej linii
  }
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
int cutcolorinfo (TStrings *Lines, int strtline, int endline) // obcina informacje o kolorze
{
  char buf[1024];
  int startfrm, endfrm; // poczatkowa i koncowa klatka
  char tekst[1024]; // opis tekstowy w klatce
  char linia[1024];
  for (int i=strtline; i<endline; i++)
  { strcpy (linia, Lines->Strings[i].c_str());
    if (!checkfrmlineerr(linia)) // sprawdzenie poprawnosci linii
    { strcpy(buf, "B³¹d w linii : ");
      char istr[20];
      itoa(i+1, istr, 10);
      strcat( strcat( strcat(buf, istr), "\n"), linia);
      strcat( buf, "\n\nKontynuowaæ zamianê");
      if (Application->MessageBox (buf,"B³¹d", 35)==IDNO)
        break;
      else
        continue;
    }
    if (strlen(linia)==0) continue; // pusta linia

    getstartfrm(linia, buf); // odczyt klatki poczatkowej
    startfrm = atoi(buf);

    getendfrm(linia, buf); // odczyt klatki koncowej
    endfrm = atoi(buf);

    getfrmtext (linia, tekst); // odczytanie tekstu

    cutcolor (tekst);

    putfrmline (startfrm, endfrm, tekst, linia); // utworzenie nowej linii
    Lines->Delete(i); // usuniecie starej linii
    Lines->Insert(i, linia); // wpisanie nowej linii
  }
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
int addfrm(TStrings *Lines, int ile, bool from, bool to, int strtline, int endline)
{
  char buf[1024];
  int startfrm, endfrm; // poczatkowa i koncowa klatka
  char tekst[1024]; // opis tekstowy w klatce
  char linia[1024];
  bool ujemna=0;
  for (int i=strtline; i<endline; i++)
  { strcpy (linia, Lines->Strings[i].c_str());
    if (!checkfrmlineerr(linia)) // sprawdzenie poprawnosci linii
    { strcpy(buf, "B³¹d w linii : ");
      char istr[20];
      itoa(i+1, istr, 10);
      strcat( strcat( strcat(buf, istr), "\n"), linia);
      strcat( buf, "\n\nKontynuowaæ zamianê");
      if (Application->MessageBox (buf,"B³¹d", 35)==IDNO)
        break;
      else
        continue;
    }
    if (strlen(linia)==0) continue; // pusta linia

    getstartfrm(linia, buf); // odczyt klatki poczatkowej
    startfrm = atoi(buf);
    if (from) startfrm += ile;

    getendfrm(linia, buf); // odczyt klatki koncowej
    endfrm = atoi(buf);
    if (to)
      if (!((startfrm>=endfrm)&&(endfrm==0))) endfrm += ile;

    if ((startfrm<0)||(endfrm<0)) ujemna=1;

    getfrmtext (linia, tekst); // odczytanie tekstu

    putfrmline (startfrm, endfrm, tekst, linia); // utworzenie nowej linii

    Lines->Delete(i); // usuniecie starej linii
    Lines->Insert(i, linia); // wpisanie nowej linii
  }
  if (ujemna)
    Application->MessageBox("Wyst¹pi³a przynajmniej jedna\nlinia z ujemn¹ wartoœci¹",
    "Informacja", 32);
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
int fpsratechange(TStrings *Lines, float aktualna, float docelowa, int strtline, int endline) // zmienia napisy z jednego fps na inny
{
  char buf[1024];
  int startfrm, endfrm; // poczatkowa i koncowa klatka
  char tekst[1024]; // opis tekstowy w klatce
  char linia[1024];
  bool ujemna=0;
  for (int i=strtline; i<endline; i++)
  { strcpy (linia, Lines->Strings[i].c_str());
    if (!checkfrmlineerr(linia)) // sprawdzenie poprawnosci linii
    { strcpy(buf, "B³¹d w linii : ");
      char istr[20];
      itoa(i+1, istr, 10);
      strcat( strcat( strcat(buf, istr), "\n"), linia);
      strcat( buf, "\n\nKontynuowaæ zamianê");
      if (Application->MessageBox (buf,"B³¹d", 35)==IDNO)
        break;
      else
        continue;
    }
    if (strlen(linia)==0) continue; // pusta linia

    getstartfrm(linia, buf); // odczyt klatki poczatkowej
    startfrm = atoi(buf);

    getendfrm(linia, buf); // odczyt klatki koncowej
    endfrm = atoi(buf);

    startfrm = int((float(startfrm)/aktualna)*docelowa +.5);
    endfrm = int((float(endfrm)/aktualna)*docelowa +.5);

    getfrmtext (linia, tekst); // odczytanie tekstu

    putfrmline (startfrm, endfrm, tekst, linia); // utworzenie nowej linii

    Lines->Delete(i); // usuniecie starej linii
    Lines->Insert(i, linia); // wpisanie nowej linii
  }
  if (ujemna)
    Application->MessageBox("Wyst¹pi³a przynajmniej jedna\nlinia z ujemn¹ wartoœci¹",
    "Informacja", 32);
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
char *cutspaces (char *linia)
{
  int spccount=0;
  for (int i=0; i<(signed int) (strlen(linia)); i++)
    if ( linia[i] == ' ') spccount++;
    else break;
  for (int i=0; i<(signed int) (strlen(linia)-spccount+1); i++)
    linia[i]=linia[i+spccount];
  return linia;
}
int delenters (TStrings *Lines, int strtline, int endline) // wycina puste linie
{
  char linia[1024];
  for (int i=strtline; i<endline; i++)
  { strcpy (linia, Lines->Strings[i].c_str());
    if (strlen(linia)==0)  // pusta linia
    {
      Lines->Delete(i); // usuniecie starej linii
      i--;
      endline--;
    }
    else
    if (checkfrmlineerr(linia))  // linia nie pusta i poprawna
    {
      char wynik[512];
      getfrmtext (linia, wynik); // odczytanie tekstu
      cutspaces(wynik);
      if (StrLen(wynik) == 0)
      {
        Lines->Delete(i); // usuniecie starej linii
        i--;
        endline--;
      }
    }
  }
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
int sortlines (TStrings *Lines, int strtline, int endline) // sortuje rosnaco napisy
{
  char buf[1024];
  int startfrm; // poczatkowa klatka
  char linia[1024]; // linia aktualnie czajona
  for (int i=strtline; i<endline; i++)
  {
    char liniafrst[1024]; // pierwsza linia
    char liniamin[1024]; // linia z maksymalna klatka
    liniafrst[0]=liniamin[0]=0;
    int j;
    strcpy (liniafrst, Lines->Strings[i].c_str());
    int minstartfrm = 99999999; // maksymalna wartosc klatki
    int position = -1; // pozycja (j) lini z maksymalna klatka
    for (j=i; j<endline; j++)
    {
      strcpy (linia, Lines->Strings[j].c_str());
      if (!checkfrmlineerr(linia)) // sprawdzenie poprawnosci linii
      { strcpy(buf, "B³¹d w linii : ");
        char istr[20];
        itoa(j+1, istr, 10);
        strcat( strcat( strcat(buf, istr), "\n"), linia);
        strcat( buf, "\n\nKontynuowaæ sortowanie?");
        if (Application->MessageBox (buf,"B³¹d", 35)==IDNO)
          break;
        else
          startfrm = -1; // coby bledna linia poszla na poczatek
      }
      else
      {
        if (strlen(linia)==0) startfrm = -1; // pusta linia
        else
        {
          getstartfrm(linia, buf); // odczyt klatki poczatkowej
          startfrm = atoi(buf);
        }
      } // error
      if (startfrm < minstartfrm)
      {
        strcpy (liniamin, Lines->Strings[j].c_str());
        minstartfrm = startfrm;
        position = j;
      }
    } // for j
    if (j<endline-1) break; // wczesniejsza petla byla zbrekowana
    if (j!=i)
    {
      Lines->Delete(position); // usuniecie starej linii
      Lines->Insert(position, liniafrst); // wpisanie nowej linii
      Lines->Delete(i); // usuniecie starej linii
      Lines->Insert(i, liniamin); // wpisanie nowej linii
    }
  } // for i
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
int przesuniecie (int frf1, int frf2, int frn1, int frn2, int frm)
{
  int e1 = frn1 - frf1;
  int e2 = frn2 - frf2;
  return
    ( float(e2-e1)/float(frn2-frn1) ) * float(frm-frn1) + e1;
}
int geomchange (TStrings *Lines, int strtline, int endline,
                int frf1, int frf2, int frn1, int frn2) // likwiduje przesuniecie geometryczne
{
  char buf[1024];
  int startfrm, endfrm; // poczatkowa i koncowa klatka
  char tekst[1024]; // opis tekstowy w klatce
  char linia[1024];
  bool ujemna=0;
  for (int i=strtline; i<endline; i++)
  { strcpy (linia, Lines->Strings[i].c_str());
    if (!checkfrmlineerr(linia)) // sprawdzenie poprawnosci linii
    { strcpy(buf, "B³¹d w linii : ");
      char istr[20];
      itoa(i+1, istr, 10);
      strcat( strcat( strcat(buf, istr), "\n"), linia);
      strcat( buf, "\n\nKontynuowaæ zamianê");
      if (Application->MessageBox (buf,"B³¹d", 35)==IDNO)
        break;
      else
        continue;
    }
    if (strlen(linia)==0) continue; // pusta linia

    getstartfrm(linia, buf); // odczyt klatki poczatkowej
    startfrm = atoi(buf);
    startfrm -= przesuniecie (frf1, frf2, frn1, frn2, startfrm);

    getendfrm(linia, buf); // odczyt klatki koncowej
    endfrm = atoi(buf);
    if (endfrm!=0)
      endfrm -= przesuniecie (frf1, frf2, frn1, frn2, endfrm);

    if ((startfrm<0)||(endfrm<0)) ujemna=1;

    getfrmtext (linia, tekst); // odczytanie tekstu

    putfrmline (startfrm, endfrm, tekst, linia); // utworzenie nowej linii

    Lines->Delete(i); // usuniecie starej linii
    Lines->Insert(i, linia); // wpisanie nowej linii
  }
  if (ujemna)
    Application->MessageBox("Wyst¹pi³a przynajmniej jedna\nlinia z ujemn¹ wartoœci¹",
    "Informacja", 32);
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
  bool numaround(char *linia, int i)
  {
    if ( (linia[i-1]>='0')&&(linia[i-1]<='9')
         &&(linia[i+1]>='0')&&(linia[i+1]<='9') )
      return true;
    else
      return false;
  }
int delnumspaces (TStrings *Lines, int strtline, int endline) // 1 0  --->  10
{
//  char buf[1024];
  char linia[1024];
  for (int i=strtline; i<endline; i++)
  { strcpy (linia, Lines->Strings[i].c_str());
/*    if (!checkfrmlineerr(linia)) // sprawdzenie poprawnosci linii
    { strcpy(buf, "B³¹d w linii : ");
      char istr[20];
      itoa(i+1, istr, 10);
      strcat( strcat( strcat(buf, istr), "\n"), linia);
      strcat( buf, "\n\nKontynuowaæ usuwanie spacji?");
      if (Application->MessageBox (buf,"B³¹d", 35)==IDNO)
        break;
      else
        continue;
    } //*/
    if (strlen(linia)<=2) continue; // pusta linia

    int ii=1;
    while (linia[ii+1]!=NULL)
    {
      if (linia[ii]==' ')
        if (numaround(linia, ii))
        {
          int j=ii;
          while (linia[j]!=NULL)
          {
            linia [j]= linia[j+1];
            j++;
          }
        }
      ii++;
    }

    Lines->Delete(i); // usuniecie starej linii
    Lines->Insert(i, linia); // wpisanie nowej linii
  }
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
  void delendspc (char *linia) // usuwa wszystkie koncowe spacje z linii
  {
    int strlength = strlen(linia);
    if (linia[strlength-1]==' ')
    {
      linia[strlength-1]=NULL;
      delendspc (linia);
    }
  }
  bool isvertafterorbefore(char *linia, int i)
  {
    if ( (linia[i+1]=='|')||(linia[i-1]=='|') )
      return true;
    else
      return false;
  }
int delvertspaces (TStrings *Lines, int strtline, int endline) // ' | '  --->  '|'
{
//  char buf[1024];
  char linia[1024];
  for (int i=strtline; i<endline; i++)
  { strcpy (linia, Lines->Strings[i].c_str());
/*    if (!checkfrmlineerr(linia)) // sprawdzenie poprawnosci linii
    { strcpy(buf, "B³¹d w linii : ");
      char istr[20];
      itoa(i+1, istr, 10);
      strcat( strcat( strcat(buf, istr), "\n"), linia);
      strcat( buf, "\n\nKontynuowaæ usuwanie spacji?");
      if (Application->MessageBox (buf,"B³¹d", 35)==IDNO)
        break;
      else
        continue;
    } //*/
    if (strlen(linia)<=2) continue; // pusta linia

    delendspc (linia); // usuwa koncowe linie

    int ii=1;
    while (linia[ii+1]!=NULL)
    {
      if (linia[ii]==' ')
        if (isvertafterorbefore(linia, ii))
        {
          int j=ii;
          while (linia[j]!=NULL)
          {
            linia [j]= linia[j+1];
            j++;
          }
        }
      ii++;
    }

    Lines->Delete(i); // usuniecie starej linii
    Lines->Insert(i, linia); // wpisanie nowej linii
  }
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
  int spacecount(char *linia, int i) // zwraca liczbe nieprzerwanych spacji za i-tym znakiem
  {
    int c=0;
    i++; // liczac od nastepnej spacji
    while (linia[i]==' ') i++, c++;
    return c;
  }
int deldoublespaces (TStrings *Lines, int strtline, int endline) // '   '  --->  ' '
{
//  char buf[1024];
  char linia[1024];
  for (int i=strtline; i<endline; i++)
  { strcpy (linia, Lines->Strings[i].c_str());
/*    if (!checkfrmlineerr(linia)) // sprawdzenie poprawnosci linii
    { strcpy(buf, "B³¹d w linii : ");
      char istr[20];
      itoa(i+1, istr, 10);
      strcat( strcat( strcat(buf, istr), "\n"), linia);
      strcat( buf, "\n\nKontynuowaæ usuwanie spacji?");
      if (Application->MessageBox (buf,"B³¹d", 35)==IDNO)
        break;
      else
        continue;
    } //*/
    if (strlen(linia)<=2) continue; // pusta linia

    int ii=1;
    int j;
    while (linia[ii+1]!=NULL)
    {
      if (linia[ii]==' ')
      {
        int sc = spacecount(linia, ii);
        j=ii;
        while (linia[j]!=NULL)
        {
          linia [j]= linia[j+sc];
          j++;
        }
      }
      ii++;
    }
    int lcount = strlen(linia);
    if (linia[lcount-1]==' ') linia[lcount-1]=NULL; // usuwa ostatnia spacje

    Lines->Delete(i); // usuniecie starej linii
    Lines->Insert(i, linia); // wpisanie nowej linii
  }
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////// FUNCTIONS ////////
int checkfrmlineerr (char *linia) // sprawdza czy linia jest poprawna
{ // 1=OK   0=BAD
  int dlugosc = strlen (linia);
  if (dlugosc == 0)
    return 1;
  if (linia[0]!='{') return 0; // sprawdza pierwszy '{'
  int poz; // pozycja w linii
  for (poz=1; poz<dlugosc; poz++) // szukanie pierwszego '}'
  {
    if (linia[poz]=='}') break; // znaleziono '}'
    if (poz==dlugosc-1) return 0; // w calej linii nie ma znaku '}'
  }
  poz++;
  if (linia[poz++]!='{') return 0; // drugi '{'
  for (poz; poz<dlugosc; poz++) // szukanie drugiego '}'
  {
    if (linia[poz]=='}') break; // znaleziono '}'
    if (poz==dlugosc-1) return 0; // w calej linii nie ma drugiego znaku '}'
  }
//  if (poz==dlugosc-1) return 0; // nie ma opisu dla linii           //########################################################################
  return 1;
}
////////////////////////////////////////////////////////////////////////////////
int getstartfrm (char *linia, char *wynik) // zwraca ramke startowa z wyslanej linii
{ // 1=OK   0=BAD
  int dlugosc = strlen (linia);
  if (dlugosc == 0)
  {
    wynik[0]=NULL;
    return 1;
  }
  int i; // pozycja '}'
  for (i=1; i<dlugosc; i++) // szukanie pierwszego '}'
    if (linia[i]=='}') break; // znaleziono '}'
  int j;
  for (j=0; j<i-1; j++)
    wynik[j]=linia[j+1];
  wynik[j]=NULL;
  return 1;
}
////////////////////////////////////////////////////////////////////////////////
int getendfrm (char *linia, char *wynik) // zwraca ramke koncowa z wyslanej linii
{ // 1=OK   0=BAD                          // uzywa   getstartfrm
  int dlugosc = strlen (linia);
  int i;
  for (i=1; i<dlugosc; i++) // szukanie pierwszego '}'
    if (linia[i]=='}') break; // znaleziono '}'
  i++;
  for (int j=0; j<dlugosc-i+1; j++)
    wynik[j]=linia[j+i];
  getstartfrm(wynik, wynik);
  return 1;
}
////////////////////////////////////////////////////////////////////////////////
int getfrmtext (char *linia, char *wynik) // zwraca tekst linii
{
  int dlugosc = strlen (linia);
  int i;
  for (i=1; i<dlugosc; i++) // szukanie pierwszego '}'
    if (linia[i]=='}') break; // znaleziono '}'
  i++;
  for (i; i<dlugosc; i++) // szukanie drugego '}'
    if (linia[i]=='}') break; // znaleziono '}'
  i++;
  for (int j=0; j<dlugosc-i+1; j++)
    wynik[j]=linia[j+i];
  return 1;
}
///////////////////////////////////////////////////////
int putfrmline (int start, int end, char *text, char *wynik) // tworzy linie z podanych danych
{
  char buf[15];
  itoa(start, buf, 10);
  strcat( strcat( strcat( strcpy(wynik, "{"), buf), "}"), "{");
  if (end!=0)
  {
    itoa(end, buf, 10);
    strcat (wynik, buf);
  }
  strcat( strcat (wynik, "}"), text);
  return 1;
}
///////////////////////////////////////////////////////
int cutcolor (char *linia) // obcina tekst z informacji o kolorze
{
  int max = strlen (linia);
  int _od=0, _do;
  while (linia[_od++]!='{') // znajduje pierwsze otwarcie nawiasu
    if (max<_od) return 0;

  _do=_od;
  while (linia[_do++]!='}') // znajduje pierwsze zamkniecie nawiasu
    if (max<_do) return 0;

  for (int i=_od; i<_od+max-_do+1; i++) // przyciecie wybranego kawalka
    linia[i-1] = linia[i+_do-_od];

  cutcolor(linia);
  return 1;
}
////////////////////////////////////////////////////////////////////////////////
int lasttimeline (char *linia) // sprawdza czy linia jest == "0:00:00:"
{
  return !strcmp(linia, "0:00:00:");
}
////////////////////////////////////////////////////////////////////////////////
int gettimeformat (char *linia) // sprawdza w jakim formacie jest zapis czasu
{
  if ( (linia[1]==':') && (linia[4]==':') && (linia[7]==':') ) return 1; // 0:00:00:
  if ( (linia[2]==':') && (linia[5]==':') && (linia[8]==':') ) return 2; // 00:00:00:
  if ( (linia[2]==':') && (linia[5]==':') && (linia[8]==' ') ) return 3; // 00:00:00
  return 0;
}
////////////////////////////////////////////////////////////////////////////////
int checktimelineerr (char *linia) // sprawdza czy linia jest poprawna
{ // 1=OK   0=BAD
  timeformat = gettimeformat(linia);
  if (timeformat == 1)
  {
    if (lasttimeline(linia)) return 1; // ok bo ostatnia linia == 0:00:00:
    int dlugosc = strlen (linia);
    if (dlugosc == 0) return 1; // oki bo linia jest pusta
    if (dlugosc<8) return 0; // error bo linia zbyt krotka // bylo 9
    if (linia[1]!=':') return 0; // error bo ni mo pierwszego ":"
    if (linia[4]!=':') return 0; // error bo ni mo drugiego ":"
    if (linia[7]!=':') return 0; // error bo ni mo ostaniego ":"
    return 1;
  }
  if (timeformat == 2)
  {
    int dlugosc = strlen (linia);
    if (dlugosc == 0) return 1; // oki bo linia jest pusta
    if (dlugosc<9) return 0; // error bo linia zbyt krotka // bylo 9
    if (linia[2]!=':') return 0; // error bo ni mo pierwszego ":"
    if (linia[5]!=':') return 0; // error bo ni mo drugiego ":"
    if (linia[8]!=':') return 0; // error bo ni mo ostaniego ":"
    return 1;
  }
  if (timeformat == 3)
  {
    int dlugosc = strlen (linia);
    if (dlugosc == 0) return 1; // oki bo linia jest pusta
    if (dlugosc<9) return 0; // error bo linia zbyt krotka // bylo 9
    if (linia[2]!=':') return 0; // error bo ni mo pierwszego ":"
    if (linia[5]!=':') return 0; // error bo ni mo drugiego ":"
    if (linia[8]!=' ') return 0; // error bo ni mo ostaniego ":"
    return 1;
  }
  return 0; // jakis inny format zapisu
}
///////////////////////////////////////////////////////
int getstarttime (char *linia, int &h, int &m, int &s) // zwraca godzine, minute i sekunde z danej linii
{
  if (timeformat==1) // 0:00:00:
  {
    char buf[255];
      h = atoi( strcut(linia, buf, 0, 1) );
      m = atoi( strcut(linia, buf, 2, 2) );
      s = atoi( strcut(linia, buf, 5, 2) );
    return 1;
  }
  if ((timeformat==2)||(timeformat==3)) // 00:00:00: lub 00:00:00
  {
    char buf[255];
      h = atoi( strcut(linia, buf, 0, 2) );
      m = atoi( strcut(linia, buf, 3, 2) );
      s = atoi( strcut(linia, buf, 6, 2) );
    return 1;
  }
  { // nie powinno wystapic
    h=-997; m=-997; s=-997;
    return 0;
  }
}
///////////////////////////////////////////////////////
int gettimetext (char *linia, char *wynik) // zwraca tekst linii
{
  int dlugosc= strlen (linia);
  if (timeformat==1) // 0:00:00:
    strcut (linia, wynik, 8, dlugosc-8);
  else
  if ((timeformat==2)||(timeformat==3)) // 00:00:00: lub 00:00:00
    strcut (linia, wynik, 9, dlugosc-9);
  else
    strcpy (wynik, "BLAD: NIE OBSLUGIWANY FORMAT CZSOWY"); // blad
  return 1;
}
///////////////////////////////////////////////////////
int puttimeline (int h, int m, int s, char *tekst, char *linia) // utworzenie nowej linii
{
  if (timeformat==1) // 0:00:00:
  {
    char ch[3], cm[3], cs[3];
    itoa(h, ch, 10);
      strcat( strcpy (linia, ch), ":"); //  0:
    itoa(m, cm, 10);
      if (strlen(cm)==1) strcat(linia, "0"); //  0:0
      strcat( strcat (linia, cm), ":"); //  0:00:
    itoa(s, cs, 10);
      if (strlen(cs)==1) strcat(linia, "0"); //  0:00:0
      strcat( strcat( strcat (linia, cs), ":"), tekst); //  0:00:00:tekst
    return 1;
  }
  if ((timeformat==2)||(timeformat==3)) // 00:00:00: lub 00:00:00
  {
    char ch[3], cm[3], cs[3];
    linia[0]=0;
    itoa(h, ch, 10);
      if (strlen(ch)==1) strcat(linia, "0"); //  0:0
      strcat( strcat (linia, ch), ":"); //  0:
    itoa(m, cm, 10);
      if (strlen(cm)==1) strcat(linia, "0"); //  0:0
      strcat( strcat (linia, cm), ":"); //  0:00:
    itoa(s, cs, 10);
      if (strlen(cs)==1) strcat(linia, "0"); //  0:00:0
    strcat (linia, cs);
    if (timeformat==3) strcat(linia , ":");
    else strcat(linia , " ");
    strcat(linia , tekst);
    return 1;
  }
  return 0;
}
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
#endif


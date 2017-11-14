// funkcje do obslugi napisow
                           // (C) 2000 by Sir Arthur

#ifndef SUBTITLE_FUN
  #define SUBTITLE_FUN
  int showsubtitle (TLabel *L1, TLabel *L2, char *tekstnapisu)
  { // ma wyskakiwac tylko przy pierwszym pokazaniu tekstu
    char tmpbuf [1024];
    int dlugosc = strlen (tekstnapisu);
    int i;
    for (i=0; i<dlugosc; i++)
      if (tekstnapisu[i]=='|')break;
    if (i<dlugosc)
    { // beda dwie linie
      strcut (tekstnapisu, tmpbuf, 0, i);
      L1->Caption = tmpbuf;
      L1->Caption = " "+L1->Caption+" ";
      strcut (tekstnapisu, tmpbuf, i+1, dlugosc-i);
      L2->Caption = tmpbuf; // pusta linia
      L2->Caption = " "+L2->Caption+" ";
    }
    else
    { // tylko jedna linia
      L1->Caption = tekstnapisu;
      L1->Caption = " "+L1->Caption+" ";
      L2->Caption = ""; // pusta linia
    }
    return 1;
  }


#endif
  

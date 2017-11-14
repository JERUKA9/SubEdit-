// zwraca linie w ktorej znajduje sie znak o pozycji pos
// (indexowanie od zera)

  int getstartposline (TStrings *Strings, int pos);
  int getendposline (TStrings *Strings, int pos);

#ifndef GETPOSLINE
 #define GETPOSLINE
  int getstartposline (TStrings *Strings, int pos)
  {
    int poscount = 0; // pozycja w tekscie
    for (int i=0; i<Strings->Count; i++)
    {
      poscount += strlen (Strings->Strings[i].c_str()) + 2;
      if (poscount>pos) return i;
    }
    return Strings->Count; // przekroczony zakres
  }

  int getendposline (TStrings *Strings, int pos)
  {
    int poscount = 0; // pozycja w tekscie
    for (int i=0; i<Strings->Count; i++)
    {
      poscount += strlen (Strings->Strings[i].c_str()) + 2;
      if (poscount>=pos) return i;
    }
    return Strings->Count; // przekroczony zakres
  }
#endif

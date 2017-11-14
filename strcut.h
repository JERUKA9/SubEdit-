// funkcja "ucina" lancuch
// lancuch jest przyciety od znaku FROM (indexowanego od zera)
// a jego dlugosc okresla zmienna COUNT
                                             // (C) 2000 by sir Arthur

char* strcut (char *source, char *dest, int from, int count);

#ifndef STRCUT
 #define STRCUT
   char* strcut (char *source, char *dest, int from, int count)// przycina lancuch od FROM. lancuch bedzie mial COUNT dlugosc
   { // from indexowane od 0
     int i;
     for (i=from; i<from+count; i++)
       dest[i-from] = source[i];
     dest[i-from]=NULL;
     return dest;
   }
#endif
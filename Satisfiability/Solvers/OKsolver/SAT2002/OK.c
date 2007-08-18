                       /* OKsolver; 5.3.1998 */

/* Autor: Oliver Kullmann, Universitaet Frankfurt am Main, Germany */
/* ab Februar 1999: University of Toronto, Computer Science Department */


/* Hauptprogramm */

/* Einheit: OK */


/* 21.8.1998: Ersetzen von "ErfK" durch "NeuK" */

/* 20.9.1998: Bisher wurde beim Finden einer Autarkie oder einer */
/* verallg. 1-Klauseln-Elim. ein neuer "Single-"Knoten erzeugt. */
/* Nun wird diese Belegung direkt ausgefuehrt, und die Auswahl */
/* einer Verzweigungs-Variablen neu begonnen. */

/* 13.11.1998: Resolutions-Baum-Verwaltung */

/* 31.3.2000: InitAbstand2() im Falle, dass DYNAMISCH gesetzt wurde */

/* 27.4.2000: Einlesen von OKVar.h */

/* 24.7.2000: Die Variablen LitTab und KlTab aus der Prozedure Einlesen */
/* nun mit "calloc" dynamisch erzeugt, und mit "free" dann geloescht. */

/* 25.7.2000: Ersetzen der drei calloc-Aufrufe durch einen malloc-Aufruf. */

/* 27.7.2000: Elimination der Rekursion (mittels Indices) */

/* 29.1.2001: Nun wurde die Elimination der Rekursion dynamisch durchgefuehrt, */
/* d.h., es wird nur soviel Speicherplatz fuer die lokalen Variablen angefordert, */
/* wie auch wirklich benoetigt wird. */

/* 29.1.2001: Die Speicherung der zweiten Belegung nun korrekt durchgefuehrt */
/* (mittels Dynamisierung). */

/* 30.1.2001: Elimination von OKVar.h */

/* 18.2.2001: Liste von Argumenten (mit Optionen) */

/* 20.2.2001: Ausgabe der Gesamtzeit. */

/* 27.2.2001: Realisierung der 1-Klauseln-Elimination fuer die Eingabe */

/* 28.2.2001: Freisetzen von Speicher und Datenstroemen wird nun ueber den */
/* NULL-Wert geregelt. */
/* 28.2.2001: Ein Syntax-Fehler fuehrt nun nicht mehr zum Abbruch. */
/* 28.2.2001: Senden des Signals SIGUSR1 bewirkt Ausdruck der Statistik */
/* (aber nicht in die Datei), und SIGUSR2 bewirkt Abbruch der Bearbeitung */
/* der aktuellen Formel und Ausdruck der Statistik (diesmal in die Datei, */
/* falls gewuenscht). */

/* 3.3.2001: Dynamisierung von relVarM; die Stapelzeiger nun wirklich als */
/* Zeiger; H und EK im Reduktionsmodul, EinerKl und Huelle im Filtermodul, */
/* sowie relVarM, relVarK und Pfad zusammengefasst; LITTAB als Uebersetzer- */
/* Option bewirkt, dass die Variablenmengen der Eingabeklauseln mit weniger */
/* Speicherplatz abgespeichert werden. */

/* 6.3.2001: Feld 14 (Redplus) aus der Statistikausgabe gestichen. */


/* --------------------------------------------------------- */


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

#ifdef SYSTIME

#include <sys/times.h>

#endif

#include "OK.h"
#include "BaumRes.h"
#include "VarLitKlm.h"
#include "Filter.h"
#include "Belegung.h"
#include "Abstand.h"
#include "Projektion.h"
#include "Einlesen.h"
#include "Parameter.h"
#include "Ausgaben.h"
#include "Speicher.h"
#include "Reduktion.h"
#ifdef LOKALLERNEN
#include "lokalesLernen.h"
#endif

/* ------------------------------------------------------------- */

const bool internal = false; // keine Entwicklungsversion

unsigned int Sprache = SPRACHE;
unsigned int Standard = STANDARD;

#ifndef BELEGUNG
bool Belegung = false;
#else
bool Belegung = true;
#endif
/* Ist Belegung = true, so wird eine erfuellende Belegung ausgegen (ggfs.), */
/* und zwar auf den Standard-Ausgabe-Strom (die naechste Zeile nach der */
/* Statistik). */
/* Das Format der Darstellung der partiellen Belegung ist: */
/*  pro Zeile wird ein Paar "v e" angegeben, wobei */
/*  v die Nummer der Variablen in der Eingabe ist, */
/*  und e entweder 0 oder 1 ist. */
/* Bsp.: F = (-4,2)(4,55)(-2) */
/* ergibt */
/*     4 0 */
/*     2 0 */
/*    55 1 */

/* Schalter: */

bool Dateiausgabe = false;
bool Monitor = false;
bool nurVorreduktion = false;
bool Schranken = false;
unsigned int Zeitschranke = 0;
bool randomisiert = false;

// Setzen des voreingestellen Ausgabeformates

#ifdef DIMACSAUS
#  ifdef XMLAUS
#    error "Keine Kombination von DIMACS- und XML-Format moeglich!"
#  endif
bool spezRueckgabe = true; // Kodierung des Ergebnisses im Rueckgabewert
enum Ausgabeformat Format = Dimacs_Format;
#else
bool spezRueckgabe = false;
#  ifdef XMLAUS
Ausgabeformat Format = XML_Format;
#  else
Ausgabeformat Format = Tabellen_Format;
#  endif
#endif
// am 10.3.2002 fuer den SAT-Wettbewerb hinzugefuegt
// falls DIMACS_Format gesetzt ist, so wird die Ausgabe einer Belegung
// als Liste von wahr gemachten Literalen ausgegeben (in einer Zeile),
// und die Kommentarzeile wird in zwei Zeilen aufgespalten:
// der SAT-Wert (0, 1 oder 2) ergibt
// s UNSATISFIABLE (SATISFIABLE, UNKNOWN)
// und die restlichen Zahlen werden in eine Zeile beginnend mit "c "
// geschrieben.
// (Fuer den Wettbewerb muss sowohl BELEGUNG als auch DIMACSAUS
// gesetzt werden.)



unsigned int MAXN = 30000;
unsigned int MAXL = 400000;
unsigned int MAXK = 150000;


/* ------------------------------------------------------------- */


static const long EPS =  /* Einheiten pro Sekunde */
#ifndef SYSTIME
    CLOCKS_PER_SEC;
#else
    CLK_TCK;
#endif

#ifdef SYSTIME
  struct tms SysZeit;
  struct tms *Zeiger = &SysZeit;
#endif

clock_t akkVerbrauch = 0; /* akkumulierter Verbrauch */


/* ------------------------------------------------------------- */

/* Die Darstellung der Eingabe */

unsigned int P, P0, N, N0, K, K0, L, L0, aktN, aktP;

/* Hilfsvariablen fuer Reduktion und Filter */

unsigned int Runde;


/* ------------------------------------------------------------- */

/* Statistik */

unsigned long int Knoten, SingleKnoten, VerSingleKnoten, QuasiSingleKnoten, PureL, Autarkien, V1KlRed, FastAutarkien, InitEinerRed, neue2Klauseln, maxneue2K;
unsigned int Suchbaumtiefe, Ueberschreitung2, init2Klauseln;

static clock_t Verbrauch;

static char *aktName;
static char* Wurzel = NULL;

enum Ergebniswerte {SAT = 1, UNSAT = 0, Unbestimmt = 2};

static enum Ergebniswerte s = Unbestimmt; /* Ergebniswert */


/* ------------------------------------------------------------- */


/* Lokale Datenstrukturen und Variablen */



/* Der Stapel, der die Belegungen fuer den jeweils zweiten Zweig enthaelt */

static StapeleintragFZ zweiteBel = NULL;

static unsigned int Zeiger2;
static unsigned int Groesse2;



/* Zur Simulation der Rekursion */

enum Spruenge { SAT1, SAT2 };

struct Sammlung {
  unsigned int P2, N2, altZeiger2;
  enum Spruenge Ruecksprung;
  unsigned int *AnzK2;
#ifndef LOKALLERNEN
  Pfadinfo *altTiefe;
#else
  Marken *Marke;
#endif
#ifdef OUTPUTTREEDATAXML
  // clock_t start_run_time;
  unsigned long int number_2_reductions_at_new_node;
#endif
  struct Sammlung * davor;
  struct Sammlung * danach;
};

static struct Sammlung *SatVar;
static struct Sammlung *SatVar0 = NULL;
/* speichert den initialen Wert von SatVar */

/* ------------------------------------------------------------- */


/* Zur Beobachtung der SAT-Entscheidung */

static unsigned int Beobachtungsniveau = 6;

static unsigned int Rekursionstiefe;

static unsigned int *Zweiglast = NULL;
/* = 2^0, ..., 2^(Beobachtungsniveau-1) */

static unsigned int Gesamtlast; /* = 2^Beobachtungsniveau */

static unsigned int *beobachtet = NULL;
static unsigned int totalbeobachtet;

static unsigned long int altKnoten;

static FILE *fpmo = NULL; /* die aktuelle Ausgabeidatei zur Ueberwachung */


__inline__ static void Monitorausgabe(unsigned int b)
{
  if (b > totalbeobachtet)
    {
      totalbeobachtet = b;
#ifndef SYSTIME
      Verbrauch = clock() - akkVerbrauch;
#else
      times(Zeiger);
      Verbrauch = SysZeit.tms_utime - akkVerbrauch;
#endif
      printf("%3d:%6ld, %6.1f, %6.1f\n", b, Knoten - altKnoten, (double) Verbrauch / EPS, ((double) Gesamtlast / b - 1) * Verbrauch / EPS);
      if (Dateiausgabe)
        {
          fprintf(fpmo, "%3d:%6ld, %6.1f, %6.1f\n", b, Knoten - altKnoten, (double) Verbrauch / EPS, ((double) Gesamtlast / b - 1) * Verbrauch / EPS);
        }
      fflush(NULL);
      altKnoten = Knoten;
    }
  return;
}

__inline__ static void Verzweigungsliteralausgabe(const LIT x, unsigned int Tiefe) {
  VAR v; VZ e;
  v = Var(x);
  if (x == Literal(v, Pos))
    e = Pos;
  else
    e = Neg;
  printf("%d : %7s %d\n", Tiefe, Symbol(v), e);
  fprintf(fpmo, "%d : %7s %d\n", Tiefe, Symbol(v), e);
  fflush(NULL);
}

/* ------------------------------------------------------------- */


typedef enum { gleich = 0, groesser = 1, kleiner = 2} VERGL;

/* Zur Bestimmung, ob einer Gleitpunktzahl "wirklich" groesser ist als eine andere: */

static VERGL Vergleich(float a, float b)
{
  float h;
  h = b * 4 * FLT_EPSILON;
  if (a > b + h)
    return groesser;
  else if (a < b - h)
    return kleiner;
  else
    return gleich;
}


/* ------------------------------------------------------------- */



/* Prozeduren zur Speicherverwaltung */


static struct Sammlung *neuerKnoten( void )
{
  struct Sammlung *s;
  s = (struct Sammlung *) xmalloc(sizeof(struct Sammlung) + (P + 1) * sizeof(unsigned int));
  s -> AnzK2 = (unsigned int *)(s + 1);
  s -> danach = NULL;
  return s;
}

/* -------------------------------------------------------------------------------- */

/* Randomisierung */

static long unsigned int Schluessel = 1;

static long unsigned int randx;

static float Verhaeltnis = 0.2;


__inline__ static void srand_S(void)
{
  randx = Schluessel;
}

__inline__ static int rand_S(void)
{
  return(((randx = randx * 1103515245L + 12345)>>16) & 0x7fff);
}

__inline__ static float Verschmierung(double x)
{
  return (rand_S() / ((float) 0x7fff) * Verhaeltnis + 1) * x;
}



/* -------------------------------------------------------------------------------- */


/* Initialisierung */


void InitSat( void )
{
  Groesse2 = N;
  zweiteBel = (StapeleintragFZ) xmalloc(Groesse2 * sizeof(StapeleintragF));
  SatVar0 = SatVar = neuerKnoten();
  SatVar -> davor = NULL;
  
  Runde = 0; Zeiger2 = 0;

  if (Monitor && (! nurVorreduktion))
    {
      unsigned int p; unsigned int *Z;
      totalbeobachtet = 0;
      Rekursionstiefe = 0;
      altKnoten = 0;
      Zweiglast = (unsigned int *) xmalloc(Beobachtungsniveau * sizeof(unsigned int));
      for (p = 1, Z = Zweiglast + Beobachtungsniveau; Z != Zweiglast; p *= 2)
        *(--Z) = p;
      Gesamtlast = p;
      beobachtet = (unsigned int *) xmalloc(Beobachtungsniveau * sizeof(unsigned int));
      beobachtet[0] = 0;
    }

  return;
}

static void AufraeumenSat(void)
{
  struct Sammlung *Z; struct Sammlung *Z0;
  
  Knoten = SingleKnoten = VerSingleKnoten = QuasiSingleKnoten = PureL = Autarkien = V1KlRed = Suchbaumtiefe = Ueberschreitung2 = FastAutarkien = InitEinerRed = neue2Klauseln = maxneue2K = init2Klauseln = 0;
  Tiefe = NULL;

  free(zweiteBel); zweiteBel = NULL;

  Z0 = SatVar0;
  while (Z0 != NULL)
    {
      Z = Z0 -> danach;
      free(Z0);
      Z0 = Z;
    }
  SatVar0 = NULL;

  free(Zweiglast); Zweiglast = NULL;
  free(beobachtet); beobachtet = NULL;
}


/* -------------------------------------------------------------------------------- */

#ifdef OUTPUTTREEDATAXML

static char* NameTreeDataFile = NULL;
static FILE* TreeDataFile = NULL;

void BeginTreeElement() {
  fprintf(TreeDataFile, "<t l=\"%ld\">", V1KlRed - SatVar -> number_2_reductions_at_new_node);
}
void EndTreeElement() {
  fprintf(TreeDataFile, "</t>");
}
void FinaliseSATPath() {
  do {
    EndTreeElement();
    SatVar = SatVar -> davor;
  } while (SatVar != NULL);
}

#endif


/* Die (rekursive) Loesungs-Prozedur */


static enum Ergebniswerte SATEntscheidung( void )

{
  unsigned int i;
  float opta; float a; unsigned int optaS;
  VAR v;
  VZ optZweig;
  enum Spruenge r;
  unsigned int DN, DN2;
  StapeleintragFZ Z;


Anfang:

  Knoten++;

#ifdef OUTPUTTREEDATAXML
  SatVar -> number_2_reductions_at_new_node = V1KlRed;
#endif  

  /* Reduktionen, die von Autarkien nicht affiziert werden */
  /* (zumindest verallgemeinerte 1-Klauseln-Elimination) */

alleReduktionen:

  switch ( Reduktion1() ) {

  case 1:
#ifdef OUTPUTTREEDATAXML
    BeginTreeElement();
    FinaliseSATPath();
#endif  
    return SAT;

  case 2:
#ifdef OUTPUTTREEDATAXML
    BeginTreeElement();
#endif
    r = SatVar -> Ruecksprung;
    SatVar = SatVar -> davor;
    if (SatVar == NULL) {
#ifdef OUTPUTTREEDATAXML
      EndTreeElement();
#endif
      return UNSAT;
    }
    if (Monitor)
      Rekursionstiefe--;
    switch (r)
      {
      case SAT1 : goto nachSAT1;
      case SAT2 : goto nachSAT2;
      }
  }


Schleife:

#ifdef DYNAMISCH

  InitAbstand2();

#endif

/* Zwar werden so die Autarkien nicht in die dynamische Gewichtsberechnung einbezogen, 
    dieser Effekt scheint mir jedoch gering, waehrend ihr Einbezug grossen Aufwand mit sich 
    braechte. So wird also nur Reduktion1() beruecksichtigt. */


  /* Reduktionen, die von Autarkien affiziert werden */
  /* (zumindest pure Literale) */

  switch ( Reduktion2() ) {
    
  case 1:
#ifdef OUTPUTTREEDATAXML
    BeginTreeElement();
    FinaliseSATPath();
#endif
    return SAT;

  case 2:
#ifdef OUTPUTTREEDATAXML
    BeginTreeElement();
#endif
    r = SatVar -> Ruecksprung;
    SatVar = SatVar -> davor;
    if (SatVar == NULL) {
#ifdef OUTPUTTREEDATAXML
      EndTreeElement();
#endif
      return UNSAT;
    }
    if (Monitor)
      Rekursionstiefe--;
    switch (r)
      {
      case SAT1 : goto nachSAT1;
      case SAT2 : goto nachSAT2;
      }
  }

  opta = 0; optaS = 0;

/*   Schleife ueber alle Variablen, die jeweils dem Filter vorgelegt werden: */
/*     Findet dieser eine Entscheidung oder eine Einer-Verzweigung, so wird eine */
/*     solche Variable ausgesucht, und die Schleife abgebrochen. */
/*     Andernfalls wird mittels "Abstand" die (Zweier-)Verzweigung bewertet, und */
/*     sie ersetzt, falls besser, die alte, bisher beste Verzweigung. */
/*     (Die Zweigauswahl wird von "Abstand" mitberechnet.) */

  for (v = ersteVar(); echteVar(v); v = naechsteVar(v))
    {
      Filter(v);
      if (erfuellt)
        {
          if (Belegung) /* Durchfuehrung der Belegung (zur Ausgabe) */
            {
              DN = DeltaN[Zweig][Schalter];
              for (i = 0, Z = Huelle[Zweig][Schalter]; i < DN; i++, Z++)
#ifndef BAUMRES
                belege(*Z);
#else
                belege(Z -> l);
#endif
            }
#ifdef OUTPUTTREEDATAXML
	  BeginTreeElement();
	  FinaliseSATPath();
#endif  
          return SAT;
        }

      if (reduziert)
        goto alleReduktionen;
      
      if (Wahl)
        {
              if (Single)  /* (zur Zeit) der (nicht-erfuellende) Autarkiefall */
            {
              /* Durchfuehrung der Belegung */
              DN = DeltaN[Zweig][Schalter];
#ifdef LOKALLERNEN
              eintragenTiefe();
#endif
              for (i = 0, Z = Huelle[Zweig][Schalter]; i < DN; i++, Z++)
#ifndef BAUMRES
                belege(*Z);
#else
                belege(Z -> l);
#endif
              
              /* Falls BAUMRES gesetzt ist: */
              /* Da der Standard-Filter nur Autarkien hier liefern kann, */
              /* die nie zur Erzeugung der leeren Klausel beitragen koennen, */
              /* muss hier in relVar nichts eingetragen werden. */
              
              aktP = LaP[Zweig][Schalter];
              aktN -= DeltaN[Zweig][Schalter];
              memcpy((void *)(aktAnzK + 2), (void *)(LaAnzK[Zweig][Schalter] + 2), (aktP - 1) * sizeof(unsigned int));
              goto Schleife;
            }
          else
            {
              QuasiSingleKnoten++;
              Schalter = ! Schalter;
              optZweig = Zweig;
              break;
            }
        }

      Abstand();
      if (randomisiert)
        a = Verschmierung(Projektion());
      else
        a = Projektion();
      switch (Vergleich(a, opta)) {
      case gleich :
        if (Projektion2() <= optaS)
          break;
      case groesser :
        opta = a; optaS = Projektion2();
        Schalter = ! Schalter;
        optZweig = Zweig;
        break;
      case kleiner :
        break;
      }
    }
  
  /* Nun ist die beste Variable gefunden, und es wird verzweigt */

#ifdef OUTPUTTREEDATAXML
  BeginTreeElement();
#endif

#ifndef LOKALLERNEN
  SatVar -> altTiefe = Tiefe;
#else
  SatVar -> Marke = Markierung();
#endif

  /* zuerst optZweig */

  DN = DeltaN[optZweig][! Schalter];
  DN2 = DeltaN[! optZweig][! Schalter];
#ifdef LOKALLERNEN
  eintragenTiefe();
#endif
#ifndef BAUMRES
  for (i = 0, Z = Huelle[optZweig][! Schalter]; i < DN; i++, Z++)
    belege(*Z);
#else
  Z = Huelle[optZweig][! Schalter];
  belege((Z++) -> l);
  for (i = 1; i < DN; i++, Z++)
    belege_VK(Z -> l, Z -> k);
#endif
  aktP = LaP[optZweig][! Schalter];
  SatVar -> P2 = LaP[! optZweig][! Schalter];
  memcpy((void *)(aktAnzK + 2), (void *)(LaAnzK[optZweig][! Schalter] + 2), (aktP - 1) * sizeof(unsigned int));
  memcpy((void *)((SatVar -> AnzK2) + 2), (void *)(LaAnzK[! optZweig][! Schalter] + 2), ((SatVar -> P2) - 1) * sizeof(unsigned int));
  SatVar -> N2 = aktN - DN2;
  aktN -= DN;
  SatVar -> altZeiger2 = Zeiger2;

/* Ist noch genug Speicher fuer die zweite Belegung?! */

  if (Zeiger2 + DN2 >= Groesse2)
    {
      Ueberschreitung2++;
      Groesse2 += N;
      zweiteBel = (StapeleintragFZ) xrealloc(zweiteBel, Groesse2 * sizeof(StapeleintragF));
    }
  memcpy((void *)(zweiteBel + Zeiger2), (void *)(Huelle[! optZweig][! Schalter]), DN2 * sizeof(StapeleintragF));
  Zeiger2 += DN2;

  if (SatVar -> danach == NULL)
    {
      struct Sammlung *Z;
      Suchbaumtiefe++;
      SatVar -> danach = (Z = neuerKnoten());
      Z -> davor = SatVar;
      SatVar = Z;
    }
  else
    SatVar = SatVar -> danach;
  SatVar -> Ruecksprung = SAT1;
  if (Monitor)
    if (++Rekursionstiefe < Beobachtungsniveau) {
      beobachtet[Rekursionstiefe] = beobachtet[Rekursionstiefe-1];
      if (Dateiausgabe)
#ifndef BAUMRES
	Verzweigungsliteralausgabe(*Huelle[optZweig][! Schalter], Rekursionstiefe - 1);
#else
        Verzweigungsliteralausgabe(Huelle[optZweig][! Schalter] -> l, Rekursionstiefe - 1);
#endif
    }
  goto Anfang;


  nachSAT1 :

#ifdef OUTPUTTREEDATAXML
    EndTreeElement();
#endif

    if (Monitor)
      if (Rekursionstiefe < Beobachtungsniveau)
        {
          beobachtet[Rekursionstiefe] += Zweiglast[Rekursionstiefe];
          Monitorausgabe(beobachtet[Rekursionstiefe]);
        }

  /* rueckgaengig machen */

#ifdef LOKALLERNEN
  Rueckgaengigmachung(SatVar -> Marke);
#else
#ifndef BAUMRES
  do
    {
      Tiefe--;
      rebelege(PfadLit());
    }
  while (Tiefe > SatVar -> altTiefe);
#else
  while (--Tiefe > SatVar -> altTiefe)
    rebelege(PfadLit());
  if (rebelege_Verz(PfadLit()))
    aktV_eintragen_relV();
  else
    {
      Zeiger2 = SatVar -> altZeiger2;
      SingleKnoten++;
      r = SatVar -> Ruecksprung;
      SatVar = SatVar -> davor;
      if (SatVar == NULL) {
#ifdef OUTPUTTREEDATAXML
	EndTreeElement();
#endif
        return UNSAT;
      }
      if (Monitor)
        Rekursionstiefe--;
      switch (r)
        {
        case SAT1 : goto nachSAT1;
        case SAT2 : goto nachSAT2;
        }
    }
#endif
#endif

  /* nun der zweite Zweig */

#ifdef LOKALLERNEN
  eintragenTiefe();
#endif
#ifndef BAUMRES
  for (i = SatVar -> altZeiger2, Z = zweiteBel + (SatVar -> altZeiger2); i < Zeiger2; i++, Z++)
    belege(*Z);
#else
  Z = zweiteBel + (SatVar -> altZeiger2);
  belege((Z++) -> l);
  for (i = SatVar -> altZeiger2 + 1; i < Zeiger2; i++, Z++)
    belege_VK(Z -> l, Z -> k);
#endif

  Zeiger2 = SatVar -> altZeiger2;
  aktP = SatVar -> P2;
  aktN = SatVar -> N2;
  memcpy((void *)(aktAnzK + 2), (void *)((SatVar -> AnzK2) + 2), (aktP - 1) * sizeof(unsigned int));

  if (SatVar -> danach == NULL)
    {
      struct Sammlung *Z;
      Suchbaumtiefe++;
      SatVar -> danach = (Z = neuerKnoten());
      Z -> davor = SatVar;
      SatVar = Z;
    }
  else
    SatVar = SatVar -> danach;
  SatVar -> Ruecksprung = SAT2;
  if (Monitor)
    if (++Rekursionstiefe < Beobachtungsniveau)
      beobachtet[Rekursionstiefe] = beobachtet[Rekursionstiefe-1];
  goto Anfang;

  nachSAT2 :

#ifdef OUTPUTTREEDATAXML
    EndTreeElement();
#endif

    if (Monitor)
      if (Rekursionstiefe < Beobachtungsniveau)
        {
          beobachtet[Rekursionstiefe] += Zweiglast[Rekursionstiefe];
          Monitorausgabe(beobachtet[Rekursionstiefe]);
        }

#ifdef LOKALLERNEN
  Rueckgaengigmachung(SatVar -> Marke);
#else
#ifndef BAUMRES
  do
  {
    Tiefe--;
    rebelege(PfadLit());
  }
  while (Tiefe > SatVar -> altTiefe);
#else
  while (--Tiefe > SatVar -> altTiefe)
    rebelege(PfadLit());
  if (rebelege_Verz(PfadLit()))
    relVMhinzufuegen();
  else
    VerSingleKnoten++;
#endif
#endif
  r = SatVar -> Ruecksprung;
  SatVar = SatVar -> davor;
  if (SatVar == NULL) {
#ifdef OUTPUTTREEDATAXML
    EndTreeElement();
#endif
    return UNSAT;
  }
  if (Monitor)
      Rekursionstiefe--;
  switch (r)
    {
    case SAT1 : goto nachSAT1;
    case SAT2 : goto nachSAT2;
    } 
}




/* -------------------------------------------------------------------------------- */


void Statistikzeile(FILE *fp)
{
  if (Format == Dimacs_Format) {
    fprintf(fp, "s ");
    switch (s) {
    case SAT :
      fprintf(fp, "SATISFIABLE"); break;
    case UNSAT :
      fprintf(fp, "UNSATISFIABLE"); break;
    case Unbestimmt :
      fprintf(fp, "UNKNOWN"); break;
    }
    fprintf(fp, "\n");
    fprintf(fp, "c sat_status=%d initial_maximal_clause_length=%d initial_number_of_variables=%d initial_number_of_clauses=%d initial_number_of_literal_occurrences=%d running_time(s)=%1.1f number_of_nodes=%ld number_of_single_nodes=%ld number_of_quasi_single_nodes=%ld number_of_2-reductions=%ld number_of_pure_literals=%ld number_of_autarkies=%ld number_of_missed_single_nodes=%ld max_tree_depth=%d number_of_table_enlargements=%d reduced_maximal_clause_length=%d reduced_number_of_variables=%d reduced_number_of_clauses=%d reduced_number_of_literal_occurrences=%d number_of_1-autarkies=%ld number_of_initial_unit-eliminations=%ld number_of_new_2-clauses=%ld maximal_number_of_added_2-clauses=%ld initial_number_of_2-clauses=%d file_name=%s\n",
	    s, P0, N0, K0, L0, (double) Verbrauch / EPS,
	    Knoten, SingleKnoten, QuasiSingleKnoten, V1KlRed, PureL, 
	    Autarkien, VerSingleKnoten, Suchbaumtiefe,
	    Ueberschreitung2, P0 - P, N0 - N, K0 - K, L0 - L,
	    FastAutarkien, InitEinerRed, neue2Klauseln, maxneue2K, init2Klauseln,
	    aktName);
  }
  else if (Format == XML_Format) {
    fprintf(fp, "<SAT-solver.output timestamp = \"%ld\" >\n", time(0));

    fprintf(fp, "  <result value = \"");
    switch (s) {
    case SAT : fprintf(fp, "satisfiable"); break;
    case UNSAT : fprintf(fp, "unsatisfiable"); break;
    case Unbestimmt : fprintf(fp, "unknown"); break;
    }
    fprintf(fp, "\" />\n");

    fprintf(fp, "  <processing-description>\n");
    fprintf(fp, "    <basic>\n");
    fprintf(fp, "      <running-time type = \"core\" sec = \"%.2f\" />\n", (double) Verbrauch / EPS);
    fprintf(fp, "      <tree-depth type = \"maximal\" count = \"%d\" />\n", Suchbaumtiefe);
    fprintf(fp, "      <autarky-reductions where = \"search-tree\" level = \"pure\" count = \"%ld\" />\n", PureL);
    fprintf(fp, "      <autarky-reductions where = \"search-tree\" level = \"non-pure\" count = \"%ld\" />\n", Autarkien);
    fprintf(fp, "      <number_of_table_enlargements count = \"%d\" />\n", Ueberschreitung2);
    fprintf(fp, "      <nodes type = \"node\" count = \"%ld\" />\n", Knoten);
    fprintf(fp, "      <nodes type = \"single\" count = \"%ld\" />\n", SingleKnoten);
    fprintf(fp, "      <nodes type = \"quasi-single\" count = \"%ld\" />\n", QuasiSingleKnoten);
    fprintf(fp, "      <nodes type = \"missed_single\" count = \"%ld\" />\n", VerSingleKnoten);
    fprintf(fp, "    </basic>\n");
    fprintf(fp, "    <extended>\n");
    fprintf(fp, "      <generalised_unit_reductions where = \"initial\" level = \"1\" count = \"%ld\" />\n", InitEinerRed);
    fprintf(fp, "      <generalised_unit_reductions where = \"search-tree\" level = \"2\" count = \"%ld\" />\n", V1KlRed);
    fprintf(fp, "      <generalised_autarky-reductions where = \"search-tree\" level = \"1\" specifier = \"total\" count = \"%ld\" />\n", FastAutarkien);
    fprintf(fp, "      <numbers_of_new_clauses list_of_clause-lengths = \"complete\" type = \"local\" specifier = \"maximum\" >\n");
    fprintf(fp, "        <nc_number length = \"2\" count = \"%ld\" />\n", maxneue2K);
    fprintf(fp, "      </numbers_of_new_clauses>\n");
    fprintf(fp, "      <numbers_of_new_clauses list_of_clause-lengths = \"complete\" type = \"local\" specifier = \"total\" >\n");
    fprintf(fp, "        <nc_number length = \"2\" count = \"%ld\" />\n", neue2Klauseln);
    fprintf(fp, "      </numbers_of_new_clauses>\n");
    fprintf(fp, "    </extended>\n");
    fprintf(fp, "  </processing-description>\n");
 
    fprintf(fp, "  <instance_specs system-name = \"%s\" >\n", aktName);

    fprintf(fp, "    <measures>\n");
    fprintf(fp, "      <reduction> <none/> </reduction>\n");
    fprintf(fp, "      <number_of_variables specifier = \"exact\" count = \"%d\" />\n", N0);
    fprintf(fp, "      <clause-length specifier = \"exact\" type = \"maximal\" value = \"%d\" />\n", P0);
    fprintf(fp, "      <total_number_of_clauses specifier = \"exact\" count = \"%d\" />\n", K0);
    fprintf(fp, "      <number_of_literal_occurrences specifier = \"exact\" count = \"%d\" />\n", L0);
    fprintf(fp, "    </measures>\n");

    fprintf(fp, "    <measures>\n");
    fprintf(fp, "      <reduction> <tautological_clauses/> <multiple_literal_occurences_in_clauses/> <unit_clause_elimination/> </reduction>\n");

    if (Knoten == 0) { // nur Vorreduktion
      if (s == UNSAT) { // Vorreduktion erzeugte die leere Klausel
	fprintf(fp, "      <numbers_of_clauses list_of_clause-lengths = \"incomplete\" >\n");
	fprintf(fp, "        <number length = \"0\" specifier = \"lower_bound\" count = \"1\" />\n");
	fprintf(fp, "      </numbers_of_clauses>\n");
      }
      else if (s == SAT) { // Vorreduktion erfuellte die Klauselmenge
	fprintf(fp, "      <total_number_of_clauses specifier = \"exact\" count = \"0\" />\n");
      }
      else { // keine Entscheidung
	fprintf(fp, "      <number_of_variables specifier = \"exact\" count = \"%d\" />\n", N);
	fprintf(fp, "      <clause-length type = \"maximal\" specifier = \"exact\" count = \"%d\" />\n", P);
	fprintf(fp, "      <total_number_of_clauses specifier = \"exact\" count = \"%d\" />\n", K);
	fprintf(fp, "      <number_of_literal_occurrences specifier = \"exact\"count = \"%d\" />\n", L);
      }
    }
    else { // nun wurde der Suchbaum aufgebaut
      fprintf(fp, "      <number_of_variables specifier = \"exact\" count = \"%d\" />\n", N);
      fprintf(fp, "      <clause-length type = \"maximal\" specifier = \"exact\" value = \"%d\" />\n", P);
      fprintf(fp, "      <total_number_of_clauses specifier = \"exact\" count = \"%d\" />\n", K);
      fprintf(fp, "      <numbers_of_clauses list_of_clause-lengths = \"complete\" >\n");
      for (unsigned int i = 0; i <= P - 2; i++)
	if (InitAnzK[i+2] != 0)
	  fprintf(fp, "        <number length = \"%d\" count = \"%d\" />\n", i+2, InitAnzK[i+2]);
      fprintf(fp, "      </numbers_of_clauses>\n");
      fprintf(fp, "      <number_of_literal_occurrences specifier = \"exact\" count = \"%d\" />\n", L);
    }
    fprintf(fp, "    </measures>\n");

    fprintf(fp, "  </instance_specs>\n");

   if (! Belegung || s != SAT || Dateiausgabe)
      fprintf(fp, "</SAT-solver.output>\n");
  }
  else
    fprintf(fp, "%1d %2d %6d %6d %6d %6.1f %7ld %6ld %6ld %8ld %8ld %5ld %4ld %4d %4d %2d %6d %6d %6d %6ld %6ld %7ld %6ld %6d %s\n",
	    s, P0, N0, K0, L0, (double) Verbrauch / EPS,
	    Knoten, SingleKnoten, QuasiSingleKnoten, V1KlRed, PureL, 
	    Autarkien, VerSingleKnoten, Suchbaumtiefe,
	    Ueberschreitung2, P0 - P, N0 - N, K0 - K, L0 - L,
	    FastAutarkien, InitEinerRed, neue2Klauseln, maxneue2K, init2Klauseln,
	    aktName);
  return;
}

char* BasisName(char* const name) {
  char* const basis = strrchr(aktName, '/');
  if (basis == NULL)
    return name;
  else
    return basis + 1;
}


/* -------------------------------------------------------------------------------- */

static FILE *fpaus = NULL; /* fuer die Ausgabe der Ergebnisse */

static void Zustandsanzeige (int signum)
{
#ifndef SYSTIME
  Verbrauch = clock() - akkVerbrauch;
#else
  times(Zeiger);
  Verbrauch = SysZeit.tms_utime - akkVerbrauch;
#endif
  Statistikzeile(stdout);
  if (Dateiausgabe) {
    Statistikzeile(fpaus);
    fflush(NULL);
  }
  signal(SIGUSR1, Zustandsanzeige);
}

jmp_buf Ausgabepunkt;

static void Abbruch (int signum)
{
  signal(SIGUSR2, Abbruch);
  signal(SIGALRM, Abbruch);
  longjmp(Ausgabepunkt, 1);
}

static FILE *fp = NULL; /* die aktuelle Eingabedatei */
static unsigned int Groesse;
static FILE *fppa = NULL; /* fuer die Ausgabe einer erfuellenden Belegung */

static unsigned int Argument;

static char *NameBel = NULL; char *NameMon = NULL;



int main(int argc, char *argv[])

{
  char *Ausgabedatei = "OKs" VERSIONSNUMMER1 "_" VERSIONSNUMMER2 "_" OPTIONENKENNUNG5 OPTIONENKENNUNG6 OPTIONENKENNUNG7 OPTIONENKENNUNG1 OPTIONENKENNUNG2 OPTIONENKENNUNG3 OPTIONENKENNUNG4".res";
  char *Version = VERSIONSNUMMER1 "." VERSIONSNUMMER2;

  signal(SIGUSR1, Zustandsanzeige);
  signal(SIGUSR2, Abbruch);
  signal(SIGALRM, Abbruch);
  if (setjmp(Ausgabepunkt))
    goto Ausgabe;

  if (Konstantenfehler())
    {
      fprintf(stderr, "%s\n", Meldung(0));
      return 1;
    }

  if (argc == 1)
    {
      fprintf(stderr, "%s\n", Meldung(3));
      return 0;
    }

  setzenStandard();

  for (Argument = 1; Argument < argc; Argument++)
    {
      if (strcmp("-V", argv[Argument]) == 0)
        {
          printf("%s %s; %s %s\n%s: %s, %s\n", Meldung(24), DATUM, Meldung(2), Version, Meldung(6), __DATE__, __TIME__);
          printf("%s", Meldung(44));
#ifdef NBAUMRES
          printf(" NBAUMRES");
#endif
#ifdef LITTAB
          printf(" LITTAB");
#endif
#ifdef SYSTIME
          printf(" SYSTIME");
#endif
#ifdef DYNAMISCH
          printf(" DYNAMISCH");
#endif
#ifdef DYNAMISCH
          printf(" FAKTOR=%.2f", FAKTOR);
#endif
#ifdef LOKALLERNEN
          printf(" LOKALLERNEN");
#endif
#ifdef NL2RED
          printf(" NL2RED");
#endif
#ifdef FASTAUTARKIE
          printf(" FASTAUTARKIE");
#endif
#ifdef KEININLINE
          printf(" KEININLINE");
#endif
#ifdef OUTPUTTREEDATAXML
	  printf(" OUTPUTTREEDATAXML");
#endif
          printf(" STANDARD=%1d", STANDARD);

          printf("\n");
          printf("%s %s\n", Meldung(45), Abstandsname);
          printf("%s %s\n", Meldung(46), Projektionsname);
        }
      else if (strcmp("-A", argv[Argument]) == 0)
        printf("%s\n", Meldung(25));
      else if (strcmp("-H", argv[Argument]) == 0)
        printf("%s\n", Meldung(26));
      else if (strcmp("-O", argv[Argument]) == 0)
        Belegung = ! Belegung;
      else if (strcmp("-F", argv[Argument]) == 0)
        Dateiausgabe = ! Dateiausgabe;
      else if (strcmp("-M", argv[Argument]) == 0)
        Monitor = ! Monitor;      
      else if (strcmp("-P", argv[Argument]) == 0)
        nurVorreduktion = ! nurVorreduktion;      
      else if (strcmp("-R", argv[Argument]) == 0)
        spezRueckgabe = ! spezRueckgabe;
      else if (strcmp("-B", argv[Argument]) == 0)
        Schranken = ! Schranken;
      else if (strcmp("-I", argv[Argument]) == 0)
        printf("%s\n%s\n", Meldung(47), Meldung(48));
      else if (strcmp("-RA", argv[Argument]) == 0)
        randomisiert = ! randomisiert;
      else if (strcmp("-DO", argv[Argument]) == 0) {
        Format = Dimacs_Format;
	spezRueckgabe = true;
      }
      else if (strcmp("-XO", argv[Argument]) == 0) {
        Format = XML_Format;
	spezRueckgabe = false;
      }
      else if (strcmp("-TO", argv[Argument]) == 0) {
        Format = Tabellen_Format;
	spezRueckgabe = false;
      }
      else if (strcmp("-specification", argv[Argument]) == 0) {
	printf("<SAT-solver.specification>\n");
	printf("  <solver-type mode = \"deterministic\">\n");
	printf("    <complete/>\n");
	printf("  </solver-type>\n");
	printf("  <solver-name base-name = \"%s\" version = \"%s\" url = \"%s\" />\n", "OKsolver", Version, "http://cs-svr1.swan.ac.uk/~csoliver/OKsolver");
	printf("  <solver-author first_name = \"Oliver\" last_name = \"Kullmann\" country = \"United Kingdom\" e-mail = \"O.Kullmann@Swansea.ac.uk\" www = \"http://cs-svr1.swan.ac.uk/~csoliver/\" />\n");
	printf("  <programming_language name = \"C++\" />\n");
	printf("  <compilation_time timestamp = \"%s %s\" />\n", __DATE__, __TIME__);
	printf("  <url for = \"executable\" value = \"");
	if (argv[0][0] == '/') // absoluter Pfadname
	  printf("%s\" />\n", argv[0]);
	else // relativer Pfadname
	  printf("%s/%s\" />\n", getenv("PWD"), argv[0]);
	printf("  <options string = \"%s\" />\n", OPTIONENKENNUNG5 OPTIONENKENNUNG6 OPTIONENKENNUNG7 OPTIONENKENNUNG1 OPTIONENKENNUNG2 OPTIONENKENNUNG3 OPTIONENKENNUNG4);
	{
	  if (internal)
	    printf("  <internal/>\n");
	}
	printf("</SAT-solver.specification>\n");
      }
      else if (strncmp("-L", argv[Argument], 2) == 0)
        {
          int Nummer;
          if (sscanf(argv[Argument] + 2, "%d", &Nummer) != 1)
            {
              fprintf(stderr, "%s\n", Meldung(18));
              return 1;
            }
          if ((Nummer < 0) || (Nummer >= ANZSPRACHEN))
            {
              fprintf(stderr, "%s %2d\n", Meldung(19), ANZSPRACHEN - 1);
              return 1;
            }
          Sprache = Nummer;
        }
      else if (strncmp("-S", argv[Argument], 2) == 0)
        {
          int Nummer;
          if (sscanf(argv[Argument] + 2, "%d", &Nummer) != 1)
            {
              fprintf(stderr, "%s\n", Meldung(20));
              return 1;
            }
          if ((Nummer < 0) || (Nummer > ANZSTANDARDS))
            {
              fprintf(stderr, "%s %2d\n", Meldung(21), ANZSTANDARDS);
              return 1;
            }
          Standard = Nummer;
          setzenStandard();
        }
      else if (strncmp("-D", argv[Argument], 2) == 0)
	// -D fuer Beobachtungstiefe (depth)
	// Verzweigungsliterale werden (falls ueberhaupt Dateiausgabe gesetzt ist)
	// nur bis zu zwei Stufen unterhalb der Beobachtungsschicht ausgegeben,
	// so dass hierfuer als das Beobachtungsniveau mindestens zwei sein
	// sollte.
        {
          int Nummer;
          if (sscanf(argv[Argument] + 2, "%d", &Nummer) != 1)
            {
              fprintf(stderr, "%s\n", Meldung(31));
              return 1;
            }
          if (Nummer < 0)
            {
              fprintf(stderr, "%s\n", Meldung(32));
              return 1;
            }
          Beobachtungsniveau = Nummer;
        }
      else if (strncmp("-MAXN=", argv[Argument], 6) == 0)
        {
          int maxn;
          if (sscanf(argv[Argument] + 6, "%d", &maxn) != 1)
            {
              fprintf(stderr, "%s\n", Meldung(33));
              return 1;
            }
          if (maxn < 0)
            {
              fprintf(stderr, "%s\n", Meldung(34));
              return 1;
            }
          MAXN = maxn;
        }
      else if (strncmp("-MAXL=", argv[Argument], 6) == 0)
        {
          int maxl;
          if (sscanf(argv[Argument] + 6, "%d", &maxl) != 1)
            {
              fprintf(stderr, "%s\n", Meldung(36));
              return 1;
            }
          if (maxl < 0)
            {
              fprintf(stderr, "%s\n", Meldung(37));
              return 1;
            }
          MAXL = maxl;
        }
      else if (strncmp("-MAXK=", argv[Argument], 6) == 0)
        {
          int maxk;
          if (sscanf(argv[Argument] + 6, "%d", &maxk) != 1)
            {
              fprintf(stderr, "%s\n", Meldung(39));
              return 1;
            }
          if (maxk < 0)
            {
              fprintf(stderr, "%s\n", Meldung(40));
              return 1;
            }
          MAXK = maxk;
        }
      else if (strncmp("-T", argv[Argument], 2) == 0)
        {
          int t;
          if (sscanf(argv[Argument] + 2, "%d", &t) != 1)
            {
              fprintf(stderr, "%s\n", Meldung(42));
              return 1;
            }
          if (t < 0)
            {
              fprintf(stderr, "%s\n", Meldung(43));
              return 1;
            }
          Zeitschranke = t;
        }
      else if (strncmp("-seed=", argv[Argument], 6) == 0)
        {
          long unsigned int S;
          if (sscanf(argv[Argument] + 6, "%lud", &S) != 1)
            {
              fprintf(stderr, "%s\n", Meldung(52));
              return 1;
            }
          Schluessel = S;
        }
      else if (strncmp("-quot=", argv[Argument], 6) == 0)
        {
          double V;
          if (sscanf(argv[Argument] + 6, "%lf", &V) != 1)
            {
              fprintf(stderr, "%s\n", Meldung(53));
              return 1;
            }
          Verhaeltnis = V;
        }
      else if (strncmp("-", argv[Argument], 1) == 0)
        {
          fprintf(stderr, "%s %s\n", Meldung(22), argv[Argument]);
          return 1;
        }
      else
        {
          aktName = argv[Argument];
          s = Unbestimmt;
          alarm(Zeitschranke);
#ifndef SYSTIME
          akkVerbrauch = clock();
#else
          times(Zeiger);
          akkVerbrauch = SysZeit.tms_utime;
#endif
          if (randomisiert)
            srand_S();
          if ((fp = fopen(aktName, "r")) == NULL)
            {
              fprintf(stderr, "%s %s\n", Meldung(4), aktName);
              return 1;
            }
          {
            struct stat stbuf;
            if (stat(aktName, &stbuf) == -1)
              {
                fprintf(stderr, Meldung(7), aktName);
                return 1;
              }
            Groesse = stbuf.st_size;
          }

          if (Dateiausgabe)
            {
              if ((fpaus = fopen(Ausgabedatei, "a")) == NULL)
                {
                  fprintf(stderr, "%s %s\n", Meldung(30), Ausgabedatei);
                  return 1;
                }
              if (Belegung || (Monitor && (! nurVorreduktion)))
                {
                  Wurzel = BasisName(aktName);
                  if (Belegung)
                    {
                      NameBel = (char *) xmalloc((strlen(Wurzel) + 3 + 1) * sizeof(char));
                      strcpy(NameBel, Wurzel); strcat(NameBel, ".pa");
                    }
                  if (Monitor && (! nurVorreduktion))
                    {
                      NameMon = (char *) xmalloc((strlen(Wurzel) + 3 + 1) * sizeof(char));
                      strcpy(NameMon, Wurzel); strcat(NameMon, ".mo");
                      if ((fpmo = fopen(NameMon, "w")) == NULL)
                        {
                          fprintf(stderr, "%s %s\n", Meldung(29), NameMon);
                          return 1;
                        }
                    }
                }     
            }

#ifdef OUTPUTTREEDATAXML
	  {
	    if (not Wurzel) Wurzel = BasisName(aktName);
	    NameTreeDataFile = (char*) xmalloc((strlen(Wurzel) + 4 + 1));
	    strcpy(NameTreeDataFile, Wurzel); strcat(NameTreeDataFile, ".xml");
	    if ((TreeDataFile = fopen(NameTreeDataFile, "w")) == NULL) {
	      fprintf(stderr, "%s %s\n", Meldung(54), NameTreeDataFile);
	      return 1;
	    }
	    fprintf(TreeDataFile, "<?xml version=\"1.0\" standalone=\"yes\" ?>\n");
	    fprintf(TreeDataFile, "<!DOCTYPE t [\n");
	    fprintf(TreeDataFile, "  <!ELEMENT t (t?, t?)>\n");
	    fprintf(TreeDataFile, "  <!ATTLIST t\n");
	    fprintf(TreeDataFile, "    l NMTOKEN #REQUIRED>\n");
	    fprintf(TreeDataFile, "]>\n\n");
	    // If already in the preprocessing phase the formula is decided, then no tree-xml-element is output, and thus the file with name NameTreeDataFile does not contain correct xml.
	  }
#endif

          switch (Einlesen(fp, Groesse)) {
          case Sat : s = SAT; break;
          case Unsat : s = UNSAT; break;
          case Fehler :
            fprintf(stdout, "%s %s.\n", Meldung(17), aktName);
            if (Dateiausgabe)
              fprintf(fpaus, "%s %s.\n", Meldung(17), aktName);
            goto Aufraeumen;
          case Norm :
            if (nurVorreduktion)
              break;
            InitVarLitKlm();
            InitSat();
#ifdef LOKALLERNEN
            InitlokalesLernen();
#endif
            if (Monitor)
              {
                printf("\n%s\n %s, %4d\n", Meldung(28), aktName, Gesamtlast);
                if (Dateiausgabe)
                  fprintf(fpmo, "%s\n %s, %4d\n", Meldung(28), aktName, Gesamtlast);
              }
            
            s = SATEntscheidung();
          }

Ausgabe :

#ifndef SYSTIME
          Verbrauch = clock() - akkVerbrauch;
#else
          times(Zeiger);
          Verbrauch = SysZeit.tms_utime - akkVerbrauch;
#endif
          if (Monitor)
            printf("\n");
          Statistikzeile(stdout);
          if (Dateiausgabe)
            Statistikzeile(fpaus);

/* Achtung: Die Analyse der Ausgabe verlangt, dass das allererste */
/*             Zeichen die SAT-Zugehoerigkeit (d.h.: 0 oder 1) angibt. */

          if (Belegung && (s == SAT))
            {
              if (! Dateiausgabe)
                AusgabeBelegung(stdout);
              else
                {
                  if ((fppa = fopen(NameBel, "w")) == NULL)
                    {
                      fprintf(stderr, "%s %s\n", Meldung(27), NameBel);
                      return 1;
                    }
                  AusgabeBelegung(fppa);
                }
            }
        Aufraeumen :

        alarm(0);
        AufraeumenSat();
#ifdef BAUMRES
        AufraeumenBaumRes();
#endif
#ifdef LOKALLERNEN
        AufraeumenlokalesLernen();
#endif
        AufraeumenEinlesen(); /* zuletzt */
        free(NameBel); NameBel = NULL;
        free(NameMon); NameMon = NULL;
#ifdef OUTPUTTREEDATAXML
	fprintf(TreeDataFile, "\n");
	free(NameTreeDataFile); NameTreeDataFile = NULL;
	if (TreeDataFile != NULL) {
	  fclose(TreeDataFile); TreeDataFile = NULL;
	}
#endif
        if (fp != NULL)
            {
              fclose(fp); fp = NULL;
            }
          if (fpmo != NULL)
            {
              fclose(fpmo); fpmo = NULL;
            }
          if (fpaus != NULL)
            {
              fclose(fpaus); fpaus = NULL;
            }
          if (fppa != NULL)
            {
              fclose(fppa); fppa = NULL;
            }
        }
    }

  if (spezRueckgabe)
    switch (s) {
    case SAT : return 10;
    case UNSAT : return 20;
    case Unbestimmt : return 0;
    }
  else
    return 0;
}

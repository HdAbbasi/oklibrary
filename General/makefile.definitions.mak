# Oliver Kullmann, 13.4.2005 (Swansea)


ifdef OKTESTSYSTEM
  OKTestsystem := -I$(OKTESTSYSTEM)
else
  OKTestsystem :=
endif

ifdef BIBLIOTHEK
  Bibliothek := -I$(BIBLIOTHEK)
else
  Bibliothek :=
endif
ifdef LOKI
  Loki := -I$(LOKI)
else
  Loki :=
endif
ifdef XERCES_H
  Xerces_h := -I$(XERCES_H)
else
  Xerces_h :=
endif
ifdef XERCES_SO
  Xerces_so := -I$(XERCES_SO)
else
  Xerces_so :=
endif

General_options := -g
Optimisation_options := -O3 -DNDEBUG

test_program := TestBibliothek

programs := NumberTheory_Application_gcd Algebra_Applications_ModulareExponentiation TimeHandling_Applications_DaysDifference TimeHandling_Applications_DifferenceList Algebra_Applications_RSA

source_libraries = $(OKTestsystem) $(Bibliothek) $(Xerces_h) $(Loki) $(Boost)

link_libraries := -lboost_date_time-gcc $(Xerces_so)

Root := $(wildcard ../../..)

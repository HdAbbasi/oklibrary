// Oliver Kullmann, 4.4.2002

#ifndef EXPERIMENTVORBEREITUNGWAECHTER

#include <string>
#include <ctime>

namespace ExperimentVorbereitung {

  namespace Fehler {

    struct ExperimentVorbereitungFehler {
      virtual void Ausgabe() const;
    };

    struct Dateifehler : ExperimentVorbereitungFehler {
      void Ausgabe() const;
    };
    struct ExpDesk_lesen : Dateifehler {
      void Ausgabe() const;
    };
    struct CompXml_lesen : Dateifehler {
      void Ausgabe() const;
    };
    struct Verzeichnis_anlegen : Dateifehler {
      void Ausgabe() const;
    };
    struct lines_read_anlegen : Dateifehler {
      void Ausgabe() const;
    };
    struct unlisted_anlegen : Dateifehler {
      void Ausgabe() const;
    };
    struct firstlast_anlegen : Dateifehler {
      void Ausgabe() const;
    };
    struct url_solver_anlegen : Dateifehler {
      void Ausgabe() const;
    };
    struct tasklist_anlegen : Dateifehler {
      void Ausgabe() const;
    };
    struct expxml_anlegen : Dateifehler {
      void Ausgabe() const;
    };

    struct Ausfuehrungsfehler : ExperimentVorbereitungFehler {
      void Ausgabe() const;
    };
    struct LoeserSpezifikation : Ausfuehrungsfehler {
      void Ausgabe() const;
    };

    struct Kommandozeilenfehler : ExperimentVorbereitungFehler {
      void Ausgabe() const;
    };
    struct Deskriptor_fehlt : Kommandozeilenfehler {
      void Ausgabe() const;
    };
    struct CompXml_fehlt : Kommandozeilenfehler {
      void Ausgabe() const;
    };
    struct Loeser_fehlt : Kommandozeilenfehler {
      void Ausgabe() const;
    };

  }
  
  class Experiment {

  public :

    Experiment(std::string DeskriptorDatei, std::string ComputerXmlDatei, std::string Loeser, std::string dtdDatei = "", const std::string& generator = "", std::string Verzeichnis = "");
    // falls Verzeichnis = "", so wird ein Standard-Name gebildet;

    Experiment& NamensergaenzungVorn(std::string s) {Verzeichnisname = s + Verzeichnisname;}
    Experiment& NamensergaenzungHinten(std::string s) {Verzeichnisname += s;}

    std::string Verzeichnis() const {return Verzeichnisname;}
    
    void anlegen() const;

  private :

    std::string Desk;
    std::string Comp;
    std::string Loes;
    std::string dtd;
    std::string gen;

    time_t aktZeit;
    tm aktDatum;

    std::string Verzeichnisname;
    
  };
}

#endif

#define EXPERIMENTVORBEREITUNGWAECHTER


#ifndef REMOLLGENHYPERON_HH
#define REMOLLGENHYPERON_HH

// remoll includes
#include "remollVEventGen.hh"
#include "remollFileReader.hh"

class remollGenHyperon : public remollVEventGen {

  public:
    remollGenHyperon();
    virtual ~remollGenHyperon();

  private:
    void SamplePhysics(remollVertex*, remollEvent*);

    static remollFileReader* fFileReader;
    remollFileReader* GetFileReader() const;

    G4int fDebugLevel;
    std::string fFile;
    G4String fParticle;
    G4int fSkip;
    G4double fRUnit;
    G4double fPUnit;
    G4double fWUnit;
};

#endif // REMOLLGENHYPERON_HH

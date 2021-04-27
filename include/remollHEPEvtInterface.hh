#ifndef REMOLLHEPEVTINTERFACE_HH
#define REMOLLHEPEVTINTERFACE_HH

#include "G4VPrimaryGenerator.hh"

class G4Event;
class remollHEPEvtMessenger;

class remollHEPEvtInterface : public G4VPrimaryGenerator {
protected:
  G4int fVerbose{0};
  G4String fFilename;

  remollHEPEvtMessenger* fMessenger;

  static G4VPrimaryGenerator* fHEPEvtInterface;

public:
  remollHEPEvtInterface();
  ~remollHEPEvtInterface() override;

  // set/get methods
  void SetFileName(G4String name) { fFilename = name; };
  G4String GetFileName() const { return fFilename; };

  void SetVerboseLevel(G4int i) { fVerbose = i; };
  G4int GetVerboseLevel() const { return fVerbose; };

  // methods...
  void Initialize();

  void GeneratePrimaryVertex(G4Event* anEvent) override;
};

#endif

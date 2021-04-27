#ifndef REMOLLHEPEVTINTERFACE_HH
#define REMOLLHEPEVTINTERFACE_HH

#include "G4VPrimaryGenerator.hh"

class G4Event;
class remollHEPEvtMessenger;

class remollHEPEvtInterface : public G4VPrimaryGenerator {
protected:
  G4int fVerbose;
  G4String fFilename;

  remollHEPEvtMessenger* fMessenger;

  static G4VPrimaryGenerator* fHEPEvtInterface;

public:
  remollHEPEvtInterface();
  ~remollHEPEvtInterface() override;

  // set/get methods
  void SetFileName(G4String name);
  G4String GetFileName() const;

  void SetVerboseLevel(G4int i);
  G4int GetVerboseLevel() const;

  // methods...
  void Initialize();

  void GeneratePrimaryVertex(G4Event* anEvent) override;
};

// ====================================================================
// inline functions
// ====================================================================

inline void remollHEPEvtInterface::SetFileName(G4String name)
{
  fFilename = name;
}

inline G4String remollHEPEvtInterface::GetFileName() const
{
  return fFilename;
}

inline void remollHEPEvtInterface::SetVerboseLevel(G4int i)
{
  fVerbose = i;
}

inline G4int remollHEPEvtInterface::GetVerboseLevel() const
{
  return fVerbose;
}

#endif

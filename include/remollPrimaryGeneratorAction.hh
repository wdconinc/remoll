#ifndef REMOLLPRIMARYGENERATORACTION_HH
#define REMOLLPRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4VPrimaryGenerator.hh"
#include "G4String.hh"

#include <map>

class G4GenericMessenger;
class G4ParticleGun;
class G4Event;
class remollBeamTarget;
class remollVEventGen;
class remollEvent;

class remollPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    remollPrimaryGeneratorAction();
    ~remollPrimaryGeneratorAction() override;

  public:
    void GeneratePrimaries(G4Event* anEvent) override;

    const remollEvent* GetEvent() const { return fEvent; }

    void SetGenerator(G4String&);

  private:
    std::map<G4String,remollVEventGen*> fEvGenMap;
    remollVEventGen *fEventGen{nullptr};
    G4String fEventGenName;

    std::map<G4String,G4VPrimaryGenerator*> fPriGenMap;
    G4VPrimaryGenerator *fPriGen{nullptr};
    G4String fPriGenName;

    G4ParticleGun* fParticleGun{nullptr};

    remollBeamTarget *fBeamTarg{nullptr};


    remollEvent *fEvent{nullptr};

    G4GenericMessenger* fMessenger{nullptr};
    G4GenericMessenger* fEvGenMessenger{nullptr};

    G4double fEffCrossSection{0};
};

#endif // REMOLLPRIMARYGENERATORACTION_HH

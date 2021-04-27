#ifndef REMOLLRUNACTION_HH
#define REMOLLRUNACTION_HH

#include "globals.hh"
#include "G4UserRunAction.hh"

class G4GenericMessenger;
class G4Timer;
class G4Run;

class remollRunAction : public G4UserRunAction
{
  public:
    remollRunAction();
    ~remollRunAction() override;

  public:
    G4Run* GenerateRun() override;

    void BeginOfRunAction(const G4Run* aRun) override;
    void EndOfRunAction(const G4Run* aRun) override;

    void UpdateSeed(const G4long seed);

  private:
    G4GenericMessenger* fMessenger;
    G4Timer* fTimer;

  private:
    G4int fInterval;
  public:
    void SetUpdateInterval(G4int interval) { fInterval = interval; };
};

#endif // REMOLLRUNACTION_HH


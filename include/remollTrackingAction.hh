#ifndef REMOLLTRACKINGACTION_HH
#define REMOLLTRACKINGACTION_HH

// geant4 includes
#include "G4Types.hh"
#include "G4UserTrackingAction.hh"

// forward declares
class G4GenericMessenger;

class remollTrackingAction : public G4UserTrackingAction
{
  public:
    remollTrackingAction();
    ~remollTrackingAction() override;

    void  PreUserTrackingAction(const G4Track* aTrack) override;
    void PostUserTrackingAction(const G4Track* aTrack) override;

  private:
    G4GenericMessenger* fMessenger{nullptr};
    G4int fTrackingFlag{3};
};

#endif // REMOLLTRACKINGACTION_HH

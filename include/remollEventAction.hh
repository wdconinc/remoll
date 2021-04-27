#ifndef remollEventAction_h
#define remollEventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Timer.hh"

#include "globals.hh"

class G4Event;

class remollPrimaryGeneratorAction;
class remollTrackReconstruct;

class remollEventAction : public G4UserEventAction
{
  public:
    remollEventAction() = default;
    ~remollEventAction() override = default;

  public:
    void BeginOfEventAction(const G4Event*) override;
    void EndOfEventAction(const G4Event*) override;

  private:
    // Pointer to primary generator action
    remollPrimaryGeneratorAction* fPrimaryGeneratorAction{nullptr};
    remollTrackReconstruct* rTrack;

    // Timer for benchmarking of simulation time per event
    G4Timer fTimer;

  public:
    // Setter for primary generator action
    void SetPrimaryGeneratorAction(remollPrimaryGeneratorAction* action) {
      fPrimaryGeneratorAction = action;
    }

};

#endif


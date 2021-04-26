#include "remollSteppingAction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4GenericMessenger.hh"

remollSteppingAction::remollSteppingAction()
= default;

remollSteppingAction::~remollSteppingAction()
= default;

void remollSteppingAction::UserSteppingAction(const G4Step *aStep)
{
}

#ifndef REMOLLSTEPPINGACTION_HH
#define REMOLLSTEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include <set>

class G4Material;
class G4GenericMessenger;

class remollSteppingAction : public G4UserSteppingAction
{
  public:
    remollSteppingAction();
    virtual ~remollSteppingAction();

    virtual void UserSteppingAction(const G4Step*);
};

#endif // REMOLLSTEPPINGACTION_HH

#ifndef REMOLLUSERTRACKINFORMATION_HH
#define REMOLLUSERTRACKINFORMATION_HH

#include "G4StepStatus.hh"
#include "G4VUserTrackInformation.hh"

class remollUserTrackInformation : public G4VUserTrackInformation
{
  public:
    remollUserTrackInformation() { fStepStatus = fUndefined; };
    virtual ~remollUserTrackInformation() = default;
    G4StepStatus GetStepStatus() const { return fStepStatus; };
    void SetStepStatus(G4StepStatus stepstatus) { fStepStatus = stepstatus; };
  private:
    G4StepStatus fStepStatus;
};

#endif // REMOLLUSERTRACKINFORMATION_HH

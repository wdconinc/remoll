/*
 * remollUserActionInitialization.hh
 *
 *  Created on: May 1, 2017
 *      Author: wdconinc
 */

#ifndef REMOLLACTIONINITIALIZATION_HH
#define REMOLLACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"

class remollActionInitialization : public G4VUserActionInitialization {
  public:
    remollActionInitialization(): G4VUserActionInitialization() { };
    virtual ~remollActionInitialization() = default;

    virtual void Build() const;
    virtual void BuildForMaster() const;
};

#endif // REMOLLACTIONINITIALIZATION_HH

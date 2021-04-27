#ifndef REMOLLRUN_HH
#define REMOLLRUN_HH

/*!
 * All the information on the run
 * The data object will get put into the output
 * stream

   This is implemented in the soliton model
 */

#include "G4Run.hh"

class remollRunData;

class remollRun: public G4Run {

  public:
    remollRun(): G4Run() { };
    virtual ~remollRun() = default;

  // Static run data access
  private:
    static remollRunData* fRunData;
  public:
    static remollRunData* GetRunData();
};

#endif // REMOLLRUN_HH

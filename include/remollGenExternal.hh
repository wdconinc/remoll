/*
 * remollGenExternal.hh
 *
 *  Created on: Mar 17, 2017
 *      Author: wdconinc
 */

#ifndef REMOLLGENEXTERNAL_HH
#define REMOLLGENEXTERNAL_HH

/*!
 * External event generator
 *
 * This event generator reads events from an external ROOT file, structured
 * like the remoll output ROOT files, and throws hits stored in a particular
 * detector ID (to be specified through a messenger class)
 *
*/

// Base class headers
#include "remollVEventGen.hh"

// System headers
#include <vector>

#include "G4AutoLock.hh"
#include "Randomize.hh"

// Forward declarations
class TFile;
class TTree;
struct remollEvent_t;
struct remollGenericDetectorHit_t;

// Class definition
class remollGenExternal : public remollVEventGen {

    public:
        remollGenExternal();
        ~remollGenExternal() override;

        void SetGenExternalFile(G4String& filename);
        void SetGenExternalZOffset(G4double tempzOffset) {
            fzOffset = tempzOffset;
        }
        void SetGenExternalDetID(const G4int detid) {
            fDetectorID = detid;
        }
        void SetGenExternalEntry(const G4int firstEventID){
            fEntry = ((firstEventID >= 0)? firstEventID : G4RandFlat::shoot(fEntries));
        }

    private:
        void SamplePhysics(remollVertex *, remollEvent *) override;

        // External event file and tree, entry number
        static TFile* fFile{nullptr};
        static TTree* fTree{nullptr};
        static Int_t fEntry{0}, fEntries{0};

        // Event and hit structures
        static remollEvent_t* fEvent{nullptr};
        static vector<remollGenericDetectorHit_t>* fHit{nullptr};

        G4double fzOffset{0};

        // Detector ID to consider
        G4int fDetectorID{28};
        G4int fLoopID{1};

};

#endif // REMOLLGENEXTERNAL_HH

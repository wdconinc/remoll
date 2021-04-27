#ifndef REMOLLGEN12CELASTIC_HH
#define REMOLLGEN12CELASTIC_HH
/*!
 * e12C elastic event generator
 *
 * Rupesh Silwal
 * Aug 9, 2013
 *
 * Based heavily on remollGenpElastic.hh
*/

#include "remollVEventGen.hh"

class remollBeamTarget;

class remollGen12CElastic : public remollVEventGen {
    public:
	remollGen12CElastic();
	~remollGen12CElastic() override;

    private:
	void SamplePhysics(remollVertex *, remollEvent *) override;

	G4double RadProfile(G4double,G4double);
	G4double EnergNumInt(G4double,G4double,G4double);

	remollBeamTarget *fBeamTarg;
};

#endif // REMOLLGEN12CELASTIC_HH

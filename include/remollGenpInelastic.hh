#ifndef REMOLLGENPINELASTIC_HH
#define REMOLLGENPINELASTIC_HH
/*!
 * Inelastic ep event generator
 *
 * Seamus Riordan
 * February 14, 2013
 *
 * Uses Christy/Bosted parameterization
*/

#include "remollVEventGen.hh"

class remollGenpInelastic : public remollVEventGen {
    public:
	remollGenpInelastic();
	virtual ~remollGenpInelastic();

    private:
	void SamplePhysics(remollVertex *, remollEvent *);

};

#endif // REMOLLGENMOLLER_HH

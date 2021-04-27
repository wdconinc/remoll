#ifndef REMOLLGENMOLLER_HH
#define REMOLLGENMOLLER_HH
/*!
 * Moller (ee) event generator
 *
 * Seamus Riordan
 * February 4, 2013
 *
 * Based heavily on previous work from mollersim
*/

#include "remollVEventGen.hh"

class remollBeamTarget;

class remollGenMoller : public remollVEventGen {
    public:
	remollGenMoller();
	~remollGenMoller() override;

    private:
	void SamplePhysics(remollVertex *, remollEvent *) override;

	remollBeamTarget *fBeamTarg;

};

#endif // REMOLLGENMOLLER_HH

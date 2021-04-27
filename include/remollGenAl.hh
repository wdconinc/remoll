#ifndef REMOLLGENAL_HH
#define REMOLLGENAL_HH

#include "remollVEventGen.hh"

#include <map>

class remollGenAl : public remollVEventGen {
public:
  remollGenAl(G4int physicsType);
  ~remollGenAl() override;
  
private:
  G4int type;

  static std::map<G4int,G4String> fNamesMap;
  static std::map<G4int,G4String> CreateNamesMap();

  void SamplePhysics(remollVertex *, remollEvent *) override;

  ///Christy Bosted fit 
  void GenInelastic(G4double beamE,G4double theta,
		    G4double &Q2,G4double &W2,G4double &effectiveXsection,
		    G4double &fWeight,G4double &eOut,G4double &asym);

  ///Christy Bosted fit 
  void GenQuasiElastic(G4double beamE,G4double theta,
		       G4double &Q2,G4double &W2,G4double &effectiveXsection,
		       G4double &fWeight,G4double &eOut,G4double &asym);
  
  void GenElastic(G4double beamE, G4double theta,
		  G4double &Q2,G4double &W2,G4double &effectiveXsection,
		  G4double &fWeight,G4double &eOut,G4double &asym);

};

#endif // REMOLLGENAL_HH

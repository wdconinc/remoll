#ifndef REMOLLPARALLELCONSTRUCTION_HH
#define REMOLLPARALLELCONSTRUCTION_HH

#include <G4VUserParallelWorld.hh>

#include "remollSearchPath.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4GDMLParser;
class G4GenericMessenger;

//
/// A parallel world construction class
///
/// - void Construct()
///     creates a parallel world in the mass world and parameterized volumes
//
class remollParallelConstruction : public G4VUserParallelWorld
{
  public:
    remollParallelConstruction(const G4String& name, const G4String& gdmlfile);
    ~remollParallelConstruction() override;

  public:

    void Construct() override;
    void ConstructSD() override;

  private:
    G4String fGDMLPath;
    G4String fGDMLFile;

    void SetGDMLFile(G4String gdmlfile) {
      gdmlfile = remollSearchPath::resolve(gdmlfile);
      size_t i = gdmlfile.rfind('/');
      if (i != std::string::npos) {
        fGDMLPath = gdmlfile.substr(0,i);
      } else fGDMLPath = ".";
      fGDMLFile = gdmlfile.substr(i + 1);
    }

    G4GDMLParser *fGDMLParser{nullptr};

    G4bool fGDMLValidate{false};
    G4bool fGDMLOverlapCheck{true};

    G4int fVerboseLevel{0};

    G4GenericMessenger* fParallelMessenger{nullptr};

    G4VPhysicalVolume* fWorldVolume{nullptr};
    G4String           fWorldName;

  private:

    void PrintGDMLWarning() const;

    G4VPhysicalVolume* ParseGDMLFile();

    void PrintAuxiliaryInfo() const;
    void ParseAuxiliaryVisibilityInfo();
    void ParseAuxiliarySensDetInfo();

};

#endif // REMOLLPARALLELCONSTRUCTION_HH

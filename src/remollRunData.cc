#include "remollRunData.hh"

#include "G4ios.hh"

#include <string.h>
#include <errno.h>

#ifdef __APPLE__
#include <unistd.h>
#endif

// External objects
extern const char* const gGitInfo;

void remollRunData::Init()
{
    fNthrown = 0;
    fSeed = 0;

    fGitInfo = gGitInfo;

    const unsigned int length = 128;

    char hostname[length];
    if (gethostname(hostname, length) == -1) {
	G4cerr << "Error:  " << __PRETTY_FUNCTION__ << " line " << __LINE__ << ": "
               << "could not get hostname" << G4endl;
    } else {
        fHostName = hostname;
    }

    char runpath[length];
    if (getcwd(runpath, length) == nullptr) {
	G4cerr << "Error:  " << __PRETTY_FUNCTION__ << " line " << __LINE__ << ": "
               << "could not get current working directory" << G4endl;
    } else {
        fRunPath = runpath;
    }
}

void remollRunData::Print()
{
    G4cout << "git repository info" << G4endl;
    G4cout << "-------------------------------------------------" << G4endl;
    G4cout << fGitInfo << G4endl;
    G4cout << "-------------------------------------------------" << G4endl;
    G4cout << "Run at " << fRunTime.AsString("ls") << " on " << fHostName << G4endl;
    G4cout << "Run path " << fRunPath << G4endl;
    G4cout << "N generated = " << fNthrown << G4endl;

    G4cout << "Field maps:" << G4endl;
    for (auto & i : fMagData){
	G4cout << "\t" << i.filename << G4endl;
	G4cout << "\t" << i.hashsum << G4endl;
	G4cout << "\t" << i.timestamp.AsString("ls") << G4endl;
    }

    G4cout << "Macro run:" << G4endl;
    G4cout << "-------------------------------------------------" << G4endl;
    fMacro.Print();
    G4cout << "-------------------------------------------------" << G4endl;
    G4cout << "Stored GDML Files:" << G4endl;
    for (auto & fGDMLFile : fGDMLFiles) {
	if( fGDMLFile.GetBufferSize() >= 1024 ){
	    G4cout << "\t" << fGDMLFile.GetFilename() << " " << fGDMLFile.GetBufferSize()/1024 << "kB" << G4endl;
	} else {
	    G4cout << "\t" << fGDMLFile.GetFilename() << " < 1kB" << G4endl;
	}
    }
    G4cout << "-------------------------------------------------" << G4endl;
}

void remollRunData::AddGDMLFile( const char *fn )
{
    // Check for duplicates I guess
    for(auto & fGDMLFile : fGDMLFiles){
	if( strcmp(fn, fGDMLFile.GetFilename()) == 0 ){
	    // Already added
	    return;
	}
    }

    fGDMLFiles.emplace_back(fn); 
}

void remollRunData::RecreateGDML( const char *adir, bool clobber )
{
    for(auto & fGDMLFile : fGDMLFiles){
	fGDMLFile.RecreateInDir(adir, clobber);
    }
}

ClassImp(remollRunData)

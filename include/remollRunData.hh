#ifndef REMOLLRUNDATA_HH
#define REMOLLRUNDATA_HH

#include "TObject.h"

#include <vector>
#include <string>

#include "remolltypes.hh"
#include "remollTextFile.hh"

/*!
 * All the information on the run
 * This will get put into the output
 * stream
*/

class remollRunData : public TObject {
  using TObject::Print;
    public:
	remollRunData() = default;
	~remollRunData() override = default;

        void Init();

	void Print();

    private:
        std::vector<filedata_t> fMagData;
    public:
	void AddMagData(filedata_t d) { fMagData.push_back(d); }

    private:
	remollTextFile fMacro;
    public:
	void SetMacroFile(const char *fn) { fMacro = remollTextFile(fn); }

    private:
	std::vector<remollTextFile> fGDMLFiles;
    public:
	void AddGDMLFile(const char *fn);
	remollTextFile GetGDMLFile(int i) const { return fGDMLFiles[i]; }
	void ClearGDMLFiles(){ fGDMLFiles.clear(); }
	void RecreateGDML(const char *adir = nullptr, bool clobber = false);

    private:
	int fNthrown; // int G4Run::GetNumberOfEventToBeProcessed()
    public:
	void SetNthrown(int n) { fNthrown = n; }
	int GetNthrown() const { return fNthrown; }

    private:
	long int fSeed; // CLHEP::HepRandom::setTheSeed(long seed, int lux)
    public:
	void SetSeed(long int seed) { fSeed = seed; }
        long int GetSeed() const { return fSeed; }

    private:
        std::string fGitInfo;
    public:
        std::string GetGitInfo() const { return fGitInfo; }

    private:
	TTimeStamp fRunTime;
    public:
        TTimeStamp GetRunTime() const { return fRunTime; }

    private:
	std::string fRunPath;
    public:
        std::string GetRunPath() const { return fRunPath; }

    private:
        std::string fHostName;
    public:
        std::string GetHostName() const { return fHostName; }

	ClassDef(remollRunData, 2);
};

#endif // REMOLLRUNDATA_HH

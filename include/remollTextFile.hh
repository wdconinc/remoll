#ifndef __REMOLLTEXTFILE_HH
#define __REMOLLTEXTFILE_HH

#define __STRLEN 1024

#include "TObject.h"

class remollTextFile : public TObject {
  using TObject::Print;
     public:       
	 remollTextFile();
	 remollTextFile(const remollTextFile &);
	 const remollTextFile& operator=(const remollTextFile &);
	 remollTextFile(const char *);
	 virtual ~remollTextFile();

	 void copyFileIn(const char *);

	void Print();

	const char *GetFilename(){ return fFilename; }
	unsigned long long int GetBufferSize(){ return fBufferSize; }
	
	void Recreate(const char *fn = nullptr, bool clobber = false);
	void RecreateInDir(const char *path, bool clobber = false);

    private:
	unsigned int fFilenameSize;
	char *fFilename;

	unsigned long long int fBufferSize;
	char *fBuffer;

	const char *GetBaseFile(const char *fp = nullptr);

	ClassDef(remollTextFile, 1);
};

#endif//__REMOLLTEXTFILE_HH

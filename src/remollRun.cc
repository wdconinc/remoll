#include "remollRun.hh"

#include "remollRunData.hh"

remollRunData* remollRun::fRunData = nullptr;

remollRunData* remollRun::GetRunData()
{
  if (!fRunData) {
    fRunData = new remollRunData();
    fRunData->Init();
  }
  return fRunData;
}

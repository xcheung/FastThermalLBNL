Bool_t LoadThermalClass()
{
  gSystem->AddIncludePath("-Wno-deprecated");

  if (gROOT->LoadMacro("TGenThermalParticles.cxx+")<0) return kFALSE;

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t LoadPythia8()
{
  char *p8dataenv = gSystem->Getenv("PYTHIA8DATA");

  if (!p8dataenv) {
    char *p8env = gSystem->Getenv("PYTHIA8");

    if (!p8env) {
      Error("TUtils.h",
            "Environment variable PYTHIA8 must contain path to pythia directory!");
      return kTRUE;
    }

    TString p8d = p8env;
    p8d += "/xmldoc";
    gSystem->Setenv("PYTHIA8DATA", p8d);
  }
//=============================================================================

  char *path = gSystem->ExpandPathName("$PYTHIA8DATA");

  if (gSystem->AccessPathName(path)) {
    Error("TUtils.h",
          "Environment variable PYTHIA8DATA must contain path to $PYTHIA8/xmldoc directory !");
    return kTRUE;
  }
//=============================================================================

  if (gSystem->Load("$PYTHIA8/lib/libpythia8")<0) return kTRUE;

  if (gSystem->Load("libEG")       <0) return kTRUE;
  if (gSystem->Load("libEGPythia8")<0) return kTRUE;
//=============================================================================

  return kFALSE;
}

//_____________________________________________________________________________
Bool_t LoadRootLibs()
{
  if (gSystem->Load("libTree")       <0) return kTRUE;
  if (gSystem->Load("libGeom")       <0) return kTRUE;
  if (gSystem->Load("libPhysics")    <0) return kTRUE;
  if (gSystem->Load("libVMC")        <0) return kTRUE;
  if (gSystem->Load("libMinuit")     <0) return kTRUE;
  if (gSystem->Load("libMinuit2")    <0) return kTRUE;

  if (gSystem->Load("libCore")       <0) return kTRUE;
  if (gSystem->Load("libXMLIO")      <0) return kTRUE;
  if (gSystem->Load("libXMLParser")  <0) return kTRUE;
  if (gSystem->Load("libProof")      <0) return kTRUE;
  if (gSystem->Load("libProofPlayer")<0) return kTRUE;
  if (gSystem->Load("libGui")        <0) return kTRUE;

  return kFALSE;
}

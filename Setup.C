void Setup()
{
  gROOT->LoadMacro("TUtils.h");
//=============================================================================

  if (LoadRootLibs()) return;
  if (LoadThermalClass()) return;
//=============================================================================

  return;
}

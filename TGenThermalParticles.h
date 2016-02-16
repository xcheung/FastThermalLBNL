/******************************************************************************
20141201:
  - Generate massless thermal particle according to Boltzmann
  - uniform eta and phi
  - fill TClonesArray with TParticle object
  - thermal particles are identified with statu code = -1
  - deltails in Example.C

//TODO
  - add other thermal models
  - add opt for particle mass
  - add opt for non-uniform eta and phi (flow, (long) range correlations...)
  - add opt to fill fastjet::PseudoJet object in std::vector
******************************************************************************/

#ifndef TGENTHERMALPARTICLES_H
#define TGENTHERMALPARTICLES_H

#include <TNamed.h>

class TF1;
class TClonesArray;

class TGenThermalParticles : public TNamed {

 public :

  TGenThermalParticles();
  TGenThermalParticles(const char *name, const char *title="Thermal Particle Generator Class");
  virtual ~TGenThermalParticles();

  void SetMultiplicity(Int_t n) { fMult = n; }

  void SetMeanPt(Double_t d) { fPtMean = d; }
  void SetPtRange(Double_t dMin, Double_t dMax) { fPtMin = dMin; fPtMax = dMax; }

  void SetEtaRange(Double_t dMin, Double_t dMax) { fEtaMin = dMin; fEtaMax = dMax; }
  void SetPhiRange(Double_t dMin, Double_t dMax) { fPhiMin = dMin; fPhiMax = dMax; }

  Int_t ImportParticles(TClonesArray *pClArr, const TString sOpt="Boltzmann");
//=============================================================================

 private :

  TGenThermalParticles(const TGenThermalParticles &);
  TGenThermalParticles& operator=(const TGenThermalParticles &);
//=============================================================================

  void InitBoltzmann();
  void FillBoltzmann(TClonesArray *pClArr);
  Double_t Boltzmann(Double_t const *x, Double_t const *par);

  Int_t CheckClArr(TClonesArray *pClArr);
//=============================================================================

  Int_t fMult;

  Double_t fPtMin;
  Double_t fPtMax;
  Double_t fPtMean;

  Double_t fEtaMin;
  Double_t fEtaMax;

  Double_t fPhiMin;
  Double_t fPhiMax;

  Bool_t fIsInitBoltzmann;

  TF1 *fFxnBoltzmann;

  ClassDef(TGenThermalParticles, 1)
};

#endif

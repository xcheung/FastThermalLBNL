#include <TClass.h>
#include <TString.h>
#include <TError.h>

#include <TMath.h>
#include <TRandom3.h>
#include <TLorentzVector.h>
#include <TF1.h>

#include <TParticle.h>
#include <TClonesArray.h>

#include "TGenThermalParticles.h"

ClassImp(TGenThermalParticles)

//_____________________________________________________________________________
TGenThermalParticles::TGenThermalParticles() :
TNamed(),
fMult(0),
fPtMin(0.),
fPtMax(0.),
fPtMean(0.),
fEtaMin(0.),
fEtaMax(0.),
fPhiMin(0.),
fPhiMax(0.),
fIsInitBoltzmann(kFALSE),
fFxnBoltzmann(0)
{
//
//  TGenThermalParticles::TGenThermalParticles
//
}

//_____________________________________________________________________________
TGenThermalParticles::TGenThermalParticles(const char *name, const char *title) :
TNamed(name,title),
fMult(2000),
fPtMin(0.15),
fPtMax(200.),
fPtMean(0.7),
fEtaMin(-0.9),
fEtaMax(0.9),
fPhiMin(0.),
fPhiMax(TMath::TwoPi()),
fIsInitBoltzmann(kFALSE),
fFxnBoltzmann(0)
{
//
//  TGenThermalParticles::TGenThermalParticles
//
}

//_____________________________________________________________________________
TGenThermalParticles::~TGenThermalParticles()
{
//
//  TGenThermalParticles::~TGenThermalParticles
//

  if (fFxnBoltzmann) { delete fFxnBoltzmann; fFxnBoltzmann = 0; }
}

//_____________________________________________________________________________
Int_t TGenThermalParticles::ImportParticles(TClonesArray *pClArr, const TString sOpt)
{
  Int_t ncs = CheckClArr(pClArr);

  if (ncs<0) {
    Error("ImportParticles", "No particle will be filled!");
    return ncs;
  }
//=============================================================================

  if (sOpt.IsNull()) {
    Error("ImportParticles", "Particle type is not defined!");
    return pClArr->GetEntriesFast();
  }
//=============================================================================

  if (sOpt=="Boltzmann") {
    InitBoltzmann();
    FillBoltzmann(pClArr);
  }
//=============================================================================

  return pClArr->GetEntriesFast();
}

//_____________________________________________________________________________
void TGenThermalParticles::FillBoltzmann(TClonesArray *pClArr)
{
//
//  TGenThermalParticles::FillBoltzmann
//

  TRandom3 r3(0);
  TLorentzVector vPseudo;
  TParticle *particle = 0;
  Int_t ncs = pClArr->GetEntriesFast();
//=============================================================================

  for (Int_t i=0; i<fMult; i++) {
    double dPt = fFxnBoltzmann->GetRandom(0., fPtMax);
    if (dPt<fPtMin) continue;

    vPseudo.SetPtEtaPhiM(dPt, r3.Uniform(fEtaMin,fEtaMax),
                              r3.Uniform(fPhiMin,fPhiMax), 0.);

    particle = new TParticle();
    particle->SetStatusCode(-1);
    particle->SetMomentum(vPseudo);
    new ((*pClArr)[ncs++]) TParticle(*particle);

    particle = 0;
  }

  return;
}

//_____________________________________________________________________________
void TGenThermalParticles::InitBoltzmann()
{
//
//  TGenThermalParticles::InitBoltzmann
//

  if (fIsInitBoltzmann) return;
//=============================================================================

  if (fFxnBoltzmann) { delete fFxnBoltzmann; fFxnBoltzmann = 0; }

  fFxnBoltzmann = new TF1("fxnBoltzmann", this, &TGenThermalParticles::Boltzmann,
                          0., fPtMax, 1, "TGenThermalParticles", "Boltzmann");
  fFxnBoltzmann->SetParameter(0, fPtMean);
  fFxnBoltzmann->SetNpx(2000);
//=============================================================================

  fIsInitBoltzmann = kTRUE;
//=============================================================================

  return;
}

//_____________________________________________________________________________
Double_t TGenThermalParticles::Boltzmann(Double_t const *x, Double_t const *par)
{
//
//  TGenThermalParticles::Boltzmann
//

  Double_t  dKernel = 2. * x[0] / par[0];
  return (dKernel * TMath::Exp(-1.*dKernel));
}

//_____________________________________________________________________________
Int_t TGenThermalParticles::CheckClArr(TClonesArray *pClArr)
{
//
//  TGenThermalParticles::CheckClArr
//

  if (pClArr) {
    TClass *cls = pClArr->GetClass();

    if (cls) {
      return pClArr->GetEntriesFast();
    } else {
      Warning("CheckClArr", "Redefine input TClonesArray to collect TParticle object!");

      pClArr->Delete("C");
      delete pClArr; pClArr = 0;

      pClArr = new TClonesArray("TParticle");
      return pClArr->GetEntriesFast();
    }
  } else {
    Warning("CheckClArr", "Init input TClonesArray to collect TParticle object!");

    pClArr = new TClonesArray("TParticle");
    return pClArr->GetEntriesFast();
  }

  return pClArr->GetEntriesFast();
}

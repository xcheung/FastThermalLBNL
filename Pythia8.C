void Pythia8(const Int_t nEvents = 10)
{
  gROOT->LoadMacro("TUtils.h");

  if (LoadRootLibs()) return;
  if (LoadPythia8())  return;
  if (LoadThermalClass()) return;
//=============================================================================

  TPythia8 *pythia8 = new TPythia8();

  pythia8->ReadString("SoftQCD:all = on");
  pythia8->ReadString("SoftQCD:singleDiffractive = on");
  pythia8->ReadString("SoftQCD:doubleDiffractive = on");

  pythia8->Initialize(2212, 2212, 14000.);
//=============================================================================

  TGenThermalParticles *thermal = new TGenThermalParticles("Boltzmann");

  thermal->SetMultiplicity(2000);

  thermal->SetMeanPt(0.7);
  thermal->SetPtRange(0.15, 200.);

  thermal->SetEtaRange(-0.8, 0.8);
  thermal->SetPhiRange(0., TMath::TwoPi());
//=============================================================================

  TClonesArray *particles = new TClonesArray("TParticle", 1000);

  for (Int_t iEvent=0; iEvent<nEvents; iEvent++) {
    pythia8->GenerateEvent();
    if (iEvent==0) pythia8->EventListing();

    pythia8->ImportParticles(particles, "Final");
    Int_t nb = particles->GetEntriesFast();
    cout << "iEvent = "<< iEvent << ", np before = " << nb;

    thermal->ImportParticles(particles, "Boltzmann");
    Int_t na = particles->GetEntriesFast();
    cout << ", np after = " << na << endl;

    TParticle *part = 0;
    for (Int_t i=0; i<na; i++) {
      part = (TParticle*)particles->At(i); if (!part) continue;
      Bool_t bThermalBkg = (part->GetStatusCode()==-1);

      if (!bThermalBkg) {
        Int_t kPDG = part->GetPdgCode();
        Float_t dCharge = TDatabasePDG::Instance()->GetParticle(kPDG)->Charge();
      }

      part = 0;
    }
  }
//=============================================================================

   pythia8->PrintStatistics();
//=============================================================================

  return;
}

#ifndef testGDML01TrackerSD_h
#define testGDML01TrackerSD_h 1

#include "testGDML01TrackerHit.h"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class testGDML01TrackerSD : public G4VSensitiveDetector {
  public:
      testGDML01TrackerSD(G4String name, G4double eff=100.0, G4bool noise=false, G4double th=0.9);
      virtual ~testGDML01TrackerSD();

      void Initialize(G4HCofThisEvent* HCE);
      G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* roHist=NULL);
      void EndOfEvent(G4HCofThisEvent* HCE);

  private:
      testGDML01TrackerHitsCollection* trackerCollection;
      G4double efficiency, noiseTH;
      G4bool addNoise;
      int tracker[5][400];
};

#endif


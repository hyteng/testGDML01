#ifndef testGDML01TrackerSD_h
#define testGDML01TrackerSD_h 1

#include "testGDML01TrackerHit.h"
#include "testGDML01BaseSD.h"
#include "testGDML01BaseSDPara.h"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class testGDML01TrackerSD :public testGDML01BaseSD {
  public:
      testGDML01TrackerSD(G4String& name, std::vector<G4String>& hits, std::vector<G4String>& pars, G4double eff=100.0, G4bool noise=false, G4double th=0.9);
      virtual ~testGDML01TrackerSD();

      void Initialize(G4HCofThisEvent* HCE);
      G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* roHist=NULL);

  protected:
      virtual G4HitsCollection* createHitsCollection(G4String& sdName, G4String& collectionName) {return new testGDML01TrackerHitsCollection(sdName, collectionName);};

  private:
      //testGDML01TrackerHitsCollection* trackerCollection;
      G4double efficiency, noiseTH;
      G4bool addNoise;
      int tracker[5][400];
};

#endif


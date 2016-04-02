#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

#include <vector>

#include "testGDML01TrackerDigitizer.h"
#include "testGDML01TrackerDigi.h"
#include "testGDML01TrackerHit.h"

testGDML01TrackerDigitizer::testGDML01TrackerDigitizer(G4String name) : G4VDigitizerModule(name) {

    G4String colName = "DigitsCollection";
    collectionName.push_back(colName);

}

testGDML01TrackerDigitizer::~testGDML01TrackerDigitizer() {
}

void testGDML01TrackerDigitizer::Digitize() {

    DigitsCollection = new testGDML01TrackerDigitsCollection("testGDML01TrackerDigitizer","DigitsCollection");
    G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();
    
    G4int THCID = DigiMan->GetHitsCollectionID("trackerCollection");
    testGDML01TrackerHitsCollection* THC = (testGDML01TrackerHitsCollection*)(DigiMan->GetHitsCollection(THCID));
    
    G4int n_hit = THC->entries();
    for(G4int i=0;i<n_hit;i++) {
        G4int TrackerId = (*THC)[i]->GetTrackID();
        G4int StripNb = (*THC)[i]->GetStrip();
        G4int ChamberNb = (*THC)[i]->GetChamberNb();
        G4ThreeVector simPos = (*THC)[i]->GetHitPos();
        G4ThreeVector Pos = (*THC)[i]->GetDigiPos();
        G4ThreeVector error = (*THC)[i]->GetError();
        G4double pt = (*THC)[i]->GetPt();
        
        testGDML01TrackerDigi* Digi = new testGDML01TrackerDigi();
        Digi->SetRun(RunNumber);
        Digi->SetEvent(EventNumber);
        Digi->SetDetector(ChamberNb);
        Digi->SetStrip(StripNb);
        Digi->SetPosition(Pos);
        Digi->SetSimPosition(simPos);
        Digi->SetError(error);
        Digi->SetPt(pt);

        DigitsCollection->insert(Digi);
    }
    StoreDigiCollection(DigitsCollection);

    G4int DCID=-1;
    if(DCID<0)
        DCID = DigiMan->GetDigiCollectionID("testGDML01TrackerDigitizer/DigitsCollection");

}

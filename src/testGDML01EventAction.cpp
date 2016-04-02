#include "G4DigiManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"

#include <stdlib.h>


#include "testGDML01EventAction.h"
#include "testGDML01TrackerHit.h"
#include "testGDML01TrackerDigi.h"
#include "testGDML01TrackerDigitizer.h"

extern std::ofstream outFile;

testGDML01EventAction::testGDML01EventAction() : trackerCollID(-1), drawFlag("all") {
    G4DigiManager * fDM = G4DigiManager::GetDMpointer();
    testGDML01TrackerDigitizer * myDM = new testGDML01TrackerDigitizer("testGDML01TrackerDigitizer");
    fDM->AddNewModule(myDM);
}

testGDML01EventAction::~testGDML01EventAction() {

}

void testGDML01EventAction::BeginOfEventAction(const G4Event* evt) {

    G4int evtNb = evt->GetEventID();
    G4cout << "Event: " << evtNb << G4endl; 
    G4SDManager * SDman = G4SDManager::GetSDMpointer();

    if(trackerCollID==-1)
        trackerCollID = SDman->GetCollectionID("trackerCollection");

}

void testGDML01EventAction::EndOfEventAction(const G4Event* evt) {

    G4int event_id = evt->GetEventID();

    G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
    testGDML01TrackerHitsCollection* THC = 0;
    
    G4DigiManager * fDM = G4DigiManager::GetDMpointer();
    
    if(HCE) {
        THC = (testGDML01TrackerHitsCollection*)(HCE->GetHC(trackerCollID));
        if(THC) {
            int n_hit = THC->entries();
            G4cout << "Number of tracker hits in this event =  " << n_hit << G4endl;
        }
        testGDML01TrackerDigitizer * myDM = (testGDML01TrackerDigitizer*)fDM->FindDigitizerModule("testGDML01TrackerDigitizer");
        myDM->SetEventNumber(event_id);
        myDM->Digitize();
    }
}  



#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "Randomize.hh"

#include "testGDML01TrackerSD.h"

testGDML01TrackerSD::testGDML01TrackerSD(G4String& name, std::vector<G4String>& hits, std::vector<G4String>& pars, G4double eff, G4bool noise, G4double th) : testGDML01BaseSD(name, hits, pars) {
    //collectionName.insert("hitsList[0]");
    efficiency = eff;
    addNoise = noise;
    noiseTH = th;
}

testGDML01TrackerSD::~testGDML01TrackerSD() {
}

void testGDML01TrackerSD::Initialize(G4HCofThisEvent* HCE) {
    /*
    hitsList[0] = new testGDML01TrackerHitsCollection(SensitiveDetectorName, collectionName[0]); 
    static G4int HCID = -1;
    if(HCID<0) { 
        HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); 
    }
    HCE->AddHitsCollection(HCID, hitsList[0]);
    */
    testGDML01BaseSD::Initialize(HCE);
    G4cout << "SD Initialize: " << G4endl;
    for(int i=0;i<5;i++)
        for(int j=0;j<400;j++)
            tracker[i][j] = -1;
}

G4bool testGDML01TrackerSD::ProcessHits(G4Step* aStep, G4TouchableHistory* roHist) {

    G4double edep = aStep->GetTotalEnergyDeposit();
    G4cout << "edep: " << edep << G4endl;
    if(edep < 0.1*MeV) 
        edep = 1.0*MeV;
    //return false;
    
    G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
    G4TouchableHistory* touchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
    G4VPhysicalVolume* motherPV = touchable->GetVolume(1);
    G4int copyNo = motherPV->GetCopyNo();

    G4VPhysicalVolume* ROPV = touchable->GetVolume();
    G4String ROPVName = ROPV->GetName();
    G4int ROPVNumber = ROPV->GetCopyNo();
    G4cout << "ROVolumeName: " << ROPVName << ", CopyNo: " << ROPVNumber << ". Strips: " << touchable->GetVolume()->GetLogicalVolume()->GetNoDaughters() << G4endl;

    G4VPhysicalVolume* worldPV = G4TransportationManager::GetTransportationManager()->GetParallelWorld("");
    navi = new G4Navigator();
    navi->SetWorldVolume(worldPV);
    navi->LocateGlobalPointAndSetup(preStepPoint->GetPosition());
    navi->CreateTouchableHistory();
    
    return true;
}

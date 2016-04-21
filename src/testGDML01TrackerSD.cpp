#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "Randomize.hh"

#include "G4TransportationManager.hh"
#include "G4Navigator.hh"
#include "G4TouchableHistoryHandle.hh"


#include "testGDML01TrackerSD.h"

#include "G4PhysicalVolumeStore.hh"
#include "G4VPhysicalVolume.hh"
#include "G4TransportationManager.hh"
#include "G4PVReplica.hh"
#include "G4PVParameterised.hh"

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


    G4TransportationManager* trans = G4TransportationManager::GetTransportationManager();
    int nWorlds = trans->GetNoWorlds();
    G4cout << "loop over worlds: " << G4endl;
    std::vector<G4VPhysicalVolume*>::iterator wIter = trans->GetWorldsIterator();
    for(int i=0; i<nWorlds; i++) {
        G4cout << (*wIter)->GetName() << ", ";
        wIter++;
    }
    G4cout << G4endl;

    G4cout << "loop over PhysicalVolumeStore: " << G4endl;
    G4PhysicalVolumeStore* pvStore = G4PhysicalVolumeStore::GetInstance();
    for(int i=0; i<pvStore->size(); i++) {
        G4VPhysicalVolume* pvIter = (*pvStore)[i];
        G4cout << pvIter->GetName() << ", ";
        if(dynamic_cast<G4PVReplica*>(pvIter)) {
            // loop over replica
            G4PVReplica* repVol = dynamic_cast<G4PVReplica*>(pvIter);
        }
        if(dynamic_cast<G4PVParameterised*>(pvIter)) {
            // loop over parameterisation
            G4PVParameterised *paramVol = dynamic_cast<G4PVParameterised*>(pvIter);
        }
    }
    G4cout << G4endl;

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

    G4VPhysicalVolume* worldPV = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking()->GetWorldVolume();//->GetParallelWorld("");
    G4Navigator* navi = new G4Navigator();
    navi->SetWorldVolume(worldPV);
    G4VPhysicalVolume* naviVolume = navi->LocateGlobalPointAndSetup(preStepPoint->GetPosition());
    G4TouchableHistoryHandle naviTouchableHandle = navi->CreateTouchableHistoryHandle();
    G4ThreeVector naviGlobalPosition = preStepPoint->GetPosition();
    G4ThreeVector naviLocalPosition = naviTouchableHandle->GetHistory()->GetTopTransform().TransformPoint(naviGlobalPosition);
    G4cout << "Navi: PV " << naviTouchableHandle->GetVolume()->GetName() << ", GPos " << naviGlobalPosition << ", LPos " << naviLocalPosition << G4endl;
    G4cout << "preStep: " << touchable->GetHistory()->GetTopTransform().TransformPoint(naviGlobalPosition) << G4endl;
    return true;
}

/**
 *  Filename: src/testGDML01GeometryHelper.cpp
 *   Created: 2016-04-20 10:48:47
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */
#include "G4PhysicalVolumeStore.hh"
#include "G4VPhysicalVolume.hh"
#include "G4TransportationManager.hh"
#include "G4PVReplica.hh"
#include "G4PVParameterised.hh"
#include "G4LogicalVolume.hh"

#include "testGDML01GeometryHelper.h"

testGDML01GeometryHelper::testGDML01GeometryHelper() {
}

testGDML01GeometryHelper::~testGDML01GeometryHelper() {
}

void testGDML01GeometryHelper::init() {
    G4TransportationManager* trans = G4TransportationManager::GetTransportationManager();
    int nWorlds = trans->GetNoWorlds();
    G4cout << "loop over worlds: " << G4endl;
    std::vector<G4VPhysicalVolume*>::const_iterator wIter = trans->GetWorldsIterator();
    for(int i=0; i<nWorlds; i++) {
        G4VPhysicalVolume* pv = (*wIter);
        G4cout << pv->GetName() << G4endl;
        loopOver(pv, 0);
        wIter++;
    }
    G4cout << G4endl;

    //geomNode gNode;
    G4cout << "loop over PhysicalVolumeStore: " << G4endl;
    G4PhysicalVolumeStore* pvStore = G4PhysicalVolumeStore::GetInstance();
    for(int i=0; i<pvStore->size(); i++) {
        G4VPhysicalVolume* pvIter = (*pvStore)[i];
        G4cout << "PV: " << pvIter->GetName() << ", LV: " << pvIter->GetLogicalVolume()->GetName() << ", No daughters: " << pvIter->GetLogicalVolume()->GetNoDaughters();
        //gNode.PV = pvIter;
        //gNode.sd = 0;
        //if(pvIter->GetLogicalVolume()->GetSensitiveDetector() != NULL)
            //gNode.sd = 1;
        //gNode.type = kNormal;
        if(dynamic_cast<G4PVReplica*>(pvIter)) {
            // loop over replica
            G4PVReplica* repVol = dynamic_cast<G4PVReplica*>(pvIter);
            G4cout << ". type replica " << repVol->GetMultiplicity();
            //gNode.type = kReplica;
        }
        if(dynamic_cast<G4PVParameterised*>(pvIter)) {
            // loop over parameterisation
            G4PVParameterised *paramVol = dynamic_cast<G4PVParameterised*>(pvIter);
            //gNode.type = kParameterised;
        }
        G4cout << G4endl;
        G4cout << "list its daughters: ";
        for(int j=0; j<pvIter->GetLogicalVolume()->GetNoDaughters(); j++) {
            G4VPhysicalVolume* Iter2 = pvIter->GetLogicalVolume()->GetDaughter(j);
            G4cout << Iter2->GetName() << ", ";
        }
        G4cout << G4endl;
    }
    G4cout << G4endl;

    return;
}

void testGDML01GeometryHelper::loopOver(const G4VPhysicalVolume* pv, G4int layer) {
    G4LogicalVolume* lv = pv->GetLogicalVolume();
    G4String mLVName = "world";
    if(layer != 0)
        mLVName = pv->GetMotherLogical()->GetName();
    pv->GetMotherLogical();
    G4cout << "node PV: " << pv->GetName() << ", LV: " << lv->GetName() << ", mother LV: " << mLVName << G4endl;
    
    switch(pv->VolumeType()) {
        case kNormal:
            break;
        case kReplica:
            break;
        case kParameterised:
            break;
    }

    G4int daughterSize = lv->GetNoDaughters();
    for(int i=0; i<daughterSize; i++) {
        G4VPhysicalVolume* pvIter = lv->GetDaughter(i);
        loopOver(pvIter, layer+1);
    }
}

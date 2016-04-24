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

testGDML01GeometryHelper* testGDML01GeometryHelper::gInstance = 0;

testGDML01GeometryHelper::testGDML01GeometryHelper() {
    naviHist = new G4NavigationHistory;
    detGeomMap = new detGeomMapType;
    gInstance = this;
}

testGDML01GeometryHelper::~testGDML01GeometryHelper() {
    naviHist->Clear();
    delete naviHist;
    detGeomMap->clear();
    delete detGeomMap;
    gInstance = 0;
}

testGDML01GeometryHelper* testGDML01GeometryHelper::getInstance() {
    if(!gInstance)
        gInstance = new testGDML01GeometryHelper;
    return gInstance;
}

void testGDML01GeometryHelper::init() {
    G4TransportationManager* trans = G4TransportationManager::GetTransportationManager();
    int nWorlds = trans->GetNoWorlds();
    
    detGeomMap->clear();
    G4String worldName;
    G4cout << "loop over worlds: " << G4endl;
    std::vector<G4VPhysicalVolume*>::const_iterator wIter = trans->GetWorldsIterator();
    for(int i=0; i<nWorlds; i++) {
        tmpGeomMap.clear();
        worldName = (*wIter)->GetName();
        G4cout << worldName << G4endl;
        naviHist->Clear();
        loopOver((*wIter), 0);
        (*detGeomMap)[worldName] = tmpGeomMap;
        wIter++;
    }
    G4cout<< G4endl;

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

const G4TouchableHistory& testGDML01GeometryHelper::getTouchable(const G4String& detId, const G4String& world) {
    G4String worldName = world;
    if(worldName=="") {
        worldName= G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking()->GetWorldVolume()->GetName();
    }
    return (*detGeomMap)[worldName][detId];
}

void testGDML01GeometryHelper::loopOver(G4VPhysicalVolume* pv, G4int layer) {
    G4LogicalVolume* lv = pv->GetLogicalVolume();
    G4String mLVName = "world";
    if(layer != 0)
        mLVName = pv->GetMotherLogical()->GetName();
    pv->GetMotherLogical();
    G4cout << "node PV: " << pv->GetName() << ", LV: " << lv->GetName() << ", mother LV: " << mLVName << G4endl;

    // the detGeometry did not specify the kReplica and kParameterised type, since later they will get change during the tracking
    switch(pv->VolumeType()) {
        case kNormal:
            naviHist->NewLevel(pv, kNormal, pv->GetCopyNo());
            loopSub(lv, layer);
            break;
        case kReplica:
            for(int replicaNo=0; replicaNo<pv->GetMultiplicity(); replicaNo++) {
                naviHist->NewLevel(pv, kReplica, replicaNo);
                loopSub(lv, layer);
            }
            break;
        case kParameterised:
            naviHist->NewLevel(pv, kParameterised, pv->GetCopyNo());
            loopSub(lv, layer);
            break;
    }
    naviHist->BackLevel();
}

void testGDML01GeometryHelper::loopSub(G4LogicalVolume* lv, G4int layer) {
    G4int daughterSize = lv->GetNoDaughters();
    for(int i=0; i<daughterSize; i++) {
        G4VPhysicalVolume* pvIter = lv->GetDaughter(i);
        if(lv->GetSensitiveDetector()) {
            detName = lv->GetName();
            detIdCountMap[detName]+=1;
            sId.clear();
            sId << detIdCountMap[detName];
            detId = detName + sId.str();
            tmpGeomMap[detId] = G4TouchableHistory((*naviHist));
        }
        loopOver(pvIter, layer+1);
    }
}

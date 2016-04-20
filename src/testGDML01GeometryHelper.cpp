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

#include "testGDML01GeometryHelper.h"

testGDML01GeometryHelper::testGDML01GeometryHelper() {
}

testGDML01GeometryHelper::~testGDML01GeometryHelper() {
}

void testGDML01GeometryHelper::init() {
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
    }
    G4cout << G4endl;

    return;
}


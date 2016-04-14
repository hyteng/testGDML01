/**
 *  Filename: src/testGDML01BaseSD.cpp
 *   Created: 2016-04-14 02:15:30
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */
#include "testGDML01BaseSD.h"

testGDML01BaseSD::testGDML01BaseSD(G4String name) : G4VSensitiveDetector(name) {
    hitFactory = new testGDML01BaseHitFactory;
}

testGDML01BaseSD::~testGDML01BaseSD() {
    delete hitFactory;
}


void testGDML01BaseSD::setHitsCollectionName(std::vector<G4String> &hitsCN) {
    for(int i=0; i<hitsCN.size(); i++)
        collectionName.isert(hitsCN[i]);
}

void testGDML01BaseSD::Initialize(G4HCofThisEvent* HCE) {
    hitsCollectionList.resize(collectionName.size());
    static G4int HCID;
    for(int i=0; i<collectionName.size(); i++) {
        hitCollection[i] = hitFactory->createHitsCollection(SensitiveDetectorName, collectionName[i]); 
        HCID = -1;
        if(HCID<0) { 
            HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[i]); 
        }
        HCE->AddHitsCollection(HCID, hitCollection[i]);
    }
}

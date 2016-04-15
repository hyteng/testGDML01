/**
 *  Filename: src/testGDML01BaseSD.cpp
 *   Created: 2016-04-14 02:15:30
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */
#include "G4SDManager.hh"

#include "testGDML01BaseSD.h"

testGDML01BaseSD::testGDML01BaseSD(G4String& name, std::vector<G4String>& hits, std::vector<G4String>& par) : G4VSensitiveDetector(name) {
    //hitFactory = new testGDML01BaseHitFactory;
    collectionName.clear();
    for(int i=0; i<hits.size(); i++)
        collectionName.insert(hits[i]);
    para = par;
    sdPara = new testGDML01BaseSDPara(para);
}

testGDML01BaseSD::~testGDML01BaseSD() {
    //delete hitFactory;
    collectionName.clear();
    delete sdPara;
}

void testGDML01BaseSD::setHitsCollectionName(std::vector<G4String>& hits) {
    collectionName.clear();
    for(int i=0; i<hits.size(); i++)
        collectionName.insert(hits[i]);
}

void testGDML01BaseSD::Initialize(G4HCofThisEvent* HCE) {
    hitsList.resize(collectionName.size());
    hitsID.resize(collectionName.size(), -1);
    for(int i=0; i<collectionName.size(); i++) {
        hitsList[i] = createHitsCollection(SensitiveDetectorName, collectionName[i]);
        if(hitsID[i] == -1) {
            hitsID[i] = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[i]);
        }
        HCE->AddHitsCollection(hitsID[i], hitsList[i]);
    }
}


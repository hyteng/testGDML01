/**
 *  Filename: src/testGDML01BaseSD.h
 *   Created: 2016-04-14 01:31:39
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */
#ifndef testGDML01BaseSD_h
#define testGDML01BaseSD_h 1

#include "G4VSensitiveDetector.hh"

#include "testGDML01BaseHit.h"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class testGDML01BaseHitFactory {
    public:
        testGDML01BaseHitFactory();
        virtual ~testGDML01BaseHitFactory();

        virtual testGDML01BaseHitsCollection* createHitsCollection(G4String& sdName, G4String& collectionName) {return new testGDML01BaseHitsCollection(sdName, collectionName);};

    private:
        /* data */
};

class testGDML01BaseSD :public G4VSensitiveDetector {
    public:
        testGDML01BaseSD(G4String name);
        virtual ~testGDML01BaseSD();

        void setHitsCollectionName(std::vector<G4String> &hitsCN);
        void Initialize(G4HCofThisEvent* HCE);
        G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* roHist=NULL);
        void EndOfEvent(G4HCofThisEvent* HCE);

    private:
        std::vector<testGDML01BaseHitsCollection*> hitsCollectionList;
        testGDML01BaseHitFactory* hitFactory;
};
#endif

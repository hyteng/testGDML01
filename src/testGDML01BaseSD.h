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
#include "testGDML01BaseSDPara.h"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class testGDML01BaseSD :public G4VSensitiveDetector {
    public:
        testGDML01BaseSD(G4String& name, std::vector<G4String>& hits, std::vector<G4String>& para);
        virtual ~testGDML01BaseSD();

        void setHitsCollectionName(std::vector<G4String> &hits);
        void Initialize(G4HCofThisEvent* HCE);
        G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* roHist=NULL)=0;
        void EndOfEvent(G4HCofThisEvent* HCE)=0;

    protected:
        virtual G4HitsCollection* createHitsCollection(G4String& sdName, G4String& collectionName)=0;

        std::vector<G4HitsCollection*> hitsList;
        std::vector<G4int> hitsID;
        testGDML01BaseSDPara* sdPara;
};
#endif

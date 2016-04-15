#ifndef testGDML01TrackerHit_h
#define testGDML01TrackerHit_h 1

#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

#include "testGDML01BaseHit.h"

class testGDML01TrackerHit :public testGDML01BaseHit {
    public:
        testGDML01TrackerHit();
        ~testGDML01TrackerHit();
        testGDML01TrackerHit(const testGDML01TrackerHit&);
        const testGDML01TrackerHit& operator=(const testGDML01TrackerHit&);
        G4int operator==(const testGDML01TrackerHit&) const;

        inline void* operator new(size_t);
        inline void  operator delete(void*);

        void Draw();
        void Print();

    public:
        void SetTrackID  (G4int track)      { trackID = track; };
        void SetChamberNb(G4int chamb)      { chamberNb = chamb; };
        void SetStrip    (G4int st)         { strip = st; };
        void SetEdep     (G4double de)      { edep = de; };
        void SetPt       (G4double p)       { pt = p; };
        void AddEdep     (G4double de)      { edep += de; };
        void SetHitPos   (G4ThreeVector x)  { hitPos = x; };
        void SetDigiPos   (G4ThreeVector y) { digiPos = y; };
        void SetError   (G4ThreeVector z)   { error = z; };

        G4int GetTrackID()          { return trackID; };
        G4int GetChamberNb()        { return chamberNb; };
        G4int GetStrip()            { return strip; };
        G4double GetEdep()          { return edep; };
        G4double GetPt()            { return pt; };
        G4ThreeVector GetHitPos()   { return hitPos; };
        G4ThreeVector GetDigiPos()  { return digiPos; };
        G4ThreeVector GetError()    { return error; };

    private:
        G4int         trackID;
        G4int         chamberNb;
        G4int         strip;
        G4double      edep;
        G4double      pt;  // since we get particle gun emit the partile vertical to B, pt=P
        G4ThreeVector hitPos;
        G4ThreeVector digiPos;
        G4ThreeVector error;
};

typedef G4THitsCollection<testGDML01TrackerHit> testGDML01TrackerHitsCollection;

extern G4ThreadLocal G4Allocator<testGDML01TrackerHit>* testGDML01TrackerHitAllocator;

inline void* testGDML01TrackerHit::operator new(size_t) {
    if(!testGDML01TrackerHitAllocator)
        testGDML01TrackerHitAllocator = new G4Allocator<testGDML01TrackerHit>;
    return (void *) testGDML01TrackerHitAllocator->MallocSingle();
}

inline void testGDML01TrackerHit::operator delete(void *aHit) {
    testGDML01TrackerHitAllocator->FreeSingle((testGDML01TrackerHit*) aHit);
}


#endif

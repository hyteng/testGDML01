#ifndef testGDML01BaseHit_h
#define testGDML01BaseHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class testGDML01BaseHit :public G4VHit {
    public:
        testGDML01BaseHit();
        virtual ~testGDML01BaseHit();

        testGDML01BaseHit(const testGDML01BaseHit&);
        const testGDML01BaseHit& operator=(const testGDML01BaseHit&);
        G4int operator==(const testGDML01BaseHit&) const;

        inline void* operator new(size_t);
        inline void  operator delete(void*);

    protected:
        /* data */
};


typedef G4THitsCollection<testGDML01BaseHit> testGDML01BaseHitsCollection;

extern G4ThreadLocal G4Allocator<testGDML01BaseHit>* testGDML01BaseHitAllocator;

inline void* testGDML01BaseHit::operator new(size_t) {
    if(!testGDML01BaseHitAllocator)
        testGDML01BaseHitAllocator = new G4Allocator<testGDML01BaseHit>;
    return (void *) testGDML01BaseHitAllocator->MallocSingle();
}


inline void testGDML01BaseHit::operator delete(void *aHit) {
    testGDML01BaseHitAllocator->FreeSingle((testGDML01BaseHit*) aHit);
}
#endif

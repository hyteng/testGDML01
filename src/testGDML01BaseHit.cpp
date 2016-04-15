#include "testGDML01BaseHit.h"

G4ThreadLocal G4Allocator<testGDML01BaseHit>* testGDML01BaseHitAllocator = NULL;

testGDML01BaseHit::testGDML01BaseHit() {
}

testGDML01BaseHit::~testGDML01BaseHit() {
}


testGDML01BaseHit::testGDML01BaseHit(const testGDML01BaseHit& right) : G4VHit() {
}

const testGDML01BaseHit& testGDML01BaseHit::operator=(const testGDML01BaseHit& right) {
    return *this;
}

G4int testGDML01BaseHit::operator==(const testGDML01BaseHit& right) const {
    return (this==&right) ? 1 : 0;
}

#include "testGDML01TrackerDigi.h"

G4ThreadLocal G4Allocator<testGDML01TrackerDigi>* testGDML01TrackerDigiAllocator;

testGDML01TrackerDigi::testGDML01TrackerDigi() {
    RunNumber = -1;
    EventNumber = -1;
    DetectorNumber = 0;
    StripNumber = -1;
    GlobalPosition = G4ThreeVector(0., 0., 0.);
    GlobalError = G4ThreeVector(0., 0., 0.);
    GlobalSimPosition = G4ThreeVector(0., 0., 0.);
    Pt = 0.;
}

testGDML01TrackerDigi::testGDML01TrackerDigi(const testGDML01TrackerDigi& right) : G4VDigi() {
    RunNumber = right.RunNumber;
    EventNumber = right.EventNumber;
    DetectorNumber = right.DetectorNumber;
    StripNumber = right.StripNumber;
    GlobalPosition = right.GlobalPosition;
    GlobalError = right.GlobalError;
    GlobalSimPosition = right.GlobalSimPosition;
    Pt = right.Pt;
}

testGDML01TrackerDigi::~testGDML01TrackerDigi() {
}

const testGDML01TrackerDigi& testGDML01TrackerDigi::operator=(const testGDML01TrackerDigi& right) {
    RunNumber = right.RunNumber;
    EventNumber = right.EventNumber;
    DetectorNumber = right.DetectorNumber;
    StripNumber = right.StripNumber;
    GlobalPosition = right.GlobalPosition;
    GlobalError = right.GlobalError;
    GlobalSimPosition = right.GlobalSimPosition;
    Pt = right.Pt;

    return *this;
}

int testGDML01TrackerDigi::operator==(const testGDML01TrackerDigi& right) const {
    return ((RunNumber==right.RunNumber)&&(EventNumber==right.EventNumber)&&(DetectorNumber==right.DetectorNumber)&&(StripNumber==right.StripNumber)&&(GlobalPosition==right.GlobalPosition)&&(GlobalError==right.GlobalError)&&(GlobalSimPosition==right.GlobalSimPosition)&&(Pt==right.Pt));
}

void testGDML01TrackerDigi::Draw() {
}

void testGDML01TrackerDigi::Print() {
}

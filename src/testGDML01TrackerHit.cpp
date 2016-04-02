#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include "testGDML01TrackerHit.h"

G4ThreadLocal G4Allocator<testGDML01TrackerHit>* testGDML01TrackerHitAllocator=0;


testGDML01TrackerHit::testGDML01TrackerHit() {}


testGDML01TrackerHit::~testGDML01TrackerHit() {}


testGDML01TrackerHit::testGDML01TrackerHit(const testGDML01TrackerHit& right) : G4VHit() {
    trackID   = right.trackID;
    chamberNb = right.chamberNb;
    strip     = right.strip;
    edep      = right.edep;
    pt        = right.pt;
    hitPos    = right.hitPos;
    digiPos   = right.digiPos;
    error     = right.error;
}


const testGDML01TrackerHit& testGDML01TrackerHit::operator=(const testGDML01TrackerHit& right) {
    trackID   = right.trackID;
    chamberNb = right.chamberNb;
    strip     = right.strip;
    edep      = right.edep;
    pt        = right.pt;
    hitPos    = right.hitPos;
    digiPos   = right.digiPos;
    error     = right.error;

    return *this;
}


G4int testGDML01TrackerHit::operator==(const testGDML01TrackerHit& right) const {
    return (this==&right) ? 1 : 0;
}


void testGDML01TrackerHit::Draw() {

    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if(pVVisManager)
    {
        G4Circle circle(hitPos);
        circle.SetScreenSize(2.);
        circle.SetFillStyle(G4Circle::filled);
        G4Colour colour(1.,0.,0.);
        G4VisAttributes attribs(colour);
        circle.SetVisAttributes(attribs);
        pVVisManager->Draw(circle);
    }
}


void testGDML01TrackerHit::Print() {

    G4cout << "  trackID: " << trackID << "  chamberNb: " << chamberNb << " strip: " << strip
        << "  energy deposit: " << G4BestUnit(edep,"Energy")
        << "  hit position: " << G4BestUnit(hitPos,"Length") 
        << "  digi position: " << G4BestUnit(digiPos,"Length") 
        << "  error: " << G4BestUnit(error,"Length") << G4endl;
}



#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "Randomize.hh"

#include "testGDML01PrimaryGeneratorAction.h"

testGDML01PrimaryGeneratorAction::testGDML01PrimaryGeneratorAction() {

    G4int n_particle = 1;
    particleGun = new G4ParticleGun(n_particle);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="mu-"));
    //particleGun->SetParticleEnergy(100.0*GeV);
    particleGun->SetParticlePosition(G4ThreeVector(-1.0*m, 0.0, 0.0));
}

testGDML01PrimaryGeneratorAction::~testGDML01PrimaryGeneratorAction() {
    delete particleGun;
}

void testGDML01PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

    G4int i = anEvent->GetEventID()%10;
    G4ThreeVector v0(1.0,0.0,0.0);
    double angle = CLHEP::RandFlat::shoot(-0.25, 0.25);
    //angle = 0.25;
    G4ThreeVector v = v0.rotateY(angle);
    G4cout << "angle: " << angle << ", v: " << v << G4endl;
    double P;
    switch(i) {
        case 0:
            P = 12.5;
            break;
        case 1:
            P = 20.0;
            break;
        case 2:
            P = 30.0;
            break;
        case 3:
            P = 40.0;
            break;
        case 4:
            P = 60.0;
            break;
        case 5:
            P = 80.0;
            break;
        case 6:
            P = 100.0;
            break;
        case 7:
            P = 150.0;
            break;
        case 8:
            P = 200.0;
            break;
        case 9:
            P = 400.0;
            break;
    }
    P = 400.0*CLHEP::RandFlat::shoot(0.05, 1.);
    //G4cout << "Event " << anEvent->GetEventID() << "th: P=" << P << "GeV" << G4endl; 
    particleGun->SetParticleEnergy(P*GeV);
    particleGun->SetParticleMomentumDirection(v);
    particleGun->GeneratePrimaryVertex(anEvent);
}



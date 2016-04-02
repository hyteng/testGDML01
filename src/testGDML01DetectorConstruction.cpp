/*=============================================================================
#     FileName: testGDML01DetectorConstruction.cpp
#         Desc: detector construction
#       Author: Haiyun TENG
#        Email: haiyun.teng@gmail.com
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2015-10-25 12:08:38
#      History: 
=============================================================================*/

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProductionCuts.hh"
#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4ios.hh"

// GDML parser include
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//#include <dlfcn.h>

#include "testGDML01DetectorConstruction.h"
//#include "testGDML01MagneticField.h"
#include "testGDML01MuonModel.h"
#include "testGDML01ExtReader.h"
#include "testGDML01ExtWriter.h"

testGDML01DetectorConstruction::testGDML01DetectorConstruction(const G4String& name, testGDML01SDFactory* fact) : G4VUserDetectorConstruction() {
    //fpMagField = new testGDML01MagneticField();
    //fpMagField->SetMagFieldValue(G4ThreeVector(0., 0.05, 0.));
    fReadFile = name+".gdml";
    fWriteFile = name+"_out.gdml";
    fWritingChoice = 1;

    factory = fact;
    fReader = new testGDML01ExtReader;
    fWriter = new testGDML01ExtWriter;
    fParser = new G4GDMLParser(fReader, fWriter);
}

testGDML01DetectorConstruction::~testGDML01DetectorConstruction() {
    //delete fpMagField;
    //delete fpSolenoidPart;
    //delete fStepLimit;
    factory = NULL;
    delete fReader;
    delete fWriter;
    delete fParser;
}

G4VPhysicalVolume* testGDML01DetectorConstruction::Construct() {
    G4VPhysicalVolume* fWorldPhysVol;
    fParser->Read(fReadFile, false);
    fWorldPhysVol = fParser->GetWorldVolume(); 
    if(fWritingChoice!=0)
        fParser->Write(fWriteFile, fWorldPhysVol, true, "./extSchema/testExtension.xsd");

    const G4GDMLAuxMapType* auxmap = fParser->GetAuxMap();
    G4cout << "Found " << auxmap->size() << " volume(s) with auxiliary information." << G4endl << G4endl;
    for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin(); iter!=auxmap->end(); iter++) {
        G4cout << "Volume " << ((*iter).first)->GetName() << " has the following list of auxiliary information: " << G4endl << G4endl;
        for(G4GDMLAuxListType::const_iterator vit=(*iter).second.begin(); vit!=(*iter).second.end(); vit++) {
            G4cout << "--> Type: " << (*vit).type << " Value: " << (*vit).value << G4endl;
        }
    }
    G4cout << G4endl;

    return fWorldPhysVol;
}

void testGDML01DetectorConstruction::ConstructSDandField() {
    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    const G4GDMLAuxMapType* auxmap = fParser->GetAuxMap();
    G4cout << "Check " << auxmap->size() << " volume(s) with auxiliary information." << G4endl << G4endl;
    for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();iter!=auxmap->end(); iter++) {
        G4cout << "Volume " << ((*iter).first)->GetName() << " has the following list of auxiliary information: " << G4endl << G4endl;
        for(G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();vit!=(*iter).second.end(); vit++) {
            G4cout << "--> Type: " << (*vit).type << " Value: " << (*vit).value << G4endl;
            if((*vit).type=="SensDet") {
                G4String sdName = (*vit).value;
                G4VSensitiveDetector* mydet = SDman->FindSensitiveDetector(sdName);
                if(mydet == NULL) {
                    mydet = factory->getSD(sdName);
                }

                if(mydet != NULL) {
                    G4cout << "get SD from gdml and create by factory" << G4endl;
                    G4LogicalVolume* myvol = (*iter).first;
                    SDman->AddNewDetector(mydet);
                    myvol->SetSensitiveDetector(mydet);
                }
            }
        }
    }
}

void testGDML01DetectorConstruction::setMagField(G4double fieldValue) {
    //fpMagField->SetMagFieldValue(fieldValue);
}

void testGDML01DetectorConstruction::setReadFile(const G4String& fname) {
    fReadFile = fname;
    fWritingChoice = 0;
}

void testGDML01DetectorConstruction::setWriteFile(const G4String& fname) {
    fWriteFile = fname;
    fWritingChoice = 1;
}

void testGDML01DetectorConstruction::setFactory(testGDML01SDFactory* fact) {
    factory = fact;
}


#include "G4SDManager.hh"

#include "testGDML01ParallelWorld.h"
#include "testGDML01MuonModel.h"
#include "testGDML01ExtReader.h"
#include "testGDML01ExtWriter.h"

testGDML01ParallelWorld::testGDML01ParallelWorld(const G4String& name, testGDML01SDFactory* fact) : G4VUserParallelWorld(name) {
    fWritingChoice = 1;
    factory = fact;
    fReader = new testGDML01ExtReader;
    fWriter = new testGDML01ExtWriter;
    fParser = new G4GDMLParser(fReader, fWriter);
}

testGDML01ParallelWorld::~testGDML01ParallelWorld() {
}

void testGDML01ParallelWorld::Construct() {
    G4VPhysicalVolume* fWorldPhysVol;
    G4String name = GetName();
    fReadFile = name+".gdml";
    fWriteFile = name+"_out.gdml";
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
}

void testGDML01ParallelWorld::ConstructSD() {
    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    const G4GDMLAuxMapType* auxmap = fParser->GetAuxMap();
    for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();iter!=auxmap->end(); iter++) {
        for(G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();vit!=(*iter).second.end(); vit++) {
            if((*vit).type=="SensDet") {
                G4String sdName = (*vit).value;
                G4VSensitiveDetector* mydet = SDman->FindSensitiveDetector(sdName);
                if(mydet == NULL) {
                    mydet = factory->getSD(sdName);
                }

                if(mydet != NULL) {
                    G4LogicalVolume* myvol = (*iter).first;
                    SDman->AddNewDetector(mydet);
                    myvol->SetSensitiveDetector(mydet);
                }
            }
        }
    }
}

void testGDML01ParallelWorld::setReadFile(const G4String& fname) {
    fReadFile = fname;
    fWritingChoice = 0;
}

void testGDML01ParallelWorld::setWriteFile(const G4String& fname) {
    fWriteFile = fname;
    fWritingChoice = 1;
}

void testGDML01ParallelWorld::setFactory(testGDML01SDFactory* fact) {
    factory = fact;
}

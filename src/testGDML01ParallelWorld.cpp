#include <sstream>
#include "G4VSensitiveDetector.hh"
#include "G4VFastSimulationModel.hh"
#include "G4PVPlacement.hh"

// GDML parser include
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProductionCuts.hh"
#include "G4RegionStore.hh"
#include "G4AutoDelete.hh"

#include "G4SDManager.hh"

#include "testGDML01ParallelWorld.h"
#include "testGDML01ExtReader.h"
#include "testGDML01ExtWriter.h"

testGDML01ParallelWorld::testGDML01ParallelWorld(const G4String& name, testGDML01SDFactory* sd, testGDML01SMFactory* sm) : G4VUserParallelWorld(name) {
    fReadFile = name+".gdml";
    fWriteFile = name+"_out.gdml";
    fWritingChoice = 0;

    sdFactory = sd;
    smFactory = sm;
    simRegionList.clear();
    ownFilterList.clear();
    fReader = new testGDML01ExtReader;
    fWriter = new testGDML01ExtWriter;
    fParser = new G4GDMLParser(fReader, fWriter);
}

testGDML01ParallelWorld::~testGDML01ParallelWorld() {
}

void testGDML01ParallelWorld::Construct() {
    G4VPhysicalVolume* trackingWorld = GetWorld();
    G4LogicalVolume* ghostWorldLV = trackingWorld->GetLogicalVolume();

    fParser->Read(fReadFile, false);
    G4VPhysicalVolume* fWorldPhysVol = fParser->GetWorldVolume();
    G4cout << "para world original name: " << fWorldPhysVol->GetName() << G4endl;
    G4LogicalVolume* fWorldLV = fWorldPhysVol->GetLogicalVolume();
    G4cout << "para world original LV name: " << fWorldLV->GetName() << G4endl;
    G4VPhysicalVolume* ghostWorldPV = (G4VPhysicalVolume*) new G4PVPlacement(0, G4ThreeVector(), fWorldLV, "ghostPhysical", ghostWorldLV, 0, 0);
    if(fWritingChoice!=0)
        fParser->Write(fWriteFile, fWorldPhysVol, true, "./extSchema/testExtension.xsd");

    simRegionList.clear();
    //paraFilterList.clear();
    const G4GDMLAuxMapType* auxmap = fParser->GetAuxMap();
    G4cout << "paraWorld " << GetName() << " found " << auxmap->size() << " volume(s) with auxiliary information." << G4endl << G4endl;
    for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin(); iter!=auxmap->end(); iter++) {
        G4LogicalVolume* myvol = (*iter).first;
        G4double generalCut = -1.0;
        G4double gammaCut = -1.0;
        G4double electronCut = -1.0;
        G4double positronCut = -1.0;
        G4bool isRegion = false;
        ownFilterList.clear();
        G4cout << "Volume " << myvol->GetName() << " has the following list of auxiliary information: " << G4endl << G4endl;
        for(G4GDMLAuxListType::const_iterator vit=(*iter).second.begin(); vit!=(*iter).second.end(); vit++) {
            G4cout << "--> Type: " << (*vit).type << " Value: " << (*vit).value << G4endl;
            if((*vit).type == "FastSimModel") {
                isRegion = true;
                G4String simName = (*vit).value;
                simRegionList.push_back(new G4Region(simName));
                simRegionList.back()->AddRootLogicalVolume(myvol);
                simRegionList.back()->SetProductionCuts(new G4ProductionCuts());
            }
            if((*vit).type == "generalCut") {
                std::stringstream tmp((*vit).value);
                tmp >> generalCut;
            }
            if((*vit).type == "gammaCut") {
                std::stringstream tmp((*vit).value);
                tmp >> gammaCut;
            }
            if((*vit).type == "electronCut") {
                std::stringstream tmp((*vit).value);
                tmp >> electronCut;
            }
            if((*vit).type == "positronCut") {
                std::stringstream tmp((*vit).value);
                tmp >> positronCut;
            }
            if((*vit).type == "particleFilter") {
                ownFilterList.push_back((*vit).value);
            }
        }

        if(isRegion) {
            if(generalCut!=-1.0) simRegionList.back()->GetProductionCuts()->SetProductionCut(generalCut);
            if(gammaCut!=-1.0) simRegionList.back()->GetProductionCuts()->SetProductionCut(gammaCut, idxG4GammaCut);
            if(electronCut!=-1.0) simRegionList.back()->GetProductionCuts()->SetProductionCut(electronCut, idxG4ElectronCut);
            if(positronCut!=-1.0) simRegionList.back()->GetProductionCuts()->SetProductionCut(positronCut, G4ProductionCuts::GetIndex("e+"));
            paraFilterList->push_back(ownFilterList);
        }
    }
    G4cout << G4endl;
}

void testGDML01ParallelWorld::ConstructSD() {
    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    std::vector<G4String> hits;
    std::vector<G4String> para;

    const G4GDMLAuxMapType* auxmap = fParser->GetAuxMap();
    G4bool isSD = false;
    for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();iter!=auxmap->end(); iter++) {
        G4LogicalVolume* myvol = (*iter).first;
        G4cout << "Volume " << myvol->GetName() << " has the following list of auxiliary information: " << G4endl << G4endl;
        for(G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();vit!=(*iter).second.end(); vit++) {
            if((*vit).type=="SensDet") {
                G4String sdName = (*vit).value;
                hits.clear();
                para.clear();
                if(vit->auxList) {
                    const G4GDMLAuxListType* auxInfoList = vit->auxList;
                    for(std::vector<G4GDMLAuxStructType>::const_iterator iaux=auxInfoList->begin(); iaux!=auxInfoList->end(); iaux++) {
                        if(iaux->type == "HitCollection")
                            hits.push_back(iaux->value);
                        if(iaux->type.find("Para_") != std::string::npos)
                            para.push_back(iaux->value);
                    }
                }
                G4VSensitiveDetector* mydet = SDman->FindSensitiveDetector(sdName);
                if(mydet == NULL) {
                    mydet = sdFactory->createSD(sdName, hits, para);
                    SDman->AddNewDetector(mydet);
                }

                if(mydet != NULL) {
                    isSD = true;
                    myvol->SetSensitiveDetector(mydet);
                }
            }
        }
    }

    if(smFactory != NULL) {
        for(G4int simRegionIter=0; simRegionIter<G4int(simRegionList.size());simRegionIter++) {
            G4Region* theEvelope = simRegionList[simRegionIter];
            G4VFastSimulationModel* simModel = smFactory->createSimModel(theEvelope->GetName(), theEvelope);
            G4AutoDelete::Register(simModel);
            // extra procedure for physical process
        }
    }
    else {
        G4cout << "no fast simulation or no SM factory present!" << G4endl;
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

void testGDML01ParallelWorld::setSDFactory(testGDML01SDFactory* sd) {
    sdFactory = sd;
}

void testGDML01ParallelWorld::setSMFactory(testGDML01SMFactory* sm) {
    smFactory = sm;
}

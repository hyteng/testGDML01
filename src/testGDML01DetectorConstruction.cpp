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

//#include "G4Material.hh"
//#include "G4Box.hh"
//#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
//#include "G4ThreeVector.hh"
//#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProductionCuts.hh"
#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4ios.hh"

#include <sstream>
#include <vector>
#include "G4VSensitiveDetector.hh"
#include "G4VFastSimulationModel.hh"

// GDML parser include
#include "G4PhysicalConstants.hh"
//#include "G4SystemOfUnits.hh"
//#include "G4ProductionCuts.hh"
#include "G4RegionStore.hh"
#include "G4AutoDelete.hh"

//#include <dlfcn.h>

#include "testGDML01DetectorConstruction.h"
//#include "testGDML01MagneticField.h"
#include "testGDML01ExtReader.h"
#include "testGDML01ExtWriter.h"

testGDML01DetectorConstruction::testGDML01DetectorConstruction(const G4String& name, testGDML01SDFactory* sd, testGDML01SMFactory* sm) : G4VUserDetectorConstruction() {
    //fpMagField = new testGDML01MagneticField();
    //fpMagField->SetMagFieldValue(G4ThreeVector(0., 0.05, 0.));
    worldName = name;
    fReadFile = name+".gdml";
    fWriteFile = name+"_out.gdml";
    fWritingChoice = 0;

    sdFactory = sd;
    smFactory = sm;
    simRegionList.clear();
    ownFilterList.clear();
    paraFilterList.clear();
    fReader = new testGDML01ExtReader;
    fWriter = new testGDML01ExtWriter;
    fParser = new G4GDMLParser(fReader, fWriter);
}

testGDML01DetectorConstruction::~testGDML01DetectorConstruction() {
    //delete fpMagField;
    //delete fpSolenoidPart;
    //delete fStepLimit;
    sdFactory = NULL;
    smFactory = NULL;
    delete fReader;
    delete fWriter;
    delete fParser;
}

G4VPhysicalVolume* testGDML01DetectorConstruction::Construct() {
    G4VPhysicalVolume* fWorldPhysVol;
    fParser->Read(fReadFile, false);
    fWorldPhysVol = fParser->GetWorldVolume(); 
    G4cout << "tracking world original name: " << fWorldPhysVol->GetName() << G4endl;
    fWorldPhysVol->SetName(worldName);
    if(fWritingChoice!=0)
        fParser->Write(fWriteFile, fWorldPhysVol, true, "./extSchema/testExtension.xsd");

    simRegionList.clear();
    paraFilterList.clear();
    const G4GDMLAuxMapType* auxmap = fParser->GetAuxMap();
    G4cout << "Found " << auxmap->size() << " volume(s) with auxiliary information." << G4endl << G4endl;
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
                if(vit->auxList) {
                    const G4GDMLAuxListType* auxInfoList = vit->auxList;
                    for(std::vector<G4GDMLAuxStructType>::const_iterator iaux=auxInfoList->begin(); iaux!=auxInfoList->end(); iaux++) {
                        if((*iaux).type == "generalCut") {
                            std::stringstream tmp((*iaux).value);
                            tmp >> generalCut;
                        }
                        if((*iaux).type == "gammaCut") {
                            std::stringstream tmp((*iaux).value);
                            tmp >> gammaCut;
                        }
                        if((*iaux).type == "electronCut") {
                            std::stringstream tmp((*iaux).value);
                            tmp >> electronCut;
                        }
                        if((*iaux).type == "positronCut") {
                            std::stringstream tmp((*iaux).value);
                            tmp >> positronCut;
                        }
                        if((*iaux).type == "particleFilter") {
                            ownFilterList.push_back((*iaux).value);
                        }

                    }
                }
            }
            /*
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
               */
        }

        if(isRegion) {
            if(generalCut!=-1.0) simRegionList.back()->GetProductionCuts()->SetProductionCut(generalCut);
            if(gammaCut!=-1.0) simRegionList.back()->GetProductionCuts()->SetProductionCut(gammaCut, idxG4GammaCut);
            if(electronCut!=-1.0) simRegionList.back()->GetProductionCuts()->SetProductionCut(electronCut, idxG4ElectronCut);
            if(positronCut!=-1.0) simRegionList.back()->GetProductionCuts()->SetProductionCut(positronCut, G4ProductionCuts::GetIndex("e+"));
            paraFilterList.push_back(ownFilterList);
        }
    }
    G4cout << G4endl;

    return fWorldPhysVol;
}

void testGDML01DetectorConstruction::ConstructSDandField() {
    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    std::vector<G4String> hits;
    std::vector<G4String> para;

    std::vector<std::pair<G4String, std::vector<G4String> > > prims;
    std::vector<G4String> filters;
    std::vector<G4int> depths;

    const G4GDMLAuxMapType* auxmap = fParser->GetAuxMap();
    G4cout << "Check " << auxmap->size() << " volume(s) with auxiliary information." << G4endl << G4endl;
    for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();iter!=auxmap->end(); iter++) {
        G4LogicalVolume* myvol = (*iter).first;
        G4cout << "Volume " << myvol->GetName() << " has the following list of auxiliary information: " << G4endl << G4endl;
        for(G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();vit!=(*iter).second.end(); vit++) {
            G4cout << "--> Type: " << (*vit).type << " Value: " << (*vit).value << G4endl;
            if((*vit).type == "SensDet") {
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
                    G4cout << "get SD from gdml and create by sdFactory" << G4endl;
                    myvol->SetSensitiveDetector(mydet);
                }
            }
            if((*vit).type == "Scorer") {
                G4String sdName = (*vit).value;
                prims.clear();
                depths.clear();
                para.clear();
                if(vit->auxList) {
                    const G4GDMLAuxListType* auxInfoList = vit->auxList;
                    for(std::vector<G4GDMLAuxStructType>::const_iterator iaux=auxInfoList->begin(); iaux!=auxInfoList->end(); iaux++) {
                        if(iaux->type == "PrimitiveName") {
                            filters.clear();
                            int vdep = 0;
                            if(iaux->auxList) {
                                const G4GDMLAuxListType* auxInfoList2 = iaux->auxList;
                                for(std::vector<G4GDMLAuxStructType>::const_iterator iaux2=auxInfoList2->begin(); iaux2!=auxInfoList2->end(); iaux2++) {
                                    if(iaux2->type == "Depth") {
                                        std::stringstream sdep(iaux2->value);
                                        sdep >> vdep;
                                    }
                                    if(iaux2->type == "ParticleFilter") {
                                        filters.push_back(iaux2->value);
                                    }

                                }
                            }
                            prims.push_back(std::pair<G4String, std::vector<G4String> >(iaux->value, filters));
                            depths.push_back(vdep);
                        }
                        if(iaux->type.find("Para_") != std::string::npos)
                            para.push_back(iaux->value);
                    }
                }
                G4VSensitiveDetector* mydet = SDman->FindSensitiveDetector(sdName);
                if(mydet == NULL) {
                    mydet = sdFactory->createScorer(sdName, prims, depths, para);
                    SDman->AddNewDetector(mydet);
                }

                if(mydet != NULL) {
                    G4cout << "get SD from gdml and create by sdFactory" << G4endl;
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
        }
    }
    else {
        G4cout << "no fast simulation or no SM factory present!" << G4endl;
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

void testGDML01DetectorConstruction::setSDFactory(testGDML01SDFactory* sd) {
    sdFactory = sd;
}

void testGDML01DetectorConstruction::setSMFactory(testGDML01SMFactory* sm) {
    smFactory = sm;
}

std::vector< std::vector<G4String> >& testGDML01DetectorConstruction::getParaFilter() {
    return paraFilterList;
}


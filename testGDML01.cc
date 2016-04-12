/*=============================================================================
FileName: sdtest.cc
Desc: GDML and ODBMS test
Author: Haiyun.TENG
Email: haiyun.teng@gmail.com
Version: 0.0.1
=============================================================================*/ 

#ifdef G4MULTITHREADED // default is enable
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "Randomize.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "testGDML01GSPBuilder.h"
#include "testGDML01PhysicsList.h"
#include "testGDML01ActionInitialization.h"
//#include "testGDML01SteppingVerbose.h"
//#include "G4GlobalFastSimulationManager.hh"

std::ofstream outFile;

int main(int argc, char** argv) {

    G4Random::setTheEngine(new CLHEP::RanecuEngine);

    // Run manager
    #ifdef G4MULTITHREADED
    G4MTRunManager * runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
    #else
    G4RunManager* runManager = new G4RunManager;
    #endif

    // User Verbose output class
    //G4VSteppingVerbose* verbosity = new testGDML01SteppingVerbose;
    //G4VSteppingVerbose::SetInstance(verbosity);

    // UserInitialization class - mandatory
    testGDML01GSPBuilder* theBuilder = new testGDML01GSPBuilder;
    theBuilder->init("gdmlList.txt");
    runManager->SetUserInitialization(theBuilder->getWorld());
    //G4VUserPhysicsList* thePhysicsList = new QGSP_BERT();
    //G4VUserPhysicsList* thePhysicsList = new testGDML01PhysicsList;
    //runManager->SetUserInitialization(thePhysicsList);
    runManager->SetUserInitialization(theBuilder->getPhysics());

    runManager->SetUserInitialization(new testGDML01ActionInitialization());

    runManager->Initialize();

    #ifdef G4VIS_USE
    G4VisManager* theVisManager = new G4VisExecutive;
    theVisManager->Initialize();
    #endif

    // User Interface
    G4UImanager* uiManager = G4UImanager::GetUIpointer();

    G4cout << "UI operation:" << G4endl;
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);
    if(argc != 1) {
        G4String theCommand = "/control/execute ";
        G4String theFileName = argv[1];
        uiManager->ApplyCommand(theCommand+theFileName);
        G4cout << "UI with para." << G4endl;
    }
    else {
        #ifdef G4UI_USE
        //G4UIExecutive *ui = new G4UIExecutive(argc, argv);
            #ifdef G4VIS_USE
            G4cout << "use vis.mac" << G4endl;
            uiManager->ApplyCommand("/control/execute vis.mac");
            #else
            G4cout << "use init.mac" << G4endl;
            uiManager->ApplyCommand("/control/execute init.mac");
            #endif
        if(ui->IsGUI()) {
            G4cout << "use gui.mac" << G4endl;
            uiManager->ApplyCommand("/control/execute gui.mac");
        }
        G4cout << "UI executive session start." << G4endl;
        //ui->SessionStart();
        //delete ui;
        #endif
    }
    ui->SessionStart();
    delete ui;


    G4int EventNumber = 10;
    runManager->BeamOn(EventNumber);

    #ifdef G4VIS_USE
    delete theVisManager;   
    #endif 

    //Job termination
    //delete verbosity;
    delete runManager;

    return 0;
}


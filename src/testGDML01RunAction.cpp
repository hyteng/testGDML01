#include <stdlib.h>
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"

#include <stdlib.h>
#include <fstream>

#include "testGDML01RunAction.h"

extern std::ofstream outFile;

testGDML01RunAction::testGDML01RunAction() {
}

testGDML01RunAction::~testGDML01RunAction() {
}

void testGDML01RunAction::BeginOfRunAction(const G4Run* aRun) {  
  // Prepare the visualization
  if(G4VVisManager::GetConcreteInstance()) {
      G4UImanager* UI = G4UImanager::GetUIpointer(); 
      UI->ApplyCommand("/vis/scene/notifyHandlers");
    } 
}

void testGDML01RunAction::EndOfRunAction(const G4Run* aRun) {
  G4cout << "End of Run " << G4endl;
  // Run ended, update the visualization
  if (G4VVisManager::GetConcreteInstance()) {
     G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
  }

}



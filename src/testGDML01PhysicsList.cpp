#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"

// for EM process
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuMultipleScattering.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"

#include "G4ionIonisation.hh"

// for StepLimiter
#include "G4StepLimiter.hh"
#include "G4UserSpecialCuts.hh"

// for parameterisation
#include "G4FastSimulationManagerProcess.hh"

// for G4cout
#include "G4ios.hh" 


#include "testGDML01PhysicsList.h"

testGDML01PhysicsList::testGDML01PhysicsList() {
}

testGDML01PhysicsList::~testGDML01PhysicsList() {
}

void testGDML01PhysicsList::ConstructParticle() {
    // In this method, static member functions should be called
    // for all particles which you want to use.
    // This ensures that objects of these particle types will be
    // created in the program. 

    //ConstructBosons();
    //ConstructLeptons();
    //ConstructMesons();
    //ConstructBaryons();

    // ConstructBosons
    G4Geantino::GeantinoDefinition();
    G4ChargedGeantino::ChargedGeantinoDefinition();
    G4Gamma::GammaDefinition(); 

    // ConstructLeptons
    // e
    G4Electron::ElectronDefinition();
    G4Positron::PositronDefinition();
    // mu
    G4MuonPlus::MuonPlusDefinition();
    G4MuonMinus::MuonMinusDefinition();
    // nu_e
    G4NeutrinoE::NeutrinoEDefinition();
    G4MuonMinus::MuonMinusDefinition();
    // nu_mu
    G4NeutrinoMu::NeutrinoMuDefinition();
    G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
}

void testGDML01PhysicsList::ConstructProcess() {
    // Define transportation process
    AddTransportation();
    //AddStepMax();
    AddParameterisation();
    //ConstructEM();
}

void testGDML01PhysicsList::ConstructEM() {

    theParticleIterator->reset();
    while( (*theParticleIterator)() ) {
        G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();

        if(particleName == "gamma") {
            // gamma         
            pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
            pmanager->AddDiscreteProcess(new G4ComptonScattering);
            pmanager->AddDiscreteProcess(new G4GammaConversion);

        } else if(particleName == "e-") {
            //electron
            pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
            pmanager->AddProcess(new G4eIonisation,         -1, 2, 2);
            pmanager->AddProcess(new G4eBremsstrahlung,     -1, 3, 3);      

        } else if(particleName == "e+") {
            //positron
            pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
            pmanager->AddProcess(new G4eIonisation,         -1, 2, 2);
            pmanager->AddProcess(new G4eBremsstrahlung,     -1, 3, 3);
            pmanager->AddProcess(new G4eplusAnnihilation,    0,-1, 4);

        } else if(particleName == "mu+" || particleName == "mu-") {
            //muon  
            pmanager->AddProcess(new G4MuMultipleScattering, -1, 1, 1);
            pmanager->AddProcess(new G4MuIonisation,         -1, 2, 2);
            pmanager->AddProcess(new G4MuBremsstrahlung,     -1, 3, 3);
            pmanager->AddProcess(new G4MuPairProduction,     -1, 4, 4);       

        } else if(particleName == "proton" || particleName == "pi-" || particleName == "pi+") {
            //proton  
            pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
            pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
            pmanager->AddProcess(new G4hBremsstrahlung,     -1, 3, 3);
            pmanager->AddProcess(new G4hPairProduction,     -1, 4, 4);       

        } else if(particleName == "alpha" || particleName == "He3" ) {
            //alpha 
            pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
            pmanager->AddProcess(new G4ionIonisation,       -1, 2, 2);

        } else if(particleName == "GenericIon" ) { 
            //Ions 
            pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
            pmanager->AddProcess(new G4ionIonisation,       -1, 2, 2);

        } else if((!particle->IsShortLived()) && (particle->GetPDGCharge() != 0.0) && (particle->GetParticleName() != "chargedgeantino")) {
            //all others charged particles except geantino
            pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
            pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
        }
    }
}

void testGDML01PhysicsList::AddParameterisation() {

    G4FastSimulationManagerProcess* smProcess = new G4FastSimulationManagerProcess("smProcess");
    paraSMProcess.clear();
    paraSDProcess.clear();
    for(int i=1; i<worldName.size(); i++) {
        // -- Fast simulation manager process for "parallel geometry":
        G4FastSimulationManagerProcess* smProcessPara = new G4FastSimulationManagerProcess("smProcessPara_"+worldName[i], worldName[i]);
        paraSMProcess.push_back(smProcessPara);
        // extra procedure for physical process 
        G4ParallelWorldScoringProcess* sdProcessPara  = new G4ParallelWorldScoringProcess("sdProcessPara_"+worldName[i]);
        sdProcessPara->SetParallelWorld(worldName[i]);
        paraSDProcess.push_back(sdProcessPara); 
    }

    G4cout << "Add Parameterisation for all worlds" << G4endl;
    theParticleIterator->reset();
    while((*theParticleIterator)()) {
        G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        // first the fast simulation
        if(paraFilter(particle->GetParticleName(), 0)) {
            pmanager->AddProcess(smProcess);
            pmanager->SetProcessOrdering(smProcess, idxAlongStep, 1);
            pmanager->SetProcessOrdering(smProcess, idxPostStep);
        }
        // then the fast simulation for parallel world
        for(int i=0; i<worldName.size()-1; i++) {
            if(paraFilter(particle->GetParticleName(), i+1)) {
                pmanager->AddProcess(paraSMProcess[i]);
                pmanager->SetProcessOrdering(paraSMProcess[i], idxAlongStep, 1);
                pmanager->SetProcessOrdering(paraSMProcess[i], idxPostStep);
            }
        }
        // last the parallel SD, put to just after G4Transporation and prior to any other physics processes, including fast simulation. 
        if(!particle->IsShortLived()) {
            for(int i=0; i<worldName.size()-1; i++) {
                pmanager->AddProcess(paraSDProcess[i]);
                pmanager->SetProcessOrderingToLast(paraSDProcess[i], idxAtRest);
                pmanager->SetProcessOrdering(paraSDProcess[i], idxAlongStep, 1);
                pmanager->SetProcessOrderingToLast(paraSDProcess[i], idxPostStep);
            }
        }
    }
}

void testGDML01PhysicsList::SetCuts() {
    // uppress error messages even in case e/gamma/proton do not exist            
    G4int temp = GetVerboseLevel();
    SetVerboseLevel(0);                                                           
    // "G4VUserPhysicsList::SetCutsWithDefault" method sets the default cut value for all particle types 
    SetCutsWithDefault();   

    // Retrieve verbose level
    SetVerboseLevel(temp);  
}

void testGDML01PhysicsList::AddTransportation() {
    G4VUserPhysicsList::AddTransportation();
}

void testGDML01PhysicsList::AddStepMax() {
  // Step limitation seen as a process
  G4StepLimiter* stepLimiter = new G4StepLimiter();
  ////G4UserSpecialCuts* userCuts = new G4UserSpecialCuts();
  
  theParticleIterator->reset();
  while((*theParticleIterator)()) {
      G4ParticleDefinition* particle = theParticleIterator->value();
      G4ProcessManager* pmanager = particle->GetProcessManager();

      if(particle->GetPDGCharge() != 0.0) {
	  pmanager ->AddDiscreteProcess(stepLimiter);
	  ////pmanager ->AddDiscreteProcess(userCuts);
      }
  }
}

void testGDML01PhysicsList::setWorld(std::vector<G4String>& nameCollection) {
    worldName = nameCollection;
}

G4bool testGDML01PhysicsList::paraFilter(const G4String& particle, int idx) {
    if(idx >= (*paraFilterList).size())
        return false;
    //if((*paraFilterList)[idx][0] == "all")
    if(find((*paraFilterList)[idx].begin(), (*paraFilterList)[idx].end(), "all") != (*paraFilterList)[idx].end())
        return true;
    G4bool pass = false;
    if(find((*paraFilterList)[idx].begin(), (*paraFilterList)[idx].end(), particle) != (*paraFilterList)[idx].end())
        pass = true;
    return pass;
}

void testGDML01PhysicsList::setParaFilter(std::vector< std::vector<G4String> >& para) {
    paraFilterList = &para;
}


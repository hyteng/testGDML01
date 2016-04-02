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

    ConstructBosons();
    ConstructLeptons();
    //ConstructMesons();
    //ConstructBaryons();
}

void testGDML01PhysicsList::ConstructBosons() {

    G4Geantino::GeantinoDefinition();
    G4ChargedGeantino::ChargedGeantinoDefinition();

    G4Gamma::GammaDefinition(); 
}

void testGDML01PhysicsList::ConstructLeptons() {

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
    //AddParameterisation();
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

    G4FastSimulationManagerProcess* fastSimProcess_Mu = new G4FastSimulationManagerProcess("Mu");

    G4cout << "AddParameterisation for muon" << G4endl;
    theParticleIterator->reset();
    while((*theParticleIterator)()) {
        G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        if (particle->GetParticleName() == "mu+" || particle->GetParticleName() == "mu-")
            pmanager->AddProcess(fastSimProcess_Mu);
            //pmanager->SetProcessOrdering(fastSimProcess_Mu, idxAlongStep, 1);
            pmanager->SetProcessOrdering(fastSimProcess_Mu, idxPostStep);
    }
}

void testGDML01PhysicsList::SetCuts() {
    // uppress error messages even in case e/gamma/proton do not exist            
    G4int temp = GetVerboseLevel();
    SetVerboseLevel(0);                                                           
    //  " G4VUserPhysicsList::SetCutsWithDefault" method sets 
    //   the default cut value for all particle types 
    SetCutsWithDefault();   

    // Retrieve verbose level
    SetVerboseLevel(temp);  
}

void testGDML01PhysicsList::AddStepMax()
{
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



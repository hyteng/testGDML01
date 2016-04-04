/*=============================================================================
#     FileName: testGDML01PhysicsList.hh
#         Desc: detector physics listn header
#       Author: Haiyun.TENG
#        Email: haiyun.teng@gmail.com
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2013-04-23 02:38:27
#      History:
=============================================================================*/
#ifndef testGDML01PhysicsList_h 
#define testGDML01PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "G4FastSimulationManagerProcess.hh"
#include "G4ParallelWorldScoringProcess.hh"

#include "globals.hh"

class testGDML01PhysicsList: public G4VUserPhysicsList {

    public:
        testGDML01PhysicsList();
        virtual ~testGDML01PhysicsList();
        
        void setWorld(std::vector<G4String>& nameCollection);
        void setParaFilter(std::vector< std::vector<G4String> >& para);

    protected:
        virtual void ConstructParticle();
        virtual void ConstructProcess();
        virtual void SetCuts(); 

    private:
        //void ConstructLeptons();
        //void ConstructBosons();
        void ConstructEM();
        void AddTransportation();
        void AddStepMax();

        void AddParameterisation();
        G4bool paraFilter(const G4String& particle, int idx);

        std::vector<G4String> worldName;
        std::vector< std::vector<G4String> >* paraFilterList;
        std::vector<G4FastSimulationManagerProcess*> paraSMProcess;
        std::vector<G4ParallelWorldScoringProcess*> paraSDProcess;
};

#endif

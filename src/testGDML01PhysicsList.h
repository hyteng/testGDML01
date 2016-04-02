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

#include "globals.hh"

class testGDML01PhysicsList: public G4VUserPhysicsList {

    public:
        testGDML01PhysicsList();
        ~testGDML01PhysicsList();

    protected:
        void ConstructParticle();
        void ConstructProcess();
        void SetCuts(); 
        void AddStepMax();

    private:
        void ConstructLeptons();
        void ConstructBosons();

        void ConstructEM();

        void AddParameterisation();
};

#endif

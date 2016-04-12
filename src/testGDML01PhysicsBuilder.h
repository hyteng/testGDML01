/**
 *  Filename: src/testGDML01PhysicsBuilder.h
 *   Created: 2016-04-13 05:22:54
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */
#ifndef testGDML01PhysicsBuilder_h
#define testGDML01PhysicsBuilder_h 1

#include "testGDML01PhysicsList.h"

class testGDML01PhysicsBuilder {
    public:
        testGDML01PhysicsBuilder();
        ~testGDML01PhysicsBuilder();
        
        void init();
        std::vector< std::vector<G4String> >& getParaFilter();
        G4VUserPhysicsList* getPhysics() {return thePhysicsList;};
        void setWorldName(std::vector<G4String>& w); 

    private:
        testGDML01PhysicsList* thePhysicsList;
        std::vector<G4String> worldNameCollection;
        std::vector< std::vector<G4String> > particleFilter;
};
#endif

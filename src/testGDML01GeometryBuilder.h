#ifndef testGDML01GeometryBuilder_h
#define testGDML01GeometryBuilder_h 1

#include <fstream>

#include "testGDML01DetectorConstruction.h"
#include "testGDML01ParallelWorld.h"
#include "testGDML01SDFactory.h"
#include "testGDML01SMFactory.h"
#include "testGDML01PhysicsList.h"

class testGDML01GeometryBuilder {
    public:
        testGDML01GeometryBuilder();
        ~testGDML01GeometryBuilder();
        
        void init(const std::string &nameList);
        G4VUserDetectorConstruction* getWorld() {return theWorld;};
        G4VUserPhysicsList* getPhysics() {return thePhysics;};

    private:
        std::vector<testGDML01ParallelWorld*> theParaWorldCollection;
        std::vector<G4String> nameCollection;
        testGDML01SDFactory* sdFactory;
        testGDML01SMFactory* smFactory;

        std::ifstream gdmlList;

        testGDML01DetectorConstruction* theWorld;
        testGDML01PhysicsList* thePhysics;
};
#endif

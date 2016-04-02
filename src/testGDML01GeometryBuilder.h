#ifndef testGDML01GeometryBuilder_h
#define testGDML01GeometryBuilder_h 1

#include <fstream>

#include "testGDML01DetectorConstruction.h"
#include "testGDML01ParallelWorld.h"
#include "testGDML01SDFactory.h"

class testGDML01GeometryBuilder {
    public:
        testGDML01GeometryBuilder();
        ~testGDML01GeometryBuilder();
        
        void init(const std::string &nameList);
        G4VUserDetectorConstruction* getWorld() {return theWorld;};

    private:
        testGDML01DetectorConstruction *theWorld;
        std::vector<testGDML01ParallelWorld*> theParaWorldCollection;
        std::vector<G4String> nameCollection;
        testGDML01SDFactory* factory;

        std::ifstream gdmlList;
};
#endif

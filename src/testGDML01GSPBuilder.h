/**
 *  Filename: src/testGDML01GSPBuilder.h
 *   Created: 2016-04-13 05:25:41
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */
#ifndef testGDML01GSPBuilder_h
#define testGDML01GSPBuilder_h 1

#include "testGDML01GeometryBuilder.h"
#include "testGDML01PhysicsBuilder.h"

class testGDML01GSPBuilder {
    public:
        testGDML01GSPBuilder();
        ~testGDML01GSPBuilder();


        void init(const std::string &nameList);
        G4VUserDetectorConstruction* getWorld() {return geomBuilder->getWorld();};
        G4VUserPhysicsList* getPhysics() {return phyBuilder->getPhysics();};

    private:
        testGDML01GeometryBuilder* geomBuilder;
        testGDML01PhysicsBuilder* phyBuilder;
};
#endif

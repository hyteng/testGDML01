#include <iostream>
#include <string>

#include "testGDML01GeometryBuilder.h"

testGDML01GeometryBuilder::testGDML01GeometryBuilder() {
    theParaWorldCollection.clear();
    nameCollection.clear();

    sdFactory = new testGDML01SDFactory;
    smFactory = new testGDML01SMFactory;
}

testGDML01GeometryBuilder::~testGDML01GeometryBuilder() {
    theParaWorldCollection.clear();

    delete sdFactory;
    delete smFactory;
}
       
void testGDML01GeometryBuilder::init(const std::string &nameList) {
    gdmlList.open(nameList.c_str(), std::ios::in);
    nameCollection.clear();
    std::string idx;
    while(getline(gdmlList, idx)) {
        nameCollection.push_back(idx);
    }

    theWorld = new testGDML01DetectorConstruction(nameCollection[0], sdFactory, smFactory);

    G4String paraName;
    for(int i=1; i<nameCollection.size(); i++) {
        paraName = nameCollection[i];
        testGDML01ParallelWorld* fParaWorld = new testGDML01ParallelWorld(paraName, sdFactory, smFactory);
        fParaWorld->setParaFilter(theWorld->getParaFilter());
        theParaWorldCollection.push_back(fParaWorld);
        theWorld->RegisterParallelWorld(fParaWorld);
    }
    /*
    // set process, as well as for parrallel SD and fast Simulation
    thePhysicsList = new testGDML01PhysicsList;
    thePhysicsList->setWorld(nameCollection);
    thePhysicsList->setParaFilter(theWorld->getParaFilter());
    */
}

void testGDML01GeometryBuilder::cloneParaFilter(std::vector< std::vector<G4String> >& filter) {
    std::vector< std::vector<G4String> > &origin = theWorld->getParaFilter();
    filter.clear();
    filter.reserve(origin.size());
    for(int i=0; i<origin.size(); i++) {
        filter.push_back(origin[i]);
    }
}


#include <iostream>
#include <string>

#include "testGDML01GeometryBuilder.h"

testGDML01GeometryBuilder::testGDML01GeometryBuilder() {
    theParaWorldCollection.clear();
    nameCollection.clear();
}

testGDML01GeometryBuilder::~testGDML01GeometryBuilder() {
    theParaWorldCollection.clear();
}
       
void testGDML01GeometryBuilder::init(const std::string &nameList) {
    gdmlList.open(nameList.c_str(), std::ios::in);
    nameCollection.clear();
    std::string idx;
    while(getline(gdmlList, idx)) {
        nameCollection.push_back(idx);
    }

    sdFactory = new testGDML01SDFactory;
    smFactory = new testGDML01SMFactory;

    theWorld = new testGDML01DetectorConstruction(nameCollection[0], sdFactory);

    G4String paraName;
    for(int i=1; i<nameCollection.size(); i++) {
        paraName = nameCollection[i];
        testGDML01ParallelWorld* fParaWorld = new testGDML01ParallelWorld(paraName, sdFactory);
        theParaWorldCollection.push_back(fParaWorld);
        theWorld->RegisterParallelWorld(fParaWorld);
    }
}

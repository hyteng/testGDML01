/**
 *  Filename: src/testGDML01SMFactory.cpp
 *   Created: 2016-04-03 17:01:50
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */

#include "testGDML01SMFactory.h"
#include "testGDML01MuonModel.h"

testGDML01SMFactory::testGDML01SMFactory() {
}

testGDML01SMFactory::~testGDML01SMFactory() {
}

G4VFastSimulationModel* testGDML01SMFactory::createSimModel(G4String name, G4Region* envelope) {
    G4VFastSimulationModel* sm = NULL;
    if(name == "MuonModel")
        sm = (G4VFastSimulationModel*) new testGDML01MuonModel(name, envelope);

    return sm;
}

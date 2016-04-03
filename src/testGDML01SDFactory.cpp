/**
 *  Filename: src/testGDML01SDFactory.cpp
 *   Created: 2016-04-01 03:53:13
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */

#include "testGDML01SDFactory.h"
#include "testGDML01TrackerSD.h"

testGDML01SDFactory::testGDML01SDFactory() {
}

testGDML01SDFactory::~testGDML01SDFactory() {
}

G4VSensitiveDetector* testGDML01SDFactory::createSD(G4String name) {
    G4VSensitiveDetector* sd = NULL;
    if(name == "tracker")
        sd = (G4VSensitiveDetector*) new testGDML01TrackerSD(name);

    return sd;
}


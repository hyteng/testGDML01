/**
 *  Filename: src/testGDML01SDFactory.h
 *   Created: 2016-03-30 05:44:33
 *      Desc: SDFactory with share functions
 *    Author: hyteng, haiyun.teng@gmail.com
 *   Company: CSNS
 */

#ifndef testGDML01SDFactory_h
#define testGDML01SDFactory_h 1

#include "G4VSensitiveDetector.hh"

class testGDML01SDFactory {
public:
    testGDML01SDFactory();
    ~testGDML01SDFactory();

    G4VSensitiveDetector* getSD(G4String name);

private:
    /* data */  
};


#endif

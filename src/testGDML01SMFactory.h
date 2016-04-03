/**
 *  Filename: testGDML01SMFactory.h
 *   Created: 2016-04-03 16:48:56
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */
#ifndef testGDML01SMFactory_h
#define testGDML01SMFactory_h 1

#include "G4VFastSimulationModel.hh"

class testGDML01SMFactory {
    public:
        testGDML01SMFactory();
        ~testGDML01SMFactory();

        G4VFastSimulationModel* createSimModel(G4String, G4Region*);
    private:
        /* data */
};

#endif

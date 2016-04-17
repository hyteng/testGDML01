/**
 *  Filename: src/testGDML01PhysicsProbe.h
 *   Created: 2016-04-18 05:22:04
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */
#ifndef testGDML01PhysicsProbe_h
#define testGDML01PhysicsProbe_h 1

#include "testGDML01BaseScorer.h"

class testGDML01PhysicsProbe :public testGDML01BaseScorer {
    public:
        testGDML01PhysicsProbe(G4String& name, std::vector<G4String>& pars);
        virtual ~testGDML01PhysicsProbe();

    private:
        /* data */
};
#endif

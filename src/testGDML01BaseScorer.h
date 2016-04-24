/**
 *  Filename: src/testGDML01BaseScorer.h
 *   Created: 2016-04-17 08:52:26
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */
#ifndef testGDML01BaseScorer_h
#define testGDML01BaseScorer_h 1

#include "G4MultiFunctionalDetector.hh"

#include "testGDML01BaseSDPara.h"
#include "testGDML01DetGeometry.h"

class testGDML01BaseScorer :public G4MultiFunctionalDetector {
    public:
        testGDML01BaseScorer(G4String& name, std::vector<G4String>& pars);
        virtual ~testGDML01BaseScorer();

    protected:
        std::vector<G4String> para;
        testGDML01BaseSDPara* sdPara;
        testGDML01DetGeometry* detGeom;

        G4String detType;
};
#endif

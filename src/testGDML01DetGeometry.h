/**
 *  Filename: src/testGDML01DetGeometry.h
 *   Created: 2016-04-18 05:32:28
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */
#ifndef testGDML01DetGeometry_h
#define testGDML01DetGeometry_h 1

#include "G4TouchableHistory.hh"

class testGDML01DetGeometry {
    public:
        testGDML01DetGeometry();
        virtual ~testGDML01DetGeometry();

    protected:
        std::map<G4String, std::map<G4String, G4TouchableHistory> > detGeomMap;
};
#endif

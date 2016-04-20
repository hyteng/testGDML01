/**
 *  Filename: src/testGDML01GeometryHelper.h
 *   Created: 2016-04-20 10:44:44
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */
#ifndef testGDML01GeometryHelper_h
#define testGDML01GeometryHelper_h 1

#include "G4PhysicalVolumeStore.hh"
#include "G4TouchableHistoryHandle.hh"

class testGDML01GeometryHelper {
    public:
        testGDML01GeometryHelper();
        virtual ~testGDML01GeometryHelper();

        void init();
    private:
        //std::vector<G4String> worldNameList;
        std::map<G4String, std::map<G4String, G4TouchableHistoryHandle> > detGeomMap;
};
#endif

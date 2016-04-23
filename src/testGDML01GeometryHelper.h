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
#include "G4NavigationHistory.hh"

class testGDML01GeometryHelper {
    public:
        testGDML01GeometryHelper();
        virtual ~testGDML01GeometryHelper();

        void init();
    private:
        void loopOver(G4VPhysicalVolume* pv, G4int layer);
        void loopSub(G4LogicalVolume* lv, G4int layer);

        G4NavigationHistory* naviHist;
        std::map<G4String, std::map<G4String, G4TouchableHistoryHandle> > detGeomMap;
};
#endif

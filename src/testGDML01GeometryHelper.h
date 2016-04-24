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
#include "G4TouchableHistory.hh"
#include "G4NavigationHistory.hh"

#include <sstream>

class testGDML01GeometryHelper {
    public:
        typedef std::map<G4String, std::map<G4String, G4TouchableHistory> > detGeomMapType;
        testGDML01GeometryHelper();
        virtual ~testGDML01GeometryHelper();

        static testGDML01GeometryHelper* getInstance();
        void init();
        const G4TouchableHistory& getTouchable(const G4String& detId, const G4String& world="");

    private:
        void loopOver(G4VPhysicalVolume* pv, G4int layer);
        void loopSub(G4LogicalVolume* lv, G4int layer);

        static testGDML01GeometryHelper* gInstance;

        G4NavigationHistory* naviHist;
        std::map<G4String, std::map<G4String, G4TouchableHistory> > *detGeomMap;
        std::map<G4String, G4TouchableHistory> tmpGeomMap;
        std::map<G4String, G4int> detIdCountMap;
        G4String detId;
        G4String detName;
        std::stringstream sId;
};
#endif

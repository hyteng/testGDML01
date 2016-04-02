/*=============================================================================
#     FileName: testGDML01DetectorConstruction.h
#         Desc: detector construction header
#       Author: Haiyun.TENG
#        Email: haiyun.teng@gmail.com
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2015-10-25 12:02:15
#      History:
=============================================================================*/

#ifndef testGDML01DetectorConstruction_h 
#define testGDML01DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include "G4GDMLParser.hh"
#include "testGDML01SDFactory.h"
//#include "testGDML01MagneticField.h"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4UserLimits;
class G4Element;
class G4Material;

class testGDML01DetectorConstruction : public G4VUserDetectorConstruction {
    public:
        testGDML01DetectorConstruction(const G4String& name, testGDML01SDFactory* fact);
        ~testGDML01DetectorConstruction();

    public:
        virtual G4VPhysicalVolume* Construct();
        virtual void ConstructSDandField();

        void setFactory(testGDML01SDFactory* fact);
        void setReadFile(const G4String& fname);
        void setWriteFile(const G4String& fname);

    private:
        void setMagField(G4double);

        //G4LogicalVolume* experimentalHall_log;
        //G4LogicalVolume* trackerBlock_log;
        //G4LogicalVolume* trackerLayer_log;
        //G4LogicalVolume* solenoidPart_log;
        //G4VPhysicalVolume* experimentalHall_phys;
        //G4VPhysicalVolume* trackerBlock_phys;
        //G4VPhysicalVolume* trackerLayer_phys;
        //G4VPhysicalVolume* solenoidPart_phys;

        //G4UserLimits* fStepLimit;

        //testGDML01MagneticField* fpMagField;
        //testGDML01SimpleSolenoidPart* fpSolenoidPart;

        G4String fReadFile, fWriteFile;
        G4bool fWritingChoice;
        G4GDMLReadStructure* fReader;
        G4GDMLWriteStructure* fWriter;
        G4GDMLParser* fParser;

        testGDML01SDFactory* factory;
        //testGDML01DetectorMessenger* fDetectorMessenger;
};
#endif

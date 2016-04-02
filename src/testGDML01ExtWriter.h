// class testGDML01ExtWriter

#ifndef testGDML01ExtWriter_H
#define testGDML01ExtWriter_H 1

#include <vector>
#include "G4GDMLWriteStructure.hh"

class G4LogicalVolume;
class G4VisAttributes;

/// GDML writer for the color attributes
class testGDML01ExtWriter : public G4GDMLWriteStructure {

    public:
        testGDML01ExtWriter();
        ~testGDML01ExtWriter();

        void AddExtension(xercesc::DOMElement* volumeElement, const G4LogicalVolume* const vol);
        void ExtensionWrite(xercesc::DOMElement* element);
        void ColorWrite(xercesc::DOMElement* volumeElement, const G4VisAttributes* const att);
        G4bool BookAttribute(const G4VisAttributes* const att);

    private:
        std::vector<const G4VisAttributes*> fAttribs;
};
#endif

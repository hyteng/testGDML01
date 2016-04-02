// class testGDML01ExtReader

#ifndef testGDML01ExtReader_H
#define testGDML01ExtReader_H 1

#include <map>
#include "G4GDMLReadStructure.hh"

class G4VisAttributes;

/// GDML reader for the color attributes

class testGDML01ExtReader : public G4GDMLReadStructure {

    public:
        testGDML01ExtReader();
        ~testGDML01ExtReader();

        void ExtensionRead(const xercesc::DOMElement* const element);
        void ColorRead(const xercesc::DOMElement* const element);
        G4VisAttributes* GetVisAttribute(const G4String& ref);

    protected:
        virtual void VolumeRead(const xercesc::DOMElement* const);

    private:
        std::map<G4String, G4VisAttributes*> fAttribs;
};

#endif

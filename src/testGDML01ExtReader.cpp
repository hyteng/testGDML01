#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"

#include "testGDML01ExtReader.h"

testGDML01ExtReader::testGDML01ExtReader() : G4GDMLReadStructure() {
}

testGDML01ExtReader::~testGDML01ExtReader() {
  std::map<G4String, G4VisAttributes*>::iterator pos;
  for(pos=fAttribs.begin(); pos!=fAttribs.end(); pos++)
  delete pos->second;
}

void testGDML01ExtReader::ExtensionRead(const xercesc::DOMElement* const extElement) {
   G4cout << "G4GDML: Reading GDML extension..." << G4endl;
   for(xercesc::DOMNode* iter=extElement->getFirstChild(); iter!=0; iter=iter->getNextSibling()) {
      if(iter->getNodeType() != xercesc::DOMNode::ELEMENT_NODE)
          continue;

      const xercesc::DOMElement* const child = dynamic_cast<xercesc::DOMElement*>(iter);
      const G4String tag = Transcode(child->getTagName());

      if(tag=="color") {
          ColorRead(child);
      }
      else {
        G4String error_msg = "Unknown tag in structure: " + tag;
        G4Exception("testGDML01ExtReader::ExtensionRead()", "ReadError", FatalException, error_msg);
      }
   }
}

void testGDML01ExtReader::VolumeRead(const xercesc::DOMElement* const volumeElement) {
   G4VSolid* solidPtr = 0;
   G4Material* materialPtr = 0;
   G4VisAttributes* attrPtr = 0;
   G4GDMLAuxListType auxList;
   
   XMLCh *name_attr = xercesc::XMLString::transcode("name");
   const G4String name = Transcode(volumeElement->getAttribute(name_attr));
   xercesc::XMLString::release(&name_attr);

   for(xercesc::DOMNode* iter=volumeElement->getFirstChild(); iter!=0; iter=iter->getNextSibling()) {
      if(iter->getNodeType() != xercesc::DOMNode::ELEMENT_NODE)
          continue;

      const xercesc::DOMElement* const child = dynamic_cast<xercesc::DOMElement*>(iter);
      const G4String tag = Transcode(child->getTagName());

      if(tag == "auxiliary") { 
          auxList.push_back(AuxiliaryRead(child));
      } 
      else if(tag == "materialref") {
          materialPtr = GetMaterial(GenerateName(RefRead(child), true));
      } 
      else if(tag =="solidref") {
          solidPtr = GetSolid(GenerateName(RefRead(child)));
      }
      else if(tag == "colorref") {
          attrPtr = GetVisAttribute(GenerateName(RefRead(child)));
      }
   }

   pMotherLogical = new G4LogicalVolume(solidPtr, materialPtr, GenerateName(name), 0, 0, 0);
   pMotherLogical->SetVisAttributes(attrPtr);

   if(!auxList.empty()) {
       auxMap[pMotherLogical] = auxList;
   }

   Volume_contentRead(volumeElement);
}

void testGDML01ExtReader::ColorRead(const xercesc::DOMElement* const colorElement) {
   G4String name;
   G4VisAttributes* color = 0;
   G4double r=0., g=0., b=0., a=0.;

   const xercesc::DOMNamedNodeMap* const attributes = colorElement->getAttributes();
   XMLSize_t attributeCount = attributes->getLength();

   for(XMLSize_t attribute_index=0; attribute_index<attributeCount; attribute_index++) {
      xercesc::DOMNode* attribute_node = attributes->item(attribute_index);
      if(attribute_node->getNodeType() != xercesc::DOMNode::ATTRIBUTE_NODE) {
          continue;
      }

      const xercesc::DOMAttr* const attribute = dynamic_cast<xercesc::DOMAttr*>(attribute_node);   
      const G4String attName = Transcode(attribute->getName());
      const G4String attValue = Transcode(attribute->getValue());

      if(attName=="name") {
          name = GenerateName(attValue);
      }
      else if(attName=="R") {
          r = eval.Evaluate(attValue);
      }
      else if(attName=="G") {
          g = eval.Evaluate(attValue);
      }
      else if(attName=="B") {
          b = eval.Evaluate(attValue);
      }
      else if(attName=="A") {
          a = eval.Evaluate(attValue);
      }
   }

   G4cout << "Color attribute (R,G,B,A) is: " << r << ", " << g << ", " << b << ", " << a << " !" << G4endl;
   color = new G4VisAttributes(G4Color(r,g,b,a));
   fAttribs.insert(std::make_pair(name,color));
}

G4VisAttributes* testGDML01ExtReader::GetVisAttribute(const G4String& ref) {
  G4VisAttributes* col = 0;
  std::map<G4String, G4VisAttributes*>::iterator pos = fAttribs.find(ref);

  if(pos != fAttribs.end()) {
    col = pos->second;
  }
  else {
    G4String err_mess = "Attribute: " + ref + " NOT found !";
    G4Exception("testGDML01ExtReader::GetVisAttribute()", "ReadError", FatalException, err_mess);
  }
  return col;
}

#ifndef _REMOLLGDMLREADSTRUCTURE_HH_
#define _REMOLLGDMLREADSTRUCTURE_HH_

#include "G4GDMLReadStructure.hh"
#include "G4GDMLReadMaterials.hh"

#include "G4UnitsTable.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4AssemblyVolume.hh"
#include "G4ReflectionFactory.hh"
#include "G4PVDivisionFactory.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

class remollGDMLReadStructure: public G4GDMLReadStructure
{
  public:
    remollGDMLReadStructure()
    : G4GDMLReadStructure()
    { }
    virtual ~remollGDMLReadStructure() { }

  public:

   void MaterialRead(const xercesc::DOMElement* const);
   virtual void MaterialsRead(const xercesc::DOMElement* const);

/*
Support something like:
  <material name="G4_Al">
    <property name="REFLECTIVITY" ref="REFLECTIVITY_CATHODE"/>
    <property name="EFFICIENCY" ref="EFFICIENCY_CATHODE"/>
  </material>
*/

   G4LogicalVolume* FileRead(const xercesc::DOMElement* const);
   void PhysvolRead(const xercesc::DOMElement* const,
                    G4AssemblyVolume* assembly=0);

/*
Support something like search paths with:
    <physvol>
      <file name="detectorDaughter.gdml"/>
      <positionref ref="detectorCenter"/>
    </physvol>
*/

   virtual void VolumeRead(const xercesc::DOMElement* const);
   virtual void Volume_contentRead(const xercesc::DOMElement* const);
   virtual void StructureRead(const xercesc::DOMElement* const);

};

void remollGDMLReadStructure::
MaterialsRead(const xercesc::DOMElement* const materialsElement)
{
   G4GDMLReadStructure::MaterialsRead(materialsElement);
}

void remollGDMLReadStructure::
MaterialRead(const xercesc::DOMElement* const materialElement)
{
   G4String name;
   G4double Z = 0.0;
   G4double a = 0.0;
   G4double D = 0.0;
   G4State state = kStateUndefined;
   G4double T = STP_Temperature;
   G4double P = STP_Pressure;
   G4double MEE = -1.0;

   const xercesc::DOMNamedNodeMap* const attributes
         = materialElement->getAttributes();
   XMLSize_t attributeCount = attributes->getLength();

   for (XMLSize_t attribute_index=0;
        attribute_index<attributeCount; attribute_index++)
   {
      xercesc::DOMNode* attribute_node = attributes->item(attribute_index);

      if (attribute_node->getNodeType() != xercesc::DOMNode::ATTRIBUTE_NODE)
      { continue; }

      const xercesc::DOMAttr* const attribute
            = dynamic_cast<xercesc::DOMAttr*>(attribute_node);   
      if (!attribute)
      {
        G4Exception("G4GDMLReadMaterials::MaterialRead()", "InvalidRead",
                    FatalException, "No attribute found!");
        return;
      }
      const G4String attName = Transcode(attribute->getName());
      const G4String attValue = Transcode(attribute->getValue());

      if (attName=="name") { name = GenerateName(attValue); } else
      if (attName=="Z") { Z = eval.Evaluate(attValue); } else
      if (attName=="state")
      {
         if (attValue=="solid")  { state = kStateSolid;  } else
         if (attValue=="liquid") { state = kStateLiquid; } else
         if (attValue=="gas")    { state = kStateGas; }
      }
   }

   size_t nComponents = 0;

   for (xercesc::DOMNode* iter = materialElement->getFirstChild();
        iter != 0; iter = iter->getNextSibling())
   {
      if (iter->getNodeType() != xercesc::DOMNode::ELEMENT_NODE) { continue; }

      const xercesc::DOMElement* const child
            = dynamic_cast<xercesc::DOMElement*>(iter);
      if (!child)
      { 
        G4Exception("G4GDMLReadMaterials::MaterialRead()", "InvalidRead",
                    FatalException, "No child found!");
        return;
      }
      const G4String tag = Transcode(child->getTagName());

      if (tag=="atom") { a = AtomRead(child); } else
      if (tag=="Dref") { D = GetQuantity(GenerateName(RefRead(child))); } else
      if (tag=="Pref") { P = GetQuantity(GenerateName(RefRead(child))); } else
      if (tag=="Tref") { T = GetQuantity(GenerateName(RefRead(child))); } else
      if (tag=="MEEref") { MEE = GetQuantity(GenerateName(RefRead(child))); } else
      if (tag=="D") { D = DRead(child); } else
      if (tag=="P") { P = PRead(child); } else
      if (tag=="T") { T = TRead(child); } else
      if (tag=="MEE") { MEE = MEERead(child); } else
      if (tag=="fraction" || tag=="composite")  { nComponents++; }
   }

   G4Material* material =  0;

   if (nComponents==0)
   {
     material = new G4Material(Strip(name),Z,a,D,state,T,P);
   }
   else
   {
     material = new G4Material(Strip(name),D,nComponents,state,T,P);
     MixtureRead(materialElement, material);
   }
   if (MEE != -1)  // ionisation potential (mean excitation energy)
   {
     material->GetIonisation()->SetMeanExcitationEnergy(MEE);
   }

   for (xercesc::DOMNode* iter = materialElement->getFirstChild();
        iter != 0; iter = iter->getNextSibling())
   {
      if (iter->getNodeType() != xercesc::DOMNode::ELEMENT_NODE) { continue; }

      const xercesc::DOMElement* const child
            = dynamic_cast<xercesc::DOMElement*>(iter);
      if (!child)
      {
        G4Exception("G4GDMLReadMaterials::MaterialRead()", "InvalidRead",
                    FatalException, "No child found!");
        return;
      }
      const G4String tag = Transcode(child->getTagName());

      if (tag=="property") { PropertyRead(child,material); }
   }
}

void remollGDMLReadStructure::
PhysvolRead(const xercesc::DOMElement* const physvolElement,
            G4AssemblyVolume* pAssembly)
{
  G4GDMLReadStructure::PhysvolRead(physvolElement, pAssembly);
}

void remollGDMLReadStructure::
Volume_contentRead(const xercesc::DOMElement* const volumeElement)
{
  G4GDMLReadStructure::Volume_contentRead(volumeElement);
}

void remollGDMLReadStructure::
StructureRead(const xercesc::DOMElement* const structureElement)
{
  G4GDMLReadStructure::StructureRead(structureElement);
}

G4LogicalVolume* remollGDMLReadStructure::
FileRead(const xercesc::DOMElement* const fileElement)
{
   G4String name;
   G4String volname;

   const xercesc::DOMNamedNodeMap* const attributes
         = fileElement->getAttributes();
   XMLSize_t attributeCount = attributes->getLength();

   for (XMLSize_t attribute_index=0;
        attribute_index<attributeCount; attribute_index++)
   {
      xercesc::DOMNode* attribute_node = attributes->item(attribute_index);

      if (attribute_node->getNodeType() != xercesc::DOMNode::ATTRIBUTE_NODE)
        { continue; }

      const xercesc::DOMAttr* const attribute
            = dynamic_cast<xercesc::DOMAttr*>(attribute_node);   
      if (!attribute)
      {
        G4Exception("G4GDMLReadStructure::FileRead()",
                    "InvalidRead", FatalException, "No attribute found!");
        return 0;
      }
      const G4String attName = Transcode(attribute->getName());
      const G4String attValue = Transcode(attribute->getValue());

      if (attName=="name") { name = attValue; } else
      if (attName=="volname") { volname = attValue; }
   }

   const G4bool isModule = true;
   G4GDMLReadStructure structure;
   structure.Read(name,validate,isModule);

   // Register existing auxiliar information defined in child module
   //
   const G4GDMLAuxMapType* aux = structure.GetAuxMap();
   if (!aux->empty())
   {
     G4GDMLAuxMapType::const_iterator pos;
     for (pos = aux->begin(); pos != aux->end(); ++pos)
     {
       auxMap.insert(std::make_pair(pos->first,pos->second));
     }
   }

   // Return volume structure from child module
   //
   if (volname.empty())
   {
     return structure.GetVolume(structure.GetSetup("Default"));
   }
   else
   {
     return structure.GetVolume(structure.GenerateName(volname));
   }
}


void remollGDMLReadStructure::
VolumeRead(const xercesc::DOMElement* const volumeElement)
{
   G4VSolid* solidPtr = 0;
   G4Material* materialPtr = 0;
   G4GDMLAuxListType auxList;

   XMLCh *name_attr = xercesc::XMLString::transcode("name");
   const G4String name = Transcode(volumeElement->getAttribute(name_attr));
   xercesc::XMLString::release(&name_attr);

   for (xercesc::DOMNode* iter = volumeElement->getFirstChild();
        iter != 0; iter = iter->getNextSibling())
   {
      if (iter->getNodeType() != xercesc::DOMNode::ELEMENT_NODE)  { continue; }

      const xercesc::DOMElement* const child
            = dynamic_cast<xercesc::DOMElement*>(iter);
      if (!child)
      {
        G4Exception("G4GDMLReadStructure::VolumeRead()",
                    "InvalidRead", FatalException, "No child found!");
        return;
      }
      const G4String tag = Transcode(child->getTagName());

      if (tag=="auxiliary")
        { auxList.push_back(AuxiliaryRead(child)); } else
      if (tag=="materialref")
        { materialPtr = GetMaterial(GenerateName(RefRead(child),true)); } else
      if (tag=="solidref")
        { solidPtr = GetSolid(GenerateName(RefRead(child))); }
   }

   pMotherLogical = new G4LogicalVolume(solidPtr,materialPtr,
                                        GenerateName(name),0,0,0);

   if (!auxList.empty()) { auxMap[pMotherLogical] = auxList; }

   Volume_contentRead(volumeElement);
}

#endif


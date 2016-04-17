/**
 *  Filename: src/testGDML01SDFactory.cpp
 *   Created: 2016-04-01 03:53:13
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */

#include "G4PSEnergyDeposit.hh"
#include "G4PSNofSecondary.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4SDParticleFilter.hh"

#include "testGDML01SDFactory.h"
#include "testGDML01BaseScorer.h"
#include "testGDML01TrackerSD.h"

testGDML01SDFactory::testGDML01SDFactory() {
}

testGDML01SDFactory::~testGDML01SDFactory() {
}

G4VSensitiveDetector* testGDML01SDFactory::createSD(G4String& name, std::vector<G4String>& hits, std::vector<G4String>& para) {
    G4VSensitiveDetector* sd = NULL;
    G4cout << "create SD: " << name << "; ";
    for(int i=0; i<hits.size(); i++)
        G4cout << hits[i] << ", ";
    G4cout << "; ";
    for(int i=0; i<para.size(); i++)
        G4cout << para[i] << ", ";
    G4cout << G4endl;

    if(name == "tracker")
        sd = (G4VSensitiveDetector*) new testGDML01TrackerSD(name, hits, para);

    return sd;
}

G4MultiFunctionalDetector* testGDML01SDFactory::createScorer(G4String& name, std::vector<std::pair<G4String, std::vector<G4String> > >& prims, std::vector<G4int>& depths, std::vector<G4String>& para) {
    G4MultiFunctionalDetector* det = new testGDML01BaseScorer(name, para);
    G4cout << "create SD: " << name << "; ";
    for(int i=0; i<para.size(); i++)
        G4cout << para[i] << ", ";
    G4cout << G4endl;

    for(int i=0; i<prims.size(); i++) {
        G4VPrimitiveScorer* primitive;
        G4String primName = prims[i].first;
        G4cout << "prim " << primName << ", depth " << depths[i];
        std::vector<G4String>& filters = prims[i].second;
        if(primName == "EnergyDeposit")
            primitive = new G4PSEnergyDeposit(primName, depths[i]);
        if(primName = "NofSecondary")
            primitive = new G4PSNofSecondary(primName, depths[i]);


        if(primitive!=NULL && filters.size()>0) {
            G4SDParticleFilter* pFilter = new G4SDParticleFilter(name);
            for(int i=0; i<filters.size(); i++) {
                G4cout << " filter " << filters[i];
                pFilter->add(filters[i]);
            }
            primitive->SetFilter(pFilter);
        }
        if(primitive != NULL) {
            det->RegisterPrimitive(primitive);
        }
    }
    G4cout << G4endl;
    return det;
}




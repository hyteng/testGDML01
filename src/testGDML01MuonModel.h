/*=============================================================================
#     FileName: testGDML01testGDML01MuonModel.h
#         Desc: detector physics listn header
#       Author: Haiyun.TENG
#        Email: haiyun.teng@gmail.com
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2013-05-05 02:38:27
#      History:
=============================================================================*/

#ifndef testGDML01MuonModel_h
#define testGDML01MuonModel_h

#include "G4VFastSimulationModel.hh"
#include "G4Step.hh"
#include "G4TouchableHandle.hh"

class testGDML01MuonModel : public G4VFastSimulationModel {

    public:
        testGDML01MuonModel(G4String, G4Region*);
        testGDML01MuonModel(G4String);
        virtual ~testGDML01MuonModel();

        // -- IsApplicable
        G4bool IsApplicable(const G4ParticleDefinition&);
        // -- ModelTrigger 
        G4bool ModelTrigger(const G4FastTrack &);
        // -- User method DoIt 
        void DoIt(const G4FastTrack&, G4FastStep&); 

    private:
        G4Step  *fFakeStep;
        G4TouchableHandle   fTouchableHandle;
        G4Navigator *fpNavigator;
        G4bool  fNaviSetup;
};

#endif

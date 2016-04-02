/*=============================================================================
#     FileName: testGDML01ActionInitialization.cpp
#         Desc: user action Initialization
#       Author: Haiyun TENG
#        Email: haiyun.teng@gmail.com
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2015-10-25 12:05:06
#      History: 
=============================================================================*/

#include "G4GlobalFastSimulationManager.hh"

#include "testGDML01ActionInitialization.h"
#include "testGDML01PrimaryGeneratorAction.h"
#include "testGDML01RunAction.h"
#include "testGDML01EventAction.h"
//#include "testGDML01TrackingAction.h"
//#include "testGDML01SteppingAction.h"

testGDML01ActionInitialization::testGDML01ActionInitialization() : G4VUserActionInitialization() {
}

testGDML01ActionInitialization::~testGDML01ActionInitialization() {    
}

void testGDML01ActionInitialization::BuildForMaster() const {
    SetUserAction(new testGDML01RunAction);
}

void testGDML01ActionInitialization::Build() const {
    SetUserAction(new testGDML01PrimaryGeneratorAction);
    SetUserAction(new testGDML01RunAction);
    SetUserAction(new testGDML01EventAction);
    //SetUserAction(new testGDML01TrackingAction);
    //SetUserAction(new testGDML01SteppingAction);
}

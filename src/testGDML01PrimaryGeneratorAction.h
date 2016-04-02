/*=============================================================================
#     FileName: testGDML01PhysicsList.h
#         Desc: detector physics listn header
#       Author: Haiyun.TENG
#        Email: haiyun.teng@gmail.com
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2013-04-23 02:38:27
#      History:
=============================================================================*/

#ifndef testGDML01PrimaryGeneratorAction_h
#define testGDML01PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class testGDML01PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  public:
    testGDML01PrimaryGeneratorAction();
    ~testGDML01PrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* anEvent);

  private:
    G4ParticleGun* particleGun;
};

#endif



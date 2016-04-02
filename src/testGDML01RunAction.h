#ifndef testGDML01RunAction_h
#define testGDML01RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class testGDML01RunAction : public G4UserRunAction
{
public:
  testGDML01RunAction();
  ~testGDML01RunAction();
  
public:
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

private:
};

#endif



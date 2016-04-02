#ifndef testGDML01EventAction_h
#define testGDML01EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class G4Event;

class testGDML01EventAction : public G4UserEventAction
{
  public:
    testGDML01EventAction();
   ~testGDML01EventAction();

  public:
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);

    void SetDrawFlag(G4String val) {drawFlag = val;};

  private:
    G4int trackerCollID;
    G4String    drawFlag;

};

#endif



#ifndef testGDML01TrackerDigitizer_h
#define testGDML01TrackerDigitizer_h 1

#include "G4VDigitizerModule.hh"
#include "globals.hh"

#include "testGDML01TrackerDigi.h"

class testGDML01TrackerDigitizer : public G4VDigitizerModule {

    public:
        testGDML01TrackerDigitizer(G4String name);
        ~testGDML01TrackerDigitizer();
    
        inline void SetRunNumber(G4int n) {RunNumber = n;};
        inline G4int GetRunNumber() {return RunNumber;};
        inline void SetEventNumber(G4int n) {EventNumber = n;};
        inline G4int GetEventNumber() {return EventNumber;};
        void Digitize();

    private:
        testGDML01TrackerDigitsCollection*  DigitsCollection;
        G4int EventNumber;
        G4int RunNumber;
};

#endif

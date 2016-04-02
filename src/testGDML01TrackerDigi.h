#ifndef testGDML01TrackerDigi_h 
#define testGDML01TrackerDigi_h 1

#include "G4VDigi.hh"
#include "G4TDigiCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class testGDML01TrackerDigi : public G4VDigi {

    public:
        testGDML01TrackerDigi();
        testGDML01TrackerDigi(const testGDML01TrackerDigi&);
        ~testGDML01TrackerDigi();
        const testGDML01TrackerDigi& operator=(const testGDML01TrackerDigi&);
        int operator==(const testGDML01TrackerDigi&) const;
        
        inline void* operator new(size_t);
        inline void  operator delete(void*);

        void Draw();
        void Print();

        inline void SetRun(const G4int & RN) {RunNumber = RN;};
        inline G4int GetRun() {return RunNumber;};
        inline void SetEvent(const G4int & EN) {EventNumber = EN;};
        inline G4int GetEvent() {return EventNumber;}; 
        inline void SetDetector(const G4int & DN) {DetectorNumber = DN;};
        inline G4int GetDetector() {return DetectorNumber;};
        inline void SetStrip(const G4int & StripNb) {StripNumber = StripNb;};
        inline G4int GetStrip() {return StripNumber;};
        inline void SetPosition(const G4ThreeVector & thePosition) {GlobalPosition = thePosition;} ;
        inline G4ThreeVector GetPosition() {return GlobalPosition;};
        inline void SetError(const G4ThreeVector & theError) {GlobalError = theError;};
        inline G4ThreeVector GetError() {return GlobalError;};
        inline void SetSimPosition(const G4ThreeVector & theSimPosition) {GlobalSimPosition = theSimPosition;};
        inline G4ThreeVector GetSimPosition() {return GlobalSimPosition;};
        inline void SetPt(G4double p) {Pt = p;};
        inline G4double GetPt() {return Pt;};

    private:
        G4int RunNumber;
        G4int EventNumber;
        G4int DetectorNumber;
        G4int StripNumber;
        G4ThreeVector GlobalPosition;
        G4ThreeVector GlobalError;
        G4ThreeVector GlobalSimPosition;
        G4double Pt;
};


typedef G4TDigiCollection<testGDML01TrackerDigi> testGDML01TrackerDigitsCollection;

extern G4ThreadLocal G4Allocator<testGDML01TrackerDigi>* testGDML01TrackerDigiAllocator;

inline void* testGDML01TrackerDigi::operator new(size_t) {
    if(!testGDML01TrackerDigiAllocator)
        testGDML01TrackerDigiAllocator = new G4Allocator<testGDML01TrackerDigi>;
    return (void*) testGDML01TrackerDigiAllocator->MallocSingle();
}

inline void testGDML01TrackerDigi::operator delete(void* aDigi) {
    testGDML01TrackerDigiAllocator->FreeSingle((testGDML01TrackerDigi*) aDigi);
}
#endif

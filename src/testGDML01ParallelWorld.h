#ifndef testGDML01ParallelWorld_h
#define testGDML01ParallelWorld_h 1

#include "G4VUserParallelWorld.hh"

#include "G4GDMLParser.hh"
#include "testGDML01SDFactory.h"

class testGDML01ParallelWorld :public G4VUserParallelWorld {
    public:
        testGDML01ParallelWorld(const G4String& name, testGDML01SDFactory* fact=NULL);
        ~testGDML01ParallelWorld();

        virtual void Construct(); // for parallel world return type is void
        virtual void ConstructSD();

        void setFactory(testGDML01SDFactory* fact);
        void setReadFile(const G4String& fname);
        void setWriteFile(const G4String& fname);

    private:
        G4String fReadFile, fWriteFile;
        G4bool fWritingChoice;
        G4GDMLReadStructure* fReader;
        G4GDMLWriteStructure* fWriter;
        G4GDMLParser* fParser;
        testGDML01SDFactory* factory;
};
#endif

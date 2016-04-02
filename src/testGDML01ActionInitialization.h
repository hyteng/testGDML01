/*=============================================================================
#     FileName: testGDML01ActionInitialization.h
#         Desc: user action header for multi thread scheme
#       Author: Haiyun TENG
#        Email: haiyun.teng@gmail.com
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2015-10-25 12:00:54
#      History: 
=============================================================================*/

#ifndef testGDML01ActionInitialization_h
#define testGDML01ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class testGDML01ActionInitialization :public G4VUserActionInitialization {
    public:
        testGDML01ActionInitialization();
        ~testGDML01ActionInitialization();
    
        virtual void BuildForMaster() const;
        virtual void Build() const;

    private:
        /* data */
};
#endif

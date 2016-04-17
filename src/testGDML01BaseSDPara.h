/**
 *  Filename: src/testGDML01BaseSDPara.h
 *   Created: 2016-04-15 06:36:24
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */
#ifndef testGDML01BaseSDPara_h
#define testGDML01BaseSDPara_h 1

#include <vector>
#include "globals.hh" 


class testGDML01BaseSDPara {
    public:
        testGDML01BaseSDPara(std::vector<G4String>& p);
        virtual ~testGDML01BaseSDPara();

        virtual void parameterisation(void* p0, void* ret);
    private:
        std::vector<G4String> para;
};
#endif

/**
 *  Filename: src/testGDML01BaseSDPara.cpp
 *   Created: 2016-04-15 06:37:13
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */
#include "testGDML01BaseSDPara.h"

testGDML01BaseSDPara::testGDML01BaseSDPara(std::vector<G4String>& p) {
    para.clear();
    for(int i=0; i<p.size(); i++)
        para.push_back(p[i]);
}

testGDML01BaseSDPara::~testGDML01BaseSDPara() {
}

void testGDML01BaseSDPara::parameterisation(void* p0, void* ret) {
}

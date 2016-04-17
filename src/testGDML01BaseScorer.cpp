/**
 *  Filename: src/testGDML01BaseScorer.cpp
 *   Created: 2016-04-17 08:55:52
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */
#include "testGDML01BaseScorer.h"

testGDML01BaseScorer::testGDML01BaseScorer(G4String& name, std::vector<G4String>& pars) : G4MultiFunctionalDetector(name) {
    para = pars;
}

testGDML01BaseScorer::~testGDML01BaseScorer() {
}

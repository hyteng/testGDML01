/**
 *  Filename: src/testGDML01PhysicsBuilder.cpp
 *   Created: 2016-04-13 05:24:08
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */
#include "testGDML01PhysicsBuilder.h"

testGDML01PhysicsBuilder::testGDML01PhysicsBuilder() {
}

testGDML01PhysicsBuilder::~testGDML01PhysicsBuilder() {
}

void testGDML01PhysicsBuilder::init() {
    // set process, as well as for parrallel SD and fast Simulation
    thePhysicsList = new testGDML01PhysicsList;
    thePhysicsList->setWorld(worldNameCollection);
    thePhysicsList->setParaFilter(particleFilter);
}

std::vector< std::vector<G4String> >& testGDML01PhysicsBuilder::getParaFilter() {
    return particleFilter;
}

void testGDML01PhysicsBuilder::setWorldName(std::vector<G4String>& w) {
    worldNameCollection = w;
}


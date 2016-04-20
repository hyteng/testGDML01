/**
 *  Filename: src/testGDML01GSPBuilder.cpp
 *   Created: 2016-04-13 05:26:22
 *      Desc: TODO (some description)
 *    Author: Haiyun Teng, haiyun.teng@gmail.com
 *   Company: CSNS
 */
#include "testGDML01GSPBuilder.h"

testGDML01GSPBuilder::testGDML01GSPBuilder() {
    geomBuilder = new testGDML01GeometryBuilder();
    phyBuilder = new testGDML01PhysicsBuilder();
    geomHelper = new testGDML01GeometryHelper;
}

testGDML01GSPBuilder::~testGDML01GSPBuilder() {
    delete geomBuilder;
    delete phyBuilder;
    delete geomHelper;
}

void testGDML01GSPBuilder::init(const std::string &nameList) {
    geomBuilder->init(nameList);
    geomBuilder->cloneParaFilter(phyBuilder->getParaFilter());
    phyBuilder->setWorldName(geomBuilder->getNameCollection());
    phyBuilder->init();
}

void testGDML01GSPBuilder::initDetGeometry() {
    geomHelper->init();
}


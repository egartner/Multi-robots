/*
 * smartBlocksSimulator.cpp
 *
 *  Created on: 12 avril 2013
 *      Author: ben
 */

#include <iostream>
#include "smartBlocksSimulator.h"

using namespace std;

namespace SmartBlocks {

SmartBlocksBlockCode*(* SmartBlocksSimulator::buildNewBlockCode)(SmartBlocksBlock*)=NULL;

SmartBlocksSimulator::SmartBlocksSimulator(int argc, char *argv[],
					   SmartBlocksBlockCode *(*smartBlocksBlockCodeBuildingFunction)
					   (SmartBlocksBlock*)) : BaseSimulator::Simulator(argc, argv) {
    cout << "\033[1;34m" << "SmartBlocksSimulator constructor" << "\033[0m" << endl;

    buildNewBlockCode = smartBlocksBlockCodeBuildingFunction;
    newBlockCode = (BlockCode *(*)(BuildingBlock *))smartBlocksBlockCodeBuildingFunction;
    parseWorld(argc, argv);
    parseBlockList();
    parseTarget();

    ((SmartBlocksWorld*)world)->linkBlocks();

    GlutContext::mainLoop();
}

SmartBlocksSimulator::~SmartBlocksSimulator() {
    //MODIF NICO : deleteScheduler() est déjà appellée par BaseSimulator::~Simulator()
    //~ deleteScheduler();
    cout << "\033[1;34m" << "SmartBlocksSimulator destructor" << "\033[0m" <<endl;
}

void SmartBlocksSimulator::createSimulator(int argc, char *argv[],
					   SmartBlocksBlockCode *(*smartBlocksBlockCodeBuildingFunction)
					   (SmartBlocksBlock*)) {
    simulator =  new SmartBlocksSimulator(argc, argv, smartBlocksBlockCodeBuildingFunction);
}

void SmartBlocksSimulator::deleteSimulator() {
    delete ((SmartBlocksSimulator*)simulator);
    simulator = NULL;
}

void SmartBlocksSimulator::loadWorld(int lx, int ly, int lz, int argc, char *argv[]) {
    SmartBlocksWorld::createWorld(lx,ly,argc,argv);
    world = SmartBlocksWorld::getWorld();
    world->loadTextures("../../simulatorCore/smartBlocksTextures");
}

void SmartBlocksSimulator::loadScheduler() {
    SmartBlocksScheduler::createScheduler();
    scheduler = SmartBlocksScheduler::getScheduler();
}

void SmartBlocksSimulator::loadBlock(TiXmlElement *blockElt, int blockId,
				     BlockCode *(*buildingBlockCodeBuildingFunction)(BuildingBlock*),
				     const Cell3DPosition &pos, const Color &color, bool master) {

    // Any additional configuration file parsing exclusive to this type of block should be performed
    //  here, using the blockElt TiXmlElement.

    // ...Parsing code...

    // Finally, add block to the world
    ((SmartBlocksWorld*)world)->addBlock(blockId,
					 (SmartBlocksBlockCode *(*)(SmartBlocksBlock *))
					 buildingBlockCodeBuildingFunction,
					 pos, color);
}

void SmartBlocksSimulator::loadTargetAndCapabilities(vector<Cell3DPosition> targetCells) {

    // Add target cells to world
    ((SmartBlocksWorld*)world)->initTargetGrid();
    for (Cell3DPosition p : targetCells) {
	((SmartBlocksWorld*)world)->setTargetGrid(fullCell, p[0], p[1]);
    }

    // then parse and load capabilities...
    TiXmlNode *nodeCapa = xmlWorldNode->FirstChild("capabilities");
    if (nodeCapa) {
	((SmartBlocksWorld*)world)->setCapabilities(new SmartBlocksCapabilities(nodeCapa));
    }
}

} // SmartBlocks namespace

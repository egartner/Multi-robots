#include <iostream>
#include <trace.h>

#include "SBMeldBlockCode.h"
#include "smartBlocksSimulator.h"
#include "smartBlocksBlockCode.h"
#include "meldInterpretVM.h"
#include "configStat.h"

using namespace std;
using namespace SmartBlocks;

int main(int argc, char **argv) {

	OUTPUT << "\033[1;33m" << "Starting SmartBlocks simulation (main) ..." << "\033[0m" << endl;

	BaseSimulator::Simulator::setType(BaseSimulator::Simulator::MELDINTERPRET);
	createSimulator(argc, argv, SBMeldBlockCode::buildNewBlockCode);

	{
		using namespace BaseSimulator;

		Simulator *s = Simulator::getSimulator();
		s->printInfo();
	}

	getSimulator()->printInfo();
	getScheduler()->printInfo();
	BaseSimulator::getWorld()->printInfo();

	// getScheduler()->waitForSchedulerEnd();

	deleteSimulator();

	OUTPUT << "\033[1;33m" << "end (main)" << "\033[0m" << endl;
	return(0);
}
#ifndef RBMELDBLOCKCODE_H_
#define RBMELDBLOCKCODE_H_



#include "robotBlocksBlock.h"
#include "meldInterpretVM.h"
#include "robotBlocksBlockCode.h"
#include "robotBlocksSimulator.h"

class RBMeldBlockCode : public RobotBlocks::RobotBlocksBlockCode {
private:
	bool hasWork, polling;
	MeldInterpret::MeldInterpretVM *vm;
	RobotBlocks::RobotBlocksBlock *bb;
	Time currentLocalDate; // fastest mode

public:
	RBMeldBlockCode(RobotBlocks::RobotBlocksBlock *host);
	~RBMeldBlockCode();

	void startup();
	void init();
	void processLocalEvent(EventPtr pev);
	void setCurrentLocalDate(Time t) {currentLocalDate = t;}
	void handleDeterministicMode(/*MeldProcess::VMCommand &command*/);
	static BlockCode *buildNewBlockCode(BuildingBlock *host);
};

#endif /* RBMELDBLOCKCODE_H_ */

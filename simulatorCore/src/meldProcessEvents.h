/*
 * meldProcessEvents.h
 *
 *  Created on: 28 March 2015
 *      Author: andre
 */

#ifndef MELDPROCESSEVENTS_H_
#define MELDPROCESSEVENTS_H_

#include "buildingBlock.h"
#include "events.h"
#include "network.h"
#include "meldProcessDebugger.h"

namespace MeldProcess {

//===========================================================================================================
//
//          VMSetIdEvent  (class)
//
//===========================================================================================================

class VMSetIdEvent : public BlockEvent {
public:

	VMSetIdEvent(uint64_t, BuildingBlock *conBlock);
	VMSetIdEvent(VMSetIdEvent *ev);
	~VMSetIdEvent();
	void consumeBlockEvent() {};
	void consume();
	const virtual string getEventName();
};

//===========================================================================================================
//
//          VMStopEvent  (class)
//
//===========================================================================================================

class VMStopEvent : public BlockEvent {
public:

	VMStopEvent(uint64_t, BuildingBlock *conBlock);
	VMStopEvent(VMStopEvent *ev);
	~VMStopEvent();
	void consumeBlockEvent() {};
	void consume();
	const virtual string getEventName();
};

//===========================================================================================================
//
//          VMAddNeighborEvent  (class)
//
//===========================================================================================================

class VMAddNeighborEvent : public BlockEvent {
public:
	uint64_t face;
	uint64_t target;
	
	VMAddNeighborEvent(uint64_t, BuildingBlock *conBlock, uint64_t f, uint64_t ta);
	VMAddNeighborEvent(VMAddNeighborEvent *ev);
	~VMAddNeighborEvent();
	void consumeBlockEvent();
	const virtual string getEventName();
};

//===========================================================================================================
//
//          VMRemoveNeighborEvent  (class)
//
//===========================================================================================================

class VMRemoveNeighborEvent : public BlockEvent {
public:
	uint64_t face;
	
	VMRemoveNeighborEvent(uint64_t, BuildingBlock *conBlock, uint64_t f);
	VMRemoveNeighborEvent(VMRemoveNeighborEvent *ev);
	~VMRemoveNeighborEvent();
	void consumeBlockEvent();
	const virtual string getEventName();
};

//===========================================================================================================
//
//          VMTapEvent  (class)
//
//===========================================================================================================

class VMTapEvent : public BlockEvent {
public:

	VMTapEvent(uint64_t, BuildingBlock *conBlock);
	VMTapEvent(VMTapEvent *ev);
	~VMTapEvent();
	void consumeBlockEvent();
	const virtual string getEventName();
};


//===========================================================================================================
//
//          VMSetColorEvent  (class)
//
//===========================================================================================================

class VMSetColorEvent : public BlockEvent {
public:
	Vecteur color;

	VMSetColorEvent(uint64_t, BuildingBlock *conBlock, float r, float g, float b, float a);
	VMSetColorEvent(uint64_t, BuildingBlock *conBlock, Vecteur &c);
	VMSetColorEvent(VMSetColorEvent *ev);
	~VMSetColorEvent();
	void consumeBlockEvent();
	const virtual string getEventName();
};

//===========================================================================================================
//
//          VMSendMessageEvent  (class)
//
//===========================================================================================================

class VMSendMessageEvent : public BlockEvent {
public:
	MessagePtr message;
	P2PNetworkInterface *sourceInterface;

	VMSendMessageEvent(uint64_t, BuildingBlock *conBlock, Message *mes, P2PNetworkInterface *ni);
	VMSendMessageEvent(VMSendMessageEvent *ev);
	~VMSendMessageEvent();
	void consumeBlockEvent();
	const virtual string getEventName();
};

//===========================================================================================================
//
//          VMAccelEvent  (class)
//
//===========================================================================================================

class VMAccelEvent : public BlockEvent {
public:
	uint64_t x;
	uint64_t y;
	uint64_t z;
	
	VMAccelEvent(uint64_t, BuildingBlock *conBlock, uint64_t xx, uint64_t yy, uint64_t zz);
	VMAccelEvent(VMAccelEvent *ev);
	~VMAccelEvent();
	void consumeBlockEvent();
	const virtual string getEventName();
};

//===========================================================================================================
//
//          VMShakeEvent  (class)
//
//===========================================================================================================

class VMShakeEvent : public BlockEvent {
public:
	uint64_t force;
	
	VMShakeEvent(uint64_t, BuildingBlock *conBlock, uint64_t f);
	VMShakeEvent(VMShakeEvent *ev);
	~VMShakeEvent();
	void consumeBlockEvent();
	const virtual string getEventName();
};

//===========================================================================================================
//
//          VMHandleDebugCommandEvent  (class)
//
//===========================================================================================================

class VMHandleDebugCommandEvent : public BlockEvent {

public:
	DebbuggerVMCommand *command;
	
	VMHandleDebugCommandEvent(uint64_t, BuildingBlock *conBlock, DebbuggerVMCommand *c);
	VMHandleDebugCommandEvent(VMHandleDebugCommandEvent *ev);
	~VMHandleDebugCommandEvent();
	void consumeBlockEvent();
	const virtual string getEventName();
};

//===========================================================================================================
//
//          VMDebugMessageEvent  (class)
//
//===========================================================================================================

class VMDebugPauseSimEvent : public Event {

public:
	
	VMDebugPauseSimEvent(uint64_t);
	VMDebugPauseSimEvent(VMDebugPauseSimEvent *ev);
	~VMDebugPauseSimEvent();
	void consume();
	const virtual string getEventName();
};

//===========================================================================================================
//
//          VMEndPollEvent  (class)
//
//===========================================================================================================

class VMEndPollEvent : public BlockEvent {
public:

	VMEndPollEvent(uint64_t, BuildingBlock *conBlock);
	VMEndPollEvent(VMEndPollEvent *ev);
	~VMEndPollEvent();
	void consumeBlockEvent();
	const virtual string getEventName();
};

} // MeldProcess namespace


#endif /* MELDPROCESSEVENTS_H_ */

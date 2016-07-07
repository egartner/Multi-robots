/**
 * @file translationEvents.h
 * @brief This file implements the realization of a translation motion events
 *  (created from refactoring of smartBlocksEvents and robotBlocksEvents)
 *
 *  Created on: 07/07/16
 *      Author: Pierre
 */

#ifndef TRANSLATIONEVENTS_H_
#define TRANSLATIONEVENTS_H_

#include "BuildingBlock.h"
#include "events.h"

namespace BaseSimulator {

//===========================================================================================================
//
//          MotionStartEvent  (class)
//
//===========================================================================================================

class MotionStartEvent : public BlockEvent {
    Vector3D finalPosition;
public:
    MotionStartEvent(uint64_t, BuildingBlock *block,const Vector3D &fpos);
    MotionStartEvent(MotionStartEvent *ev);
    ~MotionStartEvent();
    void consumeBlockEvent() {};
    void consume();
    const virtual string getEventName();
};

//===========================================================================================================
//
//          MotionStepEvent  (class)
//
//===========================================================================================================

class MotionStepEvent : public BlockEvent {
    Vector3D finalPosition;	//!< Target position of the block
    Vector3D motionStep;		//!< Motion of the block during this step
    Vector3D motionPosition;		//!< Actual position on the grid of the block in motion
public:
    MotionStepEvent(uint64_t, BuildingBlock *block,const Vector3D &fpos);
    MotionStepEvent(uint64_t, BuildingBlock *block,const Vector3D &fpos,
		    const Vector3D &step, const Vector3D &mpos);
    MotionStepEvent(MotionStepEvent *ev);
    ~MotionStepEvent();
    void consumeBlockEvent() {};
    void consume();
    const virtual string getEventName();
};

//===========================================================================================================
//
//          MotionStopEvent  (class)
//
//===========================================================================================================

class MotionStopEvent : public BlockEvent {
    Vector3D finalPosition;
public:
    MotionStopEvent(uint64_t, BuildingBlock *block,const Vector3D &fpos);
    MotionStopEvent(MotionStepEvent *ev);
    ~MotionStopEvent();
    void consumeBlockEvent() {};
    void consume();
    const virtual string getEventName();
};

//===========================================================================================================
//
//          MotionEndEvent  (class)
//
//===========================================================================================================

class MotionEndEvent : public BlockEvent {
public:
    MotionEndEvent(uint64_t, BuildingBlock *block);
    MotionEndEvent(MotionEndEvent *ev);
    ~MotionEndEvent();
    void consumeBlockEvent() {};
    void consume();
    const virtual string getEventName();
};

}
#endif /* TRANSLATIONEVENTS_H_ */
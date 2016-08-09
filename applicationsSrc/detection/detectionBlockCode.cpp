/*
 * smartblock1BlockCode.cpp
 *
 *  Created on: 12 avril 2013
 *      Author: ben
 */

#include <iostream>
#include <sstream>
#include "detectionBlockCode.h"
#include "scheduler.h"
#include "events.h"
//MODIF NICO
#include <memory>


using namespace std;
using namespace SmartBlocks;

DetectionBlockCode::DetectionBlockCode(SmartBlocksBlock *host):SmartBlocksBlockCode(host) {
	cout << "DetectionBlockCode constructor" << endl;
	scheduler = getScheduler();
	smartBlock = (SmartBlocksBlock*)hostBlock;
}

DetectionBlockCode::~DetectionBlockCode() {
	cout << "SmartBlock1BlockCode destructor" << endl;
}

void DetectionBlockCode::startup() {
	stringstream info;

	info << "  Starting DetectionBlockCode in block " << hostBlock->blockId;
	scheduler->trace(info.str());

	distance_dealer = NULL;
	my_distance = MAX_DIST;

	//If i am master block
	if( hostBlock->blockId == 1)
	{
		#ifndef NDEBUG
		cout << "Block #" << hostBlock->blockId << " : I am a master block !" << endl;
		#endif

		my_distance = 0;

		//I send distance to all of my neighbors
		Time time_offset;
		for( int i=NeighborDirection::North; i<=NeighborDirection::West; i++)
		{
			P2PNetworkInterface *p2p = smartBlock->getInterface(NeighborDirection::Direction(i));
			if( p2p->connectedInterface)
			{
				time_offset = (i+1)*1000;
				send_dist( my_distance + 1, p2p, time_offset);
				isAck[i] = false;
			}
			else
				isAck[i] = true;
		}
	}
}

void DetectionBlockCode::processLocalEvent(EventPtr pev) {
	int i;
	Time time_offset;
	unsigned int sourceId;
	MessagePtr message;
	stringstream info;

	switch (pev->eventType) {
		case EVENT_NI_RECEIVE:
			message = (std::static_pointer_cast<NetworkInterfaceReceiveEvent>(pev))->message;
			P2PNetworkInterface * recv_interface = message->destinationInterface;

			switch( message->id) {
				//If i receive a distance message :
				case DIST_MSG_ID :
				{
					//TODO completement experimental, je ne sais pas précisement les effets de cette ligne
					Dist_message_ptr recv_message = std::static_pointer_cast<Dist_message>(message);

					sourceId = recv_message->sourceInterface->hostBlock->blockId;
					info.str("");
					info << "Block " << hostBlock->blockId << " received a Dist_message '" << recv_message->getDistance() << "' from " << sourceId << endl;
					//info << "data : " << msg->data();
					scheduler->trace(info.str());

					//I compare its distance with mine
					if( recv_message->getDistance() < my_distance)
					{
						my_distance = recv_message->getDistance();
						smartBlock->setColor(my_distance);

						distance_dealer = recv_message->destinationInterface;

						//I send my new distance to all my neighbors except to its sender
						for( i = NeighborDirection::North; i <= NeighborDirection::West; i++)
						{
							P2PNetworkInterface * p2p =
								smartBlock->getInterface(NeighborDirection::Direction(i));
							if( p2p->connectedInterface) {
								//except to the sender
								if( p2p != recv_interface) {
									time_offset = (i+1)*1000;
									send_dist( my_distance + 1, p2p, time_offset);

									isAck[i] = false;
								}
								//I'm not waiting for an Ack from the sender of the distance
								else { isAck[i] = true;	}
							}
							//From where there is no neighbor, i'm not waiting for an Ack
							else { isAck[i] = true; }
						}
						//Now, i check if i can already acknowledge my new distance
						if( i_can_ack()){ send_ack( my_distance, recv_interface, 1000); }
					}
					//If my distance was better than the one i received, i ack
					else{	send_ack( my_distance, recv_interface, 1000);	}
					break;
				}

				case ACK_MSG_ID :
				{
					//TODO completement experimental, je ne sais pas précisement les effets de cette ligne
					Ack_message_ptr recv_message = std::static_pointer_cast<Ack_message>(message);

					//~ std::shared_ptr<Ack_message> recv_message = std::static_pointer_cast<Ack_message>(message);

					sourceId = message->sourceInterface->hostBlock->blockId;
					info.str("");
					info << "Block " << hostBlock->blockId << " received a Ack_message '" << recv_message->getDistance() << "' from " << sourceId << endl;

					//info << "data : " << msg->data();
					scheduler->trace(info.str());

					//I want to be sure that my neighbors is acknowledging the last distance i sent
					if( recv_message->getDistance() < my_distance + 2)
					{
						//Searching for wich neighbor answered
						isAck[ smartBlock->getDirection( recv_interface)] = true;

						//If all of my neighbors ackowledged
						if( i_can_ack()){
							//If i am master block, flood is over
							if( hostBlock->blockId == 1) {
								cout << "Flood done !" << endl;
								smartBlock->setColor(my_distance);

							}
							//else i have to acknowledge
							else{	send_ack( my_distance, distance_dealer, 1000); }
						}
					}
					break;
				}

				default :
					sourceId = message->sourceInterface->hostBlock->blockId;
					cerr << "Block " << hostBlock->blockId << " received an unrecognized message from " << sourceId << endl;
				break;
			}
		break;
	}
}

SmartBlocks::SmartBlocksBlockCode* DetectionBlockCode::buildNewBlockCode(SmartBlocksBlock *host) {
	return(new DetectionBlockCode(host));
}


void DetectionBlockCode::send_dist( unsigned int distance,  P2PNetworkInterface * by_interface, Time time_offset) {
	Dist_message * message = new Dist_message( distance);
	scheduler->schedule( new NetworkInterfaceEnqueueOutgoingEvent( scheduler->now() + time_offset, message, by_interface));
}

void DetectionBlockCode::send_ack( unsigned int distance,  P2PNetworkInterface * by_interface, Time time_offset) {
	Ack_message * ack = new Ack_message( distance);
	scheduler->schedule( new NetworkInterfaceEnqueueOutgoingEvent( scheduler->now() + time_offset, ack, by_interface));
}


bool DetectionBlockCode::i_can_ack(){
	bool result = true;
	int i = NeighborDirection::North;
	while( i <= NeighborDirection::West && result == true)
	{
		 if( isAck[ i] == false){ result = false; }
		 i++;
	}
	return result;
}


Dist_message::Dist_message(unsigned int d):Message(){
	id = DIST_MSG_ID;
	distance = d;
}

Dist_message::~Dist_message() {
}

Ack_message::Ack_message(unsigned int d):Message() {
	id = ACK_MSG_ID;
	distance = d;
}

Ack_message::~Ack_message() {
}


/*
 * socket.h
 *
 *  Created on: Feb 15, 2017
 *      Author: attar
 */

#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

#include <Ports.h>
#include <Log.h>

class Socket {
public:
	Socket();
	virtual ~Socket();

	struct Packet {
		short play;
		short location;
		short alliance;
	};
	struct PlaySelection {
		Utils::AutoPlay play;
		Utils::AutoLocation location;
		Utils::Alliance alliance;
	};

	Packet process();
	static PlaySelection packetToSelection(const Packet &packet);

	static const Packet NO_UPDATE;
private:
	bool validPacket(const Packet& packet);

	int sock;

	uint16_t raw_packet;
	int unused_packet;

	static const uint16_t PACKET_PLAY_MASK;
	static const uint16_t PACKET_LOCATION_MASK;
	static const uint16_t PACKET_ALLIANCE_MASK;

	Log* log;
};

#endif /* SRC_SOCKET_H_ */

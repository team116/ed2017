/*
 * socket.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: attar
 */

#include <Socket.h>
#include <Ports.h>

#include <arpa/inet.h>
#include <cerrno>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

const Socket::Packet Socket::NO_UPDATE = Packet{
	.play = -1,
	.location = -1,
	.alliance = -1
};

const uint16_t Socket::PACKET_PLAY_MASK = 0xFF00;
const uint16_t Socket::PACKET_LOCATION_MASK = 0x00FE;
const uint16_t Socket::PACKET_ALLIANCE_MASK = 0X0001;

Socket::Socket() :
	raw_packet(0),
	unused_packet(0)
{
	log = Log::getInstance();

    int portNum = 1184; // NOTE that the port number is same for both client and server
    string ip = "10.1.16.15";

    struct sockaddr_in server_addr;

    sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);//add	nonblocking

    if(sock < 0)
    {
    	log->write(Log::WARNING_LEVEL, "Error creating socket: %s", strerror(errno));
    	throw exception();
    }

    /*
        The socket() function creates a new socket.
        It takes 3 arguments,
            a. AF_INET: address domain of the socket.
            b. SOCK_STREAM: Type of socket. a stream socket in
            which characters are read in a continuous stream (TCP)
            c. Third is a protocol argument: should always be 0. The
            OS will choose the most appropiate protocol.
            This will return a small integer and is used for all
            references to this socket. If the socket call fails,
            it returns -1.
    */

    /*
        The variable serv_addr is a structure of sockaddr_in.
        sin_family contains a code for the address family.
        It should always be set to AF_INET.
        htons() converts the port number from host byte order
        to a port number in network byte order.
    */

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);

    // this function returns returns 1 if the IP is valid
    // and 0 if invalid
    // inet_pton converts IP to packets
    // inet_ntoa converts back packets to IP
    inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

    /* ---------- CONNECTING THE SOCKET ---------- */
    /* ---------------- connect() ---------------- */

    if(connect(sock,(struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    	log->write(Log::WARNING_LEVEL, "Unable to establish connection to RPi: %s", strerror(errno));
    }

    /*
        The connect function is called by the client to
        establish a connection to the server. It takes
        three arguments, the socket file descriptor, the
        address of the host to which it wants to connect
        (including the port number), and the size of this
        address.
        This function returns 0 on success and -1
        if it fails.
        Note that the client needs to know the port number of
        the server but not its own port number.
    */
}

Socket::Packet Socket::process () {
	int receive = recv(sock, &raw_packet + unused_packet, sizeof(raw_packet) - unused_packet, 0);
	if(receive < 1) {
		return NO_UPDATE;
	}

	if((unsigned)(unused_packet + receive) < sizeof(raw_packet)) {
		// we haven't read the entire packet
		unused_packet = unused_packet + receive;
		return NO_UPDATE;
	}

	// reset state and return expanded values
	raw_packet = 0;
	unused_packet = 0;
	return Packet{
		.play = (short)((raw_packet & PACKET_PLAY_MASK) >> 8),
		.location = (short)((raw_packet & PACKET_LOCATION_MASK) >> 1),
		.alliance = (short)(raw_packet & PACKET_ALLIANCE_MASK)
	};
}

Socket::PlaySelection Socket::packetToSelection(const Packet &packet) {
	return PlaySelection{
		.play = (Utils::AutoPlay)packet.play,
		.location = (Utils::AutoLocation)packet.location,
		.alliance = (Utils::Alliance)packet.alliance
	};
}

bool Socket::validPacket(const Packet& packet) {
	bool valid = true;
	if(packet.play < 0 || packet.play > 10) {
		log->write(Log::WARNING_LEVEL, "Auto packet contained invalid play %d", packet.play);
		valid = false;
	}
	else if(packet.location < 0 || packet.location > 8) {
		log->write(Log::WARNING_LEVEL, "Auto packet contained invalid location %d", packet.location);
		valid = false;
	}
	else if(packet.alliance < 0 || packet.alliance > 1) {
		log->write(Log::WARNING_LEVEL, "Auto packet contained invalid alliance %d", packet.alliance);
		valid = false;
	}
	return valid;
}

Socket::~Socket() {
	::close(sock);
}


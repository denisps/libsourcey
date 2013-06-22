//
// LibSourcey
// Copyright (C) 2005, Sourcey <http://sourcey.com>
//
// LibSourcey is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// LibSourcey is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//


#ifndef SOURCEY_TURN_TCPPeerConnection_H
#define SOURCEY_TURN_TCPPeerConnection_H


#include "Sourcey/BasicManager.h"
#include "Sourcey/Timeout.h"
#include "Sourcey/STUN/Message.h"
#include "Sourcey/Net/TCPSocket.h"
#include "Sourcey/Net/Reactor.h"


namespace Scy {
namespace TURN {
	

const int PEER_CONNECTION_TIMEOUT = 15;
	

class TCPAllocation;
class TCPClientConnection;

	
class TCPPeerConnection: public Net::TCPPacketSocket
{
public:
	TCPPeerConnection(TCPAllocation& allocation, Net::Reactor& reactor/* = Net::Reactor::getDefault()*/);
	TCPPeerConnection(TCPAllocation& allocation, const Poco::Net::StreamSocket& socket, Net::Reactor& reactor/* = Net::Reactor::getDefault()*/);
	virtual ~TCPPeerConnection();
	
	void bindWith(TCPClientConnection* client);
	TCPClientConnection* client() const;

	void startTimeout();
	bool expired() const;
		// If no ConnectionBind request associated with this peer data
		// connection is received after 30 seconds, the peer data
		// connection MUST be closed.
	
	UInt32 connectionID() const;
	STUN::TransactionID transactionID() const;
	void setTransactionID(const STUN::TransactionID& id);
		// The TransactionID is used to determine if this connection
		// is bound with a Connect request, in which case a response
		// must be sent on connection success/error.

	virtual const char* className() const { return "TCPPeerConnection"; }
	
protected:
	void recv(Buffer& buffer);
	void onClientDisconnect(void*);

	TCPAllocation&			_allocation;
	STUN::TransactionID		_transactionID;
	UInt32					_connectionID;
	Timeout					_timeout;
	TCPClientConnection*	_client;
	Buffer					_earlyDataBuffer;	
	mutable Poco::FastMutex _mutex;
};


typedef BasicManager<UInt32, TCPPeerConnection>	PeerConnectionManager;
typedef PeerConnectionManager::Map				PeerConnectionMap;


} } // namespace Scy::TURN


#endif // SOURCEY_TURN_TCPPeerConnection_H
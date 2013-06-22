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


#ifndef SOURCEY_RTCP_APP_PACKET_H
#define SOURCEY_RTCP_APP_PACKET_H


#include "Sourcey/RTP/RTCP/Packet.h"

#include <vector>


namespace Scy {
namespace RTP {
namespace RTCP {

	
class AppPacket: public RTCP::Packet
	///  0                   1                   2                   3
	///  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
	/// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	/// |V=2|P| subtype |   PT=APP=204  |             length            |
	/// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	/// |                           SSRC/CSRC                           |
	/// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	/// |                          name (ASCII)                         |
	/// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	/// |                   application-dependent data                ...
	/// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
{
public:
	AppPacket();
	virtual ~AppPacket();

	// TODO: clone()
	
	virtual bool read(Buffer& buffer);
	virtual void write(Buffer& buffer) const;
	
	virtual std::string toString() const;	
	virtual void print(std::ostream& os) const;
	
	virtual UInt16 computedLength() const;	
	
	UInt32 ssrc;
	std::string name; // 4 octets
	std::string data; // variable length
	
	virtual const char* className() const { return "RTCPAppPacket"; }
};


} // namespace RTCP
} // namespace RTP
} // namespace Scy 


#endif
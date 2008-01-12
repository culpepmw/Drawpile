/*******************************************************************************

   Copyright (C) 2007 M.K.A. <wyrmchild@users.sourceforge.net>

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:
   
   Except as contained in this notice, the name(s) of the above copyright
   holders shall not be used in advertising or otherwise to promote the sale,
   use or other dealings in this Software without prior written authorization.
   
   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.

*******************************************************************************/

#pragma once

#ifndef NetworkAddress_INCLUDED
#define NetworkAddress_INCLUDED

#include "config.h"

#include <string> // std::string

#include "network.h"
#include "socket.types.h"
#include "types.h"

//! Internet IP Address
/**
 * @bug There's no fallback to IPv4 if IPv6 is unsupported on current system.
 * This may however be of no consequence as IPv6 gains popularity.
 */
class Address
{
protected:
	//! Internal address representation
	union addr {
		//! base address
		sockaddr raw;
		//! Either IPv4 or IPv6 address
		/** Precisely: either sockaddr_in or sockaddr_in6 */
		Network::sockaddr_in_t ipv;
	} addr;
public:
	//! ctor
	/**
	 * @param[in] address String representation of IP address
	 */
	Address(const std::string& address) NOTHROW;
	
	#ifdef IPV6
	//! IPv6 ctor
	/**
	 * @param[in] address IPv6 address
	 * @param[in] port Port number
	 */
	Address(const uint address[4]=0, ushort port=0) NOTHROW;
	#else
	//! IPv4 ctor
	/**
	 * @param[in] address IPv4 address
	 * @param[in] port Port number
	 */
	Address(uint address=0, ushort port=0) NOTHROW;
	#endif
	
	//! Returns size of the raw address
	socklen_t size() const NOTHROW;
	
	//! Get current port number
	ushort port() const NOTHROW;
	
	//! Get address scope
	ulong scope() const NOTHROW;
	
	//! Set address scope
	void scope(ulong _scope) NOTHROW;
	
	//! Set port number
	void port(ushort _port) NOTHROW;
	
	//! Get raw address
	sockaddr& raw() NOTHROW;
	
	//! Get address family
	int family() const NOTHROW;
	//! Set address family
	void family(int _family) NOTHROW;
	
	//! Assign operator
	Address& operator= (const Address& naddr) NOTHROW;
	
	//! Is-equal operator
	bool operator== (const Address& naddr) const NOTHROW;
	
	//! Convert address to string representation of it
	std::string toString() const;
	
private:
	//! Return pointer to sin_addr or sin6_addr
	Network::in_addr_t& in_addr() NOTHROW;
	
	//! Return const pointer to sin_addr or sin6_addr
	const Network::in_addr_t& in_addr() const NOTHROW;
	
	//! Convert string to address
	/**
	 * @param[in] address string to convert
	 */
	void fromString(std::string const& address) NOTHROW;
};

#ifndef NDEBUG
//! Extension to ostream for Address
std::ostream& operator<< (std::ostream& os, const Address& addr) NOTHROW;
#endif

#endif // NetworkAddress_INCLUDED

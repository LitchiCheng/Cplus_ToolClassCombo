#pragma once
#include "stdafx.h"
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

class SocketHandleClass
{
public:
	enum protocol_type
	{
		TCP = 1,
		UDP = 2
	};
	SocketHandleClass(protocol_type type, const std::string remote_address, const int remote_port);
	~SocketHandleClass();
	void sendHex();
	void sendString();
private:
	boost::asio::io_service io_service;
	boost::system::error_code ec;
	bool m_connect_successful;
	protocol_type m_type;
};

SocketHandleClass::SocketHandleClass(protocol_type type, const std::string remote_address, const int remote_port) :m_connect_successful(false), m_type(type)
{
	if (type == UDP)
	{
		boost::asio::ip::udp::socket udp_socket(io_service);
		boost::asio::ip::udp::endpoint remote(boost::asio::ip::address::from_string(remote_address), remote_port);
		udp_socket.open(remote.protocol(), ec);
		if (ec)
		{
			m_connect_successful = false;
			std::cout << boost::system::system_error(ec).what() << std::endl;
		}
		else { m_connect_successful = true; }
	}
	else if (type == TCP)
	{
		boost::asio::ip::tcp::socket tcp_socket(io_service);
		boost::asio::ip::tcp::endpoint remote(boost::asio::ip::address::from_string(remote_address), remote_port);
		tcp_socket.connect(remote, ec);
		if (ec)
		{
			m_connect_successful = false;
			std::cout << boost::system::system_error(ec).what() << std::endl;
		}
		else { m_connect_successful = true; }
	}
}

SocketHandleClass::~SocketHandleClass()
{
	if (!io_service.stopped())
	{
		io_service.stop();
	}
}

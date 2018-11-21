#pragma once
#include "stdafx.h"
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/format.hpp>

class SocketHandleClass
{
public:
	enum protocol_type
	{
		TCP = 0,
		UDP = 1
	};
	SocketHandleClass(protocol_type type, const std::string remote_address, const int remote_port);
	~SocketHandleClass();
	void sendHex(const std::string hex_string);
	void sendString(const char* real_string);
	void readString(int read_buff_size);
	bool isConnectSuccessful()
	{
		return m_connect_successful;
	}
private:
	boost::asio::io_service io_service;
	boost::system::error_code ec;
	bool m_connect_successful;
	protocol_type m_type;
	std::string m_remote_address;
	int m_remote_port;
	void setUdpRemote();
	void setTcpRemote();
	//char *m_read_buff;
	char m_read_buff[1024];
	boost::asio::ip::udp::endpoint m_remote()
	{
		boost::asio::ip::udp::endpoint remote(boost::asio::ip::address::from_string(m_remote_address), m_remote_port);
		return remote;
	}
	boost::asio::ip::udp::socket* ptr_udp_socket;
	boost::asio::ip::udp::endpoint m_udp_remote;
	boost::asio::ip::tcp::socket* ptr_tcp_socket;
	boost::asio::ip::tcp::endpoint m_tcp_remote;
};

SocketHandleClass::SocketHandleClass(protocol_type type, const std::string remote_address, const int remote_port) :m_connect_successful(false), m_type(type), m_remote_address(remote_address), m_remote_port(remote_port), ptr_udp_socket(nullptr), ptr_tcp_socket(nullptr)
{
	if (type == UDP)
	{	
		setUdpRemote();
	}
	else if (type == TCP)
	{
		setTcpRemote();
	}
}

SocketHandleClass::~SocketHandleClass()
{
	if (!io_service.stopped())
	{
		io_service.stop();
	}
}


void SocketHandleClass::setUdpRemote()
{
	m_udp_remote = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(m_remote_address), m_remote_port);
	ptr_udp_socket = new boost::asio::ip::udp::socket(io_service);
	ptr_udp_socket->open(m_udp_remote.protocol(), ec);
	if (ec)
	{
		m_connect_successful = false;
		std::cout << boost::system::system_error(ec).what() << std::endl;
	}
	else { m_connect_successful = true; }
	std::cout << "Protocol: " << (m_type ? "UDP" : "TCP") << std::endl;
	std::cout << "Remote: " << m_udp_remote.address() << ":" << m_udp_remote.port() << std::endl;
	std::cout << "Connect: " << (m_connect_successful ? "successful" : "failed") << std::endl;
}

void SocketHandleClass::setTcpRemote()
{
	ptr_tcp_socket =new boost::asio::ip::tcp::socket(io_service);
	m_tcp_remote = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(m_remote_address), m_remote_port);
	ptr_tcp_socket->connect(m_tcp_remote, ec);
	if (ec)
	{
		m_connect_successful = false;
		std::cout << boost::system::system_error(ec).what() << std::endl;
	}
	else { m_connect_successful = true; }
	std::cout << "Protocol: " << (m_type ? "UDP" : "TCP") << std::endl;
	std::cout << "Remote: " << m_tcp_remote.address() << ":" << m_tcp_remote.port() << std::endl;
	std::cout << "Connect:" << (m_connect_successful ? "successful" : "failed") << std::endl;
}

void SocketHandleClass::sendHex(const std::string hex_string)
{
	boost::format format_object("%x");
	format_object % hex_string.c_str();
	if (m_type == TCP)
	{
		std::cout << "Send: " << format_object.str() << std::endl;
		ptr_tcp_socket->write_some(boost::asio::buffer(format_object.str(), format_object.size()), ec);
		if (ec)
		{
			std::cout << boost::system::system_error(ec).what() << std::endl;
		}
	}
	else if(m_type == UDP)
	{
		std::cout << "Send: " << format_object.str() << std::endl;
		ptr_udp_socket->send_to(boost::asio::buffer(format_object.str(), format_object.size()),m_udp_remote);
	}
}

void SocketHandleClass::sendString(const char* real_string)
{
	int len = sizeof(real_string);
	if (m_type == TCP)
	{
		std::cout << "Send: " << real_string << ":" << len << std::endl;
		size_t tcp_write_len = ptr_tcp_socket->write_some(boost::asio::buffer(real_string, len), ec);
		//std::cout << tcp_write_len << std::endl;
		if (ec)
		{
			std::cout << boost::system::system_error(ec).what() << std::endl;
		}
	}
	else if (m_type == UDP)
	{
		std::cout << "Send: " << real_string << std::endl;
		size_t udp_write_len = ptr_udp_socket->send_to(boost::asio::buffer(real_string, len), m_udp_remote);	
	}
}

void SocketHandleClass::readString(int read_buff_size = 0)			
{
	memset(m_read_buff,0,1024);
	if (m_type == TCP)
	{
		size_t len = ptr_tcp_socket->read_some(boost::asio::buffer(m_read_buff), ec);
		if (ec)
		{
			std::cout << boost::system::system_error(ec).what() << std::endl;
		}
		std::cout.write(m_read_buff, len);
		std::cout << std::endl;
	}
	else if(m_type == UDP)
	{
		size_t len = ptr_udp_socket->receive(boost::asio::buffer(m_read_buff, 1024));
		std::cout.write(m_read_buff, len);
		std::cout << std::endl;
	}
}
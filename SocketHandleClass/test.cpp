#include "stdafx.h"
#include <iostream>
#include "SocketHandleCombo.h"

using namespace std;

const char real_string[] = "robokit_log_start";
const char require[] = { 0x5A,0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x03,0xF4,0x00,0x00,0x00,0x00,0x00,0x00 };

void main()
{
	SocketHandleClass socket(SocketHandleClass::UDP,"192.168.192.5",19200, false);
	socket.send(real_string,strlen(real_string));
	SocketHandleClass tcp_socket(SocketHandleClass::TCP, "192.168.192.5", 19204, false);
	while (1)
	{
		socket.read();
		//cout << socket.returnRecieveCharPtr() << endl;
 		socket.showRecieve();
		Sleep(30);
		tcp_socket.send(require,sizeof(require));
		Sleep(30);
		tcp_socket.read();
		//tcp_socket.showRecieve();
	}
}
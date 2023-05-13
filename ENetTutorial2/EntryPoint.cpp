#include <iostream>
#include "enet/enet.h"

int  main()
{
	if (enet_initialize() != 0)
	{
		std::cout << "Enet failed to initialise." << std::endl;
		return 1;
	}
	//Scaffolding code:
	char serverAnswer;
	std::cout << "Do you want this instance to be the server? y/n" << std::endl;
	std::cin >> serverAnswer;
	bool isServer = serverAnswer == 'y';

	if (isServer)
	{
		std::cout << "Creating a server now..." << std::endl;
		//TODO write server loop here.
		
		// provide a host address with the port (e.g. 127.0.0.1)
		ENetAddress hostAddress;
		hostAddress.host = ENET_HOST_ANY;
		hostAddress.port = 1234; //Whatever you like here, it's just a matter of being consistent

		ENetHost* serverHost = enet_host_create(&hostAddress, 32, 2, 0, 0);

		while (true)
		{
			ENetEvent receivedEvent; //The variable to place the info in.
			//While more information awaits us...
			while (enet_host_service(serverHost, &receivedEvent, 100) > 0)
			{
				switch (receivedEvent.type)
				{
				case ENET_EVENT_TYPE_CONNECT:
					std::cout << "A new client connected to the server." << std::endl;
					break;
				case ENET_EVENT_TYPE_DISCONNECT:
					std::cout << "A client disconnected from the server." << std::endl;
					break;
				case ENET_EVENT_TYPE_RECEIVE:
					std::cout << "We received a user-defined packet!" << std::endl;
					break;
				default:
					std::cout << "Unknown data received." << std::endl;
				}
			}
		}
	}
	else
	{
		std::cout << "What ip address do you want to connect to?" << std::endl;
		std::string ipAddress;
		std::cin >> ipAddress;
		std::cout << "Attempting to connect client at " << ipAddress << "..." << std::endl;
		//TODO write client loop here.

		//Creating the host doesn't do all that much yet...
		ENetHost* clientHost = enet_host_create(nullptr, 1, 2, 0, 0);

		ENetAddress address;
		address.port = 1234; //Must be the same number as the server's port!
		//Populate 'address' with info about the server, based on the ip address
		enet_address_set_host(&address, ipAddress.c_str());

		//Now, we connect with our host and address to the server. We request two
		//channels, and allow five seconds before a timeout.
		enet_host_connect(clientHost, &address, 2, 5000);

		while (true)
		{
			ENetEvent receivedEvent; //The variable to place the info in.
			//While more information awaits us...
			while (enet_host_service(clientHost, &receivedEvent, 100) > 0)
			{
				//Process it accordingly
				std::cout << "Client received a packet!" << std::endl;
				switch (receivedEvent.type)
				{
					//TODO: Handle different types of information here.
				}
			}
		}
	}


	enet_deinitialize();

}


/*
OLD SERVER LOOP:

			ENetEvent receivedEvent; //The variable to place the info in.
			//While more information awaits us...
			while (enet_host_service(serverHost, &receivedEvent, 100) > 0)
			{
				//Process it accordingly
				std::cout << "Server received a packet!" << std::endl;
				switch (receivedEvent.type)
				{
					//TODO: Handle different types of information here.
				}
			}


*/
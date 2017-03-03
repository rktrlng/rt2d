/**
 * This class describes MyScene behavior.
 *
 * Copyright 2017 Rik Teerling <rik@onandoffables.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"

MyScene::MyScene() : Scene()
{
	t.start();

	text = new Text();
	text->position = Point2(50,50);
	text->scale = Point2(0.5f,0.5f);
	this->addChild(text);

	char mode[]={'8','N','1',0};

	CPORT_NR = 16; // /dev/ttyUSB0
	BDRATE = 115200;

	connected = 0;
	if(RS232_OpenComport(CPORT_NR, BDRATE, mode)) {
		text->message("Serial port not open");
	} else {
		text->message("Serial port open and connected");
		connected = 1;
	}
}


MyScene::~MyScene()
{
	RS232_CloseComport(CPORT_NR);

	this->removeChild(text);
	delete text;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}

	// ###############################################################
	// send and receive data
	// ###############################################################
	static unsigned char cmd = 'a';
	if (input()->getKeyDown( GLFW_KEY_A )) { cmd = 'a'; }
	if (input()->getKeyDown( GLFW_KEY_B )) { cmd = 'b'; }

	if (t.seconds() > 0.01f) {
		std::vector<int> tokens = transceive(cmd);

		// we now have a clean list of ints that we received
		if (connected && tokens.size() > 1) {
			std::stringstream msg;
			msg << "snd: '" << cmd << "' rcv: ";
			for (size_t i = 0; i < tokens.size(); i++) {
				if (i != 0) {
					msg << tokens[i];
					if (i != tokens.size()-1) {
						msg << ",";
					}
				}
			}
			msg << " (" << tokens[0] << " bytes)";
			text->message(msg.str());
		}

		t.start();
	} // end if t.seconds()

}

std::vector<int> MyScene::transceive(unsigned char cmd)
{
	// protocol:
	// tokens[0] = number of bytes received
	// tokens[1] = confirmation char from Arduino (cmd as int)
	// tokens[2..n] = data (different for each command)
	std::vector<int> tokens(1,0);

	if (connected) {
		// send data (a 'command')
		RS232_SendByte(CPORT_NR, cmd);

		// receive data
		unsigned char buf[4096];
		int n = RS232_PollComport(CPORT_NR, buf, 4095);
		tokens[0] = n;
		if(n > 0) { // we received something
			buf[n] = 0; // always put a "null" at the end of a string

			// replace unreadable control-codes by spaces
			for(int i=0; i < n; i++) {
				if(buf[i] < 32) {
					buf[i] = ' ';
				}
			}

			// split received data into tokens
			std::string s((char *)buf);
			std::istringstream iss(s);
			do {
				std::string sub;
				iss >> sub;
				if (sub.length() > 0) {
					int v = stoi(sub);
					tokens.push_back(v);
				}
			} while (iss);

		} // end if received
	} // end if connected

	return tokens;
}

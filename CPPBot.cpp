// CPPBot.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <chrono>
#include "corefunc.h"
#include "userfunc.h"
#include <string>
#include <unistd.h>
#include <stdint.h>
#include "json.hpp"
//#include <curses.h>
//#include <conio.h>
//#include <windows.h>

using json = nlohmann::json;
using namespace std;
vector<GrowtopiaBot> bots;

GrowtopiaBot bot1 = {"", "", "", -1};
GrowtopiaBot bot2 = {"", "", "", -1};
GrowtopiaBot bot3 = {"", "", "", -1};
GrowtopiaBot bot4 = {"", "", "", -1};
GrowtopiaBot bot5 = {"", "", "", -1};
GrowtopiaBot bot6 = {"", "", "", -1};
void BroadCastGoWorld(string name) {
	bot1.gotow(name);bot2.gotow(name);bot3.gotow(name);bot4.gotow(name);bot5.gotow(name);bot6.gotow(name);
}
void BroadCastPacket(int typ, string text) {
	bot1.packetPeer(typ, text);bot2.packetPeer(typ, text);bot3.packetPeer(typ, text);bot4.packetPeer(typ, text);bot5.packetPeer(typ, text);bot6.packetPeer(typ, text);
}
string getBotPos() {
	string datas = "";
	if (bot1.getPeer()) datas += "BOT 1: x:" + to_string(bot1.localX) + " y: " + to_string(bot1.localY) + "\n";
	if (bot2.getPeer()) datas += "BOT 1: x:" + to_string(bot2.localX) + " y: " + to_string(bot2.localY) + "\n";
	if (bot3.getPeer()) datas += "BOT 1: x:" + to_string(bot3.localX) + " y: " + to_string(bot3.localY) + "\n";
	if (bot4.getPeer()) datas += "BOT 1: x:" + to_string(bot4.localX) + " y: " + to_string(bot4.localY) + "\n";
	if (bot5.getPeer()) datas += "BOT 1: x:" + to_string(bot5.localX) + " y: " + to_string(bot5.localY) + "\n";
	if (bot6.getPeer()) datas += "BOT 1: x:" + to_string(bot6.localX) + " y: " + to_string(bot6.localY) + "\n";
	return datas;
}
void input() {
	int c = 0;
	while (1) {
		string data;
		getline(cin, data);
		if (data == "/bot") {
			if (bot1.getPeer()) cout << bot1.uname << " At " << bot1.world->name << endl;
			if (bot2.getPeer()) cout << bot2.uname << " At " << bot2.world->name << endl;
			if (bot3.getPeer()) cout << bot3.uname << " At " << bot3.world->name << endl;
			if (bot4.getPeer()) cout << bot4.uname << " At " << bot4.world->name << endl;
			if (bot5.getPeer()) cout << bot5.uname << " At " << bot5.world->name << endl;
			if (bot6.getPeer()) cout << bot6.uname << " At " << bot6.world->name << endl;
		}
		else if (data.find("/say ") != std::string::npos) BroadCastPacket(2, "action|input\n|text|" + data.substr(5));
		else if (data == "/status") {
			string status = "";
			if (bot1.getPeer()); status += "BOT 1: ON\n";
			if (bot2.getPeer()); status += "BOT 2: ON\n";
			if (bot3.getPeer()); status += "BOT 3: ON";
			if (bot4.getPeer()); status += "BOT 4: ON\n";
			if (bot5.getPeer()); status += "BOT 5: ON\n";
			if (bot6.getPeer()); status += "BOT 6: ON\n";
			cout << status << endl;
		}
		else if (data=="/pos") getBotPos();
		else if (data=="/help") cout << "Console Command: /clear, go <name>, /status, /bot (print bot world), /say <text>,/pos" << endl;
		else if (data.find("/go ") != std::string::npos) {
			string wr = data.substr(4);
			BroadCastGoWorld(wr);
			cout << "Going to: " << wr << endl;
		}
		else if (data=="/clear") system("clear");
	}
}

GrowtopiaBot makeBot(string user, string pass, string host, int port, string vers, string wname) {
	GrowtopiaBot bot = {user, pass, host, port};
	bot.gameVersion = vers;
	bot.currentWorld = wname;
	bot.userInit();
	bots.push_back(bot);
	return bot;
}
void botSetup() {
	ifstream i("config.json");
	json j;
	i >> j;
	init();
	system("clear");
	string user1 = j["bot1"].get<string>(), pass1 = j["pass1"].get<string>();
	string user2 = j["bot2"].get<string>(), pass2 = j["pass2"].get<string>();
	string user3 = j["bot3"].get<string>(), pass3 = j["pass3"].get<string>();
	string user4 = j["bot4"].get<string>(), pass4 = j["pass4"].get<string>();
	string user5 = j["bot5"].get<string>(), pass5 = j["pass5"].get<string>();
	string user6 = j["bot6"].get<string>(), pass6 = j["pass6"].get<string>();
	string vers = j["gtversion"].get<string>();
	string wn = j["home"].get<string>();
	bot1 = makeBot(user1, pass1,"213.179.209.168", 17198, vers, wn);
	bot2 = makeBot(user2, pass2,"213.179.209.168", 17198, vers, wn);
	bot3 = makeBot(user3, pass3,"213.179.209.168", 17198, vers, wn);
	bot4 = makeBot(user4, pass4,"213.179.209.168", 17198, vers, wn);
	bot5 = makeBot(user5, pass5,"213.179.209.168", 17198, vers, wn);
	bot6 = makeBot(user6, pass6,"213.179.209.168", 17198, vers, wn);
	while (true) {
		bot1.eventLoop();
		bot2.eventLoop();
		bot3.eventLoop();
		bot4.eventLoop();
		bot5.eventLoop();
		bot6.eventLoop();
	}
}
int main() {
	std::thread thr(input);
	thr.detach();
	botSetup();
}
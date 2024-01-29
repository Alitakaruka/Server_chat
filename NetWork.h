#pragma once
#include<boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/date_time.hpp>
#include <iostream>
#include <vector>

#define strSampleSettingsUsername "&UserName="
#define strSampleSettingsCodeRoom "&CodeRoom="
#define strSampleSettingsTextMsg "&Text="
class NetWork
{
private:
	boost::asio::io_context context;
	boost::system::error_code ex;
	boost::asio::ip::tcp::socket* socket;
	std::string userName;
	std::vector<char> sendBuf;
	std::vector<char> acceptBuf;
	void accept_message();
	void send_message(std::string message);
public:
	NetWork();
	void run();
	
private:
	bool connect_to_server();

	void Execute_Command(std::string comand);
	bool is_comand(std::string msg) {
		return msg[0] == '/';
	}
};

 
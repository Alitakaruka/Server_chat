#include "NetWork.h"

void NetWork::accept_message()
{
	//подождем, пока сообщение не будет отправленно
	while (this->sendBuf.size() != 0) {

	}
	this->socket->async_read_some(boost::asio::buffer(this->acceptBuf.data(), this->acceptBuf.size()), [&](boost::system::error_code ex,std::size_t length) {
		if (!ex) {
			for (auto element : acceptBuf) {
				std::cout << element;
			}
		}
		else {
			std::cout << ex.message();
		}
		acceptBuf.clear();
		accept_message();
	});
}

void NetWork::send_message(std::string message)
{
	//подождем, пока сообщение не будет принято и выведенно.
	while (this->acceptBuf.size() != 0) {

	}
	std::cout << boost::posix_time::second_clock::local_time() << ":" << message << std::endl;
	for (char el : message) {
		this->sendBuf.push_back(el);
	}
	this->socket->write_some(boost::asio::buffer(this->sendBuf.data(), sendBuf.size()), this->ex);
	sendBuf.clear();
}

NetWork::NetWork()
{
	char str[] = "1:Create room/n"
		"2:Join room";
	
	int selected;
	while (1) {
		try
		{
			std::cout << str << std::endl;
			std::cin >> selected;
			if (selected == 1 || selected == 2) {
				system("cls");
				break;
			}
			else {
				system("cls");
				continue;
			}
			std::cout << "Enter user name: "<< std::endl;
			std::cin >> this->userName;
			system("cls");
		}
		catch (...) {
			continue;
		}
	}
}

void NetWork::run()
{
	while (!connect_to_server()) {
		std::cout << "Connection failed" << this->ex.message() << std::endl;
	}
	send_message("todo");
	accept_message();
	std::string message;
	while (true) {
		std::cin >> message;
		if (message.empty()) {
			continue;
		}
		else {
			send_message(message);
			message.clear();
		}
	}

}
	

bool NetWork::connect_to_server()
{
	if (this->socket != nullptr) {
		delete this->socket;
	}
	this->socket = new boost::asio::ip::tcp::socket(this->context);
	boost::asio::ip::tcp::resolver resolver(this->context);
	boost::asio::connect(*(this->socket),resolver.resolve("127.0.0.1","55555"),this->ex);

	if (this->socket->is_open()) {
		return true;
	}
	return false;
}

void NetWork::Execute_Command(std::string comand)
{
	std::vector<std::string> comands = { "/cls","/cname","" };
	auto com = *(std::find(comands.begin(), comands.end(), comand));
	if (comand == "cls") {
		system("cls");
	}
	if (comand == "cname") {
		system("cls");
		std::cout << "Enter user name: " << std::endl;
		std::cin >> this->userName;
	}
}

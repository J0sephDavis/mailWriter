//Joseph Davis | April 17, 2023
#include <Poco/Net/MailMessage.h>
#include <string>
//Think of this as a letterhead, contains addressing information
class server {
	//strings are temporary. Intended to be replaced using Poco::Net::IPaddress
	std::string server_address;
	std::string email_address;
	unsigned int port;
	server(std::string _server_address, std::string _email, unsigned int _port) {};
};
//Handles user credentials. Currently just a burner plate implementation
class credentials {
	//The username for the credential
	std::string username;
	//The password associated with the username
	std::string password;
	credentials(std::string _username, std::string _password);
};

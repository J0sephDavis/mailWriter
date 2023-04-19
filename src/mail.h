#ifndef MAILHANDLER_H
#define MAILHANDLER_H

#include <string>
#include <curl/curl.h>
#include <iostream>
using namespace std;
struct memory_container {
	char* mem;
	size_t size;
};
class MailHandler {
	public:
		bool SSL_ENABLED = 1;
		//Constructor with only username and password
		MailHandler(string username, string password); 
		~MailHandler() {
			curl_easy_cleanup(cHandle);
		};
		memory_container get_mail(string append = "");
		void print_mem(struct memory_container data);
	private:
		string username;
		string password;
		string smtp_address;
		string pop_address;
		unsigned int smtp_port = 465;
		unsigned int pop_port = 995;
	private:
		static size_t writememCB(void *data, size_t size, size_t nmemb, void *clientp);
		CURL* cHandle = NULL;
		void init_handler();
		void init_pop();
		void init_smtp();
};
#endif

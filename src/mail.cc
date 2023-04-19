#include "mail.h"
#include <cstring>
#include <curl/curl.h>
MailHandler::MailHandler(string username, string password) {
	this->username = username;
	this->password = password;
	init_handler();
}
//initialize the handler
//process handler
//process writeback
void MailHandler::init_handler() {
	CURLcode res = CURLE_OK;
	if (cHandle != NULL) curl_easy_reset(cHandle);
	else cHandle = curl_easy_init();
	if (cHandle != NULL) {
		//ssl
		if (this->SSL_ENABLED)
			curl_easy_setopt(cHandle, CURLOPT_USE_SSL, CURLUSESSL_ALL);
		//credentials
		curl_easy_setopt(cHandle, CURLOPT_USERNAME, this->username.c_str());
		curl_easy_setopt(cHandle, CURLOPT_PASSWORD, this->username.c_str());
		//verification enabled?
		curl_easy_setopt(cHandle, CURLOPT_SSL_VERIFYHOST,0);
		curl_easy_setopt(cHandle, CURLOPT_SSL_VERIFYPEER,0);
		//other
		curl_easy_setopt(cHandle, CURLOPT_VERBOSE, 1);
		curl_easy_setopt(cHandle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
//		//pop/smtp
//		curl_easy_setopt(cHandle, CURLOPT_URL, (pop)?this->pop_address.c_str():this->smtp_address.c_str());
//		curl_easy_setopt(cHandle, CURLOPT_PORT, (pop)?this->pop_port:this->smtp_port);

	}
}
memory_container MailHandler::get_mail(string append) {
	CURLcode res= CURLE_OK;
	//init mem container
	struct memory_container data;
	data.mem = (char*)malloc(1); //allocates a byte of memory to initialize the pointer
	data.size = 0;
	if (cHandle != NULL) {
		string tmp = this->pop_address + append;
		curl_easy_setopt(cHandle, CURLOPT_URL, tmp.c_str());
		curl_easy_setopt(cHandle, CURLOPT_PORT, this->pop_port);
		//WRITEBACK
		curl_easy_setopt(cHandle, CURLOPT_WRITEFUNCTION, writememCB);
		//Check OK
		res = curl_easy_perform(cHandle);
		if (res != CURLE_OK) {
			std::cout << "easy perf, failed: " << curl_easy_strerror(res) << std::endl;
			curl_easy_cleanup(cHandle);
		}
		else {
			//process data
			std::cout << data.mem << std::endl;
			std::cout << "RETRIEVED (" << data.size << ") bytes\n";
		}
		//if (data.mem) free(data.mem);
	}
	//returns the data struct regardless of its contents
	return std::move(data);
};
size_t MailHandler::writememCB(void *data, size_t size, size_t nmemb, void *clientp) {
	//https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
	size_t realSize = size * nmemb;
	memory_container *mem= (struct memory_container *)clientp;
	char *ptr = (char*)realloc(mem->mem, mem->size + realSize+1);
	if (ptr == NULL) return 0; //out of memory
	mem->mem = ptr;
	memcpy(&(mem->mem[mem->size]),data,realSize);
	mem->mem[mem->size] = 0;
	return realSize;
}
void MailHandler::print_mem(struct memory_container data){
	std::cout << "SIZE: " << data.size << "\n";
	std::cout << data.mem << std::endl; //do not use endl normally, but flush output after printing the buffer.
}

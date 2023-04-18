#include <cstring>
#include <iostream>
#include <string>
#include<curl/curl.h>

using namespace std;

struct memStruct{
	char *memory;
	size_t size;
};
//prototype
size_t WriteMemoryCB(void *contents, size_t size, size_t nmemb, void *userp);


int main(int argc, char** argv) {
	CURL *cHandle = curl_easy_init();
	CURLcode res = CURLE_OK;
	struct memStruct data;
	data.memory = (char*)malloc(1);
	data.size = 0;
	if (cHandle) {
		//SERVER INFORMATION
		curl_easy_setopt(cHandle, CURLOPT_URL,"pop3s://pop.gmail.com/1");
		curl_easy_setopt(cHandle, CURLOPT_PORT, 995);
		//SSL/TLS
		curl_easy_setopt(cHandle, CURLOPT_USE_SSL,CURLUSESSL_ALL);
		//CREDENTIALS
		curl_easy_setopt(cHandle, CURLOPT_USERNAME, (char*)"ffff@gmail.com");
		curl_easy_setopt(cHandle, CURLOPT_PASSWORD, (char*)"password");
		//VERIFICATION
		curl_easy_setopt(cHandle, CURLOPT_SSL_VERIFYHOST,0);
		curl_easy_setopt(cHandle, CURLOPT_SSL_VERIFYPEER,0);
		//other
		curl_easy_setopt(cHandle, CURLOPT_VERBOSE, 1);
		curl_easy_setopt(cHandle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
		//WRITEBACK
		curl_easy_setopt(cHandle, CURLOPT_WRITEFUNCTION, WriteMemoryCB);
		//
		res = curl_easy_perform(cHandle);
		if (res != CURLE_OK) {
			std::cout << "easy perf, failed: " << curl_easy_strerror(res) << std::endl;
			curl_easy_cleanup(cHandle);
		}
		else {
			//process data
			std::cout << data.memory << std::endl;
			std::cout << "RETRIEVED (" << data.size << ") bytes\n";
		}
		if (data.memory)
			free(data.memory);
		curl_easy_cleanup(cHandle);
	}
	return (int)res;
};
size_t WriteMemoryCB(void *contents, size_t size, size_t nmemb, void *memory_pointer){
	size_t calc_size = size * nmemb;
	struct memStruct *mem = (struct memStruct *)memory_pointer;
	mem->memory = (char *)realloc(mem->memory, mem->size + calc_size + 1);
	if (mem->memory == NULL) {
		std::cout << "not enough memory\n";
		return 0;
	}
	memcpy(&(mem->memory[mem->size]), contents, calc_size);
	mem->size += calc_size;
	mem->memory[mem->size] = 0;
	return calc_size;
}
class MailHandler {
	string username;
	string password;
	string host;
	string port;
	MailHandler(string userName, string passWord, string host, unsigned int port) {
		username = userName;
		password = passWord;
		this->host = host;
		this->port = port;
	}
};

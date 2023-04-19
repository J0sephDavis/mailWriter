#include <iostream>
#include <mail.h>

using namespace std;

//prototype
size_t WriteMemoryCB(void *contents, size_t size, size_t nmemb, void *userp);


int main(int argc, char** argv) {
	MailHandler mail_sys("example@gmail.com", "password");
	mail_sys.print_mem(mail_sys.get_mail("/1"));
	return 0;
};

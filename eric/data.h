#ifndef DATA_H
#define DATA_H
#include <string>
#include <vector>
#include <utility>
typedef unsigned long long int int_64;
int_64 max_account_list_size 10000000;

struct log
{
	std::string from;
	std::string to;
	int_64 amount;
	log(std::string f, std::string t, int_64 a): from_to(f), to(t), amount(a){}
};

int_64 log::int_64 time=0;

struct info
{
	//index for related transactions
	std::string id;
	std::string cpassword;
	int_64 balance;
	info(std::string i, std::string p, int_64 m):id(i), cpassword(p), balance(m){}
};

struct table
{
	std::vector<info*> account_list(max_account_list_size);
    std::vector<log> transactions(max_account_list_size);
	int_64 last_successful_login_id_index;
	std::string last_successful_login_id;

	table(int_64 index, std::string id):last_successful_login_id_index(index), last_successful_login_id(id){}

	std::pair<bool, int> check(const std::string & id);
	void login(const std::string & id, const std::string & cpassword);
	void create(const std::string & id, const std::string & cpassword);
	void delete(const std::string & id, const std::string & cpassword);
	void merge(const std::string & id1, const std::string & cpassword1, const std::string & id2, const std::string & cpassword2);
	void deposit(const int_64 & a);
	void withdraw(const int_64 & a);
	void transfer(const std::string & id, const int_64 & a);
	void find(const std::string & wild_string);
	bool wildcmp(char *first, char * second);
	void search(const std::string & id);
};

void swap();
void printInfo(const info * info_content);
void printLog(const log & log_content);

#endif
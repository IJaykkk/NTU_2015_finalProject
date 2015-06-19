#include <data.h>
#include <iostream>
#include <string>
#include <string.h>
#include <utility>
using std::cout;
using std::endl;

std::pair<bool, int> table::check(const std::string & id)
{
	std::pair<bool, int> output;
	int head =0;
	int tail = this->account_list.size()-1;
	int mid = (head+tail)/2;
	while(head <= tail)
	{
		if( strcmp( id.c_str(), this->account_list.at(mid)->id.c_str() < 0)  //search left part
		{
			tail = mid-1;
			mid = (head+tail)/2;
		}
		else if( strcmp( id.c_str(), this->account_list.at(mid)->id.c_str() > 0 ) //search right part
		{
			head = mid+1;
			mid = (head+tail)/2;
		}
		else
			return output = std::make_pair(true, mid);
	}
	return output = std::make_pair(false, mid);
}

void table::login(const std::string & id, const std::string & cpassword)
{
	std::pair<bool, int> output;
	output.first = check(id);
	if(output.first)
	{
		if( this->account_list.at(output.second)->cpassword != cpassword)
			cout << "wrong password" << endl;
		else
		{
			this->last_successful_login_id_index = output.second;
			this->last_successful_login_id = id;
			cout << "success" << endl;
		}
	}
	else
		cout << "ID " << id << " not found" << endl; 
	return;
}

void table::create(const std::string & id, const std::string & cpassword)
{
	std::pair<bool, int> output;
	output.first = check(id);
	if(output.first)
	{
		cout << "ID " << id << " exists, ";
		/******need to list all the recommanded id********/ 	
	}
	else //id doesn't exist, so creat a new one
	{
		int current_size = this->account_list.size();
		if (current_size == max_account_list_size)
			this->account_list.reserve(current_size*2);

		info new_account(id, cpassword, 0ULL);
		this->account_list.push_back(new_account);

		for(int i=this->account_list.size()-1; i>0; i--)
		{
			if( strcmp(id.c_str(), this->account_list.at(i)->id.c_str() < 0 ) )
				swap(this->account_list.at(i), this->account_list.at(i-1);
			else
				break;
		}
		cout << "success" << endl;		
	}
	return;
}

void table::delete(const std::string & id, const std::string & cpassword)
{
	std::pair<bool, int> output;
	output.first = check(id);
	if(output.first)
	{
		if( this->account_list.at(output.second)->cpassword != cpassword)
			cout << "wrong password" << endl;
		else
		{
			this->account_list.erase(this->account_list.begin()+output.second);
			cout << "success" << endl;
		}		
	}
	else
		cout << "ID " << id << " not found" << endl; 
	return;
}

void merge(const std::string & id1, const std::string & cpassword1, const std::string & id2, const std::string & cpassword2)
{
	std::pair<bool, int> output1;
	output1.first = check(id1);
	std::pair<bool, int> output2;
	output2.first = check(id2);
	if(!output1.first)
		cout << "ID " << id1 << " not found" << endl; 
	else if(!output2.first)
		cout << "ID " << id2 << " not found" << endl;
	else if( this->account_list.at(output1.second)->cpassword != cpassword1 )
		cout << "wrong password1" << endl;
	else if( this->account_list.at(output2.second)->cpassword != cpassword2 )
		cout << "wrong password2" << endl;
	else
	{
		this->account_list.at(output1.second)->balance += this->account_list.at(out2.second)->balance;
		int_64 tmp = this->account_list.at(output1.second)->balance;
		/*****************change all the ID of transactions of id2 to id1 *********************/
		this->accout_list.erase(this->account_list.begin()+output2.second);
		cout << "success, " << id1 << " has " << tmp << " dollars" << endl;
	}
	return;
}

void table::deposit(const int_64 & a)
{
	int_64 & tmp = this->account_list.at(last_successful_login_id_index)->balance;
	tmp += a;
	cout << "success, " << tmp  << " dollars in current account" << endl;
	return;
}

void table::withdraw(const int_64 & a)
{
	int_64 & tmp = this->account_list.at(last_successful_login_id_index)->balance;
	if( a > tmp )
		cout << "fail, " << tmp  << " dollars only in current account" << endl;
	else
	{
		tmp -= a;
		cout << "success, "<< tmp << " dollars left in current account" << endl;
	}
	return;
}

void transfer(const std::string & id, const int_64 & a)
{
	int_64 & tmp = this->account_list.at(last_successful_login_id_index)->balance;
	std::pair<bool, int> output;
	output.first = check(id);
	if(!output.first)
	{
		cout << "ID "<< id <<" not found,";
		/***********recommand for existing id***************/
		cout << endl;
	}
	else if(tmp < a)
		cout << "fail, " << tmp << "dollars only in current account" << endl;
	else
	{
		tmp -= a;
		log record(this->last_successful_login_id, id, a)
		this->transactions.push_back(record);
		cout << "success, "<< tmp <<" dollars left in current account" << endl;
	}
	return;
}

void find(const std::string & wild_string)
{
	int_64 count=0;
	for(int i=0; i<this->account_list.size(); i++)
	{
		bool flag = match(wild_string.c_str(), this->account_list[i]->id.c_str());
		if(flag && count==0)
		{
			cout << this->account_list[i]->id;
			count++;
		}
		else if(flag && count!=0)
			cout << "," <<this->account_list[i]->id;	
	}
	return;
}

bool wildcmp(char *first, char * second)
{
	// If we reach at the end of both strings, we are done
    if (*first == '\0' && *second == '\0')
        return true;
    if(*first == '?' && *second == '\0')
 		return false;
	if(*first == '*' && *second == '\0' && *(first+1) == '*')
		return match(first+1,second);
    if (*first == '*' && *(first+1) != '\0' && *second == '\0')
        return false;
    // If the first string contains '?', or current characters of both 
    // strings match
    if (*first == '?' || *first == *second)
        return match(first+1, second+1);
    // If there is *, then there are two possibilities
    // a) We consider current character of second string
    // b) We ignore current character of second string.
    if (*first == '*')
        return match(first+1, second) || match(first, second+1);
    return false;
}

void search(const std::string & id)
{
	for(int i=0; i<this->transactions.size(); i++)
	{
		if( this->transactions.to == id)
			cout << "From" << id << this->transactions.amount << endl;
		else if( this->transactions.from == id)
			cout << "To"   << id << this->transactions.amout << endl;
	}
	return;
}


void swap(info* a, info* b)
{
	info* c = a;
	a = b;
	b = c;
	return;
}

void printInfo(const info* info_content)
{
	cout << "cpassword: " << info_content->cpassword << endl;
	cout << "balance  : " << info_content->balance   << endl;
	cout << "log      : " << endl;
	for(int i=0; i<info_content->transactions.size(); i++)
		printLog(info_content->transactions[i]);
	return;
}

void printLog(const log & log_content)
{
	cout << "         from  : " << log_content.from    << endl;
	cout << "         to    : " << log_content.to      << endl;
	cout << "         amount: " << log_content.balance << endl; 
	return;
}
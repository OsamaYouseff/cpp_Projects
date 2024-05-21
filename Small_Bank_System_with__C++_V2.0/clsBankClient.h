#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "clsPerson.h"
#include "clsString.h"

using namespace std;

class clsBankClient : public clsPerson
{

private:
	enum enMode
	{
		empty_mode = 0,
		update_mode = 1,
		add_new = 2,
		delete_client = 3,
	};
	enMode _mode;
	string _account_num, _PIN_code;
	float _account_balance;
	string _file_name = "clients.txt", _separator = "#//#";

	//// private methods
	static clsBankClient _convert_line_to_client_object(string line, string separator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::split(line, separator);

		return clsBankClient(enMode::update_mode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

	}

	static string _convert_client_obj_to_line(clsBankClient client, string separator = "#//#") {
		string final_string = "";

		final_string += client.get_first_name() + separator;
		final_string += client.get_last_name() + separator;
		final_string += client.get_email() + separator;
		final_string += client.get_phone() + separator;
		final_string += client.get_account_num() + separator;
		final_string += client.get_PIN_code() + separator;
		final_string += to_string(client.get_account_balance());
		return final_string;
	}

	static clsBankClient _get_empty_client_obj() {
		return clsBankClient(enMode::empty_mode, "", "", "", "", "", "", 0);
	};

	static vector<clsBankClient> _load_clients_data_from_file(string file_name = "clients.txt")
	{
		vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open(file_name, ios::in); // read Mode
		if (MyFile.is_open())
		{
			string Line;
			clsBankClient Client = _get_empty_client_obj();
			while (getline(MyFile, Line))
			{
				Client = clsBankClient::_convert_line_to_client_object(Line, "#//#");
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;
	}

	/////  updating
	void _update_file_data(vector<string> users_data, string file_name = "clients.txt")
	{
		fstream users;

		users.open(file_name, ios::out);

		if (users.is_open())
		{
			for (string& user : users_data)
			{
				users << user << "\n";
			}
			users.close();
		}
	}

	void _update_client_in_data_base() {

		vector <clsBankClient> _vClients_data;
		_vClients_data = _load_clients_data_from_file(_file_name);


		for (clsBankClient& client : _vClients_data)
		{
			if (client.account_num == get_account_num()) {
				client = *this;
			}

		}

		vector <string> _vClients_data_str;

		for (clsBankClient& client : _vClients_data)
		{
			_vClients_data_str.push_back(this->_convert_client_obj_to_line(client, _separator));

		}

		_update_file_data(_vClients_data_str, _file_name);



	};

	/////  adding
	void _add_data_line_to_file(string obj_as_line, string file_name = "clients.txt")
	{
		fstream MyFile;
		MyFile.open(file_name, ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << obj_as_line << endl;

			MyFile.close();
		}

	}

	void _add_new_client() {
		_add_data_line_to_file(_convert_client_obj_to_line(*this, _separator), _file_name);
	};

	/////  deleting
	void  _delete_client() {

		vector <clsBankClient> _vClients_data;
		_vClients_data = _load_clients_data_from_file(_file_name);

		vector <string> _vClients_data_str;

		for (clsBankClient& client : _vClients_data)
		{
			if (!(client.get_account_num() == get_account_num()))
				_vClients_data_str.push_back(this->_convert_client_obj_to_line(client, _separator));
		}

		_update_file_data(_vClients_data_str, _file_name);


		*this = _get_empty_client_obj();


	};

public:
	//// constructor
	clsBankClient(enMode mode, string first_name, string last_name, string email, string phone, string account_num, string PIN_code, float account_balance) : clsPerson(first_name, last_name, email, phone)
	{
		_mode = mode;
		_account_num = account_num;
		_PIN_code = PIN_code;
		_account_balance = account_balance;
		//mode = enMode::update_mode;
	};

	///// enums 
	enum enSave_results {
		faild_to_save = 0, saved_successfully = 1, new_client_was_add_succ = 2, deleted_succ = 3,
	};

	//// setters
	void set_account_num(string account_num)
	{
		_account_num = account_num;
	}

	void set_PIN_code(string PIN_code)
	{
		_PIN_code = PIN_code;
	}

	void set_account_balance(float account_balance)
	{
		_account_balance = account_balance;
	}

	//// getters
	string get_account_num()
	{
		return _account_num;
	};

	string get_PIN_code()
	{
		return _PIN_code;
	};

	float get_account_balance()
	{
		return _account_balance;
	};

	__declspec(property(get = get_account_num, put = set_account_num)) string account_num;
	__declspec(property(get = get_PIN_code, put = set_PIN_code)) string PIN_code;
	__declspec(property(get = get_account_balance, put = set_account_balance)) float account_balance;


	//// Main methods

	static clsBankClient create_an_empty_client() {
		clsBankClient client = _get_empty_client_obj();
		return client;
	}

	static clsBankClient create_new_client_with_acc_num(string acc_num) {

		return clsBankClient(enMode::add_new, "", "", "", "", acc_num, "", 0);
	}

	bool is_empty()
	{
		return _mode == enMode::empty_mode;
	};

	//// no UI related to this obj
	//void print()
	//{
	//	cout << "\nClient card";
	//	cout << "\n______________________________\n\n";
	//	cout << "First name      : " << get_first_name() << endl;
	//	cout << "Last name       : " << get_last_name() << endl;
	//	cout << "Email           : " << get_email() << endl;
	//	cout << "Phone number    : " << get_phone() << endl;
	//	cout << "Account number  : " << get_account_num() << endl;
	//	cout << "PIN code        : " << get_PIN_code() << endl;
	//	cout << "Account balance : " << get_account_balance() << endl;
	//	cout << "______________________________\n";
	//};

	static clsBankClient find(string account_num)
	{


		fstream MyFile;
		MyFile.open("clients.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient client = _convert_line_to_client_object(Line);
				if (client.get_account_num() == account_num)
				{
					MyFile.close();
					return client;
				}

			}

			MyFile.close();

		}

		return _get_empty_client_obj();
	}

	static clsBankClient find(string account_num, string PIN_code)
	{


		fstream MyFile;
		MyFile.open("clients.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient client = _convert_line_to_client_object(Line);
				if (client.get_account_num() == account_num && client.get_PIN_code() == PIN_code)
				{
					MyFile.close();
					return client;
				}

			}

			MyFile.close();

		}

		return _get_empty_client_obj();
	}

	static bool  is_client_exist(string account_num) {

		clsBankClient client = clsBankClient::find(account_num);
		return  !(client.is_empty());
	}

	static bool is_client_exist(string account_num, clsBankClient& target_client) {

		clsBankClient client = clsBankClient::find(account_num);

		if (!client.is_empty()) {
			target_client = client;
		}

		return !(client.is_empty());
	}

	void access_to_delete() {
		_mode = enMode::delete_client;
	};

	enSave_results save() {
		switch (_mode)
		{
		case clsBankClient::empty_mode:
			if (is_empty())
				return enSave_results::faild_to_save;

		case clsBankClient::update_mode:

			//// updating new client in database
			_update_client_in_data_base();
			return enSave_results::saved_successfully;

		case clsBankClient::add_new:

			///// check again if new client acc num is already exist 
			if (clsBankClient::is_client_exist(account_num)) {
				return enSave_results::faild_to_save;
			};

			//// adding new client to database
			_add_new_client();
			return enSave_results::new_client_was_add_succ;

		case clsBankClient::delete_client:

			///// check again if new client acc num is already exist 
			if (!clsBankClient::is_client_exist(account_num)) {
				return enSave_results::faild_to_save;
			};

			//// delete client from database
			_delete_client();
			return enSave_results::deleted_succ;
		default:
			break;
		}
	}

	static vector <clsBankClient> get_clients_list() {
		return _load_clients_data_from_file("clients.txt");
	}

	static double get_total_balances()
	{
		double total_balances = 0;
		vector <clsBankClient> clients_data = _load_clients_data_from_file("clients.txt");

		for (auto& client : clients_data)
		{
			total_balances += client.get_account_balance();
		}


		return total_balances;

	};

	void deposit(double amount) {
		_account_balance += amount;
		save();
	}

	bool is_amount_suitable_for_withdrawing(double amount) {
		return _account_balance >= amount;
	}

	void withdraw(double amount) {
		_account_balance -= amount;
		save();
	}

};

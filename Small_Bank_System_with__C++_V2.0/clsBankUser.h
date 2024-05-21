#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "clsPerson.h"
#include "clsUtility.h"
#include "clsString.h"
#include "global.h"

using namespace std;
class clsBankUser : public clsPerson
{
	enum enMode
	{
		empty_mode = 0,
		update_mode = 1,
		add_new = 2,
		delete_user = 3,
	};
	enMode _mode;
	string _user_name, _password;
	int _permissions = 0;
	string _file_name = "users.txt", _separator = "#//#";

	//// private methods


	static clsBankUser _convert_line_to_user_object(string line, string separator = "#//#")
	{
		vector<string> vUserData;
		vUserData = clsString::split(line, separator);

		return clsBankUser(enMode::update_mode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], clsUtility::decrypt(vUserData[5]), stod(vUserData[6]));

	}

	static string _convert_user_obj_to_line(clsBankUser user, string separator = "#//#") {
		string final_string = "";

		final_string += user.get_first_name() + separator;
		final_string += user.get_last_name() + separator;
		final_string += user.get_email() + separator;
		final_string += user.get_phone() + separator;
		final_string += user.get_user_name() + separator;
		///// encrypt passwords for security 
		final_string += clsUtility::encrypt(user.get_password()) + separator;
		final_string += to_string(user.get_permissions());
		return final_string;
	}

	static clsBankUser _get_empty_user_obj() {
		return clsBankUser(enMode::empty_mode, "", "", "", "", "", "", 0);
	};

	static vector<clsBankUser> _load_users_data_from_file(string file_name = "users.txt")
	{
		vector<clsBankUser> vUsers;

		fstream MyFile;
		MyFile.open(file_name, ios::in); // read Mode
		if (MyFile.is_open())
		{
			string Line;
			clsBankUser user = _get_empty_user_obj();
			while (getline(MyFile, Line))
			{
				user = clsBankUser::_convert_line_to_user_object(Line, "#//#");
				vUsers.push_back(user);
			}
			MyFile.close();
		}
		return vUsers;
	}

	/////  updating
	void _update_file_data(vector<string> users_data, string file_name = "users.txt")
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

	void _update_user_in_data_base() {

		vector <clsBankUser> _vUsers_data;
		_vUsers_data = _load_users_data_from_file(_file_name);


		for (clsBankUser& user : _vUsers_data)
		{
			if (user._user_name == get_user_name()) {
				user = *this;
			}

		}

		vector <string> _vUsers_data_str;

		for (clsBankUser& user : _vUsers_data)
		{
			_vUsers_data_str.push_back(this->_convert_user_obj_to_line(user, _separator));

		}

		_update_file_data(_vUsers_data_str, _file_name);



	};

	/////  adding
	void _add_data_line_to_file(string obj_as_line, string file_name = "users.txt")
	{
		fstream MyFile;
		MyFile.open(file_name, ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << obj_as_line << endl;

			MyFile.close();
		}

	}

	void _add_new_user() {
		_add_data_line_to_file(_convert_user_obj_to_line(*this, _separator), _file_name);
	};

	/////  deleting
	void _delete_user() {

		vector <clsBankUser> _vUsers_data;
		_vUsers_data = _load_users_data_from_file(_file_name);

		vector <string> _vUsers_data_str;

		for (clsBankUser& user : _vUsers_data)
		{
			if (!(user.get_user_name() == get_user_name()))
				_vUsers_data_str.push_back(this->_convert_user_obj_to_line(user, _separator));
		}

		_update_file_data(_vUsers_data_str, _file_name);


		*this = _get_empty_user_obj();


	};


public:

	//// constructor
	clsBankUser(enMode mode, string first_name, string last_name, string email, string phone, string user_name, string password, int permissions) : clsPerson(first_name, last_name, email, phone)
	{
		_mode = mode;
		_user_name = user_name;
		_password = password;
		_permissions = permissions;
		//mode = enMode::update_mode;
	};

	///// enums 
	enum enSave_results {
		faild_to_save = 0, saved_successfully = 1, new_user_was_add_succ = 2, deleted_succ = 3,
	};
	enum enPermissions {
		all = -1, clients_list = 1, add_new_client = 2, deletee_client = 4,
		update_client = 8, find_client = 16, tranactions = 32, manage_users = 64, login_register = 128,
	};


	///// setters
	void  set_user_name(string user_name) {
		_user_name = user_name;
	}
	void  set_password(string password) {
		_password = password;
	}
	void set_permissions(int permissions) {
		_permissions = permissions;
	}

	//// getters 
	string get_user_name() {
		return _user_name;
	}
	string get_password() {
		return _password;
	}
	int get_permissions() {
		return _permissions;
	}

	__declspec(property(get = get_user_name, put = set_user_name)) string user_name;
	__declspec(property(get = get_password, put = set_password)) string password;
	__declspec(property(get = get_permissions, put = set_permissions)) int permissions;

	//// Main methods

	static clsBankUser create_an_empty_user() {
		clsBankUser user = _get_empty_user_obj();
		return user;
	}

	static clsBankUser create_new_user_with_user_name(string user_name) {

		return clsBankUser(enMode::add_new, "", "", "", "", user_name, "", 0);
	}

	bool is_empty()
	{
		return _mode == enMode::empty_mode;
	};

	static clsBankUser find(string user_name)
	{


		fstream MyFile;
		MyFile.open("users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankUser user = _convert_line_to_user_object(Line);
				if (user.get_user_name() == user_name)
				{
					MyFile.close();
					return user;
				}

			}

			MyFile.close();

		}

		return _get_empty_user_obj();
	}

	static clsBankUser find(string user_name, string password)
	{


		fstream MyFile;
		MyFile.open("users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankUser user = _convert_line_to_user_object(Line);
				///// encrypt_num
				if (user.get_user_name() == user_name && user.get_password() == password)
				{
					MyFile.close();
					return user;
				}

			}

			MyFile.close();

		}

		return _get_empty_user_obj();
	}

	static bool  is_user_exist(string user_name) {

		clsBankUser user = clsBankUser::find(user_name);
		return  !(user.is_empty());
	}

	static bool is_user_exist(string user_name, clsBankUser& target_user) {

		clsBankUser user = clsBankUser::find(user_name);

		if (!user.is_empty()) {
			target_user = user;
		}

		return !(user.is_empty());
	}

	void access_to_delete() {
		_mode = enMode::delete_user;
	};

	enSave_results save() {
		switch (_mode)
		{
		case clsBankUser::empty_mode:
			if (is_empty())
				return enSave_results::faild_to_save;

		case clsBankUser::update_mode:

			//// updating new user in database
			_update_user_in_data_base();
			return enSave_results::saved_successfully;

		case clsBankUser::add_new:

			///// check again if new user acc num is already exist 
			if (clsBankUser::is_user_exist(user_name)) {
				return enSave_results::faild_to_save;
			};

			//// adding new user to database
			_add_new_user();
			return enSave_results::new_user_was_add_succ;

		case clsBankUser::delete_user:

			///// check again if new user acc num is already exist 
			if (!clsBankUser::is_user_exist(user_name)) {
				return enSave_results::faild_to_save;
			};

			//// delete user from database
			_delete_user();
			return enSave_results::deleted_succ;
		default:
			break;
		}
	}

	static vector <clsBankUser> get_users_list() {
		return _load_users_data_from_file("users.txt");
	}

	bool check_access_permission(enPermissions permission)
	{
		if (this->permissions == enPermissions::all)
			return true;

		if ((permission & this->permissions) == permission)
			return true;
		else
			return false;
	}


};


#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "clsBankUser.h"
#include "clsInputValidate.h"
#include "clsUtility.h"

using namespace std;

class clsUserMethods
{
private:

	static void _read_user_Data(clsBankUser& user) {

		cout << "\nEnter First Name: ";
		user.set_first_name(clsValidate<string>::read_string());
		cout << "\nEnter Last Name : ";
		user.set_last_name(clsValidate<string>::read_string());
		cout << "\nEnter Email: ";
		user.set_email(clsValidate<string>::read_string());
		cout << "\nEnter Phone: ";
		user.set_phone(clsValidate<string>::read_string());
		cout << "\nEnter Password: ";
		user.set_password(clsValidate<string>::read_string());
		cout << "\nEnter Permissions: ";
		user.set_permissions(_read_permissions_to_set());

	};

	static void _print_status(clsBankUser::enSave_results enResults) {
		cout << "\n_______________________________________________\n";
		switch (enResults)
		{
		case clsBankUser::new_user_was_add_succ:
			cout << "\nUser was Added successfully :-) \n";
			break;
		case clsBankUser::faild_to_save:
			cout << "\nField to update user data :-( \n";
			break;
		case clsBankUser::saved_successfully:
			cout << "\nUser was updated successfully :-) \n";
			break;
		case clsBankUser::deleted_succ:
			cout << "\nUser was deleted successfully :-) \n";
			break;
		default:
			break;
		}
		cout << "_______________________________________________\n";

	};

	static int _read_permissions_to_set()
	{

		int permissions = 0;
		char answer = 'n';


		cout << "\nDo you want to give full access? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			return -1;
		}

		cout << "\nDo you want to give access to : \n ";

		cout << "\nShow Client List? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{


			permissions += clsBankUser::enPermissions::clients_list;
		}

		cout << "\nAdd New Client? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsBankUser::enPermissions::add_new_client;
		}

		cout << "\nDelete Client? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsBankUser::enPermissions::deletee_client;
		}

		cout << "\nUpdate Client? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsBankUser::enPermissions::update_client;
		}

		cout << "\nFind Client? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsBankUser::enPermissions::find_client;
		}

		cout << "\nTransactions? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsBankUser::enPermissions::tranactions;
		}

		cout << "\nManage Users? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsBankUser::enPermissions::manage_users;
		}

		cout << "\nManage Login register? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsBankUser::enPermissions::login_register;
		}

		return permissions;

	}


public:

	////// main menu opreations 
	static void display_users_list()
	{
		vector<clsBankUser> users_data = clsBankUser::get_users_list();

		clsBankUser user = clsBankUser::create_an_empty_user();


		cout << "\n\t\t\t\t Users list (" << users_data.size() << ") Users(s)\t\t\t\t" << endl;
		cout << "--------------------------------------------------------------------------------------------" << endl;
		cout << "| User Name " << setw(21);
		cout << "| Password " << setw(29);
		cout << "| Permissions " << endl;
		cout << "--------------------------------------------------------------------------------------------\n\n";
		if (users_data.empty())
		{
			cout << "\n\t\t\t    there is no users in this system \t\t\t\t" << endl;
		}
		else
		{
			for (short i = 0; i < users_data.size(); i++)
			{
				user = users_data.at(i);
				cout << "| " << setw(20) << left << user.user_name;
				cout << "| " << setw(24) << left << user.password;
				cout << "| " << user.permissions << " \n";
			}
		}
		cout << "\n------------------------------------------------------------------------------------------\n\n";
	}

	static void add_new_user() {
		string user_name = "";
		bool is_user_exist = 1;

		//// find user acc info
		cout << "Please enter the user name : ";
		while (is_user_exist)
		{
			user_name = clsValidate<string>::read_string();
			is_user_exist = clsBankUser::is_user_exist(user_name);

			if (is_user_exist) {
				cout << "This user with user name < " << user_name << " > is already exist! try another one\n";
				cout << "Please enter the user name : ";
			}
		}

		///// perform adding new user 
		clsBankUser new_user = clsBankUser::create_new_user_with_user_name(user_name);
		_read_user_Data(new_user);

		print_user(new_user);

		clsBankUser::enSave_results enResults = new_user.save();

		_print_status(enResults);

	};

	static void delete_user() {

		string user_name = "";
		bool is_user_exist = 0;
		clsBankUser  target_user = clsBankUser::create_an_empty_user();

		//// find user acc info
		cout << "Please enter the user name : ";
		while (!is_user_exist)
		{
			user_name = clsValidate<string>::read_string();
			is_user_exist = clsBankUser::is_user_exist(user_name, target_user);

			if (!is_user_exist) {
				cout << "This user with user name < " << user_name << " > is not exist!\n";
				cout << "Please enter the user name : ";
			}
		}

		cout << "\nClient Data :";
		print_user(target_user);


		/////// ask user again if they sure to delete or not
		char sure_for_delete = 'N';
		cout << "Are you sure you want to delete this user? (Y/N) : ";
		cin >> sure_for_delete;

		if (sure_for_delete == 'N' || sure_for_delete == 'n') {
			return;
		}

		//////  give access to delete 
		target_user.access_to_delete();

		clsBankUser::enSave_results enResults = target_user.save();

		_print_status(enResults);

	};

	static void update_user() {

		string user_name = "";
		bool is_user_exist = 0;
		clsBankUser  target_user = clsBankUser::create_an_empty_user();

		//// find user acc info
		cout << "Please enter the user name : ";
		while (!is_user_exist)
		{
			user_name = clsValidate<string>::read_string();
			is_user_exist = clsBankUser::is_user_exist(user_name, target_user);

			if (!is_user_exist) {
				cout << "This user with user name < " << user_name << " > is not exist!\n";
				cout << "Please enter the user name : ";
			}
		}
		cout << "\nClient Data :";
		print_user(target_user);

		/////// ask user again if they sure to update or not
		char sure_for_update = 'N';
		cout << "\nAre you sure you want to update this user? (Y/N) : ";
		cin >> sure_for_update;

		if (sure_for_update == 'N' || sure_for_update == 'n') {
			return;
		}

		///////////
		cout << "\n__________________________\n";
		cout << "\nUpdating user Info \n";
		cout << "__________________________\n";

		_read_user_Data(target_user);

		clsBankUser::enSave_results enResults = target_user.save();

		_print_status(enResults);


		print_user(target_user);
	};

	static void find_user() {
		string user_name = "";
		bool is_user_exist = 0;
		clsBankUser  target_user = clsBankUser::create_an_empty_user();

		//// find user acc info
		cout << "Please enter the account number : ";
		while (!is_user_exist)
		{
			user_name = clsValidate<string>::read_string();
			is_user_exist = clsBankUser::is_user_exist(user_name, target_user);

			if (!is_user_exist) {
				cout << "This user with account number < " << user_name << " > is not exist!\n";
				cout << "Please enter the account number : ";
			}
		}
		cout << "\nClient was found :-)\n";
		print_user(target_user);
	};

	static void print_user(clsBankUser user)
	{
		cout << "\nUser Card:";
		cout << "\n__________________________";
		cout << "\nFirstName   : " << user.get_first_name();
		cout << "\nLastName    : " << user.get_last_name();
		cout << "\nFull Name   : " << user.full_name();
		cout << "\nEmail       : " << user.get_email();
		cout << "\nPhone       : " << user.get_phone();
		cout << "\nUser Name   : " << user.get_user_name();
		cout << "\nPassword    : " << user.get_password();
		cout << "\nPermissions : " << user.get_permissions();
		cout << "\n__________________________\n";

	}


};


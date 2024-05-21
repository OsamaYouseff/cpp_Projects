#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsUtility.h"
#include "clsScreenHeader.h"
#include "clsBankUser.h"
#include "global.h"
#include "clsMainMenu.h"
#include "clsString.h"
using namespace std;

class clsLoginScreen : protected clsScreenHeader
{
private:
	static void _run_login() {
		bool is_login_failed = false;
		string user_name, password;
		int num_of_tries = 3;

		do
		{

			cout << "Enter User Name : ";
			getline(cin >> ws, user_name);

			cout << "Enter Password : ";
			cin >> password;

			is_login_failed = clsBankUser::is_user_exist(user_name, logged_user);

			if (!is_login_failed) {
				cout << "\nWrong username or password try again\n";
				num_of_tries--;
				cout << "You have only " << num_of_tries << " To login \n\n";
			}

			///// means that user has entered wrong data for3 times
			if (num_of_tries == 0) {
				system("cls");
				stop_app_after_three_tries = true;
				return;
			}

		} while (!is_login_failed);


		///// show logged user data
		//cout << "\n$$ Welcome, " << logged_user.full_name() << " $$\n";
		//cout << "\nLogged User info \n";
		//clsUserMethods::print_user(logged_user);
		//cout << "\nPress any key to continue..\n";
		//system("pause>0");

		register_log_info();
		clsMainMenu::show_main_menu();

	}

	static void _save_log_to_file(string users_data, string file_name = "users_logs.txt")
	{
		fstream users;

		users.open(file_name, ios::out | ios::app); /// append mode

		if (users.is_open())
		{
			users << users_data << "\n";
			users.close();
		}
	}


public:

	static void register_log_info() {
		string line_of_log_info = "";

		vector <string> logged_infos;

		logged_infos.push_back(clsDate::get_current_date_and_time_in_str());
		logged_infos.push_back(logged_user.get_user_name());
		logged_infos.push_back(clsUtility::encrypt(logged_user.get_password()));
		logged_infos.push_back(to_string(logged_user.get_permissions()));

		line_of_log_info = clsString::join(logged_infos, "#//#");

		_save_log_to_file(line_of_log_info, "users_logs.txt");

	}



	static void show_login_screen() {
		system("cls");
		_draw_screen_header("Login Screen");
		_run_login();
	};

};


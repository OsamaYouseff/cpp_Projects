#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreenHeader.h"
#include "clsInputValidate.h"
#include "clsUserMethods.h"
using namespace std;

class clsManageUserMenu : protected clsScreenHeader
{
	enum enUser_menu_options { users_list = 1, add_new_user = 2, delete_user = 3, update_user = 4, find_user = 5, main_menu = 6 };

	static int _read_user_menu_options()
	{
		int Choice = clsValidate<int>::read_number_in_range("Please Enter number between [1:6] : ", "This input not valid try another one\n", 1, 6);
		return Choice;
	}

	static void _go_back_to_manage_users_menu() {
		cout << "\nPress any key to go back to Manage Users Menu...\n";
		system("pause>0");
		_clear_screen();
		show_manage_users_menu();
	}

	static void _clear_screen() {
		system("cls");
	}

	///////////

	static void _users_list() {
		_clear_screen();
		_draw_screen_header("Users List");
		clsUserMethods::display_users_list();
	};

	static void _add_new_user() {

		_clear_screen();
		_draw_screen_header("Add New User screen ");
		clsUserMethods::add_new_user();

	};

	static void _delete_user() {
		_clear_screen();
		_draw_screen_header("Delete User screen ");
		clsUserMethods::delete_user();
	};

	static void _update_user() {
		_clear_screen();
		_draw_screen_header("Update User screen ");
		clsUserMethods::update_user();
	};

	static void _find_user() {
		_clear_screen();
		_draw_screen_header("Find User screen ");
		clsUserMethods::find_user();
	};


	//////////


	static void _perform_user_menu_options(enUser_menu_options options) {

		switch (options)
		{
		case clsManageUserMenu::users_list:
			_users_list();
			_go_back_to_manage_users_menu();
			break;
		case clsManageUserMenu::add_new_user:

			_add_new_user();
			_go_back_to_manage_users_menu();
			break;
		case clsManageUserMenu::delete_user:

			_delete_user();
			_go_back_to_manage_users_menu();
			break;
		case clsManageUserMenu::update_user:

			_update_user();
			_go_back_to_manage_users_menu();
			break;
		case clsManageUserMenu::find_user:

			_find_user();
			_go_back_to_manage_users_menu();
			break;
		case clsManageUserMenu::main_menu:
			break;
		default:
			break;
		}

	}

public:

	static void show_manage_users_menu()
	{
		system("cls");
		cout << "\n===================================================\n";
		cout << "\t\tManage Users Menu\t\t\t";
		cout << "\n===================================================\n";
		cout << "[ 1 ] Users List.\n";
		cout << "[ 2 ] Add new user.\n";
		cout << "[ 3 ] Delete user.\n";
		cout << "[ 4 ] Update user.\n";
		cout << "[ 5 ] Find User.\n";
		cout << "[ 6 ] Main Menu.\n";
		cout << "===================================================\n";

		_perform_user_menu_options((enUser_menu_options)_read_user_menu_options());
	}

};


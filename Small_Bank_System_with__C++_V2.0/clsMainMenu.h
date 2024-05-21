#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreenHeader.h"
#include "clsInputValidate.h"
#include "clsClientMethods.h"
#include "clsTransactionsMenu.h"
#include "clsManageUserMenu.h"
#include "clsRegisterLoginScreen.h"
#include "global.h"
#include "clsCurrencyExchangeMenu.h"


using namespace std;


class clsMainMenu : protected clsScreenHeader
{
private:
	enum enMain_menu_choices { show_clients_list = 1, add_new_client = 2, delete_client = 3, update_client = 4, find_client = 5, transactions_menu = 6, manage_users = 7, login_register = 8,currency_exchange = 9 , logout = 10 };

	static int _read_main_menu_option()
	{
		int Choice = clsValidate<int>::read_number_in_range("Please Enter number between [1:10] : ", "This input not valid try another one\n", 1, 10);
		return Choice;
	}

	static void _go_back_to_the_main_menu() {
		cout << "\nPress any key to go back to Main Menu...\n";
		system("pause>0");
		_clear_screen();
		show_main_menu();
	}

	static void _clear_screen() {
		system("cls");
	}

	static void _show_clients_list() {
		system("cls");
		_draw_screen_header("Clients List");
		clsClientMethods::display_clients_list();
	}

	static void _add_new_client() {
		//cout << "this operation is under developing !" << endl;
		system("cls");
		_draw_screen_header("Add New Client Screen");
		clsClientMethods::add_new_client();
	}

	static void _delete_client() {
		//cout << "this operation is under developing !" << endl;
		system("cls");
		_draw_screen_header("Delete Client Screen");
		clsClientMethods::delete_client();
	}

	static void _update_client() {
		//cout << "this operation is under developing !" << endl;
		system("cls");
		_draw_screen_header("Update Client Screen");
		clsClientMethods::update_client();

	}

	static void _find_client() {
		//cout << "this operation is under developing !" << endl;
		system("cls");
		_draw_screen_header("Find Client Screen");
		clsClientMethods::find_client();
	}

	static void _transactions_menu() {
		clsTransactionsMenu::show_transactions_menu();
	}

	static void _manage_users() {
		//cout << "this operation is under developing !" << endl;
		clsManageUserMenu::show_manage_users_menu();
	}

	static void _show_login_register_screen() {
		_clear_screen();
		clsRegisterLoginScreen::display_register_info();
	}

	static void _logout() {
		//cout << "this operation is under developing !" << endl;
		_clear_screen();
		logged_user = clsBankUser::create_an_empty_user();
	}

	static void _perform_main_menu_options(enMain_menu_choices choice) {


		switch (choice)
		{
		case clsMainMenu::show_clients_list:
			//// check if user has this permission or not -> if not display decline access message 
			if (display_access_permission(clsBankUser::enPermissions::clients_list))
			{
				_show_clients_list();
			}
			_go_back_to_the_main_menu();
			break;
		case clsMainMenu::add_new_client:
			//// check if user has this permission or not -> if not display decline access message 
			if (display_access_permission(clsBankUser::enPermissions::add_new_client))
			{
				_add_new_client();
			}
			_go_back_to_the_main_menu();
			break;
		case clsMainMenu::delete_client:
			//// check if user has this permission or not -> if not display decline access message 
			if (display_access_permission(clsBankUser::enPermissions::deletee_client))
			{
				_delete_client();
			}

			_go_back_to_the_main_menu();
			break;
		case clsMainMenu::update_client:
			//// check if user has this permission or not -> if not display decline access message 
			if (display_access_permission(clsBankUser::enPermissions::update_client))
			{
				_update_client();
			}
			_go_back_to_the_main_menu();
			break;
		case clsMainMenu::find_client:

			//// check if user has this permission or not -> if not display decline access message 
			if (display_access_permission(clsBankUser::enPermissions::find_client))
			{
				_find_client();
			}
			_go_back_to_the_main_menu();
			break;
		case clsMainMenu::transactions_menu:

			//// check if user has this permission or not -> if not display decline access message 
			if (display_access_permission(clsBankUser::enPermissions::tranactions))
			{
				_transactions_menu();
			}

			_go_back_to_the_main_menu();
			break;
		case clsMainMenu::manage_users:
			//// check if user has this permission or not -> if not display decline access message 
			if (display_access_permission(clsBankUser::enPermissions::manage_users))
			{
				_manage_users();
			}
			_go_back_to_the_main_menu();
			break;
		case clsMainMenu::login_register:
			//// check if user has this permission or not -> if not display decline access message 
			if (display_access_permission(clsBankUser::enPermissions::login_register))
			{
				_show_login_register_screen();
			}
			_go_back_to_the_main_menu();
			break;

		case clsMainMenu::currency_exchange : 
			clsCurrencyExchangeMenu::show_currency_menu();
			break;

		case clsMainMenu::logout:
			_logout();
			break;
		default:
			break;
		}
	}

public:


	static void show_main_menu()
	{

		system("cls");
		_draw_screen_header("Main Screen");

		cout << "===========================================\n";
		cout << "\t\t Main Menu\n";
		cout << "===========================================\n";
		cout << "[1] Show Client List.\n";
		cout << "[2] Add New Client.\n";
		cout << "[3] Delete Client.\n";
		cout << "[4] Update Client Info.\n";
		cout << "[5] Find Client.\n";
		cout << "[6] Transactions.\n";
		cout << "[7] Manage Users.\n";
		cout << "[8] Register Login.\n";
		cout << "[9] Currency Exchange.\n";
		cout << "[10] Logout.\n";
		cout << "===========================================\n";

		_perform_main_menu_options((enMain_menu_choices)_read_main_menu_option());
	}

};


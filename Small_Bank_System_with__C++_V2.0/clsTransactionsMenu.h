#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreenHeader.h"
#include "clsInputValidate.h"
#include "clsClientMethods.h"
//#include "clsMainMenu.h"

using namespace std;

class clsTransactionsMenu : protected clsScreenHeader
{

private:
	enum enTransactions_menu_options
	{
		eDeposit = 1,
		eWithdraw = 2,
		eShowTotalBalance = 3,
		eTransfer = 4,
		eShow_transfer_logs_list = 5,
		eShowMainMenu = 6,
	};

	static int _read_transactions_menu_options()
	{
		int Choice = clsValidate<int>::read_number_in_range("Please Enter number between [1:6] : ", "This input not valid try another one\n", 1, 6);
		return Choice;
	}

	static void _go_back_to_the_transactions_menu() {
		cout << "\nPress any key to go back to Transactions Menu...\n";
		system("pause>0");
		_clear_screen();
		show_transactions_menu();
	}

	static void _clear_screen() {
		system("cls");
	}

	static void _perform_transactions_menu_options(enTransactions_menu_options choice) {


		switch (choice)
		{
		case enTransactions_menu_options::eDeposit:
			_clear_screen();
			_draw_screen_header("Deposit screen ");
			clsClientMethods::show_deposit_screen();
			_go_back_to_the_transactions_menu();
			break;
		case enTransactions_menu_options::eWithdraw:
			_clear_screen();
			_draw_screen_header("Withdraw screen ");
			clsClientMethods::show_withdraw_screen();
			_go_back_to_the_transactions_menu();
			break;
		case enTransactions_menu_options::eShowTotalBalance:
			_clear_screen();
			_draw_screen_header("Total Balances screen ");
			clsClientMethods::show_total_balances_screen();
			_go_back_to_the_transactions_menu();
			break;
		case enTransactions_menu_options::eTransfer:
			_clear_screen();
			_draw_screen_header("Transfer screen ");
			clsClientMethods::show_transfer_screen();
			_go_back_to_the_transactions_menu();
			break;
		case enTransactions_menu_options::eShow_transfer_logs_list:
			_clear_screen();
			_draw_screen_header("Transfer Logs List screen ");
			clsClientMethods::display_transfer_logs_list();
			_go_back_to_the_transactions_menu();
			break;
		case enTransactions_menu_options::eShowMainMenu:
			_clear_screen();
			break;
		default:
			break;
		}

	};


public:

	static void show_transactions_menu() {
		system("cls");
		cout << "\n===================================================\n";
		cout << "\t\tTransactions Menu\t\t\t";
		cout << "\n===================================================\n";
		cout << "[ 1 ] Deposit.\n";
		cout << "[ 2 ] withdraw.\n";
		cout << "[ 3 ] Total Balances.\n";
		cout << "[ 4 ] Transfer.\n";
		cout << "[ 5 ] Transfer Logs List.\n";
		cout << "[ 6 ] Main Menu.\n";
		cout << "===================================================\n";


		_perform_transactions_menu_options((enTransactions_menu_options)_read_transactions_menu_options());

	}



};


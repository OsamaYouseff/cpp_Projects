#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsInputValidate.h"
#include "clsScreenHeader.h"
#include "clsCurrencyScreen.h"

using namespace std;

class clsCurrencyExchangeMenu : protected clsScreenHeader
{
	enum enCurrency_options { currencies_list = 1, find_currency = 2, update_rate = 3, currency_calculator = 4, main_menu };
	static int _read_currency_menu_option()
	{
		int Choice = clsValidate<int>::read_number_in_range("Please Enter number between [1:5] : ", "This input not valid try another one\n", 1, 5);
		return Choice;
	}
	
	static void _clear_screen() {
		system("cls");
	}

	static void _go_back_to_the_currency_menu() {
		cout << "\nPress any key to go back to Main Menu...\n";
		system("pause>0");
		_clear_screen();
		show_currency_menu();
	}

	/////////////////

	static void _currencies_list() {
		_clear_screen();
		_draw_screen_header("Currency List Screen");
		clsCurrencyScreen::display_currencies_list();
	}

	static void _find_currency() {
		_clear_screen();
		_draw_screen_header("Find Currency screen");
		clsCurrencyScreen::find_currency();
	}

	static void _update_rate() {
		_clear_screen();
		_draw_screen_header("Update Currency screen");
		clsCurrencyScreen::update_currency_ex_rate();
	}

	static void _currency_calculator() {
		_clear_screen();
		_draw_screen_header("Currency Calculator screen");
		clsCurrencyScreen::currency_calculator();
	}


	////////////////

	static void _perform_currency_menu_options(enCurrency_options choice)
	{
		switch (choice)
		{
		case clsCurrencyExchangeMenu::currencies_list:
			_currencies_list();

			_go_back_to_the_currency_menu();
			break;
		case clsCurrencyExchangeMenu::find_currency:
			_find_currency();
			_go_back_to_the_currency_menu();
			break;
		case clsCurrencyExchangeMenu::update_rate:
			_update_rate();
			_go_back_to_the_currency_menu();
			break;
		case clsCurrencyExchangeMenu::currency_calculator:
			_currency_calculator();
			_go_back_to_the_currency_menu();
			break;
		case clsCurrencyExchangeMenu::main_menu:
			//_go_back_to_the_currency_menu();
			break;
		default:
			break;
		}

	}
public:


	static void show_currency_menu() {

		system("cls");
		_draw_screen_header("Currency Exchange Screen");

		cout << "===========================================\n";
		cout << "\t   Currency Exchange Menu\n";
		cout << "===========================================\n";
		cout << "[1] Currencies List.\n";
		cout << "[2] Find Currency.\n";
		cout << "[3] Update Currency.\n";
		cout << "[4] Currency Calculator.\n";
		cout << "[5] Main menu. \n";
		cout << "===========================================\n";
		_perform_currency_menu_options((enCurrency_options)_read_currency_menu_option());
	}



};


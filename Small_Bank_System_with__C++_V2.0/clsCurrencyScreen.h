#pragma once
#include <iostream>
#include <string>
#include "clsCurrency.h"
#include "clsInputValidate.h"
using namespace std;
class clsCurrencyScreen
{
private:
	static void  _show_results(clsCurrency currency) {
		if (currency.is_empty())
		{
			cout << "this code is not exist !!\n";
		}
		else {
			cout << "currency was found :-)\n";
			print_currency_info(currency);
		}
	}
	
	static float _read_rate() 
	{
		float new_rate;
		cout << "Enter new rate : ";
		new_rate = clsValidate<float>::read_a_positive_number();
		return new_rate;
	}
	
	static void  _read_currency_code(string &code , string msg) {
		bool is_currency_exist = false;

		while (!is_currency_exist)
		{
			cout << msg;
			getline(cin >> ws, code);

			is_currency_exist = clsCurrency::is_currency_exist(code);

			if (!is_currency_exist)
				cout << "this code is not exist !!\n";

		}
	}
	
	static void _print_calculations_results(float amount, clsCurrency currency1, clsCurrency currency2)
	{
		float final_exchange = 0;

		cout << "Converting from " << currency1.currency_name() << "\n";
		print_currency_info(currency1);

		cout << "\n\n";

		final_exchange = currency1.convert_to_USD(amount);

		if (currency2.currency_code() == "usd") {
			cout << "Converting to " << currency2.currency_name() << "\n";
			print_currency_info(currency2);

			cout << "\n-------------------------------------------\n";
			cout << amount << " " << currency1.currency_code() << " = " << final_exchange << " " << currency2.currency_code() ;
			cout << "\n-------------------------------------------\n";
		}
		else {
			cout << "\n-------------------------------------------\n";
			cout << amount << " " << currency1.currency_code() << " = " << final_exchange << " USD ";
			cout << "\n-------------------------------------------\n";

			cout << "\n\n";

			////// convert value from usd to second currency 
			final_exchange = currency1.convert_to_other_currency(amount, currency2);

			cout << "Converting to " << currency2.currency_name() << "\n";
			print_currency_info(currency2);

			cout << "\n-------------------------------------------\n";
			cout << amount << " " << currency1.currency_code() << " = " << final_exchange << " " << currency2.currency_code();
			cout << "\n-------------------------------------------\n\n";
			cout << "\n\n";
		}

	}
	
public:

	static void print_currency_info(clsCurrency currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << currency.country();
		cout << "\nCode       : " << currency.currency_code();
		cout << "\nName       : " << currency.currency_name();
		cout << "\nRate(1$) = : " << currency.ex_rate();

		cout << "\n_____________________________\n";

	}

	static void display_currencies_list() {

		vector <clsCurrency> currencies = clsCurrency::get_currencies_list();

		clsCurrency currency = clsCurrency::get_empty_currency_object();

		cout << "\n\n--------------------------------------------------------------------------------------------------------------------\n";
		cout << "| Country " << setw(32);
		cout << "| Code " << setw(12);
		cout << "| Name " << setw(55);
		cout << "| Ex Rate($) " << setw(33);
		cout << "\n--------------------------------------------------------------------------------------------------------------------\n\n";
		if (currencies.empty())
		{
			cout << "\n\t\t\t    there is no exchange rate in this system \t\t\t\t" << endl;
		}
		else
		{
			for (short i = 0; i < currencies.size(); i++)
			{
				currency = currencies.at(i);

				cout << "| " << setw(33) << left << currency.country();
				cout << "| " << setw(10) << left << currency.currency_code();
				cout << "| " << setw(50) << left << currency.currency_name();
				cout << "| " << setw(13) << left << currency.ex_rate() << "\n";
			}
		}
		cout << "--------------------------------------------------------------------------------------------------------------------\n\n";
	}

	static void find_currency() {

		int user_choice = clsValidate<int>::read_number_in_range("Please choice to find by [1] code or [2] country : " , "You have to choice one of these only!! ",1,2);
		if (user_choice == 1) {
			string code = "";
			cout << "Please Enter the code : ";
			getline(cin >> ws, code);
			clsCurrency currency = clsCurrency::find_by_code(code);
			_show_results(currency);
		}
		if (user_choice == 2) {
			string country_name = "";
			cout << "Please Enter the country name : ";
			getline(cin >> ws, country_name);
			clsCurrency currency = clsCurrency::find_by_country(country_name);
			_show_results(currency);
		}

		

	}

	static void update_currency_ex_rate() {
		clsCurrency currency = clsCurrency::get_empty_currency_object();
		string code = "";
		
		//////// using first method to ensure that currency is exist
		//while (currency.is_empty())
		//{
		//	cout << "Please Enter currency code : ";
		//	getline(cin >> ws, code);
		//	currency = clsCurrency::find_by_code(code);

		//	if (currency.is_empty())
		//		cout << "this code is not exist !!\n";

		//}
		// 
		//////// using second method to ensure that currency is exist
		
		do
		{
			cout << "Please Enter currency code : ";
			getline(cin >> ws, code);

			currency = clsCurrency::find_by_code(code);

			if (currency.is_empty())
				cout << "this code is not exist !!\n";

		} while (currency.is_empty());



		print_currency_info(currency);

		char want_to_change = 'n';

		cout << "Are you sure that you want to change this currency rate? (y/n) : ";

		cin >> want_to_change;
		cin.ignore();


		if (want_to_change == 'y' || want_to_change == 'Y')
		{
			cout << "\n\n__________________________________\n";

			cout << "Update New rate \n";
			cout << "__________________________________\n\n";

			currency.update_rate(_read_rate());

			cout << "Currency rate was updated successfully.";

			print_currency_info(currency);

		}
		else
			cout << "Updating Opreation was canceled\n";

		


	}

	static void currency_calculator() {

		string code1 = "" , code2 = "";
		float amount = 0  ;
		

		_read_currency_code(code1, "Please Enter the first currency code : ");
		clsCurrency currency1 = clsCurrency::find_by_code(code1 );

		cout << "\n\n";

		_read_currency_code(code2 , "Please Enter the second currency code : ");
		clsCurrency currency2 = clsCurrency::find_by_code(code2);

		cout << "\n\n";

		cout << "Please Enter the amount of exchange : ";
		amount = clsValidate<float>::read_a_positive_number();

		cout << "\n\n";

		_print_calculations_results(amount, currency1, currency2);

	};


};


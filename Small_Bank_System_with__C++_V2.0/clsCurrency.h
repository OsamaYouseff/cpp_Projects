#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"

using namespace std;

class clsCurrency
{
	enum enMode { empty_mode = 1, update_mode };

	enMode _mode;
	string _country;
	string _currency_code;
	string _currency_name;
	float _ex_rate;


	static clsCurrency _convert_line_to_currency_object(string line, string separator = "#//#")
	{
		vector<string> vCurrencyData;
		vCurrencyData = clsString::split(line, separator);

		return clsCurrency(enMode::update_mode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],
			stod(vCurrencyData[3]));

	}

	static string _convert_currency_object_to_line(clsCurrency currency, string separator = "#//#")
	{

		string stCurrencyRecord = "";
		stCurrencyRecord += currency.country() + separator;
		stCurrencyRecord += currency.currency_code() + separator;
		stCurrencyRecord += currency.currency_name() + separator;
		stCurrencyRecord += to_string(currency.ex_rate());

		return stCurrencyRecord;

	}

	static vector <clsCurrency> _load_currencies_data_from_file(string file_name = "currencies.txt")
	{
		vector <clsCurrency> vCurrencies;

		fstream MyFile;
		MyFile.open(file_name, ios::in);//read Mode

		if (MyFile.is_open())
		{

			string line;

			while (getline(MyFile, line))
			{

				clsCurrency Currency = _convert_line_to_currency_object(line);

				vCurrencies.push_back(Currency);
			}

			MyFile.close();

		}

		return vCurrencies;

	}

	static void _save_currency_data_to_file(vector <clsCurrency> vCurrencies)
	{

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsCurrency C : vCurrencies)
			{
				DataLine = _convert_currency_object_to_line(C);
				MyFile << DataLine << endl;



			}

			MyFile.close();

		}

	}

	void _update() {
		vector <clsCurrency> _vCurrencies;
		_vCurrencies = _load_currencies_data_from_file();

		for (clsCurrency& c : _vCurrencies)
		{
			if (c.currency_code() == currency_code())
			{
				c = *this;
				break;
			}

		}

		_save_currency_data_to_file(_vCurrencies);
	};

	static clsCurrency _get_empty_currency_object()
	{
		return clsCurrency(enMode::empty_mode, "", "", "", 0);
	}

public:
	//// constructor
	clsCurrency(enMode mode, string country, string currency_code, string currency_name, float ex_rate) {
		_mode = mode;
		_country = country;
		_currency_code = currency_code;
		_currency_name = currency_name;
		_ex_rate = ex_rate;
	}

	///// getters 

	string country() {
		return _country;
	}
	string currency_code() {
		return _currency_code;
	}
	string currency_name() {
		return _currency_name;
	}
	float  ex_rate() {
		return _ex_rate;
	}

	///// setters 

	bool is_empty() {
		return (_mode == enMode::empty_mode);
	}

	void update_rate(float new_rate) {
		_ex_rate = new_rate;
		_update();
	}

	static clsCurrency find_by_code(string currency_code)
	{

		currency_code = clsString::make_string_uppercase(currency_code);

		fstream MyFile;
		//// to-do : make file name variable
		MyFile.open("Currencies.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _convert_line_to_currency_object(Line);
				if (Currency.currency_code() == currency_code)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();

		}

		return _get_empty_currency_object();

	}

	static clsCurrency find_by_country(string country)
	{
		country = clsString::make_string_uppercase(country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsCurrency currency = _convert_line_to_currency_object(line);
				if (clsString::make_string_uppercase(currency.country()) == country)
				{
					MyFile.close();
					return currency;
				}

			}

			MyFile.close();

		}

		return _get_empty_currency_object();

	}

	static bool is_currency_exist(string currency_code)
	{
		clsCurrency C1 = clsCurrency::find_by_code(currency_code);
		return (!C1.is_empty());

	}

	static vector <clsCurrency> get_currencies_list()
	{
		return _load_currencies_data_from_file();
	}

	static clsCurrency get_empty_currency_object()
	{
		return _get_empty_currency_object();
	}

	float   convert_to_USD(float amount) {
		return  (amount / ex_rate() );
	}

	float   convert_to_other_currency(float amount , clsCurrency other_currency) {
		float usd_amount = convert_to_USD(amount);

		////// if other curreny  is USD don't do anything because you already convvert to USD before
		if (other_currency.currency_code() == "USD")
		{
			return usd_amount;
		}
		///// else convert normally
		return (float)(usd_amount * other_currency.ex_rate());
	}




};






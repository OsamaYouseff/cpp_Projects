#pragma once

#include <iostream>
#include <string>
#include "clsPeriod.h"
#include <cmath>
#include "ClsDate.h"
using namespace std;

template <class T>

class clsValidate
{

public:
	static bool is_num_between(T target_num, T range_from, T range_to)
	{
		return target_num >= range_from && target_num <= range_to;
	}

	static bool is_date_between(clsDate target_date, clsDate date_from, clsDate date_to)
	{
		return ((clsDate::is_date1_after_date2(target_date, date_from) || clsDate::is_first_date_equal_sec_date2(target_date, date_from)) && clsDate::is_first_date_before_sec_date2(target_date, date_to) || clsDate::is_first_date_equal_sec_date2(target_date, date_to));
	}

	static T read_number(string asking_msg, string wrong_msg)
	{
		T input_num;
		cout << asking_msg;
		cin >> input_num;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			// cout << "Invalid number please Enter a valid number : ";
			cout << wrong_msg;
			cout << asking_msg;
			cin >> input_num;
		};

		return input_num;
	};



	static T read_number(string wrong_msg)
	{
		T input_num;
		cin >> input_num;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			// cout << "Invalid number please Enter a valid number : ";
			cout << wrong_msg;
			cin >> input_num;
		};

		return input_num;
	};

	static T read_number_in_range(string asking_msg, string wrong_msg, T from, T to)
	{
		T input_num;
		cout << asking_msg;
		cin >> input_num;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			// cout << "Invalid number please Enter a valid number : ";
			cout << wrong_msg;
			cout << asking_msg;
			cin >> input_num;
		};

		while (!(input_num >= from && input_num <= to))
		{
			cout << wrong_msg;
			cout << asking_msg;
			cin >> input_num;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		return input_num;
	};





	static double read_double_number(string asking_msg, string wrong_msg)
	{
		double input_num;
		cout << asking_msg;
		cin >> input_num;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			// cout << "Invalid number please Enter a valid number : ";
			cout << wrong_msg;
			cout << asking_msg;
			cin >> input_num;
		};

		///// to force user enter number with decimal like this 44.3 or 1.4
		// while (floor(input_num) == input_num)
		//{

		//	cout << wrong_msg;
		// cout << asking_msg;
		//	cin >> input_num;
		//}

		return input_num;
	};

	static double read_double_number_in_range(string asking_msg, string wrong_msg, double from, double to)
	{
		double input_num;
		cout << asking_msg;
		cin >> input_num;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			// cout << "Invalid number please Enter a valid number : ";
			cout << wrong_msg;
			cout << asking_msg;
			cin >> input_num;
		};

		///// to force user enter number with decimal like this 44.3 or 1.4
		// while (floor(input_num) == input_num || !(input_num >= from && input_num <= to))
		// {

		// 	cout << wrong_msg;
		// cout << asking_msg;
		// 	cin >> input_num;

		// 	cin.clear();
		// 	cin.ignore(numeric_limits<streamsize>::max(), '\n');
		// }

		while (!(input_num >= from && input_num <= to))
		{

			cout << wrong_msg;
			cout << asking_msg;
			cin >> input_num;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		return input_num;
	};

	static float read_float_num()
	{
		float input_num;

		cin >> input_num;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> input_num;
		};

		return input_num;
	};
	 
	static bool is_a_valid_date(clsDate target)
	{
		return clsDate::check_is_date_valid_best(target);
	}

	static string read_string()
	{
		string S1 = "";
		getline(cin >> ws, S1);
		return S1;
	}

	static T read_a_positive_number()
	{
		float num;
		do
		{
			cin >> num;
		} while (num <= 0);
		return num;
	}
};

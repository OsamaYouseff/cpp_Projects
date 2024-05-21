#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include <vector>
#include "clsString.h"
using namespace std;

class clsDate
{
private:
	int _day, _month, _year;
	string _full_date;

	void fill_current_Day()
	{
		time_t time_now = time(0); // get time now

		tm* now = localtime(&time_now);

		_year = now->tm_year + 1900;
		_month = now->tm_mon + 1;
		_day = now->tm_mday;

		_full_date = to_string(_day) + "/" + to_string(_month) + "/" + to_string(_year);
	};

public:
	////// contactor Functions

	clsDate()
	{
		fill_current_Day();
	};

	clsDate(string full_date)
	{
		vector<string> vfull_date = clsString::split(full_date, "/");
		_day = stoi(vfull_date[0]);
		_month = stoi(vfull_date[1]);
		_year = stoi(vfull_date[2]);
		_full_date = full_date;
	};

	clsDate(int day, int month, int year)
	{
		_day = day;
		_month = month;
		_year = year;
		_full_date = to_string(_day) + "/" + to_string(_month) + "/" + to_string(_year);
	};

	clsDate(int days, int year)
	{
		_full_date = get_date_from_day_num(days, year);
		vector<string> vfull_date = clsString::split(_full_date, "/");
		_day = stoi(vfull_date[0]);
		_month = stoi(vfull_date[1]);
		_year = stoi(vfull_date[2]);
	}

	//// setters

	void set_day(int day)
	{
		_day = day;
	}
	void set_month(int month)
	{
		_month = month;
	}
	void set_year(int year)
	{
		_year = year;
	}

	//// getters
	int get_day()
	{
		return _day;
	}
	int get_month()
	{
		return _month;
	}
	int get_year()
	{
		return _year;
	}

	__declspec(property(get = get_day, put = set_day)) int(day);
	__declspec(property(get = get_month, put = set_month)) int(month);
	__declspec(property(get = get_year, put = set_year)) int(year);

	//// methods
	static bool is_leap(int year)
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	};
	///// ---------------------------------------------------------------
	static int read_a_positive_number(string msg)
	{
		int num;
		do
		{
			cout << msg;
			cin >> num;
		} while (num <= 0);
		return num;
	}

	bool is_date_year_leap()
	{
		return is_leap(_year);
	}
	///// ---------------------------------------------------------------

	static string get_current_time_in_str()
	{
		string full_time = "";
		time_t time_now = time(0); // get time now
		tm* now = localtime(&time_now);
		full_time = to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec);
		return  full_time;
	}

	///// ---------------------------------------------------------------

	static string get_current_date_and_time_in_str() {
		return (clsDate::get_full_date(clsDate()) + " - " + get_current_time_in_str());
	}

	///// ---------------------------------------------------------------
	void print()
	{
		cout << _full_date << endl;
		;
	}
	///// ---------------------------------------------------------------
	static string get_full_date(clsDate date)
	{
		return to_string(date._day) + "/" + to_string(date._month) + "/" + to_string(date._year);
	};

	string get_full_date()
	{
		return get_full_date(*this);
	}

	///// ---------------------------------------------------------------
	static int day_of_week_order(int day, int month, int year)
	{
		float a = (static_cast<float>(14) - month) / 12;
		float y = year - a;
		float m = month + (12 * a) - 2;
		int d = int(day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
		return d;
	};

	int day_of_week_order()
	{
		return day_of_week_order(_day, _month, _year);
	};
	///// ---------------------------------------------------------------

	string get_day_name_of_week(int day, int month, int year)
	{
		string arr_of_days_name[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursdays", "Friday", "Saturday" };
		int day_order = day_of_week_order(day, month, year);

		cout << "Date : " << day << "/" << month << "/" << year << endl;
		cout << "Day order : " << day_order << endl;
		cout << "Day name : " << arr_of_days_name[day_order] << endl;
		return arr_of_days_name[day_order];
	};

	///// ---------------------------------------------------------------
	static int get_month_len(int month, int year)
	{
		short days_in_month[]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		bool leap = is_leap(year);
		if (leap)
			days_in_month[1] = 29;
		return days_in_month[month - 1];
	};

	int get_month_len()
	{
		return get_month_len(_month, _year);
	};
	///// ---------------------------------------------------------------

	///// ---------------------------------------------------------------
	static string get_month_name(int month)
	{
		string months[] = { " ", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return months[month];
	};

	string get_month_name()
	{
		return get_month_name(_month);
	};

	///// ---------------------------------------------------------------
private:
	static void print_month_calendar(int day_order, string month_name, int month_len)
	{

		cout << "\n____________________ " << month_name << " ____________________\n\n";
		cout << setw(6) << "Sun" << setw(6) << "Mon" << setw(6) << "Tue" << setw(6) << "Wed" << setw(6) << "thu" << setw(6) << "Fri" << setw(6) << "Sat" << setw(6) << endl;

		int diff = -day_order + 1;
		int new_line_count = 0;

		cout << "\n";
		for (int i = diff; i <= month_len; i++)
		{
			cout << setw(6) << (i <= 0 ? " " : to_string(i));
			new_line_count++;

			if (new_line_count % 7 == 0)
				cout << "\n\n";
		}

		cout << "\n____________________________________________\n";
	};

public:
	static void display_month_calendar(int month, int year)
	{
		int day_order = day_of_week_order(1, month, year);
		string month_name = get_month_name(month);
		int month_len = get_month_len(month, year);
		print_month_calendar(day_order, month_name, month_len);
	}

	void print_month_calendar()
	{
		print_month_calendar(day_of_week_order(_day, _month, _year), get_month_name(_month), get_month_len(_month, _year));
	};

	void display_month_calendar()
	{
		print_month_calendar();
	}
	///// ---------------------------------------------------------------
	static void display_year_calendar(int year)
	{
		cout << "\n__________________________________________________\n\n";
		cout << "\t\tCalendar = " << year;
		cout << "\n__________________________________________________\n\n";
		for (int i = 1; i <= 12; i++)
		{
			display_month_calendar(i, year);
		}
		cout << "\n\n";
	}

	void display_year_calendar()
	{
		display_year_calendar(_year);
	}
	///// ---------------------------------------------------------------
	static short get_num_of_day_from_beg_of_year(int day, int month, int year)
	{
		short total_days = 0;
		for (int i = 1; i < month; i++)
		{
			total_days += get_month_len(i, year);
		}
		total_days += day;

		return total_days;
	}

	short get_num_of_day_from_beg_of_year()
	{
		return get_num_of_day_from_beg_of_year(_day, _month, _year);
	}
	///// ---------------------------------------------------------------
	static string get_date_from_day_num(int day_of_year, int year)
	{
		short month = 0;
		short days_in_month[]{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		for (int i = 0; i < 13; i++)
		{
			if (day_of_year < days_in_month[i])
			{
				break;
			}
			day_of_year -= days_in_month[i];
			month++;
		}

		return (to_string(day_of_year) + "/" + to_string(month) + "/" + to_string(year));
	}

	string get_date_from_day_num()
	{
		return get_date_from_day_num(get_num_of_day_from_beg_of_year(_day, _month, _year), _year);
	}
	///// ---------------------------------------------------------------
	static void get_date_after_num_of_days(clsDate& added_date)
	{
		int days_num_from_beg_of_year = get_num_of_day_from_beg_of_year(added_date.day, added_date.month, added_date.year);
		added_date.month = 1;
		int added_days = read_a_positive_number("How many Days You want to add ? : ");
		int total_days = days_num_from_beg_of_year + added_days;

		short days_in_this_month = 0;
		while (true)
		{
			days_in_this_month = get_month_len(added_date.month, added_date.year);
			if (total_days > days_in_this_month)
			{
				total_days -= days_in_this_month;
				added_date.month++;
				if (added_date.month > 12)
				{
					added_date.month = 1;
					added_date.year++;
				}
			}
			else
			{
				added_date.day = total_days;
				break;
			}
		}
		added_date._full_date = get_full_date(added_date);
	};

	clsDate get_date_after_num_of_days()
	{
		get_date_after_num_of_days(*this);
	}

	///// ---------------------------------------------------------------
	static bool is_first_date_before_sec_date2(clsDate date1, clsDate date2)
	{
		return (date2.year <= date1.year ? (date2.month <= date1.month ? (date2.day > date1.day) : true) : true);
	}

	bool is_first_date_before_sec_date2(clsDate date2)
	{
		return is_first_date_before_sec_date2(*this, date2);
	}

	///// ---------------------------------------------------------------
	static bool is_first_date_equal_sec_date2(clsDate date1, clsDate date2)
	{
		return (date2.year == date1.year ? (date2.month == date1.month ? (date2.day == date1.day) : false) : false);
	}

	bool is_first_date_equal_sec_date2(clsDate date2)
	{
		return is_first_date_equal_sec_date2(*this, date2);
	}
	///// ---------------------------------------------------------------
	static bool is_last_day_in_month(clsDate date)
	{
		return date.day == get_month_len(date.month, date.year);
	}

	bool is_last_day_in_month()
	{
		return is_last_day_in_month(*this);
	}

	static bool is_last_month_in_year(short month)
	{
		return month == 12;
	}

	bool is_last_month_in_year()
	{
		return is_last_month_in_year(_month);
	}
	///// ---------------------------------------------------------------
	static void increase_date_by_one_day(clsDate& date)
	{
		if (is_last_day_in_month(date))
		{
			date.day = 1;

			if (is_last_month_in_year(date.month))
			{
				date.month = 1;
				date.year++;
			}
			else
				date.month++;
		}
		else
			date.day++;
		date._full_date = get_full_date(date);
	}

	void increase_date_by_one_day()
	{
		increase_date_by_one_day(*this);
	}
	///// ---------------------------------------------------------------
	static int get_diff_between_two_dates(clsDate date1, clsDate date2, bool include_end_day = false)
	{
		bool is_first_date_before_sec = is_first_date_before_sec_date2(date1, date2);
		clsDate two_dates[2] = {};
		if (is_first_date_before_sec)
		{
			two_dates[0] = date1;
			two_dates[1] = date2;
		}
		else
		{
			two_dates[1] = date1;
			two_dates[0] = date2;
		}

		int diff_days_num = 0;

		while (!is_first_date_equal_sec_date2(two_dates[0], two_dates[1]))
		{
			increase_date_by_one_day(two_dates[0]);
			diff_days_num++;
		}

		return include_end_day ? ++diff_days_num : diff_days_num;
	}

	int get_diff_between_two_dates(clsDate date2, bool include_end_day = false)
	{
		return get_diff_between_two_dates(*this, date2, include_end_day);
	}
	///// ---------------------------------------------------------------
	static clsDate increase_date_by_x_days(clsDate date, int iteration)
	{
		clsDate new_date = date;

		for (int i = 0; i < iteration; i++)
		{
			increase_date_by_one_day(new_date);
		}
		new_date._full_date = get_full_date(new_date);
		return new_date;
	}

	static clsDate increase_date_by_one_week(clsDate date)
	{
		clsDate new_date = date;
		for (int i = 0; i < 7; i++)
		{
			increase_date_by_one_day(new_date);
		}
		new_date._full_date = get_full_date(new_date);
		return new_date;
	}

	static clsDate increase_date_by_x_weeks(clsDate date, int iteration)
	{
		clsDate new_date = date;
		for (int i = 0; i < iteration; i++)
		{
			new_date = increase_date_by_one_week(new_date);
		}

		new_date._full_date = get_full_date(new_date);
		return new_date;
	}

	static clsDate increase_date_by_one_month(clsDate date)
	{
		clsDate new_date = date;
		new_date = increase_date_by_x_days(new_date, 30);
		new_date._full_date = get_full_date(new_date);
		return new_date;
	}

	static clsDate increase_date_by_x_months(clsDate date, int iteration)
	{
		clsDate new_date = date;
		for (int i = 0; i < iteration; i++)
		{
			new_date = increase_date_by_one_month(new_date);
		}
		new_date._full_date = get_full_date(new_date);
		return new_date;
	}

	static clsDate increase_date_by_one_year(clsDate date)
	{
		clsDate new_date = date;
		for (int i = 0; i < 12; i++)
		{
			new_date = increase_date_by_one_month(new_date);
		}
		new_date._full_date = get_full_date(new_date);
		return new_date;
	}

	static clsDate increase_date_by_one_year_2(clsDate date)
	{
		clsDate new_date = date;
		new_date.year++;
		new_date._full_date = get_full_date(new_date);
		return new_date;
	}

	static clsDate increase_date_by_x_years(clsDate date, int iteration)
	{
		clsDate new_date = date;
		for (int i = 0; i < iteration; i++)
		{
			new_date = increase_date_by_one_year(new_date);
		}
		new_date._full_date = get_full_date(new_date);
		return new_date;
	}

	static clsDate increase_date_by_ten_years(clsDate date)
	{
		clsDate new_date = date;
		for (int i = 0; i < 10; i++)
		{
			new_date = increase_date_by_one_year(new_date);
		}
		new_date._full_date = get_full_date(new_date);
		return new_date;
	}

	static clsDate increase_date_by_ten_years_2(clsDate date)
	{
		clsDate new_date = date;
		new_date.year += 10;
		new_date._full_date = get_full_date(new_date);
		return new_date;
	}

	static clsDate increase_date_by_one_decade(clsDate date)
	{
		clsDate new_date = date;
		new_date.year += 10;
		new_date._full_date = get_full_date(new_date);
		return new_date;
	}

	static clsDate increase_date_by_ten_decades(clsDate date)
	{
		clsDate new_date = date;
		new_date.year += 100;
		new_date._full_date = get_full_date(new_date);
		return new_date;
	}

	static clsDate increase_date_by_x_decades(clsDate date, int iteration)
	{
		clsDate new_date = date;
		for (int i = 0; i < iteration; i++)
		{
			new_date = increase_date_by_one_decade(new_date);
		}
		new_date._full_date = get_full_date(new_date);
		return new_date;
	}

	static clsDate increase_date_by_one_century(clsDate date)
	{
		clsDate new_date = date;
		new_date.year += 100;
		new_date._full_date = get_full_date(new_date);
		return new_date;
	}

	static clsDate increase_date_by_one_millennium(clsDate date)
	{
		clsDate new_date = date;
		new_date.year += 1000;
		new_date._full_date = get_full_date(new_date);
		return new_date;
	}

	clsDate increase_date_by_x_days(int iteration)
	{
		return increase_date_by_x_days(*this, iteration);
		;
	}
	clsDate increase_date_by_one_week()
	{
		return increase_date_by_one_week(*this);
	}
	clsDate increase_date_by_x_weeks(int iteration)
	{
		return increase_date_by_x_weeks(*this, iteration);
	}
	clsDate increase_date_by_one_month()
	{
		return increase_date_by_one_month(*this);
	}
	clsDate increase_date_by_x_months(int iteration)
	{
		return increase_date_by_x_months(*this, iteration);
	}
	clsDate increase_date_by_one_year()
	{
		return increase_date_by_one_year(*this);
	}
	clsDate increase_date_by_one_year_2()
	{
		return increase_date_by_one_year_2(*this);
	}
	clsDate increase_date_by_x_years(int iteration)
	{
		return increase_date_by_x_years(*this, iteration);
	}
	clsDate increase_date_by_ten_years()
	{
		return increase_date_by_ten_years(*this);
	}
	clsDate increase_date_by_ten_years_2()
	{
		return increase_date_by_ten_years_2(*this);
	}
	clsDate increase_date_by_one_decade()
	{
		return increase_date_by_one_decade(*this);
	}
	clsDate increase_date_by_ten_decades()
	{
		return increase_date_by_ten_decades(*this);
	}
	clsDate increase_date_by_x_decades(int iteration)
	{
		return increase_date_by_x_decades(*this, iteration);
	}
	clsDate increase_date_by_one_century()
	{
		return increase_date_by_one_century(*this);
	}
	clsDate increase_date_by_one_millennium()
	{
		return increase_date_by_one_millennium(*this);
	}

	///// ---------------------------------------------------------------

	static bool is_first_day_in_month(clsDate date)
	{
		return date.day == 1;
	}
	static bool is_first_month_in_year(short month)
	{
		return month == 1;
	}
	static void decrease_date_by_one_day(clsDate& date)
	{
		if (is_first_day_in_month(date))
		{
			date.day = get_month_len((date.month == 1 ? 12 : date.month - 1), date.year);

			if (is_first_month_in_year(date.month))
			{
				date.month = 12;
				date.year--;
			}
			else
				date.month--;
		}
		else
			date.day--;
		date._full_date = get_full_date(date);
	}
	static clsDate decrease_date_by_x_days(clsDate date, int iteration)
	{
		clsDate new_date = date;

		for (int i = 0; i < iteration; i++)
		{
			decrease_date_by_one_day(new_date);
		}

		date._full_date = get_full_date(date);
		return new_date;
	}
	static clsDate decrease_date_by_one_week(clsDate date)
	{
		clsDate new_date = date;
		for (int i = 0; i < 7; i++)
		{
			decrease_date_by_one_day(new_date);
		}
		date._full_date = get_full_date(date);
		return new_date;
	}
	static clsDate decrease_date_by_x_weeks(clsDate date, int iteration)
	{
		clsDate new_date = date;
		for (int i = 0; i < iteration; i++)
		{
			new_date = decrease_date_by_one_week(new_date);
		}
		date._full_date = get_full_date(date);
		return new_date;
	}
	static clsDate decrease_date_by_one_month(clsDate date)
	{
		clsDate new_date = date;
		new_date = decrease_date_by_x_days(new_date, 30);
		date._full_date = get_full_date(date);
		return new_date;
	}
	static clsDate decrease_date_by_x_months(clsDate date, int iteration)
	{
		clsDate new_date = date;
		for (int i = 0; i < iteration; i++)
		{
			new_date = decrease_date_by_one_month(new_date);
		}
		date._full_date = get_full_date(date);
		return new_date;
	}
	static clsDate decrease_date_by_one_year(clsDate date)
	{
		clsDate new_date = date;
		for (int i = 0; i < 12; i++)
		{
			new_date = decrease_date_by_one_month(new_date);
		}
		date._full_date = get_full_date(date);
		return new_date;
	}
	static clsDate decrease_date_by_one_year_2(clsDate date)
	{
		clsDate new_date = date;
		new_date.year--;
		date._full_date = get_full_date(date);
		return new_date;
	}
	static clsDate decrease_date_by_x_years(clsDate date, int iteration)
	{
		clsDate new_date = date;
		for (int i = 0; i < iteration; i++)
		{
			new_date = decrease_date_by_one_year(new_date);
		}
		date._full_date = get_full_date(date);
		return new_date;
	}
	static clsDate decrease_date_by_ten_years(clsDate date)
	{
		clsDate new_date = date;
		for (int i = 0; i < 10; i++)
		{
			new_date = decrease_date_by_one_year(new_date);
		}
		date._full_date = get_full_date(date);
		return new_date;
	}
	static clsDate decrease_date_by_ten_years_2(clsDate date)
	{
		clsDate new_date = date;
		new_date.year -= 10;
		date._full_date = get_full_date(date);
		return new_date;
	}
	static clsDate decrease_date_by_one_decade(clsDate date)
	{
		clsDate new_date = date;
		new_date.year -= 10;
		date._full_date = get_full_date(date);
		return new_date;
	}
	static clsDate decrease_date_by_ten_decades(clsDate date)
	{
		clsDate new_date = date;
		new_date.year -= 100;
		date._full_date = get_full_date(date);
		return new_date;
	}
	static clsDate decrease_date_by_x_decades(clsDate date, int iteration)
	{
		clsDate new_date = date;
		for (int i = 0; i < iteration; i++)
		{
			new_date = decrease_date_by_one_decade(new_date);
		}
		date._full_date = get_full_date(date);
		return new_date;
	}
	static clsDate decrease_date_by_one_century(clsDate date)
	{
		clsDate new_date = date;
		new_date.year += 100;
		date._full_date = get_full_date(date);
		return new_date;
	}
	static clsDate decrease_date_by_one_millennium(clsDate date)
	{
		clsDate new_date = date;
		new_date.year -= 1000;
		date._full_date = get_full_date(date);
		return new_date;
	}

	bool is_first_day_in_month()
	{
		return is_first_day_in_month(*this);
	};
	bool is_first_month_in_year()
	{

		return is_first_month_in_year(_month);
	};
	void decrease_date_by_one_day()
	{
		return decrease_date_by_one_day(*this);
	};
	clsDate decrease_date_by_x_days(int iteration)
	{
		return decrease_date_by_x_days(*this, iteration);
	};
	clsDate decrease_date_by_one_week()
	{
		return decrease_date_by_one_week(*this);
	};
	clsDate decrease_date_by_x_weeks(int iteration)
	{
		return decrease_date_by_x_weeks(*this, iteration);
	};
	clsDate decrease_date_by_one_month()
	{
		return decrease_date_by_one_month(*this);
	};
	clsDate decrease_date_by_x_months(int iteration)
	{
		return decrease_date_by_x_months(*this, iteration);
	};
	clsDate decrease_date_by_one_year()
	{
		return decrease_date_by_one_year(*this);
	};
	clsDate decrease_date_by_one_year_2()
	{
		return decrease_date_by_one_year_2(*this);
	};
	clsDate decrease_date_by_x_years(int iteration)
	{
		return decrease_date_by_x_years(*this, iteration);
	};
	clsDate decrease_date_by_ten_years()
	{
		return decrease_date_by_ten_years(*this);
	};
	clsDate decrease_date_by_ten_years_2()
	{
		return decrease_date_by_ten_years_2(*this);
	};
	clsDate decrease_date_by_one_decade()
	{
		return decrease_date_by_one_decade(*this);
	};
	clsDate decrease_date_by_ten_decades()
	{
		return decrease_date_by_ten_decades(*this);
	};
	clsDate decrease_date_by_x_decades(int iteration)
	{
		return decrease_date_by_x_decades(*this, iteration);
	};
	clsDate decrease_date_by_one_century()
	{
		return decrease_date_by_one_century(*this);
	};
	clsDate decrease_date_by_one_millennium()
	{
		return decrease_date_by_one_millennium(*this);
	};

	///// ---------------------------------------------------------------
	static bool is_last_day_of_week(clsDate date)
	{
		return day_of_week_order(date) == 6;
	}
	static int day_of_week_order(clsDate date)
	{
		float a = (14 - date.month) / 12;
		float y = date.year - a;
		float m = date.month + (12 * a) - 2;
		int d = int(date.day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
		return d;
	}
	static bool is_it_weekend(clsDate date)
	{
		int day_order = day_of_week_order(date);
		return day_order == 6 || day_order == 0;
	}
	static int day_until_end_of_week(clsDate date)
	{
		return (6 - day_of_week_order(date));
	}
	static int day_until_end_of_month(clsDate date)
	{
		return (get_month_len(date.month, date.year) - date.day);
	}
	static short get_num_of_day_from_beg_of_year(clsDate date)
	{
		short total_days = 0;
		for (int i = 1; i < date.month; i++)
		{
			total_days += get_month_len(i, date.year);
		}
		total_days += date.day;

		return total_days;
	}
	static int day_until_end_of_year(clsDate date)
	{
		return (is_leap(date.year) ? 366 : 365) - get_num_of_day_from_beg_of_year(date);
	}

	bool is_last_day_of_week()
	{
		return is_last_day_of_week(*this);
	};
	bool is_it_weekend()
	{
		return is_it_weekend(*this);
	};
	int day_until_end_of_week()
	{
		return day_until_end_of_week(*this);
	};
	int day_until_end_of_month()
	{
		return day_until_end_of_month(*this);
	};
	int day_until_end_of_year()
	{
		return day_until_end_of_year(*this);
	};

	///// ---------------------------------------------------------------

	static short calc_actual_weekends(clsDate start_date, clsDate end_date)
	{
		int diff = get_diff_between_two_dates(start_date, end_date);
		short non_actual = 0;
		clsDate temp_date = start_date;

		for (int i = 0; i < diff; i++)
		{
			increase_date_by_one_day(temp_date);
			if (is_it_weekend(temp_date))
				non_actual++;
		}

		return diff - non_actual;
	}

	short calc_actual_weekends(clsDate end_date)
	{
		return calc_actual_weekends(*this, end_date);
	}

	///// ---------------------------------------------------------------
	static void calc_end_date_of_vacation(clsDate start_date, clsDate& end_date, int num_of_vacation_days)
	{
		while (num_of_vacation_days > 0)
		{
			if (!is_it_weekend(start_date))
				num_of_vacation_days--;

			increase_date_by_one_day(start_date);
		}

		////// if back day is actually a vacation day skip it until get the next business day

		if (is_it_weekend(start_date))
		{
			while (is_it_weekend(start_date))
			{
				increase_date_by_one_day(start_date);
			}
		}

		end_date = start_date;
	}

	void calc_end_date_of_vacation(clsDate& end_date, int num_of_vacation_days)
	{
		calc_end_date_of_vacation(*this, end_date, num_of_vacation_days);
	}
	///// ---------------------------------------------------------------
	static bool is_date1_after_date2(clsDate date1, clsDate date2)
	{
		return !is_first_date_before_sec_date2(date1, date2) && !is_first_date_equal_sec_date2(date1, date2);
	}

	bool is_date1_after_date2(clsDate date2)
	{
		return is_date1_after_date2(*this, date2);
	}
	///// ---------------------------------------------------------------
	enum enDate_compare
	{
		before = -1,
		equal = 0,
		after = 1
	};
	static enDate_compare compare_two_dates(clsDate date1, clsDate date2)
	{
		if (is_first_date_before_sec_date2(date1, date2))
			return enDate_compare::before;
		if (is_first_date_equal_sec_date2(date1, date2))
			return enDate_compare::equal;
		////// else
		return enDate_compare::after;
	}

	int compare_two_dates(clsDate date2)
	{
		return compare_two_dates(*this, date2);
	}
	///// ---------------------------------------------------------------
	static bool check_is_date_valid_best(clsDate& date)
	{
		if (date.day >= 1 && date.day <= 31)
		{
			if (date.day > get_month_len(date.month, date.year))
				return false;
		}
		else
			return false;

		if (!(date.month >= 1 && date.month <= 12))
			return false;

		if (date.year < 1)
			return false;

		return true;
	}

	bool check_is_date_valid_best()
	{
		return check_is_date_valid_best(*this);
	}
	///// ---------------------------------------------------------------
	string replace_word_in_string_using_built_in_fqn(string text, string to_replace, string replace_to)
	{

		short pos = text.find(to_replace);

		while (pos != string::npos)
		{
			text = text.replace(pos, to_replace.length(), replace_to);
			pos = text.find(to_replace);
		}
		return text;
	}

	string format_date(clsDate cDate, string date, string format = "dd/mm/yyyy")
	{
		string format_date = "";
		format_date = replace_word_in_string_using_built_in_fqn(format, "dd", to_string(cDate.day));
		format_date = replace_word_in_string_using_built_in_fqn(format_date, "mm", to_string(cDate.month));
		format_date = replace_word_in_string_using_built_in_fqn(format_date, "yyyy", to_string(cDate.year));

		return format_date;
	}

	string format_date(string date, string format = "dd/mm/yyyy")
	{
		return format_date(*this, date, format = "dd/mm/yyyy");
	}

	///// ---------------------------------------------------------------
};

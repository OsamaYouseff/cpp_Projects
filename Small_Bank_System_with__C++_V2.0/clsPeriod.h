#pragma once
#include "clsDate.h"
#include <iostream>
#include <ctime>
#include <string>
#include "clsdate.h"


class clsPeriod
{
private:
	clsDate _start_date;
	clsDate _end_date;
public:

	//// setters
	clsDate set_start_date(clsDate start_date) {
		_start_date = start_date;
	}
	clsDate  set_end_date(clsDate end_date) {
		_end_date = end_date;
	}

	//// getters
	clsDate get_start_date() {
		return _start_date;
	}

	clsDate  get_end_date() {
		return _end_date;
	}


	__declspec(property(get = get_start_date, put = set_start_date)) clsDate start_date;
	__declspec(property(get = get_end_date, put = set_end_date)) clsDate end_date;


	//// methods

	clsPeriod(clsDate start_date, clsDate end_date) {
		this->_start_date = start_date;
		this->_end_date = end_date;
	};

	enum enDate_compare
	{
		before = -1,
		equal = 0,
		after = 1
	};

	static bool check_date_period_overlap(clsPeriod period_one, clsPeriod period_two, clsDate& first_intersection_date)
	{
		///// array of struct period
		clsPeriod sorted_periods[2] = { period_one  , period_two };

		///// check which period is first and loop through it
		if (clsDate::is_first_date_before_sec_date2(period_one._start_date, period_two._start_date))
		{
			sorted_periods[0] = period_one;
			sorted_periods[1] = period_two;
		}
		else
		{
			sorted_periods[0] = period_two;
			sorted_periods[1] = period_one;
		}

		/////// get iteration number of checking
		int iter_len = clsDate::get_diff_between_two_dates(sorted_periods[0]._start_date, sorted_periods[0]._end_date);

		///// looping though earlier period
		for (int i = 0; i <= iter_len; i++)
		{
			///// if (("first))"  date of period one is equal to than (("first))"  date of period two or later than ==> means it actually there is a overlap
			if ((clsDate::compare_two_dates(sorted_periods[0]._start_date, sorted_periods[1]._start_date) == enDate_compare::equal || clsDate::compare_two_dates(sorted_periods[0]._start_date, sorted_periods[1]._start_date) == enDate_compare::after) &&
				(clsDate::compare_two_dates(sorted_periods[0]._start_date, sorted_periods[1]._end_date) == enDate_compare::equal || clsDate::compare_two_dates(sorted_periods[0]._start_date, sorted_periods[1]._end_date) == enDate_compare::before))
			{
				first_intersection_date = sorted_periods[0]._start_date;
				return true;
			}

			clsDate::increase_date_by_one_day(sorted_periods[0]._start_date);
		}

		///// if reach here means that the no overlap
		return false;
	}

	///// --------------------------------------------------------------------------------------------------

	static int calc_period_len_in_days(clsPeriod period, bool include_end_day = false)
	{
		return clsDate::get_diff_between_two_dates(period.start_date, period.end_date, include_end_day);
	}

	///// --------------------------------------------------------------------------------------------------
	static bool check_day_within_a_period(clsPeriod period, clsDate day_date)
	{
		return !((clsDate::compare_two_dates(day_date, period.start_date) == enDate_compare::before || clsDate::compare_two_dates(day_date, period.end_date) == enDate_compare::after));
	}
	///// --------------------------------------------------------------------------------------------------
	static int count_date_period_overlap_days(clsPeriod period_one, clsPeriod period_two, clsDate& first_intersection_date)
	{

		int overlap_days_count = 0;

		///// array of struct period
		clsPeriod sorted_periods[2] = { period_one ,period_two };

		int period_one_len = calc_period_len_in_days(period_one);
		int period_two_len = calc_period_len_in_days(period_two);

		///// check which period is shortest  and loop through it
		if (period_one_len < period_two_len)
		{
			sorted_periods[0] = period_one;
			sorted_periods[1] = period_two;
		}
		else
		{
			sorted_periods[0] = period_two;
			sorted_periods[1] = period_one;
		}

		///// if three is no overlap return 0
		if ((clsDate::compare_two_dates(sorted_periods[0].start_date, sorted_periods[1].start_date) == enDate_compare::equal || clsDate::compare_two_dates(sorted_periods[0].start_date, sorted_periods[1].start_date) == enDate_compare::after) &&
			(clsDate::compare_two_dates(sorted_periods[0].start_date, sorted_periods[1].end_date) == enDate_compare::equal || clsDate::compare_two_dates(sorted_periods[0].start_date, sorted_periods[1].end_date) == enDate_compare::before))
		{
			return 0;
		}

		/////// get iteration number of checking
		int iter_len = clsDate::get_diff_between_two_dates(sorted_periods[0].start_date, sorted_periods[0].end_date);

		///// looping though earlier period
		for (int i = 0; i <= iter_len; i++)
		{
			if ((clsDate::compare_two_dates(sorted_periods[0].start_date, sorted_periods[1].start_date) == enDate_compare::equal || clsDate::compare_two_dates(sorted_periods[0].start_date, sorted_periods[1].start_date) == enDate_compare::after) &&
				(clsDate::compare_two_dates(sorted_periods[0].start_date, sorted_periods[1].end_date) == enDate_compare::equal || clsDate::compare_two_dates(sorted_periods[0].start_date, sorted_periods[1].end_date) == enDate_compare::before))
			{
				first_intersection_date = sorted_periods[0].start_date;
				overlap_days_count++;
			}

			clsDate::increase_date_by_one_day(sorted_periods[0]._start_date);

			if (clsDate::compare_two_dates(sorted_periods[0].start_date, sorted_periods[1].end_date) == enDate_compare::after)
				break;
		}

		return overlap_days_count;
	}

	///// --------------------------------------------------------------------------------------------------

};

class Class2
{
};


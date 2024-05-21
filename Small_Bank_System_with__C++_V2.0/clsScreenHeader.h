#pragma once
#include <iostream>
#include "global.h"
#include "clsDate.h"

using namespace std;

class clsScreenHeader
{
protected:
	static void _draw_screen_header(string Title, string SubTitle = "")
	{
		cout << "################################################################################################";
		cout << "\n\t\t\t\t\t" << Title;
		if (SubTitle != "")
		{
			cout << "\n  " << SubTitle;
		}
		cout << "\n################################################################################################\n";

		cout << "User name : " << logged_user.get_user_name() << "\n";
		cout << "Date - time : " << clsDate::get_current_date_and_time_in_str();


		cout << "\n################################################################################################\n\n";
	}



	static bool display_access_permission(clsBankUser::enPermissions permission)
	{
		system("cls");
		if (!logged_user.check_access_permission(permission))
		{
			_draw_screen_header("Access Denied! Contact your Admin.");

			return false;
		}
		else
			return true;

	}


};

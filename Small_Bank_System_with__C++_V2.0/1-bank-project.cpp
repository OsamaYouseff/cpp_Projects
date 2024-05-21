#include <iostream>
#include "clsLoginScreen.h"

using namespace std;

int main()
{
	
	while (!stop_app_after_three_tries)
	{
		clsLoginScreen::show_login_screen();
	}

	return 0;
}
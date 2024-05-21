#pragma once
#include "clsBankUser.h"
#include <iostream>
using namespace std;

clsBankUser logged_user = clsBankUser::create_an_empty_user();

bool stop_app_after_three_tries = false;
short encrypt_num = 2;

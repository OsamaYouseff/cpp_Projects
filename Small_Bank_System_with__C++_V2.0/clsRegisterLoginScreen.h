#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsScreenHeader.h"
#include "clsString.h"
using namespace std;


class clsRegisterLoginScreen
{
private:
	static vector<string> _load_log_from_file(string file_name = "users_logs.txt") {

		vector<string> vUsers_logs;

		fstream MyFile;
		MyFile.open(file_name, ios::in); // read Mode
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				vUsers_logs.push_back(Line);
			}
			MyFile.close();
		}
		return vUsers_logs;

	}

public:

	static void display_register_info() {

		vector<string> vUsers_data = _load_log_from_file("users_logs.txt");

		vector <string> info;

		cout << "\n\t\t\t\t Logs list has (" << vUsers_data.size() << ") Logs(s)\t\t\t\t" << endl;
		cout << "--------------------------------------------------------------------------------------------------" << endl;
		cout << "| Date / Time " << setw(29);
		cout << "| User Name" << setw(21);
		cout << "| Password" << setw(28);
		cout << "| Permission";
		cout << "\n--------------------------------------------------------------------------------------------------\n\n";
		if (vUsers_data.empty())
		{
			cout << "\n\t\t\t    there is no Logs history in this system \t\t\t\t" << endl;
		}
		else
		{
			for (short i = 0; i < vUsers_data.size(); i++)
			{
				info = clsString::split(vUsers_data[i], "//#");;
				cout << "| " << setw(30) << left << info[0];
				cout << "| " << setw(20) << left << info[1];
				cout << "| " << setw(24) << left << info[2];
				cout << "| " << setw(24) << left << info[3] << " \n";
			}
		}
		cout << "\n--------------------------------------------------------------------------------------------------\n\n";



	};




};


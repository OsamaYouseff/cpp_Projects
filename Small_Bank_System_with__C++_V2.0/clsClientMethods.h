#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsDate.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtility.h"
#include "global.h"

using namespace std;

class clsClientMethods
{
private:
	struct stTransfer_log
	{
		string data_time, s_acc, d_acc, amount, s_balance, d_balance, user_name;
	};

	string _file_name = "transfer_logs.txt", _separator = "#//#";

	static void _read_client_Data(clsBankClient &client)
	{

		cout << "\nEnter First Name: ";
		client.set_first_name(clsValidate<string>::read_string());
		cout << "\nEnter Last Name : ";
		client.set_last_name(clsValidate<string>::read_string());
		cout << "\nEnter Email: ";
		client.set_email(clsValidate<string>::read_string());
		cout << "\nEnter Phone: ";
		client.set_phone(clsValidate<string>::read_string());
		cout << "\nEnter PIN Code: ";
		client.set_PIN_code(clsValidate<string>::read_string());
		cout << "\nEnter Account Balance: ";
		client.set_account_balance(clsValidate<float>::read_number("Wrong value!! try again"));
	};

	static void _print_status(clsBankClient::enSave_results enResults)
	{
		cout << "\n_______________________________________________\n";
		switch (enResults)
		{
		case clsBankClient::new_client_was_add_succ:
			cout << "\nClient was Added successfully :-) \n";
			break;
		case clsBankClient::faild_to_save:
			cout << "\nField to update client data :-( \n";
			break;
		case clsBankClient::saved_successfully:
			cout << "\nClient was updated successfully :-) \n";
			break;
		case clsBankClient::deleted_succ:
			cout << "\nClient was deleted successfully :-) \n";
			break;
		default:
			break;
		}
		cout << "_______________________________________________\n";
	};

	static void _save_transfer_log_to_file(string transfer_data, string file_name = "transfer_logs.txt")
	{

		fstream users;

		users.open(file_name, ios::out | ios::app); /// append mode

		if (users.is_open())
		{
			users << transfer_data << "\n";
			users.close();
		}
	}

	static string _prepare_transfer_log(clsBankClient client1, clsBankClient client2, float amount, string separator = "#//#")
	{
		string transfer_log_line = "";

		transfer_log_line += clsDate::get_current_date_and_time_in_str() + separator;
		transfer_log_line += client1.get_account_num() + separator;
		transfer_log_line += client2.get_account_num() + separator;
		transfer_log_line += to_string(amount) + separator;
		transfer_log_line += to_string(client1.get_account_balance()) + separator;
		transfer_log_line += to_string(client2.get_account_balance()) + separator;
		transfer_log_line += logged_user.get_user_name();
		return transfer_log_line;
	}

	static void _save_transfer_log(clsBankClient client1, clsBankClient client2, float amount, string separator = "#//#")
	{

		string transfer_log_line = _prepare_transfer_log(client1, client2, amount, separator);

		_save_transfer_log_to_file(transfer_log_line, "transfer_logs.txt");
	}

	static stTransfer_log _fill_transfer_log(string trans_log_line, string file_name = "transfer_logs.txt")
	{

		stTransfer_log tans_log;
		vector<string> vTans_log = clsString::split(trans_log_line, "#//#");

		tans_log.data_time = vTans_log[0];
		tans_log.s_acc = vTans_log[1];
		tans_log.d_acc = vTans_log[2];
		tans_log.amount = vTans_log[3];
		tans_log.s_balance = vTans_log[4];
		tans_log.d_balance = vTans_log[5];
		tans_log.user_name = vTans_log[6];

		return tans_log;
	}

	static vector<string> _load_trans_logs_data_from_file(string file_name = "transfer_logs.txt")
	{
		vector<string> vLogs;

		fstream MyFile;
		MyFile.open(file_name, ios::in); // read Mode
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				vLogs.push_back(Line);
			}
			MyFile.close();
		}
		return vLogs;
	}

public:
	////// main menu opreations
	static void display_clients_list()
	{
		vector<clsBankClient> clients_data = clsBankClient::get_clients_list();

		clsBankClient client = clsBankClient::create_an_empty_client();

		cout << "\n\t\t\t\t Client list (" << clients_data.size() << ") clients(s)\t\t\t\t" << endl;
		cout << "--------------------------------------------------------------------------------------------------" << endl;
		cout << "| Account number " << setw(15);
		cout << "| PIN code" << setw(15);
		cout << "| Client Name " << setw(20);
		cout << "| Phone " << setw(28);
		cout << "| Balance " << endl;
		cout << "--------------------------------------------------------------------------------------------------\n\n";
		if (clients_data.empty())
		{
			cout << "\n\t\t\t    there is no clients in this system \t\t\t\t" << endl;
		}
		else
		{
			for (short i = 0; i < clients_data.size(); i++)
			{
				client = clients_data.at(i);
				cout << "| " << setw(20) << left << client.get_account_num();
				cout << "| " << setw(9) << left << client.get_PIN_code();
				cout << "| " << setw(24) << left << client.full_name();
				cout << "| " << setw(24) << left << client.phone;
				cout << "| " << client.get_account_balance() << " \n";
			}
		}
		cout << "\n--------------------------------------------------------------------------------------------------\n\n";
	}

	static void add_new_client()
	{
		string account_num = "";
		bool is_client_exist = 1;

		//// find client acc info
		cout << "Please enter the account number : ";
		while (is_client_exist)
		{
			account_num = clsValidate<string>::read_string();
			is_client_exist = clsBankClient::is_client_exist(account_num);

			if (is_client_exist)
			{
				cout << "This client with account number < " << account_num << " > is already exist! try another one\n";
				cout << "Please enter the account number : ";
			}
		}

		///// perform adding new client
		clsBankClient new_client = clsBankClient::create_new_client_with_acc_num(account_num);
		_read_client_Data(new_client);

		print_client(new_client);

		clsBankClient::enSave_results enResults = new_client.save();

		_print_status(enResults);
	};

	static void delete_client()
	{

		string account_num = "";
		bool is_client_exist = 0;
		clsBankClient target_client = clsBankClient::create_an_empty_client();

		//// find client acc info
		cout << "Please enter the account number : ";
		while (!is_client_exist)
		{
			account_num = clsValidate<string>::read_string();
			is_client_exist = clsBankClient::is_client_exist(account_num, target_client);

			if (!is_client_exist)
			{
				cout << "This client with account number < " << account_num << " > is not exist!\n";
				cout << "Please enter the account number : ";
			}
		}

		cout << "\nClient Data :";
		print_client(target_client);

		/////// ask user again if they sure to delete or not
		char sure_for_delete = 'N';
		cout << "Are you sure you want to delete this client? (Y/N) : ";
		cin >> sure_for_delete;

		if (sure_for_delete == 'N' || sure_for_delete == 'n')
		{
			return;
		}

		//////  give access to delete
		target_client.access_to_delete();

		clsBankClient::enSave_results enResults = target_client.save();

		_print_status(enResults);
	};

	static void update_client()
	{

		string account_num = "";
		bool is_client_exist = 0;
		clsBankClient target_client = clsBankClient::create_an_empty_client();

		//// find client acc info
		cout << "Please enter the account number : ";
		while (!is_client_exist)
		{
			account_num = clsValidate<string>::read_string();
			is_client_exist = clsBankClient::is_client_exist(account_num, target_client);

			if (!is_client_exist)
			{
				cout << "This client with account number < " << account_num << " > is not exist!\n";
				cout << "Please enter the account number : ";
			}
		}
		cout << "\nClient Data :";
		print_client(target_client);

		/////// ask user again if they sure to update or not
		char sure_for_update = 'N';
		cout << "\nAre you sure you want to update this client? (Y/N) : ";
		cin >> sure_for_update;

		if (sure_for_update == 'N' || sure_for_update == 'n')
		{
			return;
		}

		///////////
		cout << "\n__________________________\n";
		cout << "\nUpdating client Info \n";
		cout << "__________________________\n";

		_read_client_Data(target_client);

		clsBankClient::enSave_results enResults = target_client.save();

		_print_status(enResults);

		print_client(target_client);
	};

	static void find_client()
	{
		string account_num = "";
		bool is_client_exist = 0;
		clsBankClient target_client = clsBankClient::create_an_empty_client();

		//// find client acc info
		cout << "Please enter the account number : ";
		while (!is_client_exist)
		{
			account_num = clsValidate<string>::read_string();
			is_client_exist = clsBankClient::is_client_exist(account_num, target_client);

			if (!is_client_exist)
			{
				cout << "This client with account number < " << account_num << " > is not exist!\n";
				cout << "Please enter the account number : ";
			}
		}
		cout << "\nClient was found :-)\n";
		print_client(target_client);
	};

	///// display_total_balances method1
	// void display_total_balances() {
	//	vector<clsBankClient> clients_data = clsBankClient::get_clients_list();
	//
	//	clsBankClient client = clsBankClient::create_an_empty_client();
	//
	//	double total_balances = 0;
	//
	//	cout << "\n\t\t\t\t Client list (" << clients_data.size() << ") clients(s)\t\t\t\t" << endl;
	//	cout << "--------------------------------------------------------------------------------------------------" << endl;
	//	cout << "| Account number " << setw(15);
	//	cout << "| PIN code" << setw(15);
	//	cout << "| Client Name " << setw(20);
	//	cout << "| Phone " << setw(28);
	//	cout << "| Balance " << endl;
	//	cout << "--------------------------------------------------------------------------------------------------\n\n";
	//	if (clients_data.empty())
	//	{
	//		cout << "\n\t\t\t    there is no clients in this system \t\t\t\t" << endl;
	//	}
	//	else
	//	{
	//		for (short i = 0; i < clients_data.size(); i++)
	//		{
	//			client = clients_data.at(i);
	//			cout << "| " << setw(20) << left << client.account_num;
	//			cout << "| " << setw(9) << left << client.PIN_code;
	//			cout << "| " << setw(24) << left << client.full_name();
	//			cout << "| " << setw(24) << left << client.phone;
	//			cout << "| " << client.account_balance << " \n";
	//			total_balances += client.account_balance;
	//		}
	//	}
	//	cout << "\n--------------------------------------------------------------------------------------------------\n\n";
	//	cout << "\t\t\t\t Total balances = $" << total_balances << "\t\t\t\t" << endl;
	//	cout << "\n--------------------------------------------------------------------------------------------------\n\n";
	// }

	///// display_total_balances method2
	static void display_total_balances()
	{
		double total_balances = clsBankClient::get_total_balances();

		display_clients_list();
		cout << "\t\t\t\t Total balances = $" << total_balances << "\t\t\t\t" << endl;
		cout << "\t\t    " << clsUtility::covert_number_into_text(total_balances) << "Dollars"
			<< "\n\n";
		cout << "\n--------------------------------------------------------------------------------------------------\n\n";
	}

	static void print_client(clsBankClient client)
	{
		cout << "\nClient card";
		cout << "\n______________________________\n\n";
		cout << "First name      : " << client.get_first_name() << endl;
		cout << "Last name       : " << client.get_last_name() << endl;
		cout << "Full name       : " << client.full_name() << endl;
		cout << "Email           : " << client.get_email() << endl;
		cout << "Phone number    : " << client.get_phone() << endl;
		cout << "Account number  : " << client.get_account_num() << endl;
		cout << "PIN code        : " << client.get_PIN_code() << endl;
		cout << "Account balance : " << client.get_account_balance() << endl;
		cout << "______________________________\n";
	};

	///// transactions menu opreations

	static void show_deposit_screen()
	{

		string account_num = "";
		bool is_client_exist = 0;
		clsBankClient target_client = clsBankClient::create_an_empty_client();

		//// find client acc info
		cout << "Please enter the account number : ";
		while (!is_client_exist)
		{
			account_num = clsValidate<string>::read_string();
			is_client_exist = clsBankClient::is_client_exist(account_num, target_client);

			if (!is_client_exist)
			{
				cout << "This client with account number < " << account_num << " > is not exist!\n";
				cout << "Please enter the account number : ";
			}
		}
		cout << "\nClient was found :-)\n";
		print_client(target_client);

		////// taking amount from client
		double amount = 0;
		amount = clsValidate<double>::read_number("Please enter deposit amount? : ", "Invalid input!! try again ");
		char is_client_sure = 'N';
		cout << "\nAre you sure you want to perform this transaction? (y/n) : ";
		cin >> is_client_sure;
		cin.ignore();

		if (is_client_sure == 'Y' || is_client_sure == 'y')
		{
			target_client.deposit(amount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance Is: " << target_client.get_account_balance();
		}
		else
		{
			cout << "\nThe operation Was cancelled \n";
		}
	};

	static void show_withdraw_screen()
	{

		string account_num = "";
		bool is_client_exist = 0;
		clsBankClient target_client = clsBankClient::create_an_empty_client();

		//// find client acc info
		cout << "Please enter the account number : ";
		while (!is_client_exist)
		{
			account_num = clsValidate<string>::read_string();
			is_client_exist = clsBankClient::is_client_exist(account_num, target_client);

			if (!is_client_exist)
			{
				cout << "This client with account number < " << account_num << " > is not exist!\n";
				cout << "Please enter the account number : ";
			}
		}
		cout << "\nClient was found :-)\n";
		print_client(target_client);

		////// taking amount from client & check if it's valid or not
		double amount = 0;
		char is_client_sure = 'N';

		do
		{
			amount = clsValidate<double>::read_number("Please enter deposit amount? : ", "Invalid input!! try again ");
			if (!target_client.is_amount_suitable_for_withdrawing(amount))
			{
				cout << "The amount exceeds the account balance \n";
				cout << "You can't withdraw " << amount << " you ony have " << target_client.get_account_balance() << " in your account balance\n";
			}

		} while (!target_client.is_amount_suitable_for_withdrawing(amount));

		cout << "\nAre you sure you want to perform this transaction? (y/n) : ";
		cin >> is_client_sure;
		cin.ignore();

		if (is_client_sure == 'Y' || is_client_sure == 'y')
		{
			target_client.withdraw(amount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance Is: " << target_client.get_account_balance();
		}
		else
		{
			cout << "\nThe operation Was cancelled \n";
		}
	};

	static void show_total_balances_screen()
	{
		vector<clsBankClient> clients_data = clsBankClient::get_clients_list();

		clsBankClient client = clsBankClient::create_an_empty_client();

		cout << "\n\t\t\t\t Client list (" << clients_data.size() << ") clients(s)\t\t\t\t" << endl;
		cout << "--------------------------------------------------------------------------------------------------" << endl;
		cout << "| Account number " << setw(15);
		cout << "| Client Name " << setw(20);
		cout << "| Balance " << endl;
		cout << "--------------------------------------------------------------------------------------------------\n\n";
		if (clients_data.empty())
		{
			cout << "\n\t\t\t    there is no clients in this system \t\t\t\t" << endl;
		}
		else
		{
			for (short i = 0; i < clients_data.size(); i++)
			{
				client = clients_data.at(i);
				cout << "| " << setw(20) << left << client.get_account_num();
				cout << "| " << setw(24) << left << client.full_name();
				cout << "| " << client.get_account_balance() << " \n";
			}
		}
		cout << "\n--------------------------------------------------------------------------------------------------\n\n";
		display_total_balances();
	}

	static void transfer(clsBankClient& target_client1, clsBankClient& target_client2, float amount)
	{
		target_client1.withdraw(amount);
		target_client2.deposit(amount);
	}

	static void show_transfer_screen()
	{
		string client1_acc_num = "";
		bool is_client1_exist = false;
		clsBankClient target_client1 = clsBankClient::create_an_empty_client();

		//// find client one acc info
		cout << "Please enter the account number : ";
		while (!is_client1_exist)
		{
			client1_acc_num = clsValidate<string>::read_string();
			is_client1_exist = clsBankClient::is_client_exist(client1_acc_num, target_client1);

			if (!is_client1_exist)
			{
				cout << "This client with account number < " << client1_acc_num << " > is not exist!\n";
				cout << "Please enter the account number : ";
			}
		}
		cout << "\nClient was found :-)\n";
		print_client(target_client1);

		//////////////////////////////////////////////////////////////////////////////

		string client2_acc_num = "";
		bool is_client2_exist = false, is_client_duplicated = false;

		clsBankClient target_client2 = clsBankClient::create_an_empty_client();

		//// find client two acc info
		while (!is_client2_exist || is_client_duplicated)
		{
			cout << "\n\nPlease enter the account number : ";

			client2_acc_num = clsValidate<string>::read_string();
			is_client2_exist = clsBankClient::is_client_exist(client2_acc_num, target_client2);

			if (!is_client2_exist)
			{
				cout << "This client with account number < " << client2_acc_num << " > is not exist!\n";
				cout << "Please enter the account number : ";
			}

			/////// check if user transfer from their account to their account
			if (client1_acc_num == client2_acc_num)
			{
				is_client_duplicated = true;
				cout << "You can't transfer from your account to your account \n\n";
			}
			else
				is_client_duplicated = false;
		}
		cout << "\nClient was found :-)\n";
		print_client(target_client2);

		////// taking amount from client & check if it's valid or not
		double amount = 0;
		char is_client_sure = 'N';

		do
		{
			amount = clsValidate<double>::read_number("\nPlease enter the amount? : ", "Invalid input!! try again ");
			if (!target_client1.is_amount_suitable_for_withdrawing(amount))
			{
				cout << "The amount exceeds the account balance \n";
				cout << "You can't withdraw " << amount << " you ony have " << target_client1.get_account_balance() << " in your account balance\n";
			}

		} while (!target_client2.is_amount_suitable_for_withdrawing(amount));

		cout << "\nAre you sure you want to perform this transaction? (y/n) : ";
		cin >> is_client_sure;
		cin.ignore();

		if (is_client_sure == 'Y' || is_client_sure == 'y')
		{
			//// if user is sure perform the transform operation
			transfer(target_client1, target_client2, amount);

			_save_transfer_log(target_client1, target_client2, amount, "#//#");

			cout << "\nAmount Was transferred successfully from " << target_client1.full_name() << " to " << target_client2.full_name() << "\n\n";
			cout << target_client1.full_name() << " New Balance Is: " << target_client1.get_account_balance() << "\n\n";
			cout << target_client2.full_name() << " New Balance Is: " << target_client2.get_account_balance() << "\n\n";
			print_client(target_client1);
			cout << "\n\n";
			print_client(target_client2);
		}
		else
		{
			cout << "\nThe operation Was cancelled \n";
			return;
		}
	}

	static void display_transfer_logs_list()
	{

		vector<string> transfer_logs = _load_trans_logs_data_from_file("transfer_logs.txt");

		stTransfer_log transfer_log;

		cout << "\n\t\t\t\t transfer logs (" << transfer_logs.size() << ") log(s)\t\t\t\t" << endl;
		cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "| Data / Time " << setw(33);
		cout << "| S.account " << setw(10);
		cout << "| D.account " << setw(10);
		cout << "| Amount " << setw(18);
		cout << "| S.Balance " << setw(15);
		cout << "| D.Balance " << setw(11);
		cout << "| User " << endl;
		cout << "--------------------------------------------------------------------------------------------------------------------\n\n";
		if (transfer_logs.empty())
		{
			cout << "\n\t\t\t    there is no transfer logs in this system \t\t\t\t" << endl;
		}
		else
		{
			for (short i = 0; i < transfer_logs.size(); i++)
			{
				transfer_log = _fill_transfer_log(transfer_logs[i], "transfer_logs.txt");

				cout << "| " << setw(33) << left << transfer_log.data_time;
				cout << "| " << setw(10) << left << transfer_log.s_acc;
				cout << "| " << setw(11) << left << transfer_log.d_acc;
				cout << "| " << setw(13) << left << transfer_log.s_balance;
				cout << "| " << setw(13) << left << transfer_log.d_balance;
				cout << "| " << setw(14) << left << transfer_log.amount;
				cout << "| " << transfer_log.user_name << "\n";
			}
		}
		cout << "--------------------------------------------------------------------------------------------------------------------\n\n";
	}
};

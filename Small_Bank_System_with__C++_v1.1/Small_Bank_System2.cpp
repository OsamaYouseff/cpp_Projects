#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

struct stData
{
    string acc_num;
    string name;
    string phone;
    string pin_code;
    double balance;
};

/////-----------------------------------------------------------------------------------------------------------------------

double read_a_positive_number(string msg)
{
    double num;
    do
    {
        cout << msg;
        cin >> num;
    } while (num <= 0);
    return num;
}

void display_services_menu()
{
    system("cls");
    cout << "\n===================================================\n";
    cout << "\t\tWelcome To Bank Menu\t\t\t";
    cout << "\n===================================================\n";
    cout << "[ 1 ] Show Clients List.\n";
    cout << "[ 2 ] Add New Client.\n";
    cout << "[ 3 ] Delete Client.\n";
    cout << "[ 4 ] Update Client Info.\n";
    cout << "[ 5 ] Find Client.\n";
    cout << "[ 6 ] Transactions\n";
    cout << "[ 7 ] Exit.\n";
    cout << "===================================================\n";
}

void display_transactions_menu()
{
    system("cls");
    cout << "\n===================================================\n";
    cout << "\t\tTransactions Menu\t\t\t";
    cout << "\n===================================================\n";
    cout << "[ 1 ] Deposit.\n";
    cout << "[ 2 ] withdraw.\n";
    cout << "[ 3 ] Total Balances.\n";
    cout << "[ 4 ] Main Menu.\n";
    cout << "===================================================\n";
}

void take_user_choice_num_in_range(short &user_choice, short from, short to)
{
    do
    {
        cout << "Please enter your choice from [ " << from << " ] to [ " << to << " ] : ";
        cin >> user_choice;
    } while (user_choice < from || user_choice > to);
}

/////-----------------------------------------------------------------------------------------------------------------------

void read_file_lines(string file_name, vector<string> &clients_data)
{
    fstream my_new_file;
    my_new_file.open(file_name, ios::in); //// reading  mode => reads file only
    if (my_new_file.is_open())
    {
        string line;
        while (getline(my_new_file, line))
        {
            clients_data.push_back(line);
        }

        my_new_file.close();
    }
}

vector<string> convert_line_to_record(string text, string delim = "#//#")   
{
    vector<string> result;
    string word = "";
    short pos = 0;

    while ((pos = text.find(delim)) != std::string::npos)
    {
        word = text.substr(0, pos);

        if (word != "")
            result.push_back(word);

        text.erase(0, pos + delim.length());
    }

    if (word != " ")
        result.push_back(text);

    return result;
}

void display_clients_data(vector<string> &clients_data)
{
    vector<string> client;
    cout << "\n\t\t\t\t Client list (" << clients_data.size() << ") clients(s)\t\t\t\t" << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;
    cout << "| Account number " << setw(15);
    cout << "| PIN code" << setw(15);
    cout << "| Client Name " << setw(20);
    cout << "| Phone " << setw(24);
    cout << "| Balance " << endl;
    cout << "--------------------------------------------------------------------------------------------\n\n";
    if (clients_data.empty())
    {
        cout << "\n\t\t\t    there is no clients in this system \t\t\t\t" << endl;
    }
    else
    {
        for (short i = 0; i < clients_data.size(); i++)
        {
            client = convert_line_to_record(clients_data.at(i), "#//#");
            cout << "| " << setw(20) << left << client[0];
            cout << "| " << setw(9) << left << client[1];
            cout << "| " << setw(20) << left << client[2];
            cout << "| " << setw(24) << left << client[3];
            cout << "| " << stoi(client[4]) << " \n";
            client.clear();
        }
    }
    cout << "\n--------------------------------------------------------------------------------------------\n\n";
}

void show_clients_list(const string file_name = "myFile.txt")
{
    vector<string> clients_data;
    read_file_lines(file_name, clients_data);
    display_clients_data(clients_data);
}

/////-----------------------------------------------------------------------------------------------------------------------

bool check_user_acc_num_is_not_exist_before_in_file(vector<string> clients_data, string acc_num)
{
    vector<string> client;

    for (short i = 0; i < clients_data.size(); i++)
    {
        client = convert_line_to_record(clients_data.at(i), "#//#");
        if (client[0] == acc_num)
        {
            return true;
        }
        client.clear();
    }

    return false;
}

string convert_record_to_line(stData client, string separator = "#//#")
{
    string final_string = "";

    final_string += client.acc_num + separator;
    final_string += client.pin_code + separator;
    final_string += client.name + separator;
    final_string += client.phone + separator;
    final_string += to_string(client.balance);

    return final_string;
}

string get_new_client_data_in_one_line(vector<string> clients_data)
{
    stData data;
    string num;
    string target_client;
    bool is_exist;
    do
    {
        cout << "Enter your Account Number : ";
        getline(cin, data.acc_num);
        ////// check if Account Number is not exist before
        is_exist = check_user_acc_num_is_not_exist_before_in_file(clients_data, data.acc_num);
        if (is_exist)
        {
            cout << "The account number (" << data.acc_num << ") is already exist try another one. " << endl;
        }
    } while (is_exist);

    cout << "Enter your pin code : ";
    getline(cin >> ws, data.pin_code);

    cout << "Enter your name : ";
    getline(cin, data.name);

    cout << "Enter your phone : ";
    getline(cin, data.phone);

    cout << "Enter your Account balance : ";
    getline(cin, num);
    data.balance = stod(num);

    target_client = convert_record_to_line(data, "#//#");

    return target_client;
}

void add_new_client_data_to_file(string new_client, string file_name = "myFile.txt")
{

    fstream my_new_file;
    my_new_file.open(file_name, ios::out | ios::app);
    if (my_new_file.is_open())
    {
        my_new_file << new_client << "\n";
        my_new_file.close();
    }
}

void add_new_client(vector<string> &clients_data, string file_name)
{
    char add_more = 'N';

    do
    {
        add_new_client_data_to_file(get_new_client_data_in_one_line(clients_data), file_name);

        ///// ask to add more clients
        cout << "Do you want to add more clients (Y / N) : ";
        cin >> add_more;
        cin.ignore();

    } while (add_more == 'Y' || add_more == 'y');

    cout << "New user Was Added Successfully.\n";
}

/////-----------------------------------------------------------------------------------------------------------------------

void print_client_data(vector<string> client)
{
    cout << "\n-----------------------------------\n";
    cout << "The following client data is \n";
    cout << "-----------------------------------\n";
    cout << "Account number   : " << client[0] << endl;
    cout << "PIN code         : " << client[1] << endl;
    cout << "Name             : " << client[2] << endl;
    cout << "Phone            : " << client[3] << endl;
    cout << "Account Balance  : " << stoi(client[4]) << endl;
    cout << "-----------------------------------\n";
}

bool find_client_with_acc_num(vector<string> clients_data, string client_acc_num, vector<string> &target_client, short &location)
{
    vector<string> current_client;

    for (short i = 0; i < clients_data.size(); i++)
    {
        current_client = convert_line_to_record(clients_data.at(i), "#//#");
        if (current_client[0] == client_acc_num)
        {
            target_client = current_client;
            location = i;
            return true;
        }
        current_client.clear();
    }

    return false;
}

void delete_client_from_data_vector(vector<string> &clients_data, short location)
{
    clients_data.erase(clients_data.begin() + location);
}

void update_file_data(vector<string> clients_data, string file_name)
{
    fstream users_data;

    users_data.open(file_name, ios::out);

    if (users_data.is_open())
    {
        for (string &client : clients_data)
        {
            users_data << client << "\n";
        }
        users_data.close();
    }
}

void take_acc_num(string &client_acc_num)
{
    cout << "Please enter the account number : ";
    cin >> client_acc_num;
}

void refresh_client_data_in_vector(vector<string> &clients_data, string file_name)
{
    clients_data.clear();
    read_file_lines(file_name, clients_data);
}

void delete_client(vector<string> &clients_data, string file_name)
{
    vector<string> target_client;
    string client_acc_num;
    short location;
    char confirm_delete = 'N';
    bool is_exist;
    do
    {
        take_acc_num(client_acc_num);
        is_exist = find_client_with_acc_num(clients_data, client_acc_num, target_client, location);
        if (is_exist)
        {
            print_client_data(target_client);
            cout << "Are you sure that you want to delete this client ? (Y/N)  : ";
            cin >> confirm_delete;
            if (confirm_delete == 'Y' || "y")
            {
                delete_client_from_data_vector(clients_data, location);
                update_file_data(clients_data, file_name);
                cout << "Client was deleted successfully." << endl;
            }
        }
        else
            cout << "Client with account number (" << client_acc_num << ") not found!\n";
    } while (!is_exist);

    refresh_client_data_in_vector(clients_data, file_name);
}

/////-----------------------------------------------------------------------------------------------------------------------

string get_client_data(string client_acc_num)
{
    stData data;
    string num;
    data.acc_num = client_acc_num;
    cout << "Enter your pin code : ";
    getline(cin >> ws, data.pin_code);
    cout << "Enter your name : ";
    getline(cin, data.name);
    cout << "Enter your phone : ";
    getline(cin, data.phone);
    cout << "Enter your Account balance : ";
    getline(cin, num);
    data.balance = stod(num);

    return convert_record_to_line(data, "#//#");
}

void update_client_info(vector<string> clients_data, string file_name)
{
    vector<string> target_client;
    short location;
    char confirm_update = 'N';
    string client_acc_num;
    bool is_exist;

    do
    {
        take_acc_num(client_acc_num);
        is_exist = find_client_with_acc_num(clients_data, client_acc_num, target_client, location);
        if (is_exist)
        {
            print_client_data(target_client);
            cout << "Are you sure that you want to update this client ? (Y/N)  : ";
            cin >> confirm_update;
            if (confirm_update == 'Y' || "y")
            {
                clients_data[location] = get_client_data(client_acc_num);
                update_file_data(clients_data, file_name);
                cout << "Client was updated successfully." << endl;
            }
        }
        else
            cout << "Client with account number (" << client_acc_num << ") not found!\n";
    } while (!is_exist);

    refresh_client_data_in_vector(clients_data, file_name);
}

/////-----------------------------------------------------------------------------------------------------------------------

bool get_client_from_file(vector<string> clients_data, string client_acc_num, vector<string> &target_client, short &location)
{
    vector<string> current_client;
    for (short i = 0; i < clients_data.size(); i++)
    {
        current_client = convert_line_to_record(clients_data.at(i), "#//#");
        if (current_client[0] == client_acc_num)
        {
            target_client = current_client;
            location = i;
            return true;
        }
        current_client.clear();
    }

    return false;
}

void find_client(vector<string> clients_data, string file_name)
{
    vector<string> target_client;
    string client_acc_num;
    take_acc_num(client_acc_num);
    short location;
    bool is_exist;

    is_exist = get_client_from_file(clients_data, client_acc_num, target_client, location);
    if (is_exist)
    {
        print_client_data(target_client);
    }
    else
    {
        cout << "Sorry, this client is not exist! " << endl;
    }
}

/////-----------------------------------------------------------------------------------------------------------------------

string convert_vector_record_to_line(vector<string> target_client, string separator = "#//#")
{
    string result = target_client[0];
    for (int i = 1; i < target_client.size(); i++)
    {
        if (i < target_client.size())
            result += separator;
        result += target_client[i];
    }
    return result;
}

void update_client_balance_in_vector(vector<string> &clients_data, string client_new_info, short location)
{
    clients_data[location] = client_new_info;
}

char confirm_perform(string msg)
{
    char sure;
    while (true)
    {
        cout << msg;
        cin >> sure;
        sure = toupper(sure);
        if (sure == 'Y' || sure == 'N')
        {
            // Valid input, return it
            return sure;
        }
        else
        {
            cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
        }
    }
}

void deposit_withdraw_operations(vector<string> &clients_data, string file_name, string type)
{
    vector<string> target_client;
    string client_acc_num;
    short location;
    bool is_exist;
    char sure;
    double amount = 0;
    do
    {
        take_acc_num(client_acc_num);
        is_exist = find_client_with_acc_num(clients_data, client_acc_num, target_client, location);
        if (is_exist)
        {
            double client_balance = stod(target_client[4]);
            print_client_data(target_client);
            ///// if withdraw
            if (type == "withdraw")
            {
                do
                {
                    amount = read_a_positive_number("Please Enter your amount : ");
                    if (amount <= client_balance)
                    {
                        while (sure != 'Y' && sure != 'y')
                        {
                            sure = confirm_perform("Are you sure ? (Y/N) : ");
                        }
                        client_balance -= amount;
                        break;
                    }
                    else
                        cout << "Amount Exceeds the balance you can withdraw up to " << client_balance << endl;
                } while (amount > client_balance);
            }
            ///// if deposit
            else
            {
                amount = read_a_positive_number("Please Enter your amount : ");
                while (sure != 'Y' && sure != 'y')
                {
                    sure = confirm_perform("Are you sure ? (Y/N) : ");
                }
                client_balance += amount;
            }
            target_client[4] = to_string(client_balance);
            update_client_balance_in_vector(clients_data, convert_vector_record_to_line(target_client, "#//#"), location);
            update_file_data(clients_data, file_name);

            if (type == "withdraw")
                cout << "this amount was deposited successfully and your balance now is : " << client_balance << endl;
            else
                cout << "this amount was withdrawn successfully and your balance now is : " << client_balance << endl;
        }
        else
        {
            cout << "Client with account number (" << client_acc_num << ") not found!\n";
        }
    } while (!is_exist);
}

void display_total_balances(vector<string> clients_data)
{
    vector<string> client;
    double total_balances = 0;
    cout << "\n\t\t\t\t Client list (" << clients_data.size() << ") clients(s)\t\t\t\t" << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;
    cout << "| Account number " << setw(19);
    cout << "| Client Name " << setw(28);
    cout << "| Balance " << endl;
    cout << "--------------------------------------------------------------------------------------------\n\n";
    for (short i = 0; i < clients_data.size(); i++)
    {
        client = convert_line_to_record(clients_data.at(i), "#//#");
        total_balances += stod(client[4]);
        cout << "| " << setw(20) << left << client[0];
        cout << "| " << setw(30) << left << client[2];
        cout << "| " << stoi(client[4]) << " \n";
        client.clear();
    }
    cout << "\n--------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t Total balances = $" << total_balances << "\t\t\t\t" << endl;
}

void go_to_transactions_msg()
{
    cout << "Press Any Key To go to transactions menu" << endl;
    system("pause>0");
}

void run_transactions_menu(vector<string> clients_data, string file_name)
{
    short user_choice;
    do
    {
        display_transactions_menu();
        take_user_choice_num_in_range(user_choice, 1, 4);
        cin.ignore();

        switch (user_choice)
        {
        case 1:
            deposit_withdraw_operations(clients_data, file_name, "deposit");
            go_to_transactions_msg();
            break;
        case 2:
            deposit_withdraw_operations(clients_data, file_name, "withdraw");
            go_to_transactions_msg();
            break;
        case 3:
            display_total_balances(clients_data);
            go_to_transactions_msg();
            break;
        case 4:
            cout << "Existing..." << endl;
            break;
        }
    } while (user_choice != 4);
}

/////-----------------------------------------------------------------------------------------------------------------------

void go_to_menu_msg()
{
    cout << "Press Any Key To go to menu" << endl;
    system("pause>0");
}

void small_bank_project()
{
    string file_name = "myFile.txt";
    short user_choice;
    vector<string> clients_data;
    read_file_lines(file_name, clients_data);
    do
    {
        display_services_menu();
        take_user_choice_num_in_range(user_choice, 1, 7);
        cin.ignore();
        switch (user_choice)
        {
        case 1:
            show_clients_list("myFile.txt");
            go_to_menu_msg();
            break;
        case 2:
            add_new_client(clients_data, file_name);
            go_to_menu_msg();
            break;
        case 3:
            delete_client(clients_data, file_name);
            go_to_menu_msg();
            break;
        case 4:
            update_client_info(clients_data, file_name);
            go_to_menu_msg();
            break;
        case 5:
            find_client(clients_data, file_name);
            go_to_menu_msg();
            break;
        case 6:
            run_transactions_menu(clients_data, file_name);
            break;
        case 7:
            system("cls");
            break;
        }
    } while (user_choice != 7);
}

/////-----------------------------------------------------------------------------------------------------------------------

int main()
{
    small_bank_project();

    return 0;
}
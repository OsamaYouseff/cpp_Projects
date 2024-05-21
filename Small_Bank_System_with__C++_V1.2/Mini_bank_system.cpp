#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <bitset>
#include <algorithm>
using namespace std;

struct stClient_data
{
    string acc_num;
    string name;
    string phone;
    string pin_code;
    double balance;
};

struct stUser_permissions
{
    char show_clients_list = 'N';
    char add_new_client = 'N';
    char delete_client = 'N';
    char update_client = 'N';
    char find_client = 'N';
    char transactions = 'N';
    char manage_users = 'N';
};

struct stUser_data
{
    string user_name;
    string password;
    int permissions_num;
    bool is_admin;
};

enum enMain_menu_choices
{
    one = 1,
    two = 2,
    three = 3,
    four = 4,
    five = 5,
    six = 6,
    seven = 7,
    eight = 8,
    nine = 9,
};

/////-----------------------------------------------------------------------------------------------------------------------
/////// functions declaration
void main_menu(vector<string> logged_user);

/////-----------------------------------------------------------------------------------------------------------------------
///// Displays in app

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

void display_operation_screen(string operation_name)
{
    system("cls");
    cout << "\n===================================================\n";
    cout << "\t\t" << operation_name << "\t\t\t";
    cout << "\n===================================================\n";
}

void display_login_screen()
{
    system("cls");
    cout << "\n===================================================\n";
    cout << "\t\t   Login Screen\t\t\t";
    cout << "\n===================================================\n";
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
    cout << "[ 6 ] Transactions.\n";
    cout << "[ 7 ] Manage Users.\n";
    cout << "[ 8 ] Logout.\n";
    cout << "[ 9 ] Exit.\n";
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

void display_manage_users_menu()
{
    system("cls");
    cout << "\n===================================================\n";
    cout << "\t\tManage Users Menu\t\t\t";
    cout << "\n===================================================\n";
    cout << "[ 1 ] Users List.\n";
    cout << "[ 2 ] Add new user.\n";
    cout << "[ 3 ] Delete user.\n";
    cout << "[ 4 ] Update user.\n";
    cout << "[ 5 ] Find User.\n";
    cout << "[ 6 ] Main Menu.\n";
    cout << "===================================================\n";
}

void display_declined_access_msg()
{
    cout << "\n\n===========================================\n\n";
    cout << "Access denied \n";
    cout << "You don't have any permissions to do this. \n";
    cout << "Contact with admin for more info \n";
    cout << "\n===========================================\n\n";
    system("pause>0");
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
///// show clients list technique

void read_file_lines(string clients_file_name, vector<string> &clients_data)
{
    fstream my_new_file;
    my_new_file.open(clients_file_name, ios::in); //// reading  mode => reads file only
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

void display_clients_data(vector<string> clients_data)
{
    vector<string> client;
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
            client = convert_line_to_record(clients_data.at(i), "#//#");
            cout << "| " << setw(20) << left << client[0];
            cout << "| " << setw(9) << left << client[1];
            cout << "| " << setw(24) << left << client[2];
            cout << "| " << setw(24) << left << client[3];
            cout << "| " << stoi(client[4]) << " \n";
            client.clear();
        }
    }
    cout << "\n--------------------------------------------------------------------------------------------------\n\n";
}

void show_clients_list(const string clients_file_name = "clients.txt")
{
    display_operation_screen("Show Clients List");
    vector<string> clients_data;
    read_file_lines(clients_file_name, clients_data);
    display_clients_data(clients_data);
}

/////-----------------------------------------------------------------------------------------------------------------------
/////  add new client technique

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

string convert_record_to_line(stClient_data client, string separator = "#//#")
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
    stClient_data data;
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

void add_new_client_data_to_file(string new_client, string clients_file_name = "clients.txt")
{

    fstream my_new_file;
    my_new_file.open(clients_file_name, ios::out | ios::app);
    if (my_new_file.is_open())
    {
        my_new_file << new_client << "\n";
        my_new_file.close();
    }
}

void add_new_client(vector<string> &clients_data, string clients_file_name)
{
    display_operation_screen("Add New Client");

    char add_more = 'N';

    do
    {
        add_new_client_data_to_file(get_new_client_data_in_one_line(clients_data), clients_file_name);

        ///// ask to add more clients
        cout << "Do you want to add more clients (Y / N) : ";
        cin >> add_more;
        cin.ignore();

    } while (add_more == 'Y' || add_more == 'y');

    cout << "New user Was Added Successfully.\n";
}

/////-----------------------------------------------------------------------------------------------------------------------
/////  delete client technique

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

void update_file_data(vector<string> clients_data, string clients_file_name)
{
    fstream users_data;

    users_data.open(clients_file_name, ios::out);

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

void refresh_client_data_in_vector(vector<string> &clients_data, string clients_file_name)
{
    clients_data.clear();
    read_file_lines(clients_file_name, clients_data);
}

void delete_client(vector<string> &clients_data, string clients_file_name)
{
    display_operation_screen("Delete Client");

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
                update_file_data(clients_data, clients_file_name);
                cout << "Client was deleted successfully." << endl;
            }
        }
        else
            cout << "Client with account number (" << client_acc_num << ") not found!\n";
    } while (!is_exist);

    refresh_client_data_in_vector(clients_data, clients_file_name);
}

/////-----------------------------------------------------------------------------------------------------------------------
///// update client technique

string read_client_data(string client_acc_num)
{
    stClient_data data;
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

void update_client_info(vector<string> clients_data, string clients_file_name)
{
    display_operation_screen("Update Client");

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
                clients_data[location] = read_client_data(client_acc_num);
                update_file_data(clients_data, clients_file_name);
                cout << "Client was updated successfully." << endl;
            }
        }
        else
            cout << "Client with account number (" << client_acc_num << ") not found!\n";
    } while (!is_exist);

    refresh_client_data_in_vector(clients_data, clients_file_name);
}

/////-----------------------------------------------------------------------------------------------------------------------
///// find client technique

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

void find_client(vector<string> clients_data, string clients_file_name)
{
    display_operation_screen("Find Client");
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

///// transactions menu functions

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

void take_amount_multi_of_5(int &amount)
{
    do
    {
        amount = read_a_positive_number("Please Enter your amount : ");
        if (amount % 5 != 0)
            cout << "You have to deposit money A multiple of 5  like : {5,10,15....} \n";
    } while (amount % 5 != 0);
}

void deposit_withdraw_operations(vector<string> &clients_data, string clients_file_name, string type)
{
    vector<string> target_client;
    string client_acc_num;
    short location;
    bool is_exist;
    char sure;
    int amount = 0;
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
                    take_amount_multi_of_5(amount);
                    if (amount <= client_balance)
                    {
                        while (sure != 'Y' && sure != 'y')
                        {
                            string msg = "Are you sure that you want to withdraw " + to_string(amount) + " ? (Y / N) : ";
                            sure = confirm_perform(msg);

                            if (sure == 'n' || sure == 'N')
                                return;
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
                take_amount_multi_of_5(amount);
                while (sure != 'Y' && sure != 'y')
                {
                    string msg = "Are you sure that you want to deposit " + to_string(amount) + " ? (Y / N) : ";
                    sure = confirm_perform(msg);

                    if (sure == 'n' || sure == 'N')
                        return;
                }
                client_balance += amount;
            }
            target_client[4] = to_string(client_balance);
            update_client_balance_in_vector(clients_data, convert_vector_record_to_line(target_client, "#//#"), location);
            update_file_data(clients_data, clients_file_name);

            if (type == "withdraw")
                cout << "this amount was withdrawn successfully and your balance now is : " << client_balance << endl;
            else
                cout << "this amount was deposited successfully and your balance now is : " << client_balance << endl;
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

void run_transactions_menu(vector<string> clients_data, string clients_file_name, stUser_permissions permissions)
{

    short user_choice;
    do
    {
        display_transactions_menu();
        take_user_choice_num_in_range(user_choice, 1, 4);
        cin.ignore();

        /////// performing transactions menu operations
        switch (user_choice)
        {
        case enMain_menu_choices::one:
            deposit_withdraw_operations(clients_data, clients_file_name, "deposit");
            go_to_transactions_msg();
            break;
        case enMain_menu_choices::two:
            deposit_withdraw_operations(clients_data, clients_file_name, "withdraw");
            go_to_transactions_msg();
            break;
        case enMain_menu_choices::three:
            display_total_balances(clients_data);
            go_to_transactions_msg();
            break;
        case enMain_menu_choices::four:
            cout << "Existing..." << endl;
            break;
        }
    } while (user_choice != 4);
}

/*



*/

/////-----------------------------------------------------------------------------------------------------------------------
////// login function

bool is_user_exist_in_system(string user_name, string password, vector<string> &logged_user)
{
    vector<string> users_data, current_user;
    read_file_lines("users.txt", users_data);

    for (string &user : users_data)
    {
        current_user = convert_line_to_record(user, "#//#");

        if (current_user[0] == user_name && current_user[1] == password)
        {
            logged_user = current_user;
            return true;
        }
    }

    return false;
}

void run_login_screen()
{
    string user_name, password;
    vector<string> logged_user;

    do
    {
        display_login_screen();
        cout << "Enter User Name : ";
        getline(cin >> ws, user_name);

        cout << "Enter Password : ";
        getline(cin, password);

        if (is_user_exist_in_system(user_name, password, logged_user))
            break;
        // cout << "User is exist ";
        else
        {
            cout << "User is not exist!! \n\n";
            system("pause>0");
        }

    } while (!is_user_exist_in_system(user_name, password, logged_user));

    main_menu(logged_user);
}

/////-----------------------------------------------------------------------------------------------------------------------
///// manage users menu functions

bitset<sizeof(int) * 2> convert_decimal_to_binary(int decimalNumber)
{
    bitset<sizeof(int) * 2> binaryRepresentation(decimalNumber);
    return binaryRepresentation;
}

int convert_binary_to_decimal()
{
    string binaryString;
    cout << "Enter a binary number: ";
    cin >> binaryString;
    int decimalNumber = stoi(binaryString, 0, 2); // For 32-bit integers
    return 0;
}

vector<string> add_binary_code_to_vec(string str_binary)
{
    vector<string> result;

    cout << "Binary Str :" << str_binary << endl;

    for (int i = 0; i < str_binary.length(); i++)
    {
        result.push_back(to_string(str_binary[i] - '0'));
    }

    return result;
}

char convert_permission_from_binary_to_yor_n(string num)
{
    return num == "0" ? 'N' : 'Y';
}

stUser_permissions generate_user_permissions_struct(int permissions_num)
{

    bitset<sizeof(int) * 2> binary = convert_decimal_to_binary(permissions_num);
    string str_binary = binary.to_string();
    vector<string> permissions_id = add_binary_code_to_vec(str_binary);
    reverse(permissions_id.begin(), permissions_id.end());

    stUser_permissions permissions;

    ////// -1  means user is an admin and ahve full permissions
    if (permissions_num == -1)
    {
        permissions.show_clients_list = 'Y';
        permissions.add_new_client = 'Y';
        permissions.delete_client = 'Y';
        permissions.update_client = 'Y';
        permissions.find_client = 'Y';
        permissions.transactions = 'Y';
        permissions.manage_users = 'Y';
    }
    else
    {
        permissions.show_clients_list = convert_permission_from_binary_to_yor_n(permissions_id[0]);
        permissions.add_new_client = convert_permission_from_binary_to_yor_n(permissions_id[1]);
        permissions.delete_client = convert_permission_from_binary_to_yor_n(permissions_id[2]);
        permissions.update_client = convert_permission_from_binary_to_yor_n(permissions_id[3]);
        permissions.find_client = convert_permission_from_binary_to_yor_n(permissions_id[4]);
        permissions.transactions = convert_permission_from_binary_to_yor_n(permissions_id[5]);
        permissions.manage_users = convert_permission_from_binary_to_yor_n(permissions_id[6]);
    }

    return permissions;
}

int generate_user_permissions_num(stUser_permissions permissions)
{
    int permissions_num = 0;

    if (permissions.show_clients_list == 'Y' || permissions.show_clients_list == 'y')
        permissions_num += pow(2, 0);

    if (permissions.add_new_client == 'Y' || permissions.add_new_client == 'y')
        permissions_num += pow(2, 1);

    if (permissions.delete_client == 'Y' || permissions.delete_client == 'y')
        permissions_num += pow(2, 2);

    if (permissions.update_client == 'Y' || permissions.update_client == 'y')
        permissions_num += pow(2, 3);

    if (permissions.find_client == 'Y' || permissions.find_client == 'y')
        permissions_num += pow(2, 4);

    if (permissions.transactions == 'Y' || permissions.transactions == 'y')
        permissions_num += pow(2, 5);

    if (permissions.manage_users == 'Y' || permissions.manage_users == 'y')
        permissions_num += pow(2, 6);

    return permissions_num;
}

void go_to_mange_users_menu_msg()
{
    cout << "Press Any Key To go to mange users menu" << endl;
    system("pause>0");
}

/////-------------------------------------------------------
//////  show users list technique

void display_users_data(vector<string> users_data)
{
    display_operation_screen("Display Users");
    vector<string> user;

    cout << "\n\t\t\t\t Users list (" << users_data.size() << ") Users(s)\t\t\t\t" << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;
    cout << "| User Name " << setw(21);
    cout << "| Password " << setw(29);
    cout << "| Permissions " << endl;
    cout << "--------------------------------------------------------------------------------------------\n\n";
    if (users_data.empty())
    {
        cout << "\n\t\t\t   there is no clients in this system \t\t\t\t" << endl;
    }
    else
    {
        for (short i = 0; i < users_data.size(); i++)
        {
            user = convert_line_to_record(users_data.at(i), "#//#");
            cout << "| " << setw(20) << left << user[0];
            cout << "| " << setw(24) << left << user[1];
            cout << "| " << stoi(user[2]) << " \n";
            user.clear();
        }
    }
    cout << "\n--------------------------------------------------------------------------------------------\n\n";
}

void show_users_list(vector<string> users_data, const string clients_file_name = "clients.txt")
{
    display_users_data(users_data);
}

/////-------------------------------------------------------
////// find user technique

void take_user_name(string &user_name)
{
    cout << "Please enter user name : ";
    cin >> user_name;
}

bool find_user_with_user_name(vector<string> users_data, string user_name, vector<string> &target_user, short &location)
{
    vector<string> current_user;
    for (short i = 0; i < users_data.size(); i++)
    {
        current_user = convert_line_to_record(users_data.at(i), "#//#");
        if (current_user[0] == user_name)
        {
            target_user = current_user;
            location = i;
            return true;
        }
        current_user.clear();
    }

    return false;
}

void print_user_data(vector<string> user)
{
    cout << "\n-----------------------------------\n";
    cout << "The following user data is \n";
    cout << "-----------------------------------\n";
    cout << "User Name        : " << user[0] << endl;
    cout << "Password         : " << user[1] << endl;
    cout << "Permission       : " << user[2] << endl;
    cout << "-----------------------------------\n";
}

void find_user(vector<string> users_data, string users_file_name)
{
    display_operation_screen("Find User");
    vector<string> target_user;
    string user_name;
    take_user_name(user_name);
    short location;
    bool is_exist;

    is_exist = find_user_with_user_name(users_data, user_name, target_user, location);
    if (is_exist)
    {
        print_user_data(target_user);
    }
    else
    {
        cout << "Sorry, this user is not exist! " << endl;
    }
}

/////-------------------------------------------------------
///// add new user technique

bool check_user_acc_name_is_not_exist_before_in_file(vector<string> users_data, string user_name)
{
    vector<string> user;

    for (short i = 0; i < users_data.size(); i++)
    {
        user = convert_line_to_record(users_data.at(i), "#//#");
        if (user[0] == user_name)
        {
            return true;
        }
        user.clear();
    }

    return false;
}

void choice_new_user_permissions(stUser_permissions &permissions)
{
    cout << "[ 1 ] Do want to give access to show clients list (Y/n) : ";
    cin >> permissions.show_clients_list;
    cin.ignore();
    cout << "[ 2 ] Do want to give access to add new client (Y/n) : ";
    cin >> permissions.add_new_client;
    cin.ignore();
    cout << "[ 3 ] Do want to give access to delete client (Y/n) : ";
    cin >> permissions.delete_client;
    cin.ignore();
    cout << "[ 4 ] Do want to give access to update client (Y/n) : ";
    cin >> permissions.update_client;
    cin.ignore();
    cout << "[ 5 ] Do want to give access to find client (Y/n) : ";
    cin >> permissions.find_client;
    cin.ignore();
    cout << "[ 6 ] Do want to give access to transactions (Y/n) : ";
    cin >> permissions.transactions;
    cin.ignore();
    cout << "[ 7 ] Do want to give access to manage users (Y/n) : ";
    cin >> permissions.manage_users;
    cin.ignore();
}

string convert_record_to_line_for_users(stUser_data user, string separator = "#//#")
{
    string final_string = "";

    final_string += user.user_name + separator;
    final_string += user.password + separator;
    final_string += to_string(user.permissions_num) + separator;
    final_string += to_string(user.is_admin);

    return final_string;
}

string get_new_user_data_in_one_line(vector<string> users_data)
{
    stUser_data data;
    string name;
    string target_user;
    bool is_exist;
    do
    {
        cout << "Enter User name : ";
        getline(cin >> ws, data.user_name);
        ////// check if user name is not exist before
        is_exist = check_user_acc_name_is_not_exist_before_in_file(users_data, data.user_name);

        if (is_exist)
        {
            cout << "The user name (" << data.user_name << ") is already exist try another one. " << endl;
        }
    } while (is_exist);

    cout << "Enter password : ";
    getline(cin, data.password);

    char full_access;

    cout << "Do you want to give it full access ? (y/n) : ";
    cin >> full_access;

    if (full_access == 'Y' || full_access == 'y')
    {
        data.permissions_num = -1;
        data.is_admin = true;
    }
    else
    {
        /////// read all permissions from input and covert it to special binary num
        stUser_permissions permissions;
        choice_new_user_permissions(permissions);
        data.permissions_num = generate_user_permissions_num(permissions);

        ////// means that user has all permissions
        if (data.permissions_num == 127)
        {
            data.permissions_num = -1;
            data.is_admin = true;
        }
        else
            data.is_admin = false;
    }

    target_user = convert_record_to_line_for_users(data, "#//#");
    return target_user;
}

void add_new_user_data_to_file(string new_user, string users_file_name = "users.txt")
{

    fstream my_new_file;
    my_new_file.open(users_file_name, ios::out | ios::app);
    if (my_new_file.is_open())
    {
        my_new_file << new_user << "\n";
        my_new_file.close();
    }
}

void add_new_user(vector<string> &users_data, string users_file_name)
{
    display_operation_screen("Add New User");

    char add_more = 'N';
    do
    {
        add_new_user_data_to_file(get_new_user_data_in_one_line(users_data), users_file_name);

        ///// ask to add more users
        cout << "Do you want to add more users (Y / N) : ";
        cin >> add_more;
        cin.ignore();
    } while (add_more == 'Y' || add_more == 'y');

    cout << "New user Was Added Successfully.\n";
}

/////-------------------------------------------------------
/////delete user technique

void delete_user_from_data_vector(vector<string> &users_data, short location)
{
    users_data.erase(users_data.begin() + location);
}

void update_file_data_for_users(vector<string> users_data, string users_file_name)
{
    fstream users;

    users.open(users_file_name, ios::out);

    if (users.is_open())
    {
        for (string &user : users_data)
        {
            users << user << "\n";
        }
        users.close();
    }
}

void refresh_user_data_in_vector(vector<string> &users_data, string users_file_name)
{
    users_data.clear();
    read_file_lines(users_file_name, users_data);
}

void delete_user(vector<string> &users_data, string users_file_name, vector<string> logged_user, vector<string> &target_user)
{
    display_operation_screen("Delete User");
    string user_acc_num;
    short location;
    char confirm_delete = 'N';
    bool is_exist;
    do
    {
        take_user_name(user_acc_num);
        is_exist = find_user_with_user_name(users_data, user_acc_num, target_user, location);
        if (user_acc_num == "Admin")
        {
            cout << "You can't delete Admin account! ";
            continue;
        }

        if (is_exist && user_acc_num != "Admin")
        {
            print_user_data(target_user);
            cout << "Are you sure that you want to delete this user ? (Y/N)  : ";
            cin >> confirm_delete;
            if (confirm_delete == 'Y' || "y")
            {
                delete_user_from_data_vector(users_data, location);
                update_file_data(users_data, users_file_name);
                cout << "user was deleted successfully." << endl;
                system("pause>0");
            }
        }
        else
            cout << "user with User name (" << user_acc_num << ") not found!\n";
    } while (!is_exist);

    refresh_user_data_in_vector(users_data, users_file_name);
}

/////-------------------------------------------------------
///// update user technique

vector<string> convert_line_to_record_as_vec(string text, string delim = "#//#")
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

stUser_data convert_line_to_record_for_users(string user_date)
{
    stUser_data user;
    vector<string> user_data = convert_line_to_record_as_vec(user_date, "#//#");

    user.user_name = user_data[0];
    user.password = user_data[1];
    user.permissions_num = stoi(user_data[2]);
    user.is_admin = stoi(user_data[3]);

    return user;
}

void update_user_info(vector<string> &users_data, string users_file_name, vector<string> logged_user, vector<string> &target_user)
{
    display_operation_screen("Update User");
    short location;
    char confirm_update = 'N';
    string user_name;
    bool is_exist;

    do
    {
        take_user_name(user_name);
        is_exist = find_user_with_user_name(users_data, user_name, target_user, location);
        if (is_exist)
        {
            print_user_data(target_user);
            cout << "Are you sure that you want to update this user ? (Y/N)  : ";
            cin >> confirm_update;
            if (confirm_update == 'Y' || 'y')
            {
                stUser_data updated_user = convert_line_to_record_for_users(get_new_user_data_in_one_line(users_data));
                users_data[location] = convert_record_to_line_for_users(updated_user, "#//#");
                update_file_data_for_users(users_data, users_file_name);
                cout << "user was updated successfully." << endl;
                system("pause>0");
            }
        }
        else
            cout << "user with name (" << user_name << ") not found!\n";
    } while (!is_exist);

    refresh_user_data_in_vector(users_data, users_file_name);
}

/////-------------------------------------------------------

void run_display_manage_users_menu(vector<string> users_data, string users_file_name, vector<string> logged_user, stUser_permissions permissions)
{

    vector<string> target_user;

    short user_choice;
    do
    {
        display_manage_users_menu();
        take_user_choice_num_in_range(user_choice, 1, 6);
        cin.ignore();

        /////// performing manage users menu operations
        switch (user_choice)
        {
        case enMain_menu_choices::one:
            show_users_list(users_data, users_file_name);
            go_to_mange_users_menu_msg();
            break;
        case enMain_menu_choices::two:
            add_new_user(users_data, users_file_name);
            go_to_mange_users_menu_msg();
            break;
        case enMain_menu_choices::three:
            delete_user(users_data, users_file_name, logged_user, target_user);

            //////// check if logged user is the same user with deleted acc if true log out else allow to go to manage menu
            if (logged_user[0] == target_user[0])
                run_login_screen();
            else
                go_to_mange_users_menu_msg();
            break;
        case enMain_menu_choices::four:
            update_user_info(users_data, users_file_name, logged_user, target_user);

            //////// check if logged user is the same user with updated acc if true log out else allow to go to manage menu
            if (logged_user[0] == target_user[0])
                run_login_screen();
            else
                go_to_mange_users_menu_msg();
            break;
        case enMain_menu_choices::five:
            find_user(users_data, users_file_name);
            go_to_mange_users_menu_msg();
            break;
        case enMain_menu_choices::six:
            display_services_menu();
            break;
        }

    } while (user_choice != 6);
}

/////-----------------------------------------------------------------------------------------------------------------------

void go_to_menu_msg()
{
    cout << "Press Any Key To go to menu" << endl;
    system("pause>0");
}

bool check_if_user_has_permissions(char permission_type)
{
    if (permission_type == 'N')
    {
        display_declined_access_msg();
        return false;
    }
    return true;
}

void main_menu(vector<string> logged_user)
{
    string clients_file_name = "clients.txt";
    string users_file_name = "users.txt";
    short user_choice;
    vector<string> users_data, clients_data;

    read_file_lines(users_file_name, users_data);
    read_file_lines(clients_file_name, clients_data);

    ////// create current user permissions
    stUser_permissions permissions = generate_user_permissions_struct(stoi(logged_user[2]));

    do
    {
        display_services_menu();
        take_user_choice_num_in_range(user_choice, 1, 9);
        cin.ignore();

        /////// performing main menu operations
        switch (user_choice)
        {
        case enMain_menu_choices::one:
            if (!check_if_user_has_permissions(permissions.show_clients_list))
                break;
            show_clients_list(clients_file_name);
            go_to_menu_msg();
            break;
        case enMain_menu_choices::two:
            if (!check_if_user_has_permissions(permissions.show_clients_list))
                break;
            if (permissions.add_new_client == 'N')
            {
                display_declined_access_msg();
                break;
            }
            add_new_client(clients_data, clients_file_name);
            go_to_menu_msg();
            break;
        case enMain_menu_choices::three:
            if (!check_if_user_has_permissions(permissions.delete_client))
                break;
            delete_client(clients_data, clients_file_name);
            go_to_menu_msg();
            break;
        case enMain_menu_choices::four:
            if (!check_if_user_has_permissions(permissions.update_client))
                break;
            update_client_info(clients_data, clients_file_name);
            go_to_menu_msg();
            break;
        case enMain_menu_choices::five:
            if (!check_if_user_has_permissions(permissions.find_client))
                break;
            find_client(clients_data, clients_file_name);
            go_to_menu_msg();
            break;
        case enMain_menu_choices::six:
            if (!check_if_user_has_permissions(permissions.transactions))
                break;
            run_transactions_menu(clients_data, clients_file_name, permissions);
            break;
        case enMain_menu_choices::seven:
            if (!check_if_user_has_permissions(permissions.manage_users))
                break;
            run_display_manage_users_menu(users_data, users_file_name, logged_user, permissions);
            break;
        case enMain_menu_choices::eight:
            display_login_screen();
            run_login_screen();
            break;
        case enMain_menu_choices::nine:
            cout << "Exiting..\n";
            break;
        }
    } while (user_choice != 9);
}

/////-----------------------------------------------------------------------------------------------------------------------

int main()
{
    run_login_screen();
    return 0;
}
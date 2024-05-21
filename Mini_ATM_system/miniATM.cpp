#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

struct stClient_data
{
    string acc_num;
    string name;
    string phone;
    string pin_code;
    double balance;
};

////-----------------------------------------------------------------------------------------------------------

void main_menu(vector<string> logged_client);

////-----------------------------------------------------------------------------------------------------------

int read_a_positive_number(string msg)
{
    int num;
    do
    {
        cout << msg;
        cin >> num;
    } while (num <= 0);
    return num;
}

void take_client_choice_num_in_range(short &client_choice, short from, short to)
{
    do
    {
        cout << "Please enter your choice from [ " << from << " ] to [ " << to << " ] : ";
        cin >> client_choice;
    } while (client_choice < from || client_choice > to);
}

void display_login_screen()
{
    system("cls");
    cout << "\n===================================================\n";
    cout << "\t\t   Login Screen\t\t\t";
    cout << "\n===================================================\n";
}

void display_main_menu()
{
    system("cls");
    cout << "\n===================================================\n";
    cout << "\t\tATM main Menu Screen\t\t\t";
    cout << "\n===================================================\n";
    cout << "[ 1 ] Quick withdraw.\n";
    cout << "[ 2 ] Normal withdraw.\n";
    cout << "[ 3 ] Deposit.\n";
    cout << "[ 4 ] Check balance.\n";
    cout << "[ 5 ] Logout.\n";
    cout << "[ 6 ] Exit.\n";
    cout << "===================================================\n";
}

////-----------------------------------------------------------------------------------------------------------

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

////-----------------------------------------------------------------------------------------------------------

void take_acc_num(string &client_acc_num)
{
    cout << "Please enter the account number : ";
    cin >> client_acc_num;
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

void update_client_balance_in_vector(vector<string> &clients_data, string client_new_info, short location)
{
    clients_data[location] = client_new_info;
}

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

void show_balance(vector<string> client)
{
    cout << "\n-----------------------------------\n";
    cout << "Account Balance  : " << stoi(client[4]) << endl;
    cout << "-----------------------------------\n";
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

short find_client_location_in_vec(vector<string> clients_data, string client_acc_num)
{
    vector<string> current_client;
    for (short i = 0; i < clients_data.size(); i++)
    {
        current_client = convert_line_to_record(clients_data.at(i), "#//#");
        if (current_client[0] == client_acc_num)
        {
            return i;
        }
        current_client.clear();
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

void deposit_withdraw_operations(vector<string> &clients_data, string clients_file_name, vector<string> &logged_client, string type, bool show_bala = false, int amount = 0)
{
    vector<string> target_client;
    short location;
    char sure;
    double client_balance = stod(logged_client[4]);
    bool is_amount_no_exceeds = false;

    // bool amount_exceeds = true;

    location = find_client_location_in_vec(clients_data, logged_client[0]);

    if (show_bala)
        show_balance(logged_client);

    ///// if withdraw
    if (type == "withdraw")
    {
        do
        {
            if (is_amount_no_exceeds == false)
            {
                if (amount == 0) ////// means not quick withdraw
                {
                    take_amount_multi_of_5(amount);

                    if (amount < client_balance)
                        is_amount_no_exceeds = true;
                }
            }

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
            {
                cout << "Amount Exceeds the balance you can withdraw up to " << client_balance << endl;
            }
        } while (!is_amount_no_exceeds);
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
    logged_client[4] = to_string(client_balance);
    update_client_balance_in_vector(clients_data, convert_vector_record_to_line(logged_client, "#//#"), location);
    update_file_data(clients_data, clients_file_name);

    if (type == "withdraw")
        cout << "this amount was withdrawn successfully and your balance now is : " << client_balance << endl;
    else
        cout << "this amount was deposited successfully and your balance now is : " << client_balance << endl;
}

void display_quick_withdraw_options()
{
    system("cls");
    cout << "\n===================================================\n";
    cout << "\t\t Quick withdraw menu\t\t\t";
    cout << "\n===================================================\n";
    cout << "[ 1 ] 20         [ 2 ] 50\n";
    cout << "[ 3 ] 100        [ 4 ] 150\n";
    cout << "[ 5 ] 200        [ 6 ] 500\n";
    cout << "[ 7 ] 1000       [ 8 ] 5000\n";
    cout << "[ 9 ] Exit.\n";
    cout << "===================================================\n";
}

enum enQuick_balances
{
    one = 20,
    two = 50,
    three = 100,
    four = 150,
    five = 200,
    six = 500,
    seven = 1000,
    eight = 5000,
};

void quick_withdraw_operation(vector<string> &clients_data, string clients_file_name, vector<string> &logged_client)
{
    short user_choice;
    bool is_amount_no_exceeds = false;
    display_quick_withdraw_options();
    show_balance(logged_client);
    enQuick_balances quick_amount[8] = {enQuick_balances::one, enQuick_balances::two, enQuick_balances::three, enQuick_balances::four, enQuick_balances::five, enQuick_balances::six, enQuick_balances::seven, enQuick_balances::eight};
    do
    {
        take_client_choice_num_in_range(user_choice, 1, 9);
        ////// check that user withdraw amount is lower than his balance
        if (stoi(logged_client[4]) < quick_amount[user_choice])
            cout << "Amount Exceeds the balance you can withdraw up to " << stoi(logged_client[4]) << endl;
        else
            is_amount_no_exceeds = true;
    } while (!is_amount_no_exceeds);

    switch (user_choice)
    {
    case 1:
        deposit_withdraw_operations(clients_data, clients_file_name, logged_client, "withdraw", false, enQuick_balances::one);
        break;
    case 2:
        deposit_withdraw_operations(clients_data, clients_file_name, logged_client, "withdraw", false, enQuick_balances::two);
        break;
    case 3:
        deposit_withdraw_operations(clients_data, clients_file_name, logged_client, "withdraw", false, enQuick_balances::three);
        break;
    case 4:
        deposit_withdraw_operations(clients_data, clients_file_name, logged_client, "withdraw", false, enQuick_balances::four);
        break;
    case 5:
        deposit_withdraw_operations(clients_data, clients_file_name, logged_client, "withdraw", false, enQuick_balances::five);
        break;
    case 6:
        deposit_withdraw_operations(clients_data, clients_file_name, logged_client, "withdraw", false, enQuick_balances::six);
        break;
    case 7:
        deposit_withdraw_operations(clients_data, clients_file_name, logged_client, "withdraw", false, enQuick_balances::seven);
        break;
    case 8:
        deposit_withdraw_operations(clients_data, clients_file_name, logged_client, "withdraw", false, enQuick_balances::eight);
        break;
    case 9:
        main_menu(logged_client);
        break;

    default:
        break;
    }
}

////-----------------------------------------------------------------------------------------------------------

bool is_client_exist_in_system(vector<string> clients_data, string client_acc_num, vector<string> &target_client, short &location)
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

void run_login_screen()
{
    string clients_file_name = "clients.txt";
    vector<string> clients_data;
    read_file_lines(clients_file_name, clients_data);
    string account_num, pin;
    vector<string> logged_client;
    short location;

    do
    {
        display_login_screen();
        cout << "Enter your account num : ";
        getline(cin >> ws, account_num);

        cout << "Enter pin : ";
        getline(cin, pin);

        if (is_client_exist_in_system(clients_data, account_num, logged_client, location))
            break;
        else
        {
            cout << "wrong account number or password  !! \n\n";
            system("pause>0");
        }

    } while (!is_client_exist_in_system(clients_data, account_num, logged_client, location));

    main_menu(logged_client);
}

////-----------------------------------------------------------------------------------------------------------

void go_to_menu_msg()
{
    cout << "Press Any Key To go to menu" << endl;
    system("pause>0");
}

enum enMain_menu_choices
{
    one = 1,
    two = 2,
    three = 3,
    four = 4,
    five = 5,
    six = 6,
};

void main_menu(vector<string> logged_client)
{
    string clients_file_name = "clients.txt";
    vector<string> clients_data;
    read_file_lines(clients_file_name, clients_data);
    short client_choice;

    do
    {
        display_main_menu();
        take_client_choice_num_in_range(client_choice, 1, 6);
        cin.ignore();

        /////// performing main menu operations
        switch (client_choice)
        {
        case enMain_menu_choices::one:
            quick_withdraw_operation(clients_data, clients_file_name, logged_client);
            go_to_menu_msg();
            break;
        case enMain_menu_choices::two:
            deposit_withdraw_operations(clients_data, clients_file_name, logged_client, "withdraw", true);
            go_to_menu_msg();
            break;
        case enMain_menu_choices::three:
            deposit_withdraw_operations(clients_data, clients_file_name, logged_client, "deposit", true);
            go_to_menu_msg();
            break;
        case enMain_menu_choices::four:
            show_balance(logged_client);
            go_to_menu_msg();
            break;
        case enMain_menu_choices::five:
            run_login_screen();
            break;
        case enMain_menu_choices::six:
            cout << "Exiting..\n";
            return;
        }
    } while (client_choice != 6);
}

int main()
{
    run_login_screen();
    return 0;
}
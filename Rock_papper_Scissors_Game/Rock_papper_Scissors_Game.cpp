#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

enum enGameChoices
{
    rock,
    paper,
    scissors
};

struct stGame_info
{
    string arr_of_res[100];
    int arr_length = 0;
    bool more = false;
    int player_score = 0, computer_score = 0;
};

struct stRound_info
{
    int player_choice, computer_choice;
    string round_score = "";
};

void game_beginning_msg()
{
    cout << "///////////////////////////////////////////////////\n\n";
    cout << "        Welcome to Rock Paper Scissors Game\n\n";
    cout << "///////////////////////////////////////////////////\n\n ";
}

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

int read_a_positive_number_in_range(string msg, int from, int to)
{
    int num;
    do
    {
        cout << msg;
        cin >> num;
    } while (num < from || num > to);
    return num;
}

int random_number(int from, int to)
{
    return (rand() % (to - from + 1) + from);
}

int make_computer_chose()
{
    srand((unsigned)time(NULL)); //// you should call this line in plus these libraries ( #include <cstdlib> ,  #include <time.h> )
    int computer_choice = random_number(1, 3);

    return computer_choice;
}

void take_choices(int &player_choice, int &computer_choice)
{
    player_choice = read_a_positive_number_in_range("\nPlease Enter your choice [ (1) Rock - (2) Paper - (3) Scissors ] : ", 1, 3);

    computer_choice = make_computer_chose();
}

enGameChoices detect_choice(int choice)
{
    switch (choice)
    {
    case 1:
        return enGameChoices::rock;
    case 2:
        return enGameChoices::paper;
    case 3:
        return enGameChoices::scissors;
    default:
        return enGameChoices::rock;
    }
}

string choices_names(enGameChoices choice)
{
    switch (choice)
    {
    case enGameChoices::rock:
        return "Rock";
    case enGameChoices::paper:
        return "Paper";
    case enGameChoices::scissors:
        return "Scissors";
    default:
        break;
    }
}

void print_players_choices(enGameChoices player_choice, enGameChoices computer_choice)
{
    cout << "- Player have choice : " << choices_names(player_choice) << endl;
    cout << "- Computer have choice : " << choices_names(computer_choice) << endl;
}

int check_who_won(enGameChoices player_choice, enGameChoices computer_choice, int &player_score, int &computer_score)
{
    int winner;

    if (player_choice == computer_choice)
    {
        return 0;
    }

    //// Rock
    if (player_choice == enGameChoices::rock)
    {
        if (computer_choice == enGameChoices::paper)
        {
            winner = 2;
            computer_score++;
        }

        else
        {
            winner = 1;
            player_score++;
        }
    }

    //// Paper
    else if (player_choice == enGameChoices::paper)
    {
        if (computer_choice == enGameChoices::scissors)
        {
            winner = 2;
            computer_score++;
        }

        else
        {
            winner = 1;
            player_score++;
        }
    }

    //// scissors
    else if (player_choice == enGameChoices::scissors)
    {
        if (computer_choice == enGameChoices::rock)
        {
            winner = 2;
            computer_score++;
        }

        else
        {
            winner = 1;
            player_score++;
        }
    }

    return winner;
}

string print_round_winner(int winner_num)
{
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n";
    if (winner_num == 1)
    {
        cout << "\t\t- And The winner is << Player >> " << endl;
        system("color 2f");
        return "The Player won! ";
    }
    else if (winner_num == 2)
    {
        cout << "\t\t- And The winner is << Computer >> " << endl;
        system("color 4f");
        return "The Computer won! ";
    }
    else
    {
        cout << "\t\t- And No one won! result is 'Draw'  " << endl;
        system("color 6f");
        return "No one won! ";
    }
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
}

void add_result_to_array_results(string arr[100], int &arr_length, string ele)
{
    arr[arr_length] = ele;
    arr_length++;
}

void print_round_score(int player_score, int computer_score)
{
    cout << "\t\tThe Score now is "
         << "(( Player [" << player_score << "] :: Computer [" << computer_score << "] ))" << endl;
}

void rock_paper_scissors_round(string arr_of_res[100], int &arr_length, int &player_score, int &computer_score)
{
    //// data
    stRound_info round_info;

    take_choices(round_info.player_choice, round_info.computer_choice);

    enGameChoices player = detect_choice(round_info.player_choice);
    enGameChoices computer = detect_choice(round_info.computer_choice);

    cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    print_players_choices(player, computer);
    round_info.round_score = print_round_winner(check_who_won(player, computer, player_score, computer_score));
    cout << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";

    add_result_to_array_results(arr_of_res, arr_length, round_info.round_score);

    round_info.round_score = "";

    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n ";
    print_round_score(player_score, computer_score);
    cout << "\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n ";
}

void print_list_of_results(string arr[100], int arr_length)
{
    cout << "\n---------------------------------------------------------- \n";
    cout << "\t\tAll Rounds Results are ";
    cout << "\n---------------------------------------------------------- \n";
    for (size_t i = 0; i < arr_length; i++)
    {
        cout << "\t\tRound [ " << i + 1 << " ] - " << arr[i] << endl;
    }
    cout << "---------------------------------------------------------- \n";
}

void reset_the_game(int &player_score, int &computer_score, int &arr_length)
{
    player_score = 0;
    computer_score = 0;
    arr_length = 0;
    system("color 0f");
}

bool ask_for_more()
{
    bool ans;

    cout << "Do you want to play more ? ([1] yes  - [0] No) : ";
    cin >> ans;

    if (ans == 1)
        return true;
    else
        return false;
}

void print_full_game_results(stGame_info game_info, int num_of_rounds)
{
    cout << "\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n";
    print_list_of_results(game_info.arr_of_res, game_info.arr_length);
    cout << "\t\tPlayer won " << game_info.player_score << " time(s)" << endl;
    cout << "\t\tComputer won " << game_info.computer_score << " time(s)" << endl;
    cout << "\t\tDraw was " << (num_of_rounds - (game_info.player_score + game_info.computer_score)) << " time(s)" << endl;
    cout << "\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n";

    if (game_info.player_score > game_info.computer_score)
        cout
            << "\t\t<<Player >> is the final winner " << endl;
    else if (game_info.computer_score > game_info.player_score)
        cout << "\t\t<< Computer >> is the final winner " << endl;
    else
        cout << "\t\tNo one is the final winner " << endl;
    cout << "---------------------------------------------------------- \n";
    cout << "\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n ";
}

void the_full_game()
{

    game_beginning_msg();

    //// data
    stGame_info game_info;

    int num_of_rounds = read_a_positive_number("\nPlease Enter a number of rounds : ");
    cout << "\n\n";

    //// game mechanism
    for (int i = 0; i < num_of_rounds; i++)
    {
        cout << "\n\n~~~~~~~~~~~~~  Round [" << (i < 0 ? 0 : i + 1) << "] Begins ~~~~~~~~~~~~~\n\n ";
        rock_paper_scissors_round(game_info.arr_of_res, game_info.arr_length, game_info.player_score, game_info.computer_score);

        if (i + 1 == num_of_rounds)
        {

            print_full_game_results(game_info, num_of_rounds);

            reset_the_game(game_info.player_score, game_info.computer_score, game_info.arr_length);

            game_info.more = ask_for_more();
            system("cls");
            if (!game_info.more)
            {
                i = num_of_rounds;
                break;
            }
            else
            {
                i = -1;
                num_of_rounds = read_a_positive_number("\nPlease Enter a number of rounds : ");
            }
        }
    }
}

int main()
{

    the_full_game();

    return 0;
}

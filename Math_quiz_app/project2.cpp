#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

enum enQuestion_level
{
    Easy = 1,
    Mid = 2,
    Hard = 3,
    Mix = 4,
};

enum enOperation_type
{
    Add = 1,
    Sub = 2,
    Multi = 3,
    Division = 4,
    Mixed = 5
};

struct stRound_info
{
    short round_number;
    short first_num;
    short second_num;
    char op_type;
    short user_answer;
    short right_answer;
};

struct stExam_info
{
    short answered_questions = 0;
    short num_of_right_answers = 0;
    short num_of_wrong_answers = 0;
    enQuestion_level question_level;
    enOperation_type op_type;
    bool success_condition;
};

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

int read_a_number(string msg)
{
    int num;
    cout << msg;
    cin >> num;
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

int generate_random_number(int from, int to)
{
    return (rand() % (to - from + 1) + from);
}

void print_current_question_num(short curr_round_num, short rounds_num)
{
    cout << "Question [ " << curr_round_num << " / " << rounds_num << " ]" << endl;
    cout << "\n";
}

enQuestion_level check_question_level()
{
    int q_level = read_a_positive_number_in_range("Enter question level [1] Easy [2] Mid [3] Hard [4] Mix : ", 1, 4);
    switch (q_level)
    {
    case 1:
        return enQuestion_level::Easy;
    case 2:
        return enQuestion_level::Mid;
    case 3:
        return enQuestion_level::Hard;
    case 4:
        return enQuestion_level::Mix;
    default:
        return enQuestion_level::Easy;
        break;
    }
}

enOperation_type check_operation_type()
{
    int op_type = read_a_positive_number_in_range("Enter Operation type [1] Add [2] Sub [3] Multi [4] Division [5] Mix : ", 1, 5);

    switch (op_type)
    {
    case 1:
        return enOperation_type::Add;
    case 2:
        return enOperation_type::Sub;
    case 3:
        return enOperation_type::Multi;
    case 4:
        return enOperation_type::Division;
    case 5:
        return enOperation_type::Mixed;
    default:
        return enOperation_type::Add;
        break;
    }
}

short get_a_quiz_num(enQuestion_level level)
{
    switch (level)
    {
    case enQuestion_level::Easy:
        return generate_random_number(1, 10);
    case enQuestion_level::Mid:
        return generate_random_number(10, 50);
    case enQuestion_level::Hard:
        return generate_random_number(50, 100);
    case enQuestion_level::Mix:
        return generate_random_number(1, 100);

    default:
        return generate_random_number(1, 10);
    }
}

char get_operation_sign_as_char(enOperation_type op_type)
{
    srand((unsigned)time(NULL));

    char op_arr[5] = {' ', '+', '-', '*', '/'};

    switch (op_type)
    {
    case enOperation_type::Add:
        return op_arr[1];
    case enOperation_type::Sub:
        return op_arr[2];
    case enOperation_type::Multi:
        return op_arr[3];
    case enOperation_type::Division:
        return op_arr[4];
    case enOperation_type::Mixed:
        return op_arr[generate_random_number(1, 4)];

    default:
        return op_arr[1];
    }
}

short calc_two_nums(short f_num, short s_num, char op)
{
    switch (op)
    {
    case '+':
        return f_num + s_num;
    case '-':
        return f_num - s_num;
    case '*':
        return f_num * s_num;
    case '/':
        return f_num / s_num;

    default:
        return f_num + s_num;
    }
}

void display_current_question_on_screen(short f_num, short s_num, char op)
{
    cout << "\n";
    cout << to_string(f_num) << "\n";
    cout << to_string(s_num) << " ";
    cout << op << "\n";
    cout << "___________________\n";
};

void show_right_answer_reaction()
{
    system("color 2F"); // Green
    cout << "Right answer :-) \n";
    cout << "\n\n";
}

void show_right_wrong_answer(short right_answer)
{
    system("color 4F"); // Red
    cout << "\a";
    cout << "Wrong answer :-( \n";
    cout << "The right answer is :  " << right_answer << endl;
    cout << "\n\n";
}

stExam_info fill_exam_info(short num_of_questions, short num_of_right_answers, short num_of_wrong_answers, enQuestion_level qes_level, enOperation_type op_type)
{
    stExam_info exam_info;

    exam_info.answered_questions = num_of_questions;
    exam_info.num_of_right_answers = num_of_right_answers;
    exam_info.num_of_wrong_answers = num_of_wrong_answers;
    exam_info.question_level = qes_level;
    exam_info.op_type = op_type;

    if (num_of_right_answers >= num_of_wrong_answers)
    {
        exam_info.success_condition = true;
    }
    else
    {
        exam_info.success_condition = false;
    }

    return exam_info;
}

stExam_info start_exam(short num_of_questions, enQuestion_level qes_level, enOperation_type op_type)
{
    stRound_info round;
    short answered_questions = 0;
    short num_of_right_answers = 0;
    short num_of_wrong_answers = 0;

    for (short qes_num = 1; qes_num <= num_of_questions; qes_num++)
    {
        round.round_number = qes_num;

        round.first_num = get_a_quiz_num(qes_level);
        round.second_num = get_a_quiz_num(qes_level);
        round.op_type = get_operation_sign_as_char(op_type);
        round.right_answer = calc_two_nums(round.first_num, round.second_num, round.op_type);

        print_current_question_num(round.round_number, num_of_questions);
        display_current_question_on_screen(round.first_num, round.second_num, round.op_type);
        round.user_answer = read_a_number("\n");

        if (round.user_answer == round.right_answer)
        {
            show_right_answer_reaction();
            num_of_right_answers++;
        }
        else
        {
            show_right_wrong_answer(round.right_answer);
            num_of_wrong_answers++;
        }
        answered_questions++;
    }
    return fill_exam_info(answered_questions, num_of_right_answers, num_of_wrong_answers, qes_level, op_type);
}

void reset_screen()
{
    system("cls");
    system("color 0F");
}

string show_level_name(enQuestion_level level)
{
    switch (level)
    {
    case enQuestion_level::Easy:
        return "Easy";

    case enQuestion_level::Mid:
        return "Mid";

    case enQuestion_level::Hard:
        return "Hard";

    case enQuestion_level::Mix:
        return "Mix";
    default:
        break;
    }
}

string show_operation_name(enOperation_type op)
{
    switch (op)
    {
    case enOperation_type::Add:
        return "Addition ";

    case enOperation_type::Sub:
        return "Subtraction";

    case enOperation_type::Multi:
        return "Multiplication ";

    case enOperation_type::Division:
        return "Division";

    case enOperation_type::Mixed:
        return "Mix ";

    default:
        break;
    }
}

void set_screen_color(bool Right)
{
    if (Right)
        system("color 2F"); // turn screen to Green
    else
    {
        system("color 4F"); // turn screen to Red
        cout << "\a";
    }
}

void show_exam_results(stExam_info exam_info)
{
    cout << "--------------------------------------------\n";
    cout << "    Final result is ";

    if (exam_info.success_condition)
    {
        cout << "Success :-)" << endl;
    }
    else
    {
        system("color 4F"); // Red
        cout << "Fail :-( " << endl;
    }
    set_screen_color(exam_info.success_condition);

    cout << "--------------------------------------------\n";

    cout << "Number of questions :  " << to_string(exam_info.answered_questions) << endl;
    cout << "Questions level :  " << show_level_name(exam_info.question_level) << endl;
    cout << "Operation type :  " << show_operation_name(exam_info.op_type) << endl;
    cout << "Right Answers :  " << to_string(exam_info.num_of_right_answers) << endl;
    cout << "Wrong Answers :  " << to_string(exam_info.num_of_wrong_answers) << endl;

    cout << "\n--------------------------------------------\n";
}

void exam_main_steps()
{
    short num_of_questions = 0;
    enQuestion_level qes_level;
    enOperation_type op_type;

    num_of_questions = read_a_positive_number("How many questions you want to answer ? : ");
    qes_level = check_question_level();
    op_type = check_operation_type();
    stExam_info exam_info = start_exam(num_of_questions, qes_level, op_type);

    show_exam_results(exam_info);
}

void math_test()
{
    char play_again = 'Y';
    do
    {
        reset_screen();
        exam_main_steps();

        cout << "\n "<< "Do you want to play again? Y/N? : ";
        cin >> play_again;

    } while (play_again == 'Y' || play_again == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    math_test();
    return 0;
}
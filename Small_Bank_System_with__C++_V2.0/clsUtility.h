#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

class clsUtility
{
private:
	enum enRandomType
	{
		small_letter,
		capital_letter,
		special_char,
		number
	};

	static bool ask_for_more()
	{
		string answer;
		cout << "Do you want add more : ";
		cin >> answer;
		switch (answer[0])
		{
		case 'Y':
		case 'y':
			return true;
		case 'N':
		case 'n':
			return false;
		default:
			return false;
		}
	};

	//unsigned long long int _read_a_positive_number(string msg)
	//{
	//	unsigned long long int num;
	//	do
	//	{
	//		cout << msg;
	//		cin >> num;
	//	} while (num <= 0);
	//	return num;
	//}

	static vector<string> _slice_num_into_pieces(int num)
	{
		vector<string> result;
		string num_as_str = to_string(num);

		int str_len = num_as_str.length() % 3 == 0 ? num_as_str.length() / 3 : (num_as_str.length() / 3) + 1;

		for (int i = str_len; i > 0; i -= 3)
		{
			while (num_as_str.length() >= 3)
			{
				result.push_back(num_as_str.substr(num_as_str.length() - 3, 3));
				num_as_str.erase(num_as_str.length() - 3, num_as_str.length());
			}
			if (num_as_str.length() > 0)
				result.push_back(num_as_str);
		}

		return result;
	}

	static int _convert_str_to_num(string str, short from, short count)
	{
		return stoi(str.substr(from, count));
	};

	static string _convert_slice_of_nums_to_text(string num)
	{
		string result = "";
		string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen", "Twenty" };
		string arr2[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

		if (num.length() == 1)
		{
			return (arr[stoi(num)]);
		}
		else if (num.length() == 2)
		{
			result += arr2[_convert_str_to_num(num, 0, 1)] + " " + arr[_convert_str_to_num(num, 1, 2)];
			return result;
		}
		else
		{
			if (_convert_str_to_num(num, 0, 1) >= 1 && _convert_str_to_num(num, 0, 1) <= 9)
				result += arr[_convert_str_to_num(num, 0, 1)] + " Hundred ";

			int second_slice = _convert_str_to_num(num, 1, 2);
			if (second_slice <= 20 && second_slice >= 1)
			{
				result += "and " + arr[second_slice];
			}
			if (second_slice > 20)
			{
				result += "and " + arr2[_convert_str_to_num(num, 1, 1)] + " " + arr[_convert_str_to_num(num, 2, 1)];
			}
			return result;
		}
	}


public:
	static char read_a_digit(string msg)
	{
		int num;
		cout << msg;
		cin >> num;
		return static_cast<char>(num);
	};

	static void Srand()
	{
		srand((unsigned)time(NULL));
		;
	};

	static int random_number(int from, int to)
	{
		int range = 10;
		return (rand() % (to - from + 1) + from);
	};

	static void swap(int& item1, int& item2)
	{
		int temp = item1;
		item1 = item2;
		item2 = temp;
	}

	static void swap(string& item1, string& item2)
	{
		string temp = item1;
		item1 = item2;
		item2 = temp;
	}

	static void swap(float& item1, float& item2)
	{
		float temp = item1;
		item1 = item2;
		item2 = temp;
	}

	static void swap(double& item1, double& item2)
	{
		double temp = item1;
		item1 = item2;
		item2 = temp;
	}

	static void run_fibonacci(int length)
	{
		int array[100];
		array[length];
		short ele1 = 1, ele2 = 1;

		array[0] = ele1;
		array[1] = ele2;

		for (int i = 2; i < length; i++)
		{
			array[i] = array[i - 1] + array[i - 2];
			cout << array[i] << " ";
		}
	};

	static void run_fibonacci(unsigned int length, int prev1, int prev2)
	{

		int fibonacci_num = 0;
		if (length > 0)
		{
			fibonacci_num = prev1 + prev2;
			prev2 = prev1;
			prev1 = fibonacci_num;
			cout << fibonacci_num << "  ";

			run_fibonacci(length - 1, prev1, prev2);
		}
	};

	static bool check_if_prime(int num)
	{
		if (num == 1)
			return 1;

		int m = (num / 2);

		for (int i = 2; i <= m; i++)
		{
			if (num % i == 0)
			{
				return 0;
			}
		}
		return 1;
	};

	static float _read_a_positive_number(string msg)
	{
		float num;
		do
		{
			cout << msg;
			cin >> num;
		} while (num <= 0);
		return num;
	};

	static int sum_factors(int num)
	{
		int sum = 0;
		for (int i = 1; i < num; i++)
		{
			if (num % i == 0)
				sum += i;
		}
		return sum;
	};

	static void print_is_perfect_or_not(int num, bool status)
	{
		if (status)
			cout << "The number [ " << to_string(num) << " ] is perfect";
		else
			cout << "The number [ " << to_string(num) << " ] is not perfect";
	};

	static void check_perfect(unsigned int num)
	{
		num = _read_a_positive_number("Enter number to check if it is perfect or not : ");
		int sum = sum_factors(num);

		if (num == sum)
			print_is_perfect_or_not(num, true);
		else
			print_is_perfect_or_not(num, false);
	};

	static void check_perfect_until_num()
	{
		unsigned int num = _read_a_positive_number("Enter number to get all perfect number fom 2 to your number : ");
		for (int i = 2; i <= num; i++)
		{
			check_perfect(i);
		}
	};

	static int calc_reversed_numbers_in_str(string num)
	{
		int sum = 0;
		int number_length = num.length();
		for (int i = number_length - 1; i >= 0; i--)
		{
			sum += int(num[i] - '0');
		}
		return sum;
	};

	static int calc_reversed_numbers(int num)
	{
		int reminder = 0;
		int sum = 0;

		while (num > 0)
		{
			reminder = num % 10;
			num /= 10;
			sum += reminder;
		}
		return sum;
	};

	static int reverse_number(string num)
	{
		string reversed_number = "";

		int number_length = num.length();
		for (int i = number_length - 1; i >= 0; i--)
		{
			reversed_number += num[i];
		}

		return stoi(reversed_number);
	};

	static int reverse_number2(int num)
	{
		int reminder = 0, reversed_number = 0;
		while (num > 0)
		{
			reminder = num % 10;
			num /= 10;
			reversed_number = reversed_number * 10 + reminder;
		}
		return reversed_number;
	};

	static int count_frequent_digit(string num, int digit)
	{
		int counter = 0;

		int number_length = num.length();
		for (int i = number_length - 1; i >= 0; i--)
		{
			if (int(num[i] - '0') == digit)
				counter++;
		}

		return counter;
	};

	static int count_frequent_digit2(int digit, int num)
	{
		int reminder = 0, counter = 0;
		while (num > 0)
		{
			reminder = num % 10;
			num /= 10;
			if (int(reminder) == digit)
			{
				counter++;
			}
		}

		return counter;
	};

	static int count_frequent_digit(string num, char digit)
	{
		int counter = 0;
		int number_length = num.length();
		for (int i = number_length - 1; i >= 0; i--)
		{
			if (num[i] == digit)
				counter++;
		}
		return counter;
	};

	static string read_a_number(string msg)
	{
		int num;
		cout << msg;
		cin >> num;
		return to_string(num);
	}

	static int read_a_number2(string msg)
	{
		int num;
		cout << msg;
		cin >> num;
		return num;
	}

	static int count_frequent_digit_for_all_digits()
	{
		string number1 = read_a_number("Please Enter a number  : ");
		int num_len = number1.length();
		vector<char> hash_map = {};
		for (int i = 0; i < num_len; i++)
		{
			bool found = binary_search(hash_map.begin(), hash_map.end(), number1[i]);
			if (found)
				continue;
			else
			{
				cout << "Digit " << number1[i] << " Frequency is : " << count_frequent_digit(number1, number1[i]) << " Time(s)" << endl;
				hash_map.push_back(number1[i]);
			}
		}
	};

	static void print_numbers_reversed(string num)
	{
		int number_length = num.length();
		for (int i = 0; i <= number_length - 1; i++)
		{
			cout << int(num[i] - '0') << "\n";
		}
	};

	static void print_numbers_reversed2(int num)
	{
		int reminder = 0;

		while (num > 0)
		{
			reminder = num % 10;
			num /= 10;
			cout << reminder << "\n";
		}
	};

	static bool check_if_palindrome(int num)
	{
		string num_as_str = to_string(num);

		int len = num_as_str.length();

		for (int i = 0; i < floor(len / 2); i++)
		{
			if (num_as_str[i] != num_as_str[len - 1 - i])
				return false;
		}
		return true;
	};

	static void invert_number(int num)
	{
		for (int i = 0; i < num; i++)
		{
			for (int j = num; j > i; j--)
			{
				cout << num - i;
			}
			cout << "\n";
		}
	};

	static void invert_number2(int num)
	{
		for (int i = num; i >= 1; i--)
		{
			for (int j = 1; j <= i; j++)
			{
				cout << (i);
			}
			cout << "\n";
		}
	};

	static void number_pattern(int num)
	{
		for (int i = 1; i <= num; i++)
		{
			for (int j = 1; j <= i; j++)
			{
				cout << i;
			}
			cout << "\n";
		}
	};

	static void PrintInvertedLetterPattern(int num)
	{
		for (int i = 0; i < num; i++)
		{
			for (int j = num; j > i; j--)
			{
				cout << char(num - i + 64);
			}
			cout << "\n";
		}
	};

	static void PrintInvertedLetterPattern2(int num)
	{
		for (int i = num; i >= 1; i--)
		{
			for (int j = 1; j <= i; j++)
			{
				cout << char(i + 64);
			}
			cout << "\n";
		}
	};

	static void PrintLetterPattern(int num)
	{
		for (int i = 0; i <= num; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				cout << char(i + 65);
			}
			cout << "\n";
		}
	};

	static bool check_password(string pass)
	{
		int counter = 0;
		string tested_password = "";
		for (int i = 65; i <= 90; i++)
		{
			for (int j = 65; j <= 90; j++)
			{
				for (int k = 65; k <= 90; k++)
				{
					tested_password += char(i);
					tested_password += char(j);
					tested_password += char(k);
					counter++;
					if (pass == tested_password)
					{
						cout << "password is : " << tested_password << endl;
						cout << "was found after : " << counter << " trail(s)" << endl;
						return true;
					}
					tested_password = "";
				}
			}
		}
		return false;
	};

	static string encrypt(string text, short encrypt_text_key = 2)
	{
		for (int i = 0; i < text.length(); i++)
		{
			text[i] = char((int)text[i] + encrypt_text_key);
		}
		return text;
	};

	static string decrypt(string text, short encrypt_text_key = 2)
	{
		for (int i = 0; i < text.length(); i++)
		{
			text[i] = char((int)text[i] - encrypt_text_key);
		}
		return text;
	};

	static char random_char(int from, int to)
	{
		return char(rand() % (to - from + 1) + from);
	};

	static char generate_random_char(enRandomType type)
	{
		switch (type)
		{
		case enRandomType::number:
			return random_number(48, 57);
		case enRandomType::capital_letter:
			return random_char(65, 90);
		case enRandomType::small_letter:
			return random_char(97, 122);
		case enRandomType::special_char:
			return random_char(33, 47);
		default:
			break;
		}
	};

	static enRandomType convert_str_into_enRandomType(string type)
	{
		if (type == "number")
		{
			return enRandomType::number;
		};

		if (type == "capital_letter")
		{
			return enRandomType::capital_letter;
		};

		if (type == "small_letter")
		{
			return enRandomType::small_letter;
		};

		if (type == "special_char")
		{
			return enRandomType::special_char;
		};
	}

	static string generate_password_key(string type, short word_length, short key_length)
	{
		enRandomType en_type = convert_str_into_enRandomType(type);
		string password = "";
		for (int i = 0; i < key_length; i++)
		{
			for (int j = 0; j < word_length; j++)
			{
				password += generate_random_char(en_type);
			}
			if (i < word_length - 1)
				password += '-';
		}

		return password;
	};

	static void generate_num_of_keys(int num)
	{
		srand((unsigned)time(NULL)); //// you should call this line in plus these libraries ( #include <cstdlib> ,  #include <time.h> )
		int len_of_keys = _read_a_positive_number("please Enter length of keys you want : ");
		for (int i = 0; i < num; i++)
		{
			cout << "Key [" << i + 1 << "] : " << generate_password_key("capital_letter", len_of_keys, len_of_keys) << endl;
		}
	};

	static string get_array_elements_from_user(int num)
	{
		string result = "";
		for (int i = 0; i < num; i++)
		{
			string msg = "Element [" + to_string(i + 1) + "] : ";
			result += _read_a_positive_number(msg);
		}
		return result;
	};

	static void check_number_iteration(string result)
	{
		char digit = read_a_digit("Which number you want to check : ");

		cout << "Elements are : [ ";
		for (int i = 0; i < result.size(); i++)
		{
			cout << int(result[i]) << (i < result.size() - 1 ? ", " : "");
		}
		cout << " ]" << endl;

		cout << "[" << int(digit) << "] is repeated " << count_frequent_digit(result, digit) << " time(s) ";
	};

	static void print_arr(int arr[100], int arr_length)
	{
		cout << "[ ";
		for (size_t i = 0; i < arr_length; i++)
		{
			cout << arr[i] << (i < arr_length - 1 ? ", " : "");
		}
		cout << " ]" << endl;
	};

	static void fill_arr_with_random_nums(int arr[100], int& arr_length)
	{
		srand((unsigned)time(NULL)); //// you should call this line in plus these libraries ( #include <cstdlib> ,  #include <time.h> )
		arr_length = _read_a_positive_number("Please Enter a number of elements you want : ");
		for (int i = 0; i < arr_length; i++)
		{
			arr[i] = random_number(0, 100);
		}
		cout << endl;
	};

	static int max_num_of_array(int arr[100], int arr_length)
	{
		int max_num = arr[0];

		for (int i = 1; i < arr_length; i++)
		{
			if (arr[i] > max_num)
				max_num = arr[i];
		}

		return max_num;
	};

	static int min_num_of_array(int arr[100], int arr_length)
	{
		int min_num = arr[0];

		for (int i = 1; i < arr_length; i++)
		{
			if (arr[i] < min_num)
				min_num = arr[i];
		}

		return min_num;
	};

	static int sum_all_nums_in_array(int arr[100], int arr_length)
	{
		int sum = 0;

		for (int i = 0; i < arr_length; i++)
		{
			sum += arr[i];
		}

		return sum;
	};

	static float average_of_all_nums_in_array(int arr[100], int arr_length)
	{
		return (float)sum_all_nums_in_array(arr, arr_length) / arr_length;
	};

	static int* copy_arr_int(int arr[100], int arr_length)
	{
		int* copied_arr = new int[100];
		for (int i = 0; i < arr_length; i++)
		{
			copied_arr[i] = arr[i];
		}
		return copied_arr;
	};

	static void copy_arr_void(int original_arr[100], int arr_length, int copied_arr[100])
	{
		for (int i = 0; i < arr_length; i++)
		{
			copied_arr[i] = original_arr[i];
		}
	};

	static int* copy_only_prime_numbers_int(int original_arr[100], int arr_length, int& copied_arr_length)
	{
		int* copied_arr = new int[100];
		for (int i = 0; i < arr_length; i++)
		{
			if (check_if_prime(original_arr[i]))
			{
				copied_arr[copied_arr_length] = original_arr[i];
				copied_arr_length++;
			}
		}
		return copied_arr;
	}

	static void copy_only_prime_numbers_void(int original_arr[100], int arr_length, int copied_arr[100], int& copied_arr_length)
	{
		for (int i = 0; i < arr_length; i++)
		{
			if (check_if_prime(original_arr[i]))
			{
				copied_arr[copied_arr_length] = original_arr[i];
				copied_arr_length++;
			}
		}
	};

	static void sum_two_arrays(int arr1[100], int arr2[100], int length_of_two_array, int sum_arr[100])
	{
		for (int i = 0; i < length_of_two_array; i++)
		{
			sum_arr[i] = arr1[i] + arr2[i];
		}
	};

	static void fill_arr_nums_from_1_to_10(int arr[100], int arr_length)
	{
		for (int i = 0; i < arr_length; i++)
		{
			arr[i] = i + 1;
		}
		cout << endl;
	};

	static void shuffle_array(int arr[100], int arr_length)
	{
		srand((unsigned)time(NULL));
		for (int i = 0; i < arr_length; i++)
		{
			int random1 = random_number(0, arr_length - 1);
			int random2 = random_number(0, arr_length - 1);
			swap(arr[random1], arr[random2]);
		}
	};

	static int* copy_arr_reversed_int(int arr[100], int arr_length)
	{
		int* copied_arr = new int[100];
		for (int i = 0; i < arr_length; i++)
		{
			copied_arr[i] = arr[arr_length - 1 - i];
		}
		return copied_arr;
	};

	static void copy_arr_reversed_void(int original_arr[100], int arr_length, int copied_arr[100])
	{
		for (int i = 0; i < arr_length; i++)
		{
			copied_arr[i] = original_arr[arr_length - 1 - i];
		}
	};

	static void find_a_number_in_array_void(int arr[100], int& arr_length)
	{

		int target_num = read_a_number2("Please Enter a number to find : ");
		cout << "The number that you are locking for is : " << target_num << endl;

		int cond = false;

		for (int i = 0; i < arr_length; i++)
		{
			if (arr[i] == target_num)
			{
				cout << "The number is found at position : " << i << endl;
				cout << "The number is found its order : " << i + 1 << endl;
				cond = true;
				break;
			}
		}

		if (!cond)
			cout << "The number is not found :-(" << endl;
	};

	static bool find_a_number_in_array_bool(int arr[100], int& arr_length)
	{
		int target_num = read_a_number2("Please Enter a number to find : ");
		cout << "The number that you are locking for is : " << target_num << endl;
		for (int i = 0; i < arr_length; i++)
		{
			if (arr[i] == target_num)
			{
				return true;
			}
		}
		return false;
	};

	static void fill_arr_with_nums_until_user_stop(int arr[100], int& arr_length)
	{
		int i = 0;
		int num;
		bool more = true;

		while (more)
		{

			if (i >= 100)
			{
				cout << "Array is full. Cannot add more numbers." << endl;
				break;
			}

			num = read_a_number2("please Enter a number : ");
			arr[i] = num;
			arr_length++;
			i++;

			more = ask_for_more();
		}

		cout << endl;
	};

	static void add_element_to_array(int arr[100], int& arr_length, int ele)
	{
		arr[arr_length] = ele;
		arr_length++;
	};

	static void fill_arr_with_nums_until_user_stop2(int arr[100], int& arr_length)
	{
		int i = 0;
		int num = 0;
		bool more = true;

		while (more)
		{

			if (i >= 100)
			{
				cout << "Array is full. Cannot add more numbers." << endl;
				break;
			}

			num = read_a_number2("please Enter a number : ");
			add_element_to_array(arr, arr_length, num);

			more = ask_for_more();
		}

		cout << endl;
	};

	static int* copy_odd_numbers_int(int arr[100], int arr_length, int& copied_arr2_len)
	{
		int* copied_arr = new int[100];
		for (int i = 0; i < arr_length; i++)
		{
			if (arr[i] % 2 != 0)
				add_element_to_array(copied_arr, copied_arr2_len, arr[i]);
			else
				continue;
		}
		return copied_arr;
	};

	static void copy_odd_numbers2_void(int original_arr[100], int arr_length, int copied_arr[100], int& copied_arr_len)
	{
		for (int i = 0; i < arr_length; i++)
		{
			if (original_arr[i] % 2 != 0)
				add_element_to_array(copied_arr, copied_arr_len, original_arr[i]);
			else
				continue;
		}
	};

	static int* copy_prime_numbers_int(int arr[100], int arr_length, int& copied_arr2_len)
	{
		int* copied_arr = new int[100];
		for (int i = 0; i < arr_length; i++)
		{
			if (check_if_prime(arr[i]))
				add_element_to_array(copied_arr, copied_arr2_len, arr[i]);
			else
				continue;
		}
		return copied_arr;
	};

	static void copy_prime_numbers2_void(int original_arr[100], int arr_length, int copied_arr[100], int& copied_arr_len)
	{
		for (int i = 0; i < arr_length; i++)
		{
			if (check_if_prime(original_arr[i]))
				add_element_to_array(copied_arr, copied_arr_len, original_arr[i]);
			else
				continue;
		}
	};

	static bool is_num_in_arr(int arr[100], int arr_len, int num)
	{
		for (size_t i = 0; i < arr_len; i++)
		{
			if (arr[i] == num)
				return true;
		}
		return false;
	};

	static int* copy_distinct_to_array_int(int arr[100], int arr_length, int& copied_arr2_len)
	{
		int* copied_arr = new int[100];
		for (int i = 0; i < arr_length; i++)
		{
			if (!is_num_in_arr(copied_arr, arr_length, arr[i]))
				add_element_to_array(copied_arr, copied_arr2_len, arr[i]);
		}
		return copied_arr;
	};

	static void copy_distinct_to_array_void(int original_arr[100], int arr_length, int copied_arr[100], int& copied_arr_len)
	{
		for (int i = 0; i < arr_length; i++)
		{
			if (!is_num_in_arr(copied_arr, arr_length, original_arr[i]))
				add_element_to_array(copied_arr, copied_arr_len, original_arr[i]);
		}
	};

	static bool is_palindrome_in_arr(int arr1[100], int arr1_length)
	{
		for (int i = 0; i < ceil(arr1_length / 2); i++)
		{
			if (arr1[i] != arr1[arr1_length - 1 - i])
				return false;
		}
		return true;
	};

	static bool check_if_odd(int num)
	{
		return num % 2 != 0;
	};

	static int count_odd_number_in_arr(int arr[100], int arr_length)
	{
		int count = 0;

		for (size_t i = 0; i < arr_length; i++)
		{
			if (check_if_odd(arr[i]))
				count++;
		}

		return count;
	};

	static bool check_if_even(int num)
	{
		return num % 2 == 0;
	};

	static int count_even_number_in_arr(int arr[100], int arr_length)
	{
		int count = 0;

		for (size_t i = 0; i < arr_length; i++)
		{
			if (check_if_even(arr[i]))
				count++;
		}

		return count;
	};

	static bool check_if_positive(int num)
	{
		return num > 0;
	};

	static int count_positive_number_in_arr(int arr[100], int arr_length)
	{
		int count = 0;

		for (size_t i = 0; i < arr_length; i++)
		{
			if (check_if_positive(arr[i]))
				count++;
		}

		return count;
	};

	static bool check_if_negative(int num)
	{
		return num < 0;
	};

	static int count_negative_number_in_arr(int arr[100], int arr_length)
	{
		int count = 0;

		for (size_t i = 0; i < arr_length; i++)
		{
			if (check_if_negative(arr[i]))
				count++;
		}

		return count;
	};

	static float get_round(float num)
	{
		string str_num = to_string(num);
		string res = "";
		for (int i = 0; i < str_num.length(); i++)
		{
			if (str_num[i] != '.')
			{
				res += str_num[i];
			}
			else
			{
				if (str_num[i + 1] >= '5')
				{
					res += '.';
					res += str_num[i] + 1;
				}
				else
					break;
			}
		}

		return res[0] == '-' ? stof(res) - 1 : stof(res) + 1;
	};

	static float get_fraction(float num)
	{
		return num - int(num);
	};

	static float get_abs(float num)
	{
		return num > 0 ? num : -num;
	};

	static float get_round_2(float num)
	{

		int int_value_of_num = int(num);
		float fraction_value_of_num = get_fraction(num);

		if (get_abs(fraction_value_of_num) >= 0.5)
		{
			if (num > 0)
				return ++int_value_of_num;
			else
				return --int_value_of_num;
		}
		else
			return int_value_of_num;
	};

	static float get_floor(float num)
	{

		int int_value = int(num);

		if (num > 0)
			return int_value;
		else
			return --int_value;
	};

	static float get_ceil(float num)
	{

		int int_value_of_num = int(num);
		float fraction_value = get_fraction(num);

		if (get_abs(fraction_value) > 0)
		{
			if (num > 0)
				return ++int_value_of_num;
			else
				return int_value_of_num;
		}
		else
			return int_value_of_num;
	};

	static int get_pow(int num, int pow)
	{
		int res = 1;
		for (int i = 0; i < pow; i++)
		{
			res *= num;
		}
		return res;
	};

	static float get_sqrt(float num)
	{
		return pow(num, 0.5);
	};

	static string covert_number_into_text(unsigned long long int num)
	{
		string result = "";
		vector<string> slice_of_num = _slice_num_into_pieces(num);
		string arr_of_decimal_place[] = { " ", "Thousand", "Million", "Billion" };

		switch (num)
		{
		case 100:
			return "One Hundred ";
			break;
		case 1000:
			return "One Thousand ";
			break;
		case 10000:
			return "Ten Thousand ";
			break;
		case 100000:
			return "One Hundred Thousand ";
			break;
		case 1000000:
			return "One Million ";
			break;
		case 10000000:
			return "Ten Million ";
			break;
		case 100000000:
			return "One Hundred Million ";
			break;
		case 1000000000:
			return "One Billion ";
			break;
		default:
			break;
		}

		int vec_len = slice_of_num.size() - 1;
		for (int i = vec_len; i >= 0; i--)
		{
			result += _convert_slice_of_nums_to_text(slice_of_num[i]) + " " + arr_of_decimal_place[i] + " ";
		}

		return result;
	}
};

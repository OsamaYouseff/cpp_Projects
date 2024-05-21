#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class clsString
{
private:
	string _value;
	//// methods
	static char invert_char(char c)
	{
		return islower(c) ? toupper(c) : tolower(c);
	}

public:

	clsString() {
		_value = "";
	}

	clsString(string input_value) {
		_value = input_value;
	}

	////// ------------------------------------------------------------------------
	// setters
	void set_value(string input_value) {
		_value = input_value;
	}
	
	////// ------------------------------------------------------------------------
	// getters
	string get_value() {
		return _value;
	}
	__declspec(property(get = get_value, put = set_value)) string value;
	
	//// --------------------------------------------------------------------------
	//// methods
	static int str_length(string str) {
		return str.length();
	}

	int length() {
		return str_length(_value);
	}
	//// -------------------------------------------------------------
	static void print_first_char(string sentence)
	{
		bool is_first_letter = true;
		for (int i = 0; i < sentence.length(); i++)
		{
			if (is_first_letter && sentence[i] != ' ')
			{
				cout << sentence[i] << " ";
				is_first_letter = false;
			}
			else if (!is_first_letter && sentence[i] == ' ')
			{
				cout << sentence[i + 1] << " ";
			}
		}
	}

	void print_first_char() {
		return print_first_char(_value);
	}
	//// -------------------------------------------------------------
	static string make_first_char_upper(string sentence)
	{
		bool is_first_letter = true;
		for (int i = 0; i < sentence.length(); i++)
		{
			if (is_first_letter && sentence[i] != ' ')
			{
				sentence[i] = toupper(sentence[i]);
				is_first_letter = false;
			}
			else if (!is_first_letter && sentence[i] == ' ' && sentence[i + 1] != ' ')
			{
				sentence[i + 1] = toupper(sentence[i + 1]);
			}
		}
		return sentence;
	}

	void make_first_char_upper() {
		_value = make_first_char_upper(_value);
	}
	//// -------------------------------------------------------------
	static string make_first_char_lower(string sentence)
	{
		bool is_first_letter = true;
		for (int i = 0; i < sentence.length(); i++)
		{
			if (is_first_letter && sentence[i] != ' ')
			{
				sentence[i] = tolower(sentence[i]);
				is_first_letter = false;
			}
			else if (!is_first_letter && sentence[i] == ' ' && sentence[i + 1] != ' ')
			{
				sentence[i + 1] = tolower(sentence[i + 1]);
			}
		}
		return sentence;
	}

	void make_first_char_lower() {
		_value = make_first_char_lower(_value);
	}
	//// -------------------------------------------------------------
	static string make_string_uppercase(string sentence)
	{
		for (int i = 0; i < sentence.length(); i++)
		{
			if (sentence[i] != ' ')
				sentence[i] = toupper(sentence[i]);
		}
		return sentence;
	}

	void make_string_uppercase() {
		_value = make_string_uppercase(_value);
	}
	//// -------------------------------------------------------------
	static string make_string_lowercase(string sentence)
	{
		for (int i = 0; i < sentence.length(); i++)
		{
			if (sentence[i] != ' ')
				sentence[i] = tolower(sentence[i]);
		}
		return sentence;
	}

	void make_string_lowercase() {
		_value = make_string_lowercase(_value);
	}
	//// -------------------------------------------------------------
	static string invert_string_chars(string sentence)
	{
		for (int i = 0; i < sentence.length(); i++)
		{
			sentence[i] = invert_char(sentence[i]);
		}
		return sentence;
	}

	void invert_string_chars() {
		_value = invert_string_chars(_value);
	}
	//// -------------------------------------------------------------
	static int count_str_upper_letters(string str)
	{
		int counter = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (isupper(str[i]) && str[i] != ' ')
				counter++;
		}
		return counter;
	}

	int count_str_upper_letters() {
		return  count_str_upper_letters(_value);
	};
	//// -------------------------------------------------------------
	static int count_str_lower_letters(string str)
	{
		int counter = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (islower(str[i]) && str[i] != ' ')
				counter++;
		}
		return counter;
	}

	int count_str_lower_letters() {
		return  count_str_lower_letters(_value);
	};
	//// -------------------------------------------------------------
	static int count_char_in_string(string str, char target)
	{
		short counter = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (tolower(str[i]) == tolower(target))
				counter++;
		}
		return counter;
	}

	int count_char_in_string(char target) {
		return  count_char_in_string(_value, target);
	};
	//// -------------------------------------------------------------
	static int count_char_in_string_sensetive_opt(string str, char target, bool case_sens = true)
	{
		short counter = 0;
		for (int i = 0; i < str.length(); i++)
		{
			if (case_sens)
			{
				if (str[i] == target)
					counter++;
			}
			else
			{
				if (tolower(str[i]) == tolower(target))
					counter++;
			}
		}
		return counter;
	}

	int count_char_in_string_sensetive_opt(char target) {
		return  count_char_in_string_sensetive_opt(_value, target);
	};
	//// -------------------------------------------------------------
	static bool is_vowel(char chr)
	{
		return (chr == 'a' || chr == 'e' || chr == 'i' || chr == 'o' || chr == 'u');
	}
	static unsigned short count_vowels(string text)
	{
		unsigned short counter = 0;

		for (unsigned short i = 0; i < text.length(); i++)
		{
			if (is_vowel(text[i]))
				counter++;
		}

		return counter;
	}
	unsigned short count_vowels() {
		return  count_vowels(_value);
	}
	static void print_vowels(string text)
	{

		for (unsigned short i = 0; i < text.length(); i++)
		{
			if (is_vowel(text[i]))
				cout << text[i] << " ";
		}
	}
	void print_vowels() {
		return print_vowels(_value);
	}
	//// -------------------------------------------------------------
	static void print_each_word_alone(string text)
	{
		string word = "", delim = " ";

		short pos = 0;

		while ((pos = text.find(delim)) != std::string::npos)
		{
			word = text.substr(0, pos);

			if (word != "")
				cout << word << endl;

			text.erase(0, pos + delim.length());
		}

		if (word != " ")
			cout << text << endl;
	}

	void print_each_word_alone() {
		return print_each_word_alone(_value);
	}
	//// -------------------------------------------------------------
	static int count_words_in_text(string text)
	{
		string word = "", delim = " ";

		short pos = 0, counter = 0;

		while ((pos = text.find(delim)) != std::string::npos)
		{
			word = text.substr(0, pos);

			if (word != "")
				counter++;

			text.erase(0, pos + delim.length());
		}

		if (word != " ")
			counter++;

		return counter;
	}

	int count_words_in_text() {
		return  count_words_in_text(_value);
	}
	//// -------------------------------------------------------------
	static vector<string> split(string text, string delim)
{
	vector<string> result;
	string word = "";
	short pos = 0;

	while ((pos = text.find(delim)) != std::string::npos)
	{
		word = text.substr(0, pos);

		//if (word != "")
			result.push_back(word);

		text.erase(0, pos + delim.length());
	}

	if (word != " ")

		result.push_back(text);

	return result;
}
	

	vector<string> split(string delim) {
			return split(_value, delim);
		}

	//// -------------------------------------------------------------
	static string trim_left(string text)
	{
		string word = "";

		for (int i = 0; i < text.length(); i++)
		{
			if (text[i] != ' ')
				return text.substr(i, text.length() - i);
		}
	}
	static string trim_right(string text)
	{
		for (int i = text.length() - 1; i >= 0; i--)
		{
			if (text[i] != ' ')
				return text.substr(0, i + 1);
		}
	}
	static string trim(string text)
	{
		return trim_left(trim_right(text));
	}
	void trim_left() {
		_value = trim_left(_value);
	}
	void trim_right() {
		_value = trim_left(_value);
	}
	void trim() {
		_value = trim(_value);
	}
	//// -------------------------------------------------------------
	static string join(vector<string> words, string delim)
	{
		string result = words[0];
		short counter = 1;

		while (counter < words.size())
		{
			result += delim;
			result += words.at(counter++);
		}

		return result;
	}
	static string join(string words[], string delim, short length)
	{
		string result = words[0];

		for (int i = 1; i < length; i++)
		{
			if (i < length)
				result += delim;

			result += words[i];
		}
		return result;
	}

	//// -------------------------------------------------------------
	static  string reverse_words_in_string(string S1)
	{
		vector<string> vString;
		string S2 = "";
		vString = split(S1, " "); // declare iterator

		vector<string>::iterator iter = vString.end();

		while (iter != vString.begin())
		{
			--iter;
			S2 += *iter + " ";
		}
		S2 = S2.substr(0, S2.length() - 1); // remove last space.
		return S2;
	}

	void reverse_words_in_string() {
		_value = reverse_words_in_string(_value);
	}
	//// -------------------------------------------------------------
	string replace_word_in_string_using_built_in_fqn(string text, string to_replace, string replace_to)
	{

		short pos = text.find(to_replace);

		while (pos != string::npos)
		{
			text = text.replace(pos, to_replace.length(), replace_to);
			pos = text.find(to_replace);
		}
		return text;
	}

	void replace_word_in_string_using_built_in_fqn(string to_replace, string replace_to) {
		_value = replace_word_in_string_using_built_in_fqn(_value, to_replace, replace_to);
	}
	//// -------------------------------------------------------------
	static string lower_string(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = tolower(S1[i]);
		}
		return S1;
	}
	static string ReplaceWordInStringUsingSplit(string S1, string StringToReplace, string sReplaceTo, bool MatchCase = true)
	{
		vector<string> vString = split(S1, " ");
		for (string& s : vString)
		{
			if (MatchCase)
			{
				if (s == StringToReplace)
				{
					s = sReplaceTo;
				}
			}
			else
			{
				if (lower_string(s) == lower_string(StringToReplace))
				{
					s = sReplaceTo;
				}
			}
		}
		return join(vString, " ");
	}

	void lower_string() {
		_value = lower_string(_value);
	}
	void ReplaceWordInStringUsingSplit(string StringToReplace, string sReplaceTo, bool MatchCase = true) {
		_value = ReplaceWordInStringUsingSplit(_value, StringToReplace, sReplaceTo, MatchCase);
	}
	//// -------------------------------------------------------------
	static string remove_punctuation(string text)
	{
		string res = "";

		for (short i = 0; i < text.length(); i++)
		{
			if (!ispunct(text[i]))
				res += text[i];
		}

		return res;
	}

	void remove_punctuation() {
		_value = remove_punctuation(_value);
	}
	//// -------------------------------------------------------------
};




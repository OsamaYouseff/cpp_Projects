#pragma once
#include <iostream>
#include <string>
#include "clsInterfaceCommunication.h"

using namespace std;

class clsPerson :public clsInterfaceCommunication
{
private:
	string _first_name;
	string _last_name;
	string _email;
	string _phone;

public:
	clsPerson(string first_name, string last_name, string email, string phone)
	{
		_first_name = first_name;
		_last_name = last_name;
		_email = email;
		_phone = phone;
	}

	///// getters
	string get_first_name()
	{
		return _first_name;
	};
	string get_last_name()
	{
		return _last_name;
	};
	string get_email()
	{
		return _email;
	};
	string get_phone()
	{
		return _phone;
	};
	
	///// setters
	void set_first_name(string first_name)
	{
		_first_name = first_name;
	};
	void set_last_name(string last_name)
	{
		_last_name = last_name;
	};
	void set_email(string email)
	{
		_email = email;
	};
	void set_phone(string phone)
	{
		_phone = phone;
	};

	__declspec(property(get = get_first_name, put = set_first_name)) string first_name;
	__declspec(property(get = get_last_name, put = set_last_name)) string last_name;
	__declspec(property(get = get_email, put = set_email)) string email;
	__declspec(property(get = get_phone, put = set_phone)) string phone;


	string full_name()
	{
		return _first_name + " " + _last_name;
	}

	//// if you don't add these methods you'll get an Error because you have to impelement abstract methods
	void send_email(string title, string body) {

	}

	void  send_fax(string title, string body) {

	};

	void  send_message(string title, string body) {

	};

};
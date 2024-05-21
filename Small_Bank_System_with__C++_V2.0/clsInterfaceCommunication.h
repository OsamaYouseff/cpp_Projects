#pragma once
#include <iostream>
#include <string>
using namespace std;

class clsInterfaceCommunication
{


public:

	virtual void  send_email(string title, string body) = 0;
	virtual void  send_fax(string title, string body) = 0;
	virtual void  send_message(string title, string body) = 0;



};


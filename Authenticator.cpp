#include "pch.h"
#include "Authenticator.h"


bool Authenticator::AuthenticateAdminLogin(const char * pass)
{
	return strcmp(adminPass, pass) ? false:true;
}

Authenticator::Authenticator()
{
	USER _t{ "david","pass" };
	activeUsers.push_back(_t);
	userVector.push_back(_t);


}


Authenticator::~Authenticator()
{
}

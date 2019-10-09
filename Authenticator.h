#pragma once
#include <string.h>
#include <vector>
#include "ext/json.hpp"

#define MAX_USERNAME_SIZE 20
#define MAX_PASSWORD_SIZE 20

enum ACCESS_LEVEL{READ_ONLY, READ_WRITE, SUPERVISOR, ADMIN};

typedef struct {
	char username[MAX_USERNAME_SIZE];
	char password[MAX_PASSWORD_SIZE];
}USER ;


class Authenticator
{
	

private:
	const char *adminPass= "adminPass";
	std::vector<USER> userVector;
	std::vector<USER> activeUsers;

public:
	bool AuthenticateAdminLogin(const char *pass);

	bool userExists(USER _user);
	bool checkDuplicateAddUser(USER _user);

	Authenticator();
	~Authenticator();
};


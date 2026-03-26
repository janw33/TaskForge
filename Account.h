#pragma once
#include <string>
class Account
{
	std::string username;
	std::string password;
	int id;
public:
	Account(const std::string& username, const std::string& password, int id);

	const std::string& getUsername() const;
	const std::string& getPassword() const;
	int getId() const;

	void setUsername(const std::string &newUsername);
	void setPassword(const std::string &newPassword);
};
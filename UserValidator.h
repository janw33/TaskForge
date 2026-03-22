#pragma once
#include <string>
#include <vector>

class UserValidator
{
public:
	static std::vector<std::string>isUsernameValid(const std::string& username);
	static std::vector<std::string>isPasswordValid(const std::string& password);
};
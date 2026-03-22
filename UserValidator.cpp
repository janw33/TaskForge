#include <cctype>
#include "UserValidator.h"

std::vector<std::string> UserValidator::isUsernameValid(const std::string& username)
{
    std::vector<std::string> errors;

    if (username.size() < 3)
        errors.push_back("Username is too short (minimum 3 characters)!");
    if (username.size() > 20)
        errors.push_back("Username is too long! (maximum 20 characters)");

    for (unsigned char c : username)
    {
        if (!std::isalnum(c))
        {
            errors.push_back("Username cannot contain special characters!");
            break;
        }
    }

    return errors;
}
std::vector<std::string> UserValidator::isPasswordValid(const std::string& password)
{
    std::vector<std::string> errors;

    if (password.size() < 8)
        errors.push_back("Password is too short! (minimum 8 characters)");
    if (password.size() > 30)
        errors.push_back("Password is too long! (maximum 30 characters)");

    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    bool hasSpace = false;

    for (unsigned char c : password)
    {
        if (std::isupper(c)) hasUpper = true;
        if (std::islower(c)) hasLower = true;
        if (std::isdigit(c)) hasDigit = true;
        if (c == ' ') hasSpace = true;
        if (!std::isalnum(c) && c != ' ') hasSpecial = true;
    }

    if (hasSpace)
        errors.push_back("Password cannot contain spaces!");
    if (!hasSpecial)
        errors.push_back("Password must contain a special character!");
    if (!hasUpper)
        errors.push_back("Password must contain an uppercase letter!");
    if (!hasLower)
        errors.push_back("Password must contain a lowercase letter!");
    if (!hasDigit)
        errors.push_back("Password must contain a digit!");

    return errors;
}
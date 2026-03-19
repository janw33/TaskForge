#include "Account.h"

Account::Account(const std::string& username, const std::string& password, int id)
	:username(username), password(password), id(id)
{
}



const std::string& Account::getUsername() const
{
    return username;
}

const std::string& Account::getPassword() const
{
    return password;
}

int Account::getId() const
{
    return id;
}


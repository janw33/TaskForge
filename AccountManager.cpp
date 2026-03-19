#include "AccountManager.h"

AccountManager::AccountManager(Interface& ui)
    : ui(ui), nextId(1)
{
}



void AccountManager::signUp(bool &logged)
{
    std::string username = ui.askString("Enter Username: ");
    std::string password = ui.askString("Enter Passwor : ");
    accounts.emplace_back(username, password, nextId++);
    logged = true;
}



bool AccountManager::isDataValid(const std::string& username, const std::string& password)
{
    for (const auto& acc : accounts)
    {
        if (acc.getUsername() == username && acc.getPassword() == password)
        {
            ui.print("Logged in Sucesfully!");
            return true;
        }
    }
    return false;
}
void AccountManager::logIn(bool& logged)
{
    while (true)
    {
        std::string username = ui.askString("Enter Username: ");
        std::string password = ui.askString("Enter Passwor : ");

        if (isDataValid(username, password))
        {
            logged = true;
            return;
        }

        ui.print("Username or password is invalid. Please try again!");
    }
}
#include "AccountManager.h"

AccountManager::AccountManager(Interface& ui)
    : ui(ui), nextId(1)
{
}



bool AccountManager::isUsernameTaken(const std::string &username)
{
    for (const auto& acc : accounts)
    {
        if (acc.getUsername() == username)
        {
            return true;
        }
    }
    return false;
}
void AccountManager::signUp(bool &logged)
{
    while (true)
    {
        std::string username = ui.askString("Enter Username: ");
        /* userValidation
        if (isUsernameTaken(username))
        {
            ui.printPauseClear("Username is already taken");
            continue;
        }
       
        auto usernameErrors = UserValidator::isUsernameValid(username);

        if (!usernameErrors.empty())
        {
            for (const auto& error : usernameErrors)
            {
                ui.print (error);
            }
            ui.pauseClear();
            continue;
        }
        */

        std::string password = ui.askPassword("Enter Password: ");

        /* passwordValidation
        auto passwordErrors = UserValidator::isPasswordValid(password);

        if (!passwordErrors.empty())
        {
            for (const auto& error : passwordErrors)
            {
                ui.print(error);
            }
            ui.pauseClear();
            continue;
        }
        */
        accounts.emplace_back(std::move(username), std::move(password), nextId++);
        logged = true;
        ui.printPauseClear("Sign up Successfully");
        return;
    }
}



bool AccountManager::areCredentialsValid(const std::string& username, const std::string& password)
{
    for (const auto& acc : accounts)
    {
        if (acc.getUsername() == username && acc.getPassword() == password)
        {
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
        std::string password = ui.askPassword("Enter Password: ");

        if (areCredentialsValid(username, password))
        {
            ui.printPauseClear("Logged in Successfully!");
            logged = true;
            return;
        }

        ui.printPauseClear("Username or password is invalid. Please try again!");
    }
}
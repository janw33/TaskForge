#include "AccountManager.h"

AccountManager::AccountManager(Interface& ui)
    : ui(ui), nextId(1)
{
}

int AccountManager::findAccountIndexById(int id) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].getId() == id) {
            return i;
        }
    }
    return -1; 
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

bool AccountManager::wantContinue(std::string &confirmation)
{
    std::transform(confirmation.begin(), confirmation.end(), confirmation.begin(), [](unsigned char c) { return std::toupper(c); });

    if (confirmation != "YES")
    {
    return false;
    }

    return true;
}
void AccountManager::signUp(bool &logged)
{
    while (true)
    {
        std::string confirmation = ui.askString("Do you want to continue: (YES)");

        if(!wantContinue(confirmation))
        {
            ui.clearScreen();
            return;
        }

        std::string username = ui.askString("Enter Username: ");

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
        
        std::string password = ui.inputPassword("Enter Password: ");

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
        
        accounts.emplace_back(std::move(username), std::move(password), nextId);
        currentAccountId = nextId;
        nextId++;
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
            currentAccountId = acc.getId();
            return true;
        }
    }
    return false;
}
void AccountManager::logIn(bool& logged)
{
    while (true)
    {
        std::string confirmation = ui.askString("Do you want to continue: (YES)");

        if(!wantContinue(confirmation))
        {
            ui.clearScreen();
            return;
        }

        std::string username = ui.askString("Enter Username: ");
        std::string password = ui.inputPassword("Enter Password: ");

        if (areCredentialsValid(username, password))
        {
            ui.printPauseClear("Logged in Successfully!");
            logged = true;
            return;
        }

        ui.printPauseClear("Username or password is invalid. Please try again!");
    }
}


void AccountManager::changeUsername()
{
    int index = findAccountIndexById(currentAccountId);

    if (index == -1)
    {   
    ui.printPauseClear("Account not found");
    return;
    }

    auto &acc = accounts[index];

    std::string password = ui.inputPassword("Please enter your password to verify your identity: ");

    if(password != acc.getPassword())
    {
        ui.printPauseClear("Invalid Password");
        return;
    }
    std::string newUsername;

    while (true)
    {
    std::string confirmation = ui.askString("Do you want to continue: (YES)");

        if(!wantContinue(confirmation))
        {
        ui.clearScreen();
        return;
        }

    newUsername = ui.askString("Enter new username: ");

        if (isUsernameTaken(newUsername))
        {
            ui.printPauseClear("Username is already taken");
            continue;
        }
       
        auto usernameErrors = UserValidator::isUsernameValid(newUsername);

        if (!usernameErrors.empty())
        {
            for (const auto& error : usernameErrors)
            {
                ui.print (error);
            }
            ui.pauseClear();
            continue;
        }
        break;
    }   
    acc.setUsername(newUsername);
    ui.printPauseClear("Username changed Successfully");
}
void AccountManager::changePassword()
{
    int index = findAccountIndexById(currentAccountId);

    if (index == -1)
    {   
    ui.printPauseClear("Account not found");
    return;
    }

    auto &acc = accounts[index];

    std::string password = ui.inputPassword("Please enter your password to verify your identity: ");

    if(password != acc.getPassword())
    {
        ui.printPauseClear("Invalid Password");
        return;
    }

    std::string newPassword;

    while(true)
    {

    std::string confirmation = ui.askString("Do you want to continue: (YES)");

        if(!wantContinue(confirmation))
        {
        ui.clearScreen();
        return;
        }

    newPassword = ui.inputPassword("Enter new password: ");

        auto passwordErrors = UserValidator::isPasswordValid(newPassword);

        if (!passwordErrors.empty())
        {
            for (const auto& error : passwordErrors)
            {
                ui.print(error);
            }
            ui.pauseClear();
            continue;
        }
        break;
    }

    acc.setPassword(newPassword);
    ui.printPauseClear("Password changed Successfully");
}

void AccountManager::deleteAccount(int &accountChoice, int &choice)
{
    int index = findAccountIndexById(currentAccountId);

    if (index == -1)
    {   
    ui.printPauseClear("Account not found");
    return;
    }

    auto &acc = accounts[index];

    std::string password = ui.inputPassword("Please enter your password to verify your identity: ");

    if(password != acc.getPassword())
    {
        ui.printPauseClear("Invalid Password");
        return;
    }

    std::string confirmation = ui.askString("Do you really want to delete your account: (YES)");

    if(!wantContinue(confirmation))
    {
        ui.clearScreen();
        return;
    }

    accounts.erase(accounts.begin() + index);
    ui.printPauseClear("Account was deleted successfully");
    choice = 4;
    accountChoice = 5;
    currentAccountId = -1;
}

void AccountManager::settings(int &accountChoice)
{
    int choice = 0;

    while (choice!=4)
    {
        ui.printAccountSettings();
        choice = ui.getChoice(1, 4);
        ui.clearScreen();

        switch(choice)
        {
        case 1: changeUsername(); break;
        case 2: changePassword(); break;
        case 3: deleteAccount(accountChoice, choice); break;
        case 4: break;
        }
    }
}
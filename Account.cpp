#include "Account.h"

Account::Account(const std::string& username, const std::string& password, std::uint64_t ID)
	:username(username), password(password), ID(ID), projectNextID(1)
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

std::uint64_t Account::getID() const
{
    return ID;
}
const std::vector<Project>& Account::getProjects() const
{
    return projects;
}
const std::vector<std::uint64_t>& Account::getFriendsIDs() const{
    return friendsIDs;
}

void Account::setUsername(const std::string &newUsername)
{
    username = newUsername;
}
void Account::setPassword(const std::string &newPassword)
{
    password = newPassword;
}

	
Project* Account::findProjectByID(std::uint64_t ID)
{
    for(size_t i = 0; i < projects.size(); i++)
    {
        if(ID == projects[i].getID()) return &projects[i];
    }
    return nullptr;
}
std::ptrdiff_t Account::findProjectIndexByID(std::uint64_t ID)
{
    for(size_t i = 0; i < projects.size(); i++)
    {
        if(ID == projects[i].getID()) return i;
    }
    return -1;
}

void Account::addProject(const std::string &name)
{
    projects.emplace_back(name, projectNextID++);
}
void Account::deleteProject(size_t index)
{
    projects.erase(projects.begin() + index);
}



void Account::addFriend(std::uint64_t ID) {
    friendsIDs.push_back(ID);
}
std::ptrdiff_t Account::findFriendIndexByID(std::uint64_t ID) {
    for(size_t i = 0; i < friendsIDs.size(); i++) 
    {
        if(friendsIDs[i] == ID) return i;
    }
    return -1;
}
bool Account::deleteFriend(std::uint64_t ID) {
    size_t index = findFriendIndexByID(ID);
    if(index == -1) return false;

    friendsIDs.erase(friendsIDs.begin() + index);
    return true;
}
bool Account::isHeMyFriend(std::uint64_t ID) {
    for(const auto& friendID : friendsIDs) 
        if(friendID == ID) return true;

    return false;
}
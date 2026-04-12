#include "Account.h"

Account::Account(const std::string& username, const std::string& password, std::uint64_t ID)
	:username(username), password(password), ID(ID)
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
const std::vector<std::uint64_t>& Account::getProjectsIDs() const
{
    return projectsIDs;
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

	
std::ptrdiff_t Account::findProjectsIDsIndexByID(std::uint64_t ID)
{
    for(size_t i = 0; i < projectsIDs.size(); i++)
    {
        if(ID == projectsIDs[i]) return i;
    }
    return -1;
}

void Account::addProjectID(std::uint64_t ID)
{
    projectsIDs.push_back(ID);
}
bool Account::deleteProjectID(std::uint64_t ID)
{
    std::ptrdiff_t index = findProjectsIDsIndexByID(ID);
    if(index == -1) return false;

    projectsIDs.erase(projectsIDs.begin() + index);
    return true;
}



void Account::addFriend(std::uint64_t ID) {
    friendsIDs.push_back(ID);
}
size_t Account::findFriendIndexByID(std::uint64_t ID) {
    for(size_t i = 0; i < friendsIDs.size(); i++) 
        if(friendsIDs[i] == ID) return i;
}
void Account::deleteFriend(std::uint64_t ID) {
    size_t index = findFriendIndexByID(ID);
    friendsIDs.erase(friendsIDs.begin() + index);
}
bool Account::isHeMyFriend(std::uint64_t ID) {
    for(auto friendID : friendsIDs) 
        if(friendID == ID) return true;

    return false;
}
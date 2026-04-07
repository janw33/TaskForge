#include "ProjectMember.h"

ProjectMember::ProjectMember(std::uint64_t ID ,const std::string &username, Role role) 
    : ID(ID), username(username), role(role)
{
}
  
Role ProjectMember::getRole() const {
    return role;
}
std::uint64_t ProjectMember::getID() const {
    return ID;
}
const std::string &ProjectMember::getUsername() const {
    return username;
}
std::string ProjectMember::roleToString() const {
    switch (role) {
        case Role::USER: return "USER";
        case Role::ADMIN: return "ADMIN";
        case Role::OWNER: return "OWNER";
    }
    return "Unknown";
}

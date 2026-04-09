#include "ProjectMember.h"

ProjectMember::ProjectMember(std::uint64_t ID , Role role) 
    : ID(ID), role(role)
{
}
  
Role ProjectMember::getRole() const {
    return role;
}
std::uint64_t ProjectMember::getID() const {
    return ID;
}

std::string ProjectMember::roleToString() const {
    switch (role) {
        case Role::USER: return "USER";
        case Role::ADMIN: return "ADMIN";
        case Role::OWNER: return "OWNER";
    }
    return "Unknown";
}

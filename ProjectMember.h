
#pragma once
#include <string>

enum class Role {USER, ADMIN, OWNER};

class ProjectMember {
    private:
    Role role;
    std::uint64_t ID;
    std::string username;

    public:
    ProjectMember(std::uint64_t ID, const std::string &username, Role role);
    Role getRole() const;
    std::uint64_t getID() const;
    const std::string &getUsername() const; 
    std::string roleToString() const;
}; 
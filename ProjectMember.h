
#pragma once
#include <string>

enum class Role {USER, ADMIN, OWNER};

class ProjectMember {
    private:
    Role role;
    std::uint64_t ID;

    public:
    ProjectMember(std::uint64_t ID, Role role);
    Role getRole() const;
    std::uint64_t getID() const;
    std::string roleToString() const;
}; 
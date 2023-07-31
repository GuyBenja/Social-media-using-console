#ifndef ENTITIY_H
#define ENTITIY_H
#include <iostream>
#include <fstream>
#include "Status.h"
#include "Exceptions.h"
#include <unordered_map>

class Entity
{

protected:
    std::string												m_name;
    std::unordered_map<std::string, Entity*>				m_connectedEntity;
    std::vector<Status*>									m_wallOfStatus;

    virtual void saveAdditionalData(std::ofstream& file) const {}

public:
    Entity() = default;
    Entity(const std::string& name)throw(NameException);
    virtual ~Entity() { for (auto iter : m_wallOfStatus) delete iter; }
    virtual void operator+=(Entity& new_follower) = 0;
    bool operator>(const Entity& other);

    void setName(const std::string& name)
    {
        m_name = name;
    }
    inline const std::string& getName()const { return m_name; }
    inline int getAmountOfFollowers()const { return m_connectedEntity.size(); }
    void addStatus(const std::string& text);
    void addStatus(const std::string& text, const std::string& path);
    void displayWall(int i = 0)const;
    void removeFollower(const std::string& NameToRemove);
    void displayMyFollowers()const;
    bool isFollowerExist(const std::string& nameToCheck)const;
    void saveToFile(std::ofstream& file)const ;
    inline std::unordered_map<std::string, Entity*>& getConnectedEntity() { return m_connectedEntity; }
};
#endif // !"ENTITIY_H"

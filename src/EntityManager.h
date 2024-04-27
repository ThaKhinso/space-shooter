#pragma once
#include "Common.h"
#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>>    EntityVec;
typedef std::map<std::string, EntityVec>        EntityMap;

class EntityManager{
public:
private:
    EntityVec   m_entities;
    EntityMap   m_entityMap;
    EntityVec   m_toAdd;
    size_t      m_totalEntities;

    void removeDeadEntities(EntityVec& vec);
};
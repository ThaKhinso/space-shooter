#pragma once

#include "Common.h"
#include "CInput.h"
#include "CLifeSpan.h"
#include "CScore.h"
#include "CShape.h"
#include "CCollision.h"
#include "CTransform.h"
#include <string>


class Entity {
public:
    std::shared_ptr<CInput>     cinput;
    std::shared_ptr<CCollision> collision;
    std::shared_ptr<CLifeSpan>  clifespan;
    std::shared_ptr<CShape>     cshape;
    std::shared_ptr<CScore>     cscore;
    std::shared_ptr<CTransform> ctransform;


    void destroy();
    size_t id() const;
    bool isActive() const;
    const std::string& tag() const;

private:
    friend class EntityManager;
    size_t      m_id {0};
    std::string m_tag{"default"};
    bool        m_active{true};

    Entity(size_t id, const std::string& tag);      
};
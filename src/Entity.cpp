#include "StdAfx.h"
#include "Entity.h"

namespace stellabellum {

    bool Entity::isFixedPosition() {
        return false;
    }

    Entity::EntityType Entity::getType() {
        return m_type;
    }

    Entity::Entity(World* world, ISceneNode* parent, ISceneManager* mgr, s32 id,
        const core::vector3df& position,
        const core::vector3df& rotation,
        const core::vector3df& scale):
    ISceneNode(parent, mgr, id, position, rotation, scale),
        m_acceleration(0,0,0),
        m_velocity(0,0,0),
        m_type(GenericEntity),
        m_world(world)
    {}

    void Entity::render()
    {

    }

    void Entity::OnRegisterSceneNode()
    {
        if (IsVisible)
            SceneManager->registerNodeForRendering(this);

        ISceneNode::OnRegisterSceneNode();
    }

    const core::aabbox3d<f32>& Entity::getBoundingBox() const
    {
        return m_box;
    }

}
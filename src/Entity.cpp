#include "stellabellum.h"
#include "Entity.h"

namespace stellabellum {
    namespace entities {

        Entity::Entity(game::World* world, scene::ISceneNode* parent,
            scene::ISceneManager* mgr, s32 id,
            const core::vector3df& position,
            const core::vector3df& rotation,
            const core::vector3df& scale)

            :ISceneNode(parent, mgr, id, position, rotation, scale),
            m_acceleration(0,0,0),
            m_velocity(0,0,0),
            m_type(GenericEntity),
            m_world(world)
        {
            setAutomaticCulling(scene::EAC_OFF);
        }

        Entity::EntityType Entity::getType() {
            return m_type;
        }

        bool Entity::isFixedPosition() {
            return false;
        }

        void Entity::render() {}

        void Entity::OnRegisterSceneNode() {
            if (IsVisible)
                SceneManager->registerNodeForRendering(this);

            ISceneNode::OnRegisterSceneNode();
        }

        const core::aabbox3d<f32>& Entity::getBoundingBox() const {
            return m_box;
        }

    }
}
#include "stellabellum.h"
#include "Asteroid.h"

namespace stellabellum {
    namespace entities {

        Asteroid::Asteroid(game::World* world, scene::ISceneNode* parent,
            scene::ISceneManager* mgr, s32 id,
            scene::IAnimatedMesh* mesh, video::ITexture* tex,
            const core::vector3df& position,
            const core::vector3df& rotation,
            const core::vector3df& scale)

            :Entity(0, parent, mgr, id, position, rotation, scale )
        {
            scene::IAnimatedMeshSceneNode* asteroidMeshNode =
                mgr->addAnimatedMeshSceneNode(mesh, this, id);

            asteroidMeshNode->setMaterialTexture(0, tex);
            asteroidMeshNode->setMaterialFlag(video::EMF_LIGHTING, false);
        }

        bool Asteroid::update(const float delta) {
            m_velocity += m_acceleration;

            core::vector3df position = getPosition();
            core::vector3df positionChange = m_velocity * delta;
            setPosition(position + positionChange);

            core::vector3df rotation = this->getRotation();
            core::vector3df rotationChange = m_angularvelocity * delta;
            setRotation(rotation + rotationChange);

            return true;
        }

    }
}
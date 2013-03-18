#include "stellabellum.h"
#include "Entity.h"
#include "Asteroid.h"

namespace stellabellum {
    namespace entities {

        CAsteroid::CAsteroid(game::CWorld* world, scene::ISceneNode* parent,
            scene::ISceneManager* mgr, s32 id,
            scene::IAnimatedMesh* mesh, video::ITexture* tex,
            const core::vector3df& position,
            const core::vector3df& rotation,
            const core::vector3df& scale)

            :CEntity(world, mgr, position, rotation, scale)
        {
            scene::IAnimatedMeshSceneNode* asteroidMeshNode =
                mgr->addAnimatedMeshSceneNode(mesh, this, id);


        }

        bool CAsteroid::update(const game::CGame *, const float delta) {
            Velocity += Acceleration;

            core::vector3df position = getPosition();
            core::vector3df positionChange = Velocity * delta;
            setPosition(position + positionChange);

            core::vector3df rotation = this->getRotation();
            core::vector3df rotationChange = AngularVelocity * delta;
            setRotation(rotation + rotationChange);

            return true;
        }

    }
}
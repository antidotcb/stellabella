#include "stellabellum.h"
#include "Rocket.h"

namespace stellabellum {
    namespace entities {

        CRocket::CRocket(game::CWorld* world, scene::ISceneManager* scene, 
            const core::vector3df& position)
            : CEntity(world, scene, position)
        {
            Type = CEntity::ProjectileEntity;
        }

        bool CRocket::update( const game::CGame *, const float delta ) {
            core::vector3df position = getPosition();

            Velocity += Acceleration * delta;
            position += Velocity * delta;

            core::vector3df rotation = getRotation();
            rotation += AngularVelocity * delta;

            setPosition(position);
            setRotation(rotation);

            return !isOutOfConstrains(position);
        }

        bool CRocket::isOutOfConstrains(core::vector3df &position) {
            const f32 width = getWidth();
            const f32 height = getHeight();
            return  Constrains.MinEdge.X > position.X + width   ||
                Constrains.MaxEdge.X < position.X - width   ||
                Constrains.MinEdge.Y > position.Y + height  ||
                Constrains.MaxEdge.Y < position.Y - height;
        }

    }
}
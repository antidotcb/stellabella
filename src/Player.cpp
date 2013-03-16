#include "stellabellum.h"
#include "Player.h"
#include "Game.h"
#include "Input.h"

namespace stellabellum {
    namespace entities {

        Player::Player(
            game::World* world, scene::ISceneNode* parent,
            scene::ISceneManager* mgr, s32 id,
            const core::vector3df& position,
            const core::vector3df& rotation,
            const core::vector3df& scale)

            :Entity(world, parent, mgr, id, position, rotation, scale)
        {
            m_type = Entity::PlayerEntity;
            setName("Player");
        }

        bool Player::update(const game::Game * g, float delta) {            
            move(g, delta);

            u32 m_lastAsteroid=0, time = g->getDevice()->getTimer()->getTime();

            if (g->getPlayerControl().isFirePressed()) {
                if (time - m_lastAsteroid > 100)
                {
                    //addRocket();
                    m_lastAsteroid = time;
                }
            }

            return true;
        }

        void Player::move(const game::Game * g, const f32 delta) {
            const f32 movementVelocity = 150.f;

            core::vector3df position = getPosition();
            core::vector2df movement(0.f, 0.f);

            g->getPlayerControl().getMovement(movement);

            position.X += movement.X * movementVelocity * delta;
            position.Y += movement.Y * movementVelocity * delta;

            setPosition(position);
        }

    }
}
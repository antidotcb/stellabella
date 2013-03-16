#pragma once

#include "Entity.h"

namespace stellabellum {
    namespace entities {

        class Player: public Entity {
        public:
            Player(game::World* world, scene::ISceneNode* parent,
                scene::ISceneManager* mgr, s32 id,
                const core::vector3df& position = core::vector3df(0,0,0),
                const core::vector3df& rotation = core::vector3df(0,0,0),
                const core::vector3df& scale = core::vector3df(1,1,1));

            virtual bool update(const game::Game * g, const float delta);

            void Player::move(const game::Game * g, const f32 delta);
        };

    }
}
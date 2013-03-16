#pragma once

#include "Entity.h"

namespace stellabellum {
    namespace entities {

        class Asteroid: public Entity {
        public:
            Asteroid(game::World* world, scene::ISceneNode* parent,
                scene::ISceneManager* mgr, s32 id,
                scene::IAnimatedMesh* mesh, video::ITexture* tex,
                const core::vector3df& position = core::vector3df(0,0,0),
                const core::vector3df& rotation = core::vector3df(0,0,0),
                const core::vector3df& scale = core::vector3df(1,1,1));

            virtual bool update(const float delta);
        };

    }
}
#pragma once

#include "Entity.h"

namespace stellabellum {
    namespace entities {

        class CAsteroid: public CEntity {
        public:
            CAsteroid(game::CWorld* world, scene::ISceneNode* parent,
                scene::ISceneManager* mgr, s32 id,
                scene::IAnimatedMesh* mesh, video::ITexture* tex,
                const core::vector3df& position = core::vector3df(0,0,0),
                const core::vector3df& rotation = core::vector3df(0,0,0),
                const core::vector3df& scale = core::vector3df(1,1,1));

            virtual bool update(const game::CGame *, const float delta);
        };

    }
}
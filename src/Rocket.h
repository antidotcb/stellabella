#pragma once

#include "Entity.h"

namespace stellabellum {
    namespace entities {

        class CRocket: public CEntity {
        public:
            CRocket(game::CWorld* world, scene::ISceneManager* scene,
                const core::vector3df& position = core::vector3df(0,0,0));

            virtual bool update( const game::CGame *, const float delta );

            bool isOutOfConstrains(core::vector3df &position);
        };

    }
}
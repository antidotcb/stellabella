#pragma once

#include "stellabellum.h"

namespace stellabellum {

    class Asteroid: public Entity {
    public:
        Asteroid(Game * game, ISceneNode* parent, ISceneManager* mgr, s32 id,
            scene::IAnimatedMesh * mesh, video::ITexture * tex,
            const core::vector3df& position = core::vector3df(0,0,0),
            const core::vector3df& rotation = core::vector3df(0,0,0),
            const core::vector3df& scale = core::vector3df(1,1,1));

        virtual bool update( float delta );

        virtual scene::ESCENE_NODE_TYPE getType() const {
            return scene::ESNT_EMPTY;
        }

    private:
        scene::IAnimatedMeshSceneNode* m_child;
    };

}
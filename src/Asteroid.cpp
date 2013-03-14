#include "StdAfx.h"
#include "Game.h"
#include "Asteroid.h"

namespace stellabellum {

    Asteroid::Asteroid(
        Game * game, ISceneNode* parent, ISceneManager* mgr, s32 id,
        scene::IAnimatedMesh * mesh, video::ITexture * tex,
        const core::vector3df& position,
        const core::vector3df& rotation,
        const core::vector3df& scale):
    Entity(0, parent, mgr, id, position, rotation, scale )
    {
        setAutomaticCulling(scene::EAC_OFF);

        m_child = mgr->addAnimatedMeshSceneNode(mesh, this, id);
        
        m_child->setPosition(core::vector3df(0,0,0));
        m_child->setMaterialTexture(0, tex);
        m_child->setMaterialFlag(video::EMF_LIGHTING, false);
    }

    bool Asteroid::update(float delta) {
        m_velocity += m_acceleration;
        core::vector3df movement = m_velocity * delta;

        setPosition(getPosition() + movement);

        return true;
    }
}
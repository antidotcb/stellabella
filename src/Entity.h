#pragma once

#include <vector>
using std::vector;

#include <irrlicht.h>
#include <ISceneNode.h>
#include <IMeshSceneNode.h>
#include <IAnimatedMeshSceneNode.h>


using namespace irr;

using scene::ISceneNode;
using scene::ISceneManager;

namespace stellabellum {

    class World;

    class Entity: public ISceneNode {
    public:
        enum EntityType {
            GenericEntity, PlayerEntity, EnemyEntity, ProjectileEntity
        };

        Entity(World * world, ISceneNode* parent, ISceneManager* mgr, s32 id,
            const core::vector3df& position = core::vector3df(0,0,0),
            const core::vector3df& rotation = core::vector3df(0,0,0),
            const core::vector3df& scale = core::vector3df(1,1,1));

        virtual EntityType getType();

        virtual bool isFixedPosition();

        virtual bool update(float delta) = 0;

        ///* abstract methods from ISceneNode *///////////////////////////////////

        void render();

        void OnRegisterSceneNode();

        const core::aabbox3d<f32>& getBoundingBox() const;

    protected:
        World * const m_world;

        core::vector3df m_acceleration;
        core::vector3df m_velocity;
        core::vector3df m_angularvelocity;

        EntityType m_type;

    private:
        core::aabbox3d<f32> m_box;
    };

}
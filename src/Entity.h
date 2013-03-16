#pragma once

#include <vector>

namespace stellabellum {
    namespace entities {

        class Entity: public scene::ISceneNode {
        public:
            virtual bool update(const game::Game *, const float delta) = 0;

            enum EntityType {
                GenericEntity, PlayerEntity, EnemyEntity, ProjectileEntity
            };

            Entity(game::World* world, scene::ISceneNode* parent,
                scene::ISceneManager* mgr, s32 id,
                const core::vector3df& position = core::vector3df(0,0,0),
                const core::vector3df& rotation = core::vector3df(0,0,0),
                const core::vector3df& scale = core::vector3df(1,1,1));

            virtual EntityType getType();

            virtual bool isFixedPosition();

            void render();

            void OnRegisterSceneNode();

            const core::aabbox3d<f32>& getBoundingBox() const;

        protected:
            game::World* const m_world;

            core::vector3df m_acceleration;
            core::vector3df m_velocity;
            core::vector3df m_angularvelocity;

            EntityType m_type;

        private:
            core::aabbox3d<f32> m_box;
        };

    }
}
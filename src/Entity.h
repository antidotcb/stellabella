#pragma once

#include <vector>

namespace stellabellum {
    namespace entities {

        class CEntity: public scene::ISceneNode {
        public:
            virtual bool update(const game::CGame *, const float delta) = 0;

            enum EntityType {
                GenericEntity, PlayerEntity, EnemyEntity, ProjectileEntity
            };

            CEntity(game::CWorld* world,
                scene::ISceneManager* scene,
                const core::vector3df& position = core::vector3df(0,0,0),
                const core::vector3df& rotation = core::vector3df(0,0,0),
                const core::vector3df& scale = core::vector3df(1,1,1));

            ~CEntity();

            virtual EntityType getType();

            virtual bool isFixedPosition();

            void render();

            void OnRegisterSceneNode();

            virtual const core::aabbox3d<f32>& getBoundingBox() inline const;

            virtual void setMesh(scene::IAnimatedMesh* mesh);

            virtual void setTexture(video::ITexture* texture);

            virtual void setConstrains(const core::aabbox3df& box);

            virtual void setVelocity(const core::vector3df& velocity);

            virtual void setAcceleration(const core::vector3df& acceleration);

            virtual void setAngularVelocity(const core::vector3df& angularVelocity);

        protected:
            virtual f32 getWidth() inline const { return Width; }
            virtual f32 getHeight() inline const { return Height; }

            virtual void updateSizes();

            game::CWorld* const World;

            core::vector3df Acceleration;
            core::vector3df Velocity;
            core::vector3df AngularVelocity;

            EntityType Type;

            core::aabbox3d<f32> Constrains;

        private:
            core::aabbox3d<f32> Box;
            
            scene::ISceneNode* Node;

            f32 Width;
            f32 Height;
        };

    }
}
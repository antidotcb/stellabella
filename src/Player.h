#pragma once

#include "Entity.h"

namespace stellabellum {
    namespace entities {

        class CPlayer: public CEntity {
        public:
            CPlayer(game::CWorld* world, scene::ISceneManager* scene,
                const core::vector3df& position = core::vector3df(0,0,0));

            virtual ~CPlayer();

            virtual bool update(const game::CGame * g, const float delta);

            void move(const game::CGame * g, const f32 delta);

            void fitIntoConstrains(core::vector3df& position);
            
            void makeShot();

            f32 getRocketAcceleration();
            f32 getPlayerVelocity();
            f32 getRocketVelocity();
        protected:
            virtual void updateSizes();

        private:
            u32 LastRocketShotTime;
            bool WingLastShot;

            scene::ISceneNode* LeftWing;
            scene::ISceneNode* RightWing;

            core::vector3df Rotation;
            f32 Width;
            f32 Height;
        };

    }
}
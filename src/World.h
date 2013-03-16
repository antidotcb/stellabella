#pragma once

#include "list"

namespace stellabellum {
    namespace game {

        class World
        {
        public:
            World(scene::ICameraSceneNode* camera);

            void init(game::Game* g, scene::ISceneManager* mgr);

            void update(game::Game* g, f32 delta);

            ~World();

        private:
            scene::ICameraSceneNode* m_camera;
            entities::Player* m_player;

            typedef std::list<entities::Entity *> m_entities;
            typedef std::list<entities::Entity *> m_newEntities;
        };

    }
}
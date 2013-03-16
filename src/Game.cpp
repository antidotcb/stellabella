#include "stellabellum.h"
#include "Game.h"
#include "Screen.h"
#include "Input.h"

namespace stellabellum {
    namespace game {

        Game::Game(Options& options): m_options(options), m_playerControl(&m_input){
            init();
        }

        void Game::run()
        {
            u32 then = m_device->getTimer()->getTime();

            while(m_device->run()) {                
                const u32 now = m_device->getTimer()->getTime();        
                const f32 frameDeltaTime = (f32)(now - then) / 1000.f;

                updateFPS();

                update(frameDeltaTime);

                render();

                then = now;
            }
        }

        Game::~Game() {
            m_device->drop();
        }

        void Game::init() {
            core::dimension2d<u32> windowSize(m_options.Width, m_options.Height);
            
            m_device = createDevice(m_options.Driver, windowSize, 16,
                false, false, false, dynamic_cast<IEventReceiver*>(&m_input));

            if (!m_device) {
                throw std::exception("Cannot initialize rendering device.");
            }

            m_input.initGamepads(m_device);

            m_driver = m_device->getVideoDriver();
            m_scene = m_device->getSceneManager();
        }

        void Game::render() {
            Screen* scr = getActiveScreen();

            if (scr) {
                m_driver->beginScene(true, true, scr->getBgColor());
                scr->render();
                m_driver->endScene();
            }
        }

        Screen* Game::getActiveScreen() {
            return dynamic_cast<Screen *>(getCurrentState());
        }

        void Game::updateFPS() {
            int fps = m_driver->getFPS();
            if (m_fps != fps) {
                m_fps = fps;

                core::stringw tmp(m_title);
                tmp += L" - [";
                tmp += m_driver->getName();
                tmp += L"] fps: ";
                tmp += fps;

                m_device->setWindowCaption(tmp.c_str());
            }
        }

        ISceneManager* Game::createNewScene() {
            ISceneManager* scene = m_scene->createNewSceneManager();
            return scene;
        }

        const wchar_t* Game::m_title = L"Stella Bellum";

    }
}
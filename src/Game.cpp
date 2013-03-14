#include "StdAfx.h"
#include "Game.h"
#include "Screen.h"

namespace stellabellum {
    Game::Game(Options & options): m_options(options) {
        init();
    }

    void Game::run()
    {
        u32 then = m_device->getTimer()->getTime();

        // main loop
        while(m_device->run()) {
            // Work out a frame delta time.
            const u32 now = m_device->getTimer()->getTime();        
            const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds

            updateFPS();

            update(frameDeltaTime);

            render();

            Sleep(0);
        }
    }

    Game::~Game() {
        m_device->drop();
    }

    void Game::init() {
        core::dimension2d<u32> windowSize(m_options.Width, m_options.Height);
        // creation of rendering device
        m_device = createDevice(m_options.Driver, windowSize, 16,
            false, false, false, &m_receiver);

        if (!m_device) {
            DebugBreak();
            throw std::exception("Cannot initialize rendering device.");
        }

        m_device->activateJoysticks(m_joystickInfo);

        m_driver = m_device->getVideoDriver();
        m_scene = m_device->getSceneManager();
    }

    void Game::render() {
        Screen * scr = getActiveScreen();

        if (scr) {
            m_driver->beginScene(true, true, scr->getBgColor());
            scr->render();
            m_driver->endScene();
        }
    }

    Screen * Game::getActiveScreen() {
        return dynamic_cast<Screen *>(_getCurrentState());
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

    ISceneManager * Game::createNewScene() {
        ISceneManager * scene = m_scene->createNewSceneManager();
        return scene;
    }

    const TCHAR * Game::m_title = L"Stella Bellum";

}
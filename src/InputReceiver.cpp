#include "StdAfx.h"
#include "InputReceiver.h"

namespace stellabellum {

    InputReceiver::InputReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            m_keyPressed[i] = false;
    }

    bool InputReceiver::OnEvent( const SEvent& event )
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            m_keyPressed[event.KeyInput.Key] = event.KeyInput.PressedDown;

        // Remember the mouse state
        if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
        {
            switch(event.MouseInput.Event)
            {
            case EMIE_RMOUSE_PRESSED_DOWN:
                m_mouseState.rightBtnPressed = true;
                break;

            case EMIE_RMOUSE_LEFT_UP:
                m_mouseState.rightBtnPressed = true;
                break;

            case EMIE_LMOUSE_PRESSED_DOWN:
                m_mouseState.leftBtnPressed = true;
                break;

            case EMIE_LMOUSE_LEFT_UP:
                m_mouseState.leftBtnPressed = false;
                break;

            case EMIE_MOUSE_MOVED:
                m_mouseState.position.X = event.MouseInput.X;
                m_mouseState.position.Y = event.MouseInput.Y;
                break;

            default:
                // no wheel support
                break;
            }
        }

        // store the state of the first joystick, ignoring others.
        if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
            && event.JoystickEvent.Joystick == 0) {
                m_joystickState = event.JoystickEvent;
        }

        return false;
    }

}
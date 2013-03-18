#include "stellabellum.h"
#include "Input.h"

namespace stellabellum {
    namespace game {

        CInput::CInput()
            : GamepadCount(0)
        {
            for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
                IsKeyPressed[i] = false;
        }

        CInput::~CInput() {
            // empty
        }

        bool CInput::OnEvent(const SEvent& event) {
            if (core::equals(event.EventType, irr::EET_KEY_INPUT_EVENT)) {
                IsKeyPressed[event.KeyInput.Key] = event.KeyInput.PressedDown;
            }

            if (core::equals(event.EventType, irr::EET_MOUSE_INPUT_EVENT)) {
                switch(event.MouseInput.Event) {
                case EMIE_RMOUSE_PRESSED_DOWN:
                    MouseState.RightBtnPressed = true;
                    break;

                case EMIE_RMOUSE_LEFT_UP:
                    MouseState.RightBtnPressed = false;
                    break;

                case EMIE_LMOUSE_PRESSED_DOWN:
                    MouseState.LeftBtnPressed = true;
                    break;

                case EMIE_LMOUSE_LEFT_UP:
                    MouseState.LeftBtnPressed = false;
                    break;

                case EMIE_MOUSE_MOVED:
                    MouseState.Position.X = event.MouseInput.X;
                    MouseState.Position.Y = event.MouseInput.Y;
                    break;

                default:
                    break;
                }
            }

            for (u32 i = 0; i < GamepadCount; i++) {
                u32 gamepad = (u32)event.JoystickEvent.Joystick;
                if (core::equals(event.EventType, irr::EET_JOYSTICK_INPUT_EVENT)
                    && core::equals(gamepad, i)) {
                        GamepadStates[i] = event.JoystickEvent;
                }
            }

            return false;
        }

        const CInput::SMouseState& CInput::getMouseState() const {
            return MouseState;
        }

        bool CInput::isKeyPressed(const EKEY_CODE keyCode) const {
            return IsKeyPressed[keyCode];
        }

        const CInput::SGamepadState& CInput::getGamepadState(const u32 j) const {
            return GamepadStates[j];
        }

        const bool CInput::isGamepadAvailable( const u32 j ) const {
            return j < GamepadCount;
        }

        void CInput::initGamepads(IrrlichtDevice* device) {
            device->activateJoysticks(GamepadInfos);

            GamepadCount = GamepadInfos.size();
            for(int i = GamepadCount; i--;) {
                GamepadStates.push_back(SGamepadState());
            }
        }


        CInput::SMouseState::SMouseState()
            :LeftBtnPressed(false),
            RightBtnPressed(false) {}


        CControls::CControls(game::CInput* input)
            : Input(input),
            Gamepad(0)
        {
        }

        bool CControls::isFirePressed() const {
            bool keyPressed = Input->isKeyPressed(getFireKey());
            bool buttonPressed = false;

            if (Input->isGamepadAvailable(Gamepad)) {
                const CInput::SGamepadState& joyState =
                    Input->getGamepadState(Gamepad);

                buttonPressed = joyState.IsButtonPressed(getFireButton());
            }

            return  keyPressed || buttonPressed;
        }

        void CControls::getMovement(core::vector2df& movement) const {            
            if (!getGamepadMovement(movement)) {
                const CInput::SMouseState& mState = Input->getMouseState();
                
                if (Input->isKeyPressed(getLeftKey())) {
                    movement.X -= 1.f;
                }

                if (Input->isKeyPressed(getRightKey())) {
                    movement.X += 1.f;
                }

                if (Input->isKeyPressed(getUpKey())) {
                    movement.Y += 1.f;
                }

                if (Input->isKeyPressed(getDownKey())) {
                    movement.Y -= 1.f;
                }
            }
        }

        bool CControls::getGamepadMovement(core::vector2df& movement) const {
            if (!Input->isGamepadAvailable(Gamepad)) {
                return false;
            }

            const stellabellum::game::CInput::SGamepadState& joyState = 
                Input->getGamepadState(Gamepad);

            f32 deadZone = getDeadZone();

            f32 hMove = 0.f;
            f32 vMove = 0.f;

            u32 vAxis = getVerticalAxis();
            vMove = (f32) joyState.Axis[vAxis] / -32767.f;
            vMove = (fabs(vMove) < DeadZone) ? 0.f : vMove;

            u32 hAxis = getHorizontalAxis();
            hMove = (f32) joyState.Axis[hAxis] / 32767.f;
            hMove = (fabs(hMove) < DeadZone) ? 0.f : hMove;

            if (core::equals(hMove, 0.f) && core::equals(vMove, 0.f)) {
                return false;
            } else {
                movement.X = hMove;
                movement.Y = vMove;

                return true;
            }
        }

        const f32 CControls::DeadZone = 0.05f;

    }
}
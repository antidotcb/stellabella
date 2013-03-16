#pragma once

namespace stellabellum {
    namespace game {

        class Input: public IEventReceiver {
        public:
            Input();

            virtual ~Input();

            virtual bool OnEvent(const SEvent& event);

            typedef SEvent::SJoystickEvent GamepadState;

            struct MouseState {
                bool LeftBtnPressed;
                bool RightBtnPressed;
                core::position2di Position;

                MouseState();
            };

            virtual bool isKeyPressed(const EKEY_CODE keyCode) const;
            
            virtual const MouseState& getMouseState() const;

            virtual const GamepadState& getGamepadState(const u32 joy) const;
            
            virtual const bool isGamepadAvailable(const u32 joy) const;

            virtual void initGamepads(IrrlichtDevice* device);

        private:
            core::array<SJoystickInfo> m_GamepadInfo;
            u32 m_GamepadCount;

            bool m_keyPressed[KEY_KEY_CODES_COUNT];
            core::array<GamepadState> m_GamepadState;
            MouseState m_mouseState;
        };


        class PlayerControl {
        public:
            PlayerControl(game::Input* input);

            bool isFirePressed() const;

            void getMovement(core::vector2df& movement) const;

        private:
            const f32 getDeadZone() inline const        { return m_deadZone ; }

            const EKEY_CODE getUpKey() inline const     { return m_upKey; }
            const EKEY_CODE getDownKey() inline const   { return m_downKey; }
            const EKEY_CODE getLeftKey() inline const   { return m_leftKey; }
            const EKEY_CODE getRightKey() inline const  { return m_rightKey; }
            const EKEY_CODE getFireKey() inline const   { return m_fireKey; }

            const u32 getFireButton() inline const      { return m_fireButton; }
            const u32 getHorizontalAxis() inline const  { return m_hAxis; }
            const u32 getVerticalAxis() inline const    { return m_vAxis; }

            bool getGamepadMovement(core::vector2df & movement) const;

            u32 m_GamepadNum;

            game::Input* m_input;

            static const EKEY_CODE m_fireKey    = KEY_SPACE;
            static const EKEY_CODE m_upKey      = KEY_UP;
            static const EKEY_CODE m_downKey    = KEY_DOWN;
            static const EKEY_CODE m_leftKey    = KEY_LEFT;
            static const EKEY_CODE m_rightKey   = KEY_RIGHT;

            static const u32 m_fireButton = 0;

            static const u32 m_hAxis = game::Input::GamepadState::AXIS_X;
            static const u32 m_vAxis = game::Input::GamepadState::AXIS_Y;

            static const f32 m_deadZone;
        };
    }
}
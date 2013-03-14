#pragma once

namespace stellabellum {

    class StateMachine;

    class State {
    public:
        State(): m_inited(false), m_game(0) {}

        virtual void enter() = 0;
        virtual void leave() = 0;
        virtual void init() = 0;

        virtual void update(const f32 delta) = 0;

        virtual int getId() = 0;

        virtual ~State(void) {}
    protected:
        virtual StateMachine * _getStateMachine() {
            return m_game;
        }
    private:
        void init(StateMachine * game) {
            if (game) {
                m_game = game;
            } else {
                DebugBreak();
                throw std::exception("Null pointer as state based game.");
            }

            if (!m_inited) {
                init();
                m_inited = true;
            }
        }

        bool m_inited;
        StateMachine * m_game;

        friend class StateMachine;
    };

}
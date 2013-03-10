#pragma once
#ifndef H_STATE_BASED_GAME_11C21A23_DD29_4106_B88B_6485922CF572
#define H_STATE_BASED_GAME_11C21A23_DD29_4106_B88B_6485922CF572

#include <map>

#include "State.h"

namespace stellabellum {

    class StateMachine {
    protected:
        typedef std::map<int, State *> StateList;

    public:
        StateMachine(): m_previous(0), m_current(0) {}
        
        virtual ~StateMachine(void) {
            StateList::const_iterator it;
            for(it = m_states.begin(); it != m_states.end(); ++it) {
                delete it->second;
            }
            m_states.clear();
        }

        void addState(State * state) {
            if (state) {
                int id = state->getId();
                m_states[id] = state;

                if (!m_current) {
                    _enterState(state);
                }
            } else {
                DebugBreak();
                throw std::exception("Null pointer as game state.");
            }
        }

        void enterState(int id) {
            State * next = m_states.at(id);
            _enterState(next);
        }

        void returnBack() {
            if (m_previous) {
                _enterState(m_previous);
            } else {
                DebugBreak();
                throw std::exception("Null pointer as previous game state.");
            }
        }
    protected:
        void update(const f32 delta) {
            if (m_current) {
                m_current->update(delta);
            }
        }

        State * _getCurrentState() {
            return m_current;
        }

        virtual void _enterState( State * next ) {
            if (m_current) {
                if (!m_current->m_inited) {
                    m_current->_init(this);
                }

                m_current->leave();
            }
            m_previous = m_current;

            if (next) {
                if (!next->m_inited) {
                    next->_init(this);
                }

                next->enter();
            } else {
                DebugBreak();
                throw std::exception("Null pointer as next game state.");
            }
            m_current = next;
        }

    private:
        StateList m_states;
        State * m_current;
        State * m_previous;
    };

}

#endif
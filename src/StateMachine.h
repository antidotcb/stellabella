#pragma once

#include <map>

#include "State.h"

namespace stellabellum {
    namespace states {

        class StateMachine {
        protected:
            typedef std::map<int, State *> StateList;

        public:
            StateMachine(): m_previous(0), m_current(0) {}

            virtual ~StateMachine(void) {
                if (m_current) {
                    m_current->leave();
                }

                StateList::const_iterator it;
                for(it = m_states.begin(); it != m_states.end(); ++it) {
                    delete it->second;
                }
                m_states.clear();
            }

            void addState(State* state, const bool enterIfFirst = true) {
                if (state) {
                    int id = state->getId();
                    m_states[id] = state;

                    if (!m_current && enterIfFirst) {
                        enter(state);
                    }
                } else {
                    throw std::exception("Null pointer as game state.");
                }
            }

            void enterState(int id) {
                State* next = m_states.at(id);
                enter(next);
            }

            void returnBack() {
                if (m_previous) {
                    enter(m_previous);
                } else {
                    throw std::exception("Null pointer as previous game state.");
                }
            }
        protected:
            void update(const f32 delta) {
                if (m_current) {
                    m_current->update(delta);
                }
            }

            State* getCurrentState() {
                return m_current;
            }

            virtual void enter(State* next) {
                if (m_current) {
                    m_current->setup(this);

                    m_current->leave();
                }
                m_previous = m_current;

                if (next) {
                    next->setup(this);

                    next->enter();
                } else {
                    throw std::exception("Null pointer as next state.");
                }
                m_current = next;
            }

        private:
            StateList m_states;
            State* m_current;
            State* m_previous;
        };

    }
}

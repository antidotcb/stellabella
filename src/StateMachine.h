#pragma once

#include <map>

#include "State.h"

namespace stellabellum {
    namespace states {

        class CStateMachine {
        protected:
            typedef std::map<int, CState *> StateList;

        public:
            CStateMachine()
                : Previous(0), Current(0)
            {}

            virtual ~CStateMachine(void) {
                if (Current) {
                    Current->leave();
                }

                StateList::const_iterator it;
                for(it = States.begin(); it != States.end(); ++it) {
                    delete it->second;
                }
                States.clear();
            }

            void addState(CState* state, const bool enterIfFirst = true) {
                if (state) {
                    int id = state->getId();
                    States[id] = state;

                    if (!Current && enterIfFirst) {
                        enter(state);
                    }
                } else {
                    throw std::exception("Null pointer as game state.");
                }
            }

            void enterState(int id) {
                CState* next = States.at(id);
                enter(next);
            }

            void returnBack() {
                if (Previous) {
                    enter(Previous);
                } else {
                    throw std::exception("Null pointer as previous game state.");
                }
            }
        protected:
            void update(const f32 delta) {
                if (Current) {
                    Current->update(delta);
                }
            }

            CState* getCurrentState() {
                return Current;
            }

            virtual void enter(CState* next) {
                if (Current) {
                    Current->setup(this);

                    Current->leave();
                }
                Previous = Current;

                if (next) {
                    next->setup(this);

                    next->enter();
                } else {
                    throw std::exception("Null pointer as next state.");
                }
                Current = next;
            }

        private:
            StateList States;
            CState* Current;
            CState* Previous;
        };

    }
}

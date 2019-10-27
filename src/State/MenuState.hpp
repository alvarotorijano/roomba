#pragma once

#include "State.hpp"

/**
 * State that allows program selection with the buttons on the Roomba.
 */
class MenuState : public State
{
public:
    /**
     * State constructor.
     * bot: Bot.
     */
    MenuState(Bot *bot);

    /**
     * Called when the state is entered.
     */
    void enter();

    /**
     * Called periodically.
     * delta: Time delta.
     */
    void update(unsigned long delta);

    /**
     * Called when the state is exited.
     */
    void exit();
};
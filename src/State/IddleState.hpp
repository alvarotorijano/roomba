#pragma once

#include "State.hpp"

/**
 * Starting state for the bot.
 */
class IddleState : public State
{
public:
    /**
     * State constructor.
     * bot: Bot.
     */
    IddleState(Bot *bot);

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
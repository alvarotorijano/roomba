#pragma once

#include "State.hpp"

/**
 * Square drawing state for the bot.
 */
class SquareSideState : public State
{
private:
    int side;
    unsigned long start;
public:
    /**
     * State constructor.
     * bot: Bot.
     */
    SquareSideState(Bot *bot);

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
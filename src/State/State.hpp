#pragma once

class Bot;

/**
 * State of the bot.
 */
class State {
protected:
    /**
     * Bot.
     */
    Bot *bot;
public:
    /**
     * State constructor.
     * bot: Bot.
     */
    State(Bot *_bot);



    /**
     * Called when the state is entered.
     */
    virtual void enter() = 0;

    /**
     * Called periodically.
     * delta: Time delta.
     */
    virtual void update(unsigned long delta) = 0;

    /**
     * Called when the state is exited.
     */
    virtual void exit() = 0;
};
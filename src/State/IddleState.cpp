#include "IddleState.hpp"

#include "../Bot.hpp"

/**
 * State constructor.
 * bot: Bot.
 */
IddleState::IddleState(Bot *bot) : State(bot) {
}

/**
 * Called when the state is entered.
 */
void IddleState::enter() {
}

/**
 * Called periodically.
 * delta: Time delta.
 */
void IddleState::update(unsigned long delta) {
}

/**
 * Called when the state is exited.
 */
void IddleState::exit() {
}
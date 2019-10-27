#include "MenuState.hpp"

#include "../Bot.hpp"
#include "../Leonidas.hpp"
#include "../OpenInterface/Buttons.hpp"

/**
 * State constructor.
 * bot: Bot.
 */
MenuState::MenuState(Bot *bot) : State(bot) {
}

/**
 * Called when the state is entered.
 */
void MenuState::enter() {
    bot->lcd.clear();
    bot->lcd.print("MENU");
}

/**
 * Called periodically.
 * delta: Time delta.
 */
void MenuState::update(unsigned long delta) {
    uint8_t buttons = bot->roomba.getButtons();
    //bot->lcd.clear();
    //bot->lcd.print(buttons);
    Leonidas *leo = (Leonidas *)bot;
    if (buttons & Buttons::SPOT) {
        bot->setState(&leo->seek);
    } else if (buttons & Buttons::DOCK) {
        bot->setState(&leo->squareSide);
    } else if (buttons & Buttons::DAY) {
        bot->setState(&leo->calibrateAngle);
    } else if (buttons & Buttons::HOUR) {
        bot->setState(&leo->calibrateDistance);
    } else if (buttons & Buttons::MINUTE) {
        bot->setState(&leo->dummy);
    }
}

/**
 * Called when the state is exited.
 */
void MenuState::exit() {
    for (int i = 0; i < 2; i++) {
        byte ledInfo1[3] = {0X0F, 0x00, 0x00};
        bot->roomba.send(Opcode::LEDS, ledInfo1, 3);
        delay(500);
        byte ledInfo2[3] = {0X0F, 0x80, 0xFF};
        bot->roomba.send(Opcode::LEDS, ledInfo2, 3);
        delay(500);
    }
}
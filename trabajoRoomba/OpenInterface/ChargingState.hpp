#pragma once

/**
 * Roomba Open Interface Charging States
 */
enum class ChargingState
{
    NOT_CHARGING = 0,
    REACONDITIONING_CHARGING = 1,
    FULL_CHARGING = 2,
    TRICKLE_CHARGING = 3,
    WAITING = 4,
    CHARGING_FAULT_CONDITION = 5
};
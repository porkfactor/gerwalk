#include <iostream>
#include "timer.hpp"

typedef unsigned int digital_pin_t;

static constexpr digital_pin_t STARBOARD_NAVIGATION_LIGHT = 1 << 0;
static constexpr digital_pin_t PORT_NAVIGATION_LIGHT = 1 << 1;
static constexpr digital_pin_t ANTI_COLLSION_LIGHT = 1 << 2;
static constexpr digital_pin_t AFT_LIGHT = 1 << 3;
static constexpr digital_pin_t LOGO_LIGHT = 1 << 4;

typedef timer<64> timer_type;

timer_type t;

static void timer_callback(
        timer_type::identifier_type identifier,
        void *opaque,
        void *context)
{
    static bool toggle = false;

    toggle = !toggle;
    digitalWrite(0, toggle ? HIGH : LOW);
}

void setup(void)
{
    for(digital_pin_t i = 0; i < 16; ++i)
    {
        pinMode(i, OUTPUT);
    }

    t.repeat(123, 500000, nullptr);
}

void loop(void)
{
    t.update(timer_callback);
}


#include <iostream>
#include "timer.hpp"

typedef unsigned int digital_pin_t;
typedef timer<64> timer_type;

static constexpr digital_pin_t STARBOARD_NAVIGATION_LIGHT = 1 << 0;
static constexpr digital_pin_t PORT_NAVIGATION_LIGHT = 1 << 1;
static constexpr digital_pin_t ANTI_COLLSION_LIGHT = 1 << 2;
static constexpr digital_pin_t AFT_LIGHT = 1 << 3;
static constexpr digital_pin_t LOGO_LIGHT = 1 << 4;

template<typename _Timer, int _OnDuration, int _OffDuration = _OnDuration>
class blinker
{
public:
    typedef enum { OFF, ON } state_type;

    blinker(digital_pin_t pin, _Timer &timer) :
        timer_(timer),
        pin_(pin),
        state_(OFF)
    {
        setLow();
    }

    static void on_timeout(timer_type::identifier_type identifier, void *opaque, void *user)
    {
        blinker *self = static_cast<decltype(self)>(opaque);

        self->setHigh();
    }

    static void off_timeout(timer_type::identifier_type identifier, void *opaque, void *user)
    {
        blinker *self = static_cast<decltype(self)>(opaque);

        self->setLow();
    }

    void setHigh()
    {
        digitalWrite(pin_, LOW);
        timer_.start(pin_, _OffDuration, off_timeout, static_cast<void *>(this));
    }

    void setLow()
    {
        digitalWrite(pin_, HIGH);
        timer_.start(pin_, _OnDuration, on_timeout, static_cast<void *>(this));
    }

private:
    _Timer &timer_;
    digital_pin_t pin_;
    state_type state_;
};

static timer_type t;
static blinker<timer_type, 100000, 100000> aft_light(AFT_LIGHT, t);
static blinker<timer_type, 500000, 500000> collision_light(ANTI_COLLSION_LIGHT, t);

void setup(void)
{
    for(digital_pin_t i = 0; i < 16; ++i)
    {
        pinMode(i, OUTPUT);
    }
}

void loop(void)
{
    t.update();
}


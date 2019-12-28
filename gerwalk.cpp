#include <iostream>
#include "timer.hpp"
#include "morse.h"

typedef unsigned int digital_pin_t;
typedef timer<64> timer_type;

static constexpr digital_pin_t STARBOARD_NAVIGATION_LIGHT = 1 << 0;
static constexpr digital_pin_t PORT_NAVIGATION_LIGHT = 1 << 1;
static constexpr digital_pin_t ANTI_COLLSION_LIGHT = 1 << 2;
static constexpr digital_pin_t AFT_LIGHT = 1 << 3;
static constexpr digital_pin_t LOGO_LIGHT = 1 << 4;

/*
 * TODO: see if we can reduce the amount of state data involved in this.
 */
template<typename _Timer = timer_type>
class morser
{
public:
    static constexpr timer_type::duration_type TRANSMITION_UNIT = 150000;

    static constexpr timer_type::duration_type SHORT_MARK_DURATION = TRANSMITION_UNIT;
    static constexpr timer_type::duration_type LONG_MARK_DURATION = 3 * TRANSMITION_UNIT;
    static constexpr timer_type::duration_type INTER_ELEMENT_GAP_DURATION = TRANSMITION_UNIT;
    static constexpr timer_type::duration_type SHORT_GAP_DURATION = 3 * TRANSMITION_UNIT;
    static constexpr timer_type::duration_type MEDIUM_GAP_DURATION = 7 * TRANSMITION_UNIT;

    morser(digital_pin_t pin, char const *data, _Timer &timer) :
        timer_(timer),
        pin_(pin),
        data_(data),
        pos_(0),
        nDigits_(0),
        currentDigit_(0)
    {
        enqueue_morse_character();
        setLow(MEDIUM_GAP_DURATION);
    }

    void handle_mark_timeout()
    {
        switch(next_digit())
        {
        case MORSE_EOM:
            /* NO BREAK */
        case MORSE_EOW:
            setLow(MEDIUM_GAP_DURATION);
            break;

        case MORSE_EOC:
            enqueue_morse_character();
            setLow(SHORT_GAP_DURATION);
            break;

        default:
            setLow(INTER_ELEMENT_GAP_DURATION);
            break;
        }
    }

    void handle_gap_timeout()
    {
        switch(current_digit())
        {
        case MORSE_DOT:
            setHigh(SHORT_MARK_DURATION);
            break;
        case MORSE_DASH:
            setHigh(LONG_MARK_DURATION);
            break;
        default:
            /* something went wrong enqueue-ing the last character; ignore and move on */
            enqueue_morse_character();
            setLow(INTER_ELEMENT_GAP_DURATION);
            break;
        }
    }

    enum morse_e next_digit(void)
    {
        return digits_[++currentDigit_];
    }

    enum morse_e current_digit(void)
    {
        return digits_[currentDigit_];
    }

    void setHigh(timer_type::duration_type timeout)
    {
        digitalWrite(pin_, HIGH);
        timer_.start(pin_, timeout, high_timeout, static_cast<void *>(this));
    }

    void setLow(timer_type::duration_type timeout)
    {
        digitalWrite(pin_, LOW);
        timer_.start(pin_, timeout, low_timeout, static_cast<void *>(this));
    }

protected:
    void enqueue_morse_character()
    {
        currentDigit_ = 0;
        nDigits_ = 0;

        /* if we've reached the end of data, wrap to the beginning */
        if(data_[pos_] == 0)
            pos_ = 0;

        morse_encode_character(data_[pos_++], morse_callback, this);
    }

    void enqueue_morse_digit(enum morse_e digit)
    {
        digits_[nDigits_++] = digit;
    }

private:
    static void morse_callback(enum morse_e digit, void *opaque)
    {
        morser *self = static_cast<decltype(self)>(opaque);

        self->enqueue_morse_digit(digit);
    }

    static void high_timeout(timer_type::identifier_type identifier, void *opaque, void *user)
    {
        morser *self = static_cast<decltype(self)>(opaque);

        self->handle_mark_timeout();
    }

    static void low_timeout(timer_type::identifier_type identifier, void *opaque, void *user)
    {
        morser *self = static_cast<decltype(self)>(opaque);

        self->handle_gap_timeout();
    }

    _Timer &timer_;
    digital_pin_t pin_;

    char const *data_;
    unsigned int pos_;

    /* morse digits associated with the current symbol being emitted */
    enum morse_e digits_[8];
    unsigned char nDigits_;
    unsigned char currentDigit_;
};

template<int _OnDuration, int _OffDuration = _OnDuration, typename _Timer = timer_type>
class blinker
{
public:
    blinker(digital_pin_t pin, _Timer &timer) :
        timer_(timer),
        pin_(pin)
    {
        setLow(_OffDuration);
    }

    void setHigh(timer_type::duration_type timeout)
    {
        digitalWrite(pin_, HIGH);
        timer_.start(pin_, timeout, high_timeout, static_cast<void *>(this));
    }

    void setLow(timer_type::duration_type timeout)
    {
        digitalWrite(pin_, LOW);
        timer_.start(pin_, timeout, low_timeout, static_cast<void *>(this));
    }

private:
    static void low_timeout(timer_type::identifier_type identifier, void *opaque, void *user)
    {
        blinker *self = static_cast<decltype(self)>(opaque);

        self->setHigh(_OnDuration);
    }

    static void high_timeout(timer_type::identifier_type identifier, void *opaque, void *user)
    {
        blinker *self = static_cast<decltype(self)>(opaque);

        self->setLow(_OffDuration);
    }

    _Timer &timer_;
    digital_pin_t pin_;
};

static timer_type t;
static morser<> port_navigation_light(PORT_NAVIGATION_LIGHT, "I hope you complete your mission, and can safely return to the Macross.", t);
static blinker<100000> aft_light(AFT_LIGHT, t);
static blinker<500000> collision_light(ANTI_COLLSION_LIGHT, t);

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


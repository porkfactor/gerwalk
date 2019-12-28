#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <curses.h>
#include <signal.h>
#include "emulator.hpp"

static constexpr uint64_t nanoseconds_per_second = 1000000000ULL;
/* time functions */
static inline uint64_t seconds_to_nanoseconds(uint64_t seconds)
{
    return seconds * nanoseconds_per_second;
}

static inline uint64_t milliseconds_to_microseconds(uint64_t milliseconds)
{
    return milliseconds * 1000ULL;
}

static inline uint64_t nanoseconds_to_seconds(uint64_t nanoseconds)
{
    return nanoseconds / nanoseconds_per_second;
}

static inline uint64_t nanoseconds_to_milliseconds(uint64_t nanoseconds)
{
    return nanoseconds / 1000000ULL;
}

static inline uint64_t nanoseconds_to_microseconds(uint64_t nanoseconds)
{
    return nanoseconds / 1000ULL;
}

static inline unsigned long timespec_to_nanoseconds(struct timespec const *ts)
{
    return seconds_to_nanoseconds(ts->tv_sec) + static_cast<uint64_t>(ts->tv_nsec);
}

static inline unsigned long timespec_to_microseconds(struct timespec const *ts)
{
    return nanoseconds_to_microseconds(timespec_to_nanoseconds(ts));
}

static inline unsigned long timespec_to_milliseconds(struct timespec const *ts)
{
    return nanoseconds_to_milliseconds(timespec_to_nanoseconds(ts));
}

void delay(unsigned long ms)
{
    usleep(milliseconds_to_microseconds(ms));
}

void delayMicroseconds(unsigned long us)
{
    usleep(us);
}

static inline uint64_t monotonic_timestamp_nanoseconds(void)
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return timespec_to_nanoseconds(&ts);
}

static uint64_t nanoseconds_elapsed(void)
{
    static uint64_t initial = monotonic_timestamp_nanoseconds();
    uint64_t timestamp = monotonic_timestamp_nanoseconds();

    return timestamp - initial;
}

class emulator
{
public:
    emulator() :
        screen_(nullptr)
    {
        screen_ = initscr();
        wclear(screen_);

        start_color();
        init_pair(0, COLOR_WHITE, COLOR_BLACK);
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);

        for(auto i = 0; i < 16; ++i)
        {
            mvwaddch(screen_, digital_pin_y + i, digital_pin_x + 0, 'D');
            mvwaddch(screen_, digital_pin_y + i, digital_pin_x + 1, (i < 10) ? '0' + i : 'A' + (i - 10));

            write(i, LOW);
        }
    }

    ~emulator()
    {
        endwin();
    }

    void update(void)
    {
        curs_set(0);
        wrefresh(screen_);
    }

    void write(int pin, int state)
    {
        switch(state)
        {
        case HIGH:
            wattrset(screen_, A_REVERSE | COLOR_PAIR(1));
            mvwaddch(screen_, pin + digital_pin_y, digital_pin_x + 4, ' ');
            wattrset(screen_, A_NORMAL | COLOR_PAIR(0));
            break;

        case LOW:
            wattrset(screen_, A_REVERSE | COLOR_PAIR(2));
            mvwaddch(screen_, pin + digital_pin_y, digital_pin_x + 4, ' ');
            wattrset(screen_, A_NORMAL | COLOR_PAIR(0));
            break;
        }
    }

    void read(int pin)
    {

    }

private:
    static constexpr int digital_pin_y = 4;
    static constexpr int digital_pin_x = 20;

    WINDOW *screen_;
};

/* External API */

static emulator e;
static bool running = true;

void pinMode(int pin, int mode)
{
    
}

void digitalWrite(int pin, int state)
{
    e.write(pin, state);
}

unsigned long micros(void)
{
    return static_cast<unsigned long>(nanoseconds_to_microseconds(nanoseconds_elapsed()));
}

unsigned long millis(void)
{
    return static_cast<unsigned long>(nanoseconds_to_milliseconds(nanoseconds_elapsed()));
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, [](int){ running = false; });

    setup();

    while(running)
    {
        loop();
        e.update();
    }

    return 0;
}
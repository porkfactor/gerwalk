#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include "arduino.h"

static constexpr uint64_t nanoseconds_per_second = 1000000000ULL;

void digitalWrite(int pin, int state)
{
}

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

unsigned long micros(void)
{
    return static_cast<unsigned long>(nanoseconds_to_microseconds(nanoseconds_elapsed()));
}

unsigned long millis(void)
{
    return static_cast<unsigned long>(nanoseconds_to_milliseconds(nanoseconds_elapsed()));
}

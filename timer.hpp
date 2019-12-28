#include "emulator.hpp"
#include "queue.h"

#define TIMER_REPEAT 0x1

class basic_timer
{
public:
    typedef unsigned long timestamp_type;
    typedef unsigned int identifier_type;
    typedef unsigned int duration_type;

protected:
    struct timeslot
    {
        timestamp_type start_timestamp;
        duration_type duration;
        unsigned long identifier;
        unsigned int flags;
        void *opaque;

        TAILQ_ENTRY(timeslot) next;
    };
};

template<size_t _Count>
class timer : public basic_timer
{
public:
    timer()
    {
        initialize();
    }

    unsigned long timestamp_useconds(void)
    {
        return micros();
    }

    bool repeat(identifier_type identifier, duration_type duration, void *opaque)
    {
        bool rv = false;
        struct timeslot *node = allocate_timeslot();

        if(node != nullptr)
        {
            node->start_timestamp = timestamp_useconds();
            node->duration = duration;
            node->identifier = identifier;
            node->opaque = opaque;
            node->flags |= TIMER_REPEAT;

            TAILQ_INSERT_TAIL(&active_list, node, next);

            rv = true;
        }

        return rv;
    }

    bool start(identifier_type identifier, duration_type duration, void *opaque)
    {
        bool rv = false;
        struct timeslot *node = allocate_timeslot();

        if(node != nullptr)
        {
            node->start_timestamp = timestamp_useconds();
            node->duration = duration;
            node->identifier = identifier;
            node->opaque = opaque;
            node->flags = 0;

            TAILQ_INSERT_TAIL(&active_list, node, next);

            rv = true;
        }

        return rv;
    }

    void stop(identifier_type identifier)
    {
        struct timeslot *timer = NULL;

        for(timer = TAILQ_FIRST(&active_list); timer != NULL;)
        {
            if(timer->identifier == identifier)
            {
                struct timeslot *tmp = timer;

                timer = TAILQ_NEXT(timer, next);

                TAILQ_REMOVE(&active_list, tmp, next);

                release_timeslot(tmp);
            }
            else
            {
                timer = TAILQ_NEXT(timer, next);
            }
        }
    }

    void update(void (*callback)(identifier_type, void *, void *), timestamp_type timestamp = micros())
    {
        while(!TAILQ_EMPTY(&active_list))
        {
            struct timeslot *node = TAILQ_FIRST(&active_list);

            if(timer_expired(node, timestamp))
            {
                TAILQ_REMOVE(&active_list, node, next);

                callback(node->identifier, node->opaque, nullptr);

                if(node->flags & TIMER_REPEAT)
                {
                    node->start_timestamp = timestamp;
                    TAILQ_INSERT_TAIL(&active_list, node, next);
                }
            }
            else
            {
                break;
            }
        }
    }

    void clear(void)
    {
        initialize();
    }

protected:
    bool timer_expired(struct timer::timeslot *node, timestamp_type timestamp) const
    {
        return (node->start_timestamp + node->duration) <= timestamp;
    }

private:

    struct timeslot *allocate_timeslot(void)
    {
        struct timeslot *node = TAILQ_FIRST(&free_list);

        if(node != nullptr)
        {
            TAILQ_REMOVE(&free_list, node, next);
        }

        return node;
    };

    void release_timeslot(struct timeslot *node)
    {
        if(node != nullptr)
        {
            TAILQ_INSERT_TAIL(&free_list, node, next);
        }
    }

    void initialize(void)
    {
        TAILQ_INIT(&active_list);
        TAILQ_INIT(&free_list);

        for(size_t i = 0U; i < (sizeof(slots) / sizeof(slots[0])); ++i)
        {
            release_timeslot(&slots[i]);
        }
    }

    struct timeslot slots[_Count];

    TAILQ_HEAD(, timeslot) active_list;
    TAILQ_HEAD(, timeslot) free_list;
};



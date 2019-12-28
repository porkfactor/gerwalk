#include "morse.h"

void morse_encode_character(
    char c,
    morse_callback_t emit,
    void *context)
{
    switch (c)
    {
    case 'a': case 'A':
        emit(MORSE_DOT, context);
        emit(MORSE_DASH, context);
        break;

    case 'b': case 'B':
        emit(MORSE_DASH, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DOT, context);
        break;

    case 'c': case 'C':
        emit(MORSE_DASH, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DASH, context);
        emit(MORSE_DOT, context);
        break;

    case 'd': case 'D':
        emit(MORSE_DASH, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DOT, context);
        break;

    case 'e': case 'E':
        emit(MORSE_DOT, context);
        break;

    case 'f': case 'F':
        emit(MORSE_DOT, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DASH, context);
        emit(MORSE_DOT, context);
        break;

    case 'g': case 'G':
        emit(MORSE_DASH, context);
        emit(MORSE_DASH, context);
        emit(MORSE_DOT, context);
        break;

    case 'h': case 'H':
        emit(MORSE_DOT, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DOT, context);
        break;

    case 'i': case 'I':
        emit(MORSE_DOT, context);
        emit(MORSE_DOT, context);
        break;

    case 'j': case 'J':
        emit(MORSE_DOT, context);
        emit(MORSE_DASH, context);
        emit(MORSE_DASH, context);
        emit(MORSE_DASH, context);
        break;

    case 'k': case 'K':
        emit(MORSE_DASH, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DASH, context);
        break;

    case 'l': case 'L':
        emit(MORSE_DOT, context);
        emit(MORSE_DASH, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DOT, context);
        break;

    case 'm': case 'M':
        emit(MORSE_DASH, context);
        emit(MORSE_DASH, context);
        break;

    case 'n': case 'N':
        emit(MORSE_DASH, context);
        emit(MORSE_DOT, context);
        break;

    case 'o': case 'O':
        emit(MORSE_DASH, context);
        emit(MORSE_DASH, context);
        emit(MORSE_DASH, context);
        break;

    case 'p': case 'P':
        emit(MORSE_DOT, context);
        emit(MORSE_DASH, context);
        emit(MORSE_DASH, context);
        emit(MORSE_DOT, context);
        break;

    case 'q': case 'Q':
        emit(MORSE_DASH, context);
        emit(MORSE_DASH, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DASH, context);
        break;

    case 'r': case 'R':
        emit(MORSE_DOT, context);
        emit(MORSE_DASH, context);
        emit(MORSE_DOT, context);
        break;

    case 's': case 'S':
        emit(MORSE_DOT, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DOT, context);
        break;

    case 't': case 'T':
        emit(MORSE_DASH, context);
        break;

    case 'u': case 'U':
        emit(MORSE_DOT, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DASH, context);
        break;

    case 'v': case 'V':
        emit(MORSE_DOT, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DASH, context);
        break;

    case 'w': case 'W':
        emit(MORSE_DOT, context);
        emit(MORSE_DASH, context);
        emit(MORSE_DASH, context);
        break;

    case 'x': case 'X':
        emit(MORSE_DASH, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DASH, context);
        break;

    case 'y': case 'Y':
        emit(MORSE_DASH, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DASH, context);
        emit(MORSE_DASH, context);
        break;

    case 'z': case 'Z':
        emit(MORSE_DASH, context);
        emit(MORSE_DASH, context);
        emit(MORSE_DOT, context);
        emit(MORSE_DOT, context);
        break;   
    }

    emit(MORSE_EOC, context);
}

void morse_encode_string(
    char const *string,
    morse_callback_t emit,
    void *context)
{
    char const *pos = string;

    while (*pos)
    {
        morse_encode_character(*pos, emit, context);

        pos++;
    }
}

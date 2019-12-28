#include "morse.h"

void morse_encode_character(
    char c,
    void (*emit)(enum morse_e morse, void *context),
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
    }
}

void morse_encode_string(
    char const *string,
    void (*emit)(enum morse_e, void *context),
    void *context)
{
    char const *pos = string;

    while (*pos)
    {
        morse_encode_character(*pos, emit, context);

        pos++;
    }
}

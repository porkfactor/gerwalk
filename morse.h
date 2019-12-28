#ifndef MORSE_H_
#define MORSE_H_

enum morse_e
{
    MORSE_EOM,                          ///< End of message
    MORSE_EOW,                          ///< End of word
    MORSE_EOC,                          ///< End of character
    MORSE_DOT,                          ///< Short mark
    MORSE_DASH,                         ///< long mark
};

typedef void (*morse_callback_t)(enum morse_e morse, void *context);

extern void morse_encode_character(char c, morse_callback_t emit, void *context);
extern void morse_encode_string(char const *s, morse_callback_t emit, void *context);

#endif

enum morse_e
{
  MORSE_DOT,
  MORSE_DASH,
};

extern void encode_morse(
    char const *,
    void (*emit)(enum morse_e, void *context),
    void *context);

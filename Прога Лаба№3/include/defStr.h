#ifndef STR
#define STR

struct Str {
    char *data;
    unsigned len;

    Str(unsigned strsize);
    ~Str();
};

#endif
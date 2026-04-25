#include <stdio.h>
#include <stdlib.h>

static constexpr char SLASH = '/';
static constexpr char STAR = '*';
static constexpr char CHAR_MARKER = '\'';
static constexpr char STRING_MARKER = '"';

enum ReadState {
    Normal,
    AlmostComment,
    InSingleLineComment,
    InMultilineComment,
    AlmostEndMultilineComment,
    InChar,
    InString,
};

static void handle_normal(const int c, enum ReadState* state) {
    if (c == SLASH) {
        *state = AlmostComment;
        return;
    }
    if (c == CHAR_MARKER) {
        *state = InChar;
    } else if (c == STRING_MARKER) {
        *state = InString;
    }
    putchar(c);
}

static bool handle_almost_comment(const int c, enum ReadState* state) {
    if (c == SLASH) {
        *state = InSingleLineComment;
    } else if (c == STAR) {
        *state = InMultilineComment;
    } else {
        *state = Normal;
        putchar(SLASH);
        if (ungetc(c, stdin) == EOF) {
            return false;
        }
    }
    return true;
}

static void handle_single_comment(const int c, enum ReadState* state) {
    if (c == '\n') {
        putchar(c);
        *state = Normal;
    }
}

static void handle_multi_comment(const int c, enum ReadState* state) {
    if (c == STAR) {
        *state = AlmostEndMultilineComment;
    }
}

static void handle_almost_end(const int c, enum ReadState* st) {
    if ('/' == c) {
        *st = Normal;
    } else if (c != STAR) {
        *st = InMultilineComment;
    }
}

static void handle_string_char(const int c, enum ReadState* state, bool* escaped) {
    putchar(c);

    if (*escaped) {
        *escaped = false;
        return;
    }

    if (c == '\\') {
        *escaped = true;
        return;
    }

    if ((*state == InChar && c == CHAR_MARKER) ||
        (*state == InString && c == STRING_MARKER)) {
        *state = Normal;
    }
}

int main(void) {
    int c = 0;
    bool escaped = false;
    enum ReadState state = Normal;

    while ((c = getchar()) != EOF) {
        switch (state) {
            case Normal:
                handle_normal(c, &state);
                break;

            case AlmostComment:
                if (!handle_almost_comment(c, &state)) {
                    return EXIT_FAILURE;
                }
                break;

            case InSingleLineComment:
                handle_single_comment(c, &state);
                break;

            case InMultilineComment:
                handle_multi_comment(c, &state);
                break;

            case AlmostEndMultilineComment:
                handle_almost_end(c, &state);
                break;

            case InChar:
            case InString:
                handle_string_char(c, &state, &escaped);
                break;
        }
    }

    if (state == AlmostComment) {
        putchar(SLASH);
    }

    return EXIT_SUCCESS;
}

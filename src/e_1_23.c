#include <stdio.h>
#include <stdlib.h>

constexpr char SLASH = '/';
constexpr char STAR = '*';
constexpr char CHAR_MARKER = '\'';
constexpr char STRING_MARKER = '"';

enum ReadState {
    Normal,
    AlmostComment,
    InSingleLineComment,
    InMultilineComment,
    InChar,
    InString,
};

// Exercise 1-23. Write a program to remove all comments from a C program.
// Don’t forget to handle quoted strings and character constants properly. C
// comments do not nest.
int main() {
    int cur_c, prev_c = 0;
    enum ReadState current_state = Normal;

    while ((cur_c = getchar()) != EOF) {
        switch (current_state) {
            case Normal:
                switch (cur_c) {
                    case SLASH:
                        current_state = AlmostComment;
                        continue;
                    case CHAR_MARKER:
                        current_state = InChar;
                        break;
                    case STRING_MARKER:
                        current_state = InString;
                        break;
                }

                putchar(cur_c);
                break;
            case AlmostComment:
                switch (cur_c) {
                    case SLASH:
                        current_state = InSingleLineComment;
                        break;
                    case STAR:
                        current_state = InMultilineComment;
                        break;
                    default:
                        current_state = Normal;

                        putchar(SLASH);
                        putchar(cur_c);
                }
                break;
            case InSingleLineComment:
                if (cur_c == '\n') {
                    putchar(cur_c);
                    current_state = Normal;
                };
                break;
            case InMultilineComment:
                if (cur_c == SLASH && prev_c == STAR) {
                    current_state = Normal;
                }
                break;
            case InChar:
                putchar(cur_c);
                if (cur_c == CHAR_MARKER && prev_c != '\\')
                    current_state = Normal;
                break;
            case InString:
                putchar(cur_c);
                if (cur_c == STRING_MARKER && prev_c != '\\')
                    current_state = Normal;
                break;
        }

        prev_c = cur_c;
    }

    if (current_state == AlmostComment) putchar(SLASH);

    return EXIT_SUCCESS;
}

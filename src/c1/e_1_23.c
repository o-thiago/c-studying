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
    AlmostEndMultilineComment,
    InChar,
    InString,
};

// Exercise 1-23. Write a program to remove all comments from a C program.
// Don’t forget to handle quoted strings and character constants properly. C
// comments do not nest.
int main() {
    int cur_c;
    bool escaped = false;
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
                        ungetc(cur_c, stdin);

                        continue;
                }
                break;
            case InSingleLineComment:
                if (cur_c == '\n') {
                    putchar(cur_c);
                    current_state = Normal;
                };
                break;
            case InMultilineComment:
                if (cur_c == STAR) {
                    current_state = AlmostEndMultilineComment;
                }
                break;
            case AlmostEndMultilineComment:
                if (cur_c == '/')
                    current_state = Normal;
                else if (cur_c != '*')
                    current_state = InMultilineComment;
            case InChar:
            case InString:
                putchar(cur_c);
                if (escaped)
                    escaped = false;
                else if (cur_c == '\\')
                    escaped = true;
                else if ((current_state == InChar && cur_c == CHAR_MARKER) ||
                         (current_state == InString && cur_c == STRING_MARKER))
                    current_state = Normal;
                break;
        }
    }

    if (current_state == AlmostComment) putchar(SLASH);

    return EXIT_SUCCESS;
}

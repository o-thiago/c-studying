#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

constexpr int STACK_SIZE = 1024;

typedef enum {
    NORMAL,
    IN_STRING,
    IN_CHAR,
    IN_LINE_COMMENT,
    IN_BLOCK_COMMENT
} ParserState;

typedef enum {
    TOK_LPAREN = '(',
    TOK_RPAREN = ')',
    TOK_LBRACE = '{',
    TOK_RBRACE = '}',
    TOK_LBRACKET = '[',
    TOK_RBRACKET = ']',
    TOK_DQUOTE = '"',
    TOK_SQUOTE = '\'',
    TOK_SLASH = '/',
    TOK_STAR = '*',
    TOK_NEWLINE = '\n',
    TOK_ESCAPE = '\\'
} TokenType;

bool is_match(TokenType open, TokenType close) {
    return (open == TOK_LPAREN && close == TOK_RPAREN) ||
           (open == TOK_LBRACE && close == TOK_RBRACE) ||
           (open == TOK_LBRACKET && close == TOK_RBRACKET);
}

int main() {
    int c, prev = 0;
    ParserState state = NORMAL;

    TokenType stack[STACK_SIZE];
    int top = -1;

    while ((c = getchar()) != EOF) {
        switch (state) {
            case NORMAL:
                switch (c) {
                    case TOK_DQUOTE:
                        state = IN_STRING;
                        break;
                    case TOK_SQUOTE:
                        state = IN_CHAR;
                        break;
                    case TOK_SLASH:
                        if (prev == TOK_SLASH) state = IN_LINE_COMMENT;
                        break;
                    case TOK_STAR:
                        if (prev == TOK_SLASH) state = IN_BLOCK_COMMENT;
                        break;
                    case TOK_LPAREN:
                    case TOK_LBRACE:
                    case TOK_LBRACKET:
                        stack[++top] = (TokenType)c;
                        break;
                    case TOK_RPAREN:
                    case TOK_RBRACE:
                    case TOK_RBRACKET:
                        if (top == -1 ||
                            !is_match(stack[top--], (TokenType)c)) {
                            printf("Error: Mismatched or unexpected '%c'\n", c);
                            return EXIT_FAILURE;
                        }
                        break;
                }
                break;
            case IN_STRING:
                if (c == TOK_DQUOTE && prev != TOK_ESCAPE) state = NORMAL;
                break;
            case IN_CHAR:
                if (c == TOK_SQUOTE && prev != TOK_ESCAPE) state = NORMAL;
                break;
            case IN_BLOCK_COMMENT:
                if (prev == TOK_STAR && c == TOK_SLASH) state = NORMAL;
                break;
            case IN_LINE_COMMENT:
                if (c == TOK_NEWLINE) state = NORMAL;
                break;
        }

        prev = (c == TOK_ESCAPE && prev == TOK_ESCAPE) ? 0 : c;
    }

    if (top != -1) {
        printf("Error: Unclosed '%c'\n", stack[top]);
        return EXIT_FAILURE;
    }

    if (state != NORMAL && state != IN_LINE_COMMENT) {
        printf("Error: Unexpected end of file.\n");
        return EXIT_FAILURE;
    }

    printf("Syntax check passed.\n");
    return EXIT_SUCCESS;
}

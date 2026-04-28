#include <stdio.h>
#include <stdlib.h>

static constexpr int STACK_SIZE = 1024;

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

static bool is_match(const TokenType open, const TokenType close)
{
	return ((open == TOK_LPAREN && close == TOK_RPAREN) ||
			(open == TOK_LBRACE && close == TOK_RBRACE) ||
			(open == TOK_LBRACKET && close == TOK_RBRACKET)) != 0;
}

static bool handle_mismatch(const char c)
{
	printf("Error: Mismatched or unexpected '%c'\n", c);
	return false;
}

static bool handle_normal(const int c, const int prev, ParserState *st,
						  TokenType *stack, int *top)
{
	switch (c) {
	case TOK_DQUOTE:
		*st = IN_STRING;
		break;
	case TOK_SQUOTE:
		*st = IN_CHAR;
		break;
	case TOK_SLASH:
		if (prev == TOK_SLASH) {
			*st = IN_LINE_COMMENT;
		}
		break;
	case TOK_STAR:
		if (prev == TOK_SLASH) {
			*st = IN_BLOCK_COMMENT;
		}
		break;
	case TOK_LPAREN:
	case TOK_LBRACE:
	case TOK_LBRACKET:
		if (*top + 1 >= STACK_SIZE) {
			return false;
		}
		stack[++(*top)] = (TokenType)c;
		break;
	case TOK_RPAREN:
	case TOK_RBRACE:
	case TOK_RBRACKET:
		if (*top == -1) {
			return handle_mismatch((char)c);
		};

		if (!is_match(stack[(*top)--], (TokenType)c)) {
			return handle_mismatch((char)c);
		}

		break;
	default:
		return true;
	}

	return true;
}

static void handle_string(const int c, const int prev, ParserState *st)
{
	if (c == TOK_DQUOTE && prev != TOK_ESCAPE) {
		*st = NORMAL;
	}
}

static void handle_char(const int c, const int prev, ParserState *st)
{
	if (c == TOK_SQUOTE && prev != TOK_ESCAPE) {
		*st = NORMAL;
	}
}

static void handle_block_comment(const int c, const int prev, ParserState *st)
{
	if (prev == TOK_STAR && c == TOK_SLASH) {
		*st = NORMAL;
	}
}

static void handle_line_comment(const int c, ParserState *st)
{
	if (c == TOK_NEWLINE) {
		*st = NORMAL;
	}
}

int main(void)
{
	int c = 0;
	int prev = 0;
	ParserState st = NORMAL;

	TokenType stack[STACK_SIZE];
	int top = -1;

	while ((c = getchar()) != EOF) {
		switch (st) {
		case NORMAL:
			if (!handle_normal(c, prev, &st, stack, &top)) {
				return EXIT_FAILURE;
			}
			break;
		case IN_STRING:
			handle_string(c, prev, &st);
			break;
		case IN_CHAR:
			handle_char(c, prev, &st);
			break;
		case IN_BLOCK_COMMENT:
			handle_block_comment(c, prev, &st);
			break;
		case IN_LINE_COMMENT:
			handle_line_comment(c, &st);
			break;
		}
		prev = (c == TOK_ESCAPE && prev == TOK_ESCAPE) ? 0 : c;
	}

	if (top != -1) {
		printf("Error: Unclosed '%c'\n", stack[top]);
		return EXIT_FAILURE;
	}

	if (st != NORMAL && st != IN_LINE_COMMENT) {
		printf("Error: Unexpected end of file.\n");
		return EXIT_FAILURE;
	}

	printf("Syntax check passed.\n");
	return EXIT_SUCCESS;
}

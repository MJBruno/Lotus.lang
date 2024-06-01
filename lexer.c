#include "lexer.h"

Lexer create_lexer(const char *source) {
    Lexer lexer;
    lexer.source = source;
    lexer.position = 0;
    lexer.current_token.type = TOKEN_INVALID;
    lexer.current_token.value = NULL;
    return lexer;
}

static char peek(Lexer *lexer) {
    return lexer->source[lexer->position];
}

static char advance(Lexer *lexer) {
    return lexer->source[lexer->position++];
}

static void skip_whitespace(Lexer *lexer) {
    while (isspace(peek(lexer))) {
        advance(lexer);
    }
}

static Token create_token(TokenType type, const char *value) {
    Token token;
    token.type = type;
    token.value = strdup(value);
    return token;
}

Token get_next_token(Lexer *lexer) {
    skip_whitespace(lexer);

    char current = peek(lexer);
    if (isdigit(current)) {
        char buffer[64];
        int length = 0;
        while (isdigit(peek(lexer))) {
            buffer[length++] = advance(lexer);
        }
        buffer[length] = '\0';
        return create_token(TOKEN_NUMBER, buffer);
    }

    if (isalpha(current)) {
        char buffer[64];
        int length = 0;
        while (isalnum(peek(lexer)) || peek(lexer) == '_') {
            buffer[length++] = advance(lexer);
        }
        buffer[length] = '\0';

        if (strcmp(buffer, "print") == 0) {
            return create_token(TOKEN_PRINT, buffer);
        }

        return create_token(TOKEN_IDENTIFIER, buffer);
    }

    switch (current) {
        case '+': advance(lexer); return create_token(TOKEN_PLUS, "+");
        case '-': advance(lexer); return create_token(TOKEN_MINUS, "-");
        case '*': advance(lexer); return create_token(TOKEN_MULT, "*");
        case '/': advance(lexer); return create_token(TOKEN_DIV, "/");
        case '=': advance(lexer); return create_token(TOKEN_ASSIGN, "=");
        case ';': advance(lexer); return create_token(TOKEN_SEMICOLON, ";");
        case '(': advance(lexer); return create_token(TOKEN_LPAREN, "(");
        case ')': advance(lexer); return create_token(TOKEN_RPAREN, ")");
        case '\0': return create_token(TOKEN_END, "");
        default: advance(lexer); return create_token(TOKEN_INVALID, "");
    }
}

void free_token(Token token) {
    if (token.value) {
        free(token.value);
    }
}

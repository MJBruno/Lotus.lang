#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_ASSIGN,
    TOKEN_SEMICOLON,
    TOKEN_PRINT,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_END,
    TOKEN_INVALID
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

typedef struct {
    const char *source;
    size_t position;
    Token current_token;
} Lexer;

Lexer create_lexer(const char *source);
Token get_next_token(Lexer *lexer);
void free_token(Token token);

#endif // LEXER_H

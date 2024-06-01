#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum {
    NODE_NUMBER,
    NODE_IDENTIFIER,
    NODE_BINARY_OP,
    NODE_ASSIGNMENT,
    NODE_PRINT
} NodeType;

typedef struct ASTNode {
    NodeType type;
    struct ASTNode *left;
    struct ASTNode *right;
    char *value;
} ASTNode;

ASTNode* parse(Lexer *lexer);
void free_ast(ASTNode *node);

#endif // PARSER_H

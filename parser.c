#include "parser.h"

static ASTNode* parse_expression(Lexer *lexer);
static ASTNode* parse_term(Lexer *lexer);
static ASTNode* parse_factor(Lexer *lexer);

static void advance(Lexer *lexer) {
    lexer->current_token = get_next_token(lexer);
}

static ASTNode* create_node(NodeType type, const char *value) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    node->value = value ? strdup(value) : NULL;
    return node;
}

ASTNode* parse(Lexer *lexer) {
    advance(lexer);
    return parse_expression(lexer);
}

static ASTNode* parse_expression(Lexer *lexer) {
    ASTNode *node = parse_term(lexer);

    while (lexer->current_token.type == TOKEN_PLUS || lexer->current_token.type == TOKEN_MINUS) {
        TokenType op = lexer->current_token.type;
        advance(lexer);
        ASTNode *right = parse_term(lexer);
        ASTNode *new_node = create_node(NODE_BINARY_OP, op == TOKEN_PLUS ? "+" : "-");
        new_node->left = node;
        new_node->right = right;
        node = new_node;
    }

    return node;
}

static ASTNode* parse_term(Lexer *lexer) {
    ASTNode *node = parse_factor(lexer);

    while (lexer->current_token.type == TOKEN_MULT || lexer->current_token.type == TOKEN_DIV) {
        TokenType op = lexer->current_token.type;
        advance(lexer);
        ASTNode *right = parse_factor(lexer);
        ASTNode *new_node = create_node(NODE_BINARY_OP, op == TOKEN_MULT ? "*" : "/");
        new_node->left = node;
        new_node->right = right;
        node = new_node;
    }

    return node;
}

static ASTNode* parse_factor(Lexer *lexer) {
    Token token = lexer->current_token;
    if (token.type == TOKEN_NUMBER) {
        advance(lexer);
        return create_node(NODE_NUMBER, token.value);
    } else if (token.type == TOKEN_IDENTIFIER) {
        advance(lexer);
        return create_node(NODE_IDENTIFIER, token.value);
    } else if (token.type == TOKEN_LPAREN) {
        advance(lexer);
        ASTNode *node = parse_expression(lexer);
        if (lexer->current_token.type != TOKEN_RPAREN) {
            printf("Error: expected )\n");
            exit(1);
        }
        advance(lexer);
        return node;
    } else {
        printf("Error: unexpected token %d\n", token.type);
        exit(1);
    }
}

void free_ast(ASTNode *node) {
    if (node) {
        if (node->left) free_ast(node->left);
        if (node->right) free_ast(node->right);
        if (node->value) free(node->value);
        free(node);
    }
}

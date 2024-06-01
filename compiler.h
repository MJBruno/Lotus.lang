#ifndef COMPILER_H
#define COMPILER_H

#include "parser.h"

typedef enum {
    OP_PUSH,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_STORE,
    OP_LOAD,
    OP_PRINT,
    OP_HALT
} OpCode;

typedef struct {
    OpCode *code;
    int *constants;
    char **identifiers;
    size_t code_size;
    size_t code_capacity;
    size_t const_size;
    size_t const_capacity;
    size_t ident_size;
    size_t ident_capacity;
} ByteCode;

ByteCode compile(ASTNode *root);
void free_bytecode(ByteCode bytecode);

#endif // COMPILER_H

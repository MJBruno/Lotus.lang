#include "compiler.h"

static void emit(ByteCode *bc, OpCode opcode) {
    if (bc->code_size >= bc->code_capacity) {
        bc->code_capacity *= 2;
        bc->code = realloc(bc->code, bc->code_capacity * sizeof(OpCode));
    }
    bc->code[bc->code_size++] = opcode;
}

static int add_constant(ByteCode *bc, int value) {
    if (bc->const_size >= bc->const_capacity) {
        bc->const_capacity *= 2;
        bc->constants = realloc(bc->constants, bc->const_capacity * sizeof(int));
    }
    bc->constants[bc->const_size] = value;
    return bc->const_size++;
}

static int add_identifier(ByteCode *bc, const char *name) {
    for (size_t i = 0; i < bc->ident_size; i++) {
        if (strcmp(bc->identifiers[i], name) == 0) {
            return i;
        }
    }
    if (bc->ident_size >= bc->ident_capacity) {
        bc->ident_capacity *= 2;
        bc->identifiers = realloc(bc->identifiers, bc->ident_capacity * sizeof(char*));
    }
    bc->identifiers[bc->ident_size] = strdup(name);
    return bc->ident_size++;
}

static void compile_node(ByteCode *bc, ASTNode *node) {
    switch (node->type) {
        case NODE_NUMBER: {
            int index = add_constant(bc, atoi(node->value));
            emit(bc, OP_PUSH);
            emit(bc, index);
            break;
        }
        case NODE_IDENTIFIER: {
            int index = add_identifier(bc, node->value);
            emit(bc, OP_LOAD);
            emit(bc, index);
            break;
        }
        case NODE_BINARY_OP: {
            compile_node(bc, node->left);
            compile_node(bc, node->right);
            if (strcmp(node->value, "+") == 0) emit(bc, OP_ADD);
            else if (strcmp(node->value, "-") == 0) emit(bc, OP_SUB);
            else if (strcmp(node->value, "*") == 0) emit(bc, OP_MUL);
            else if (strcmp(node->value, "/") == 0) emit(bc, OP_DIV);
            break;
        }
        case NODE_ASSIGNMENT: {
            int index = add_identifier(bc, node->left->value);
            compile_node(bc, node->right);
            emit(bc, OP_STORE);
            emit(bc, index);
            break;
        }
        case NODE_PRINT: {
            compile_node(bc, node->left);
            emit(bc, OP_PRINT);
            break;
        }
        default:
            printf("Error: unknown node type %d\n", node->type);
            exit(1);
    }
}

ByteCode compile(ASTNode *root) {
    ByteCode bytecode;
    bytecode.code = malloc(64 * sizeof(OpCode));
    bytecode.constants = malloc(64 * sizeof(int));
    bytecode.identifiers = malloc(64 * sizeof(char*));
    bytecode.code_size = 0;
    bytecode.code_capacity = 64;
    bytecode.const_size = 0;
    bytecode.const_capacity = 64;
    bytecode.ident_size = 0;
    bytecode.ident_capacity = 64;

    compile_node(&bytecode, root);
    emit(&bytecode, OP_HALT);

    return bytecode;
}

void free_bytecode(ByteCode bytecode) {
    free(bytecode.code);
    free(bytecode.constants);
    for (size_t i = 0; i < bytecode.ident_size; i++) {
        free(bytecode.identifiers[i]);
    }
    free(bytecode.identifiers);
}

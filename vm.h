#ifndef VM_H
#define VM_H

#include "compiler.h"

typedef struct {
    int *stack;
    int sp;
    int *variables;
    size_t var_size;
    size_t var_capacity;
} VM;

VM create_vm();
void run(VM *vm, ByteCode *bytecode);
void free_vm(VM *vm);

#endif // VM_H

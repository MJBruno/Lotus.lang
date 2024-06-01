#include "vm.h"

VM create_vm() {
    VM vm;
    vm.stack = malloc(64 * sizeof(int));
    vm.sp = -1;
    vm.variables = malloc(64 * sizeof(int));
    vm.var_size = 0;
    vm.var_capacity = 64;
    return vm;
}

void free_vm(VM *vm) {
    free(vm->stack);
    free(vm->variables);
}

static void push(VM *vm, int value) {
    vm->stack[++vm->sp] = value;
}

static int pop(VM *vm) {
    return vm->stack[vm->sp--];
}

void run(VM *vm, ByteCode *bytecode) {
    size_t ip = 0;
    while (1) {
        OpCode opcode = bytecode->code[ip++];
        switch (opcode) {
            case OP_PUSH: {
                int const_index = bytecode->code[ip++];
                push(vm, bytecode->constants[const_index]);
                break;
            }
            case OP_ADD: {
                int b = pop(vm);
                int a = pop(vm);
                push(vm, a + b);
                break;
            }
            case OP_SUB: {
                int b = pop(vm);
                int a = pop(vm);
                push(vm, a - b);
                break;
            }
            case OP_MUL: {
                int b = pop(vm);
                int a = pop(vm);
                push(vm, a * b);
                break;
            }
            case OP_DIV: {
                int b = pop(vm);
                int a = pop(vm);
                push(vm, a / b);
                break;
            }
            case OP_STORE: {
                size_t var_index = bytecode->code[ip++];
                if (var_index >= vm->var_size) {
                    vm->var_size = var_index + 1;
                }
                vm->variables[var_index] = pop(vm);
                break;
            }
            case OP_LOAD: {
                int var_index = bytecode->code[ip++];
                push(vm, vm->variables[var_index]);
                break;
            }
            case OP_PRINT: {
                int value = pop(vm);
                printf("%d\n", value);
                break;
            }
            case OP_HALT:
                return;
            default:
                printf("Error: unknown opcode %d\n", opcode);
                exit(1);
        }
    }
}

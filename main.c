#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include "compiler.h"
#include "vm.h"

int main() {
    const char *source_code = "print(2+2);";

    Lexer lexer = create_lexer(source_code);
    ASTNode *root = parse(&lexer);

    ByteCode bytecode = compile(root);

    VM vm = create_vm();
    run(&vm, &bytecode);

    free_ast(root);
    free_bytecode(bytecode);
    free_vm(&vm);
    
    return 0;
}

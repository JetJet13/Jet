//
// Created by Johny Georges on 2024-06-15.
//

#ifndef JETLANG_BOOL_LITERAL_IR_STRATEGY_H
#define JETLANG_BOOL_LITERAL_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../../core/ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"

class BoolLiteralIRStrategy {
public:
    llvm::Value* generate(ASTBooleanLiteralNode* node, std::unique_ptr<llvm::LLVMContext>*);
};

#endif //JETLANG_BOOL_LITERAL_IR_STRATEGY_H

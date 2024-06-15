//
// Created by Johny Georges on 2024-06-15.
//

#ifndef JETLANG_INT_LITERAL_IR_STRATEGY_H
#define JETLANG_INT_LITERAL_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../../core/ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"

class IntLiteralIRStrategy {
public:
    llvm::Value* generate(ASTIntLiteralNode* node, std::unique_ptr<llvm::LLVMContext>* context);
};

#endif //JETLANG_INT_LITERAL_IR_STRATEGY_H

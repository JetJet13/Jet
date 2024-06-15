//
// Created by Johny Georges on 2024-06-15.
//

#ifndef JETLANG_FLOAT_LITERAL_IR_STRATEGY_H
#define JETLANG_FLOAT_LITERAL_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "../../../../../core/ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"
#include "../../../../../core/ast/ast-nodes/ast-literal-nodes/ast-float-literal-node.h"

class FloatLiteralIRStrategy {
public:
    llvm::Value* generate(ASTFloatLiteralNode* node, std::unique_ptr<llvm::LLVMContext>*);
};

#endif //JETLANG_FLOAT_LITERAL_IR_STRATEGY_H

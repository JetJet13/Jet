//
// Created by Johny Georges on 2024-06-26.
//

#ifndef JETLANG_IDENTIFIER_IR_STRATEGY_H
#define JETLANG_IDENTIFIER_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../ir-lookup-table/ir-lookup-table.h"
#include "../../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"


class IdentifierIRStrategy {
public:
    llvm::Value* generate(ASTIdentifierExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context);
    llvm::Value* generate(ASTIdentifierNode* node, std::unique_ptr<llvm::LLVMContext>* context);
};

#endif //JETLANG_IDENTIFIER_IR_STRATEGY_H

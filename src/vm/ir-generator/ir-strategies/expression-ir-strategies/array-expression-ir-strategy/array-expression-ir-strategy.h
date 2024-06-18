//
// Created by Johny Georges on 2024-06-17.
//

#ifndef JETLANG_ARRAY_EXPRESSION_IR_STRATEGY_H
#define JETLANG_ARRAY_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-array-expression-node.h"

class ArrayExpressionIRStrategy {
private:
    llvm::Type* generateArrayType(ASTArrayExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope);
public:
    llvm::Value* generate(ASTArrayExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope);
};

#endif //JETLANG_ARRAY_EXPRESSION_IR_STRATEGY_H

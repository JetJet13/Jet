//
// Created by Johny Georges on 2024-06-25.
//

#ifndef JETLANG_TUPLE_EXPRESSION_IR_STRATEGY_H
#define JETLANG_TUPLE_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-expression-node.h"

class TupleExpressionIRStrategy {
private:
    llvm::StructType* generateTupleType(ASTTupleExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope);
public:
    llvm::Value* generate(ASTTupleExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope);
};

#endif //JETLANG_TUPLE_EXPRESSION_IR_STRATEGY_H

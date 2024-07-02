//
// Created by Johny Georges on 2024-06-25.
//

#ifndef JETLANG_TUPLE_EXPRESSION_IR_STRATEGY_H
#define JETLANG_TUPLE_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-tuple-expression-node.h"

class TupleExpressionIRStrategy {
public:
    IRTupleExpressionNode* generate(ASTTupleExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope);
};

#endif //JETLANG_TUPLE_EXPRESSION_IR_STRATEGY_H

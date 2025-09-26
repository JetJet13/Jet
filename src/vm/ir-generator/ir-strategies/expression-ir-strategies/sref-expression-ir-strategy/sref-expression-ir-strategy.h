//
// Created by Johny Georges on 2025-03-29.
//

#ifndef JETLANG_SREF_EXPRESSION_IR_STRATEGY_H
#define JETLANG_SREF_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-sref-expression-node.h"

class SrefExpressionIRStrategy {
private:
    IRInstructionNode* generateAllocation(ASTSrefExpressionNode* node, IRRefType* irType, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation);
public:
    IRExpressionNode* generate(ASTSrefExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
};

#endif //JETLANG_SREF_EXPRESSION_IR_STRATEGY_H

//
// Created by Johny Georges on 2025-02-10.
//

#ifndef JETLANG_DREF_EXPRESSION_IR_STRATEGY_H
#define JETLANG_DREF_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-dref-expression-node.h"

class DrefExpressionIRStrategy {
private:
    IRInstructionNode* generateAllocation(ASTDrefExpressionNode* node, IRType* irType, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation);
public:
    IRExpressionNode* generate(ASTDrefExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
};

#endif //JETLANG_DREF_EXPRESSION_IR_STRATEGY_H

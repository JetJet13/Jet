//
// Created by Johny Georges on 2025-02-10.
//

#ifndef JETLANG_REF_EXPRESSION_IR_STRATEGY_H
#define JETLANG_REF_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-ref-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-ref-expression-node.h"

class RefExpressionIRStrategy {
private:
    IRInstructionNode* generateAllocation(ASTRefExpressionNode* node, IRRefType* irType, IRGenerator* irGenerator, IRContext* irContext, IROperationType irOperationType);
public:
    IRRefExpressionNode* generate(ASTRefExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType);
};


#endif //JETLANG_REF_EXPRESSION_IR_STRATEGY_H

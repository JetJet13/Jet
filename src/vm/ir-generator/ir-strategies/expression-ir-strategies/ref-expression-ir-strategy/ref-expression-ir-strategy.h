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
    IRInstructionNode* generateAllocation(std::shared_ptr<ASTRefExpressionNode> node, IRRefType* irType, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation);
public:
    IRRefExpressionNode* generate(std::shared_ptr<ASTRefExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
};


#endif //JETLANG_REF_EXPRESSION_IR_STRATEGY_H

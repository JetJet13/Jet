//
// Created by Johny Georges on 2024-06-26.
//

#ifndef JETLANG_IDENTIFIER_EXPRESSION_IR_STRATEGY_H
#define JETLANG_IDENTIFIER_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-aggregate-identifier-expression-node.h"

class IdentifierExpressionIRStrategy {
private:
    IRAggregateIdentifierExpressionNode* generateForAggregate(ASTIdentifierExpressionNode* node, IRInstructionNode* allocation, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType);
    IRAggregateIdentifierExpressionNode* generateForGlobalAggregate(ASTIdentifierExpressionNode* node, IRInstructionNode* allocation, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType);
public:
    IRExpressionNode* generate(ASTIdentifierExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType);
};

#endif //JETLANG_IDENTIFIER_EXPRESSION_IR_STRATEGY_H

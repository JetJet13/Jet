//
// Created by Johny Georges on 2025-06-09.
//

#ifndef JETLANG_CONCAT_EXPRESSION_IR_STRATEGY_H
#define JETLANG_CONCAT_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-concat-expression-node.h"
#include "../../../ir-generator.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-concat-expression-node.h"

class ConcatExpressionIRStrategy {
public:
    IRConcatExpressionNode* generate(std::shared_ptr<ASTConcatExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
};

#endif //JETLANG_CONCAT_EXPRESSION_IR_STRATEGY_H

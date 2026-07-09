//
// Created by Johny Georges on 2026-06-15.
//

#ifndef JETLANG_THIS_EXPRESSION_IR_STRATEGY_H
#define JETLANG_THIS_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-this-expression-node.h"

class ThisExpressionIRStrategy {
public:
    std::shared_ptr<IRExpressionNode> generate(std::shared_ptr<ASTThisExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_THIS_EXPRESSION_IR_STRATEGY_H

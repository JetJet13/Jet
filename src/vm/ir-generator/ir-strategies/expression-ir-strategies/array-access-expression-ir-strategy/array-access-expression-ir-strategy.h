//
// Created by Johny Georges on 2024-06-21.
//

#ifndef JETLANG_ARRAY_ACCESS_EXPRESSION_IR_STRATEGY_H
#define JETLANG_ARRAY_ACCESS_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-array-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-access-expression-node.h"


class ArrayAccessExpressionIRStrategy {
public:
    std::shared_ptr<IRArrayAccessExpressionNode> generate(std::shared_ptr<ASTArrayAccessExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_ARRAY_ACCESS_EXPRESSION_IR_STRATEGY_H

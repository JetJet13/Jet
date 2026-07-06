//
// Created by Johny Georges on 2024-06-25.
//

#ifndef JETLANG_UNARY_EXPRESSION_IR_STRATEGY_H
#define JETLANG_UNARY_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-logical-expression-node.h"
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-operator-nodes/ast-unary-operators/ast-unary-operator-node.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-unary-expression-nodes/ir-unary-expression-node.h"

class UnaryExpressionIRStrategy {
public:
    std::shared_ptr<IRUnaryExpressionNode> generate(std::shared_ptr<ASTUnaryExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
};

#endif //JETLANG_UNARY_EXPRESSION_IR_STRATEGY_H

//
// Created by Johny Georges on 2024-11-25.
//

#ifndef JETLANG_EXPRESSION_STATEMENT_IR_STRATEGY_H
#define JETLANG_EXPRESSION_STATEMENT_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-declaration-node.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-expression-statement-node.h"

class ExpressionStatementIRStrategy {
public:
    std::shared_ptr<IRStatementNode> generate(std::shared_ptr<ASTExpressionStatementNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext);
};

#endif //JETLANG_EXPRESSION_STATEMENT_IR_STRATEGY_H

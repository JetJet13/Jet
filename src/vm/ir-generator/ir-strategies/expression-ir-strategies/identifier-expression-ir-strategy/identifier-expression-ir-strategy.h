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
public:
    std::shared_ptr<IRExpressionNode> generate(std::shared_ptr<ASTIdentifierExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_IDENTIFIER_EXPRESSION_IR_STRATEGY_H

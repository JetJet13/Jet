//
// Created by Johny Georges on 2026-07-13.
//

#ifndef JETLANG_SHARE_EXPRESSION_IR_STRATEGY_H
#define JETLANG_SHARE_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-share-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-share-expression-node.h"

class ShareExpressionIRStrategy {
public:
    std::shared_ptr<IRShareExpressionNode> generate(std::shared_ptr<ASTShareExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_SHARE_EXPRESSION_IR_STRATEGY_H

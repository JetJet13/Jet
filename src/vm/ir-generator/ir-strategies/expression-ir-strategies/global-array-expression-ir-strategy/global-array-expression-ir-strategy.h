//
// Created by Johny Georges on 2025-02-24.
//

#ifndef JETLANG_GLOBAL_ARRAY_EXPRESSION_IR_STRATEGY_H
#define JETLANG_GLOBAL_ARRAY_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-array-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-global-array-expression-node.h"

class GlobalArrayExpressionIRStrategy {
public:
    IRGlobalArrayExpressionNode* generate(ASTArrayExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType);
};

#endif //JETLANG_GLOBAL_ARRAY_EXPRESSION_IR_STRATEGY_H

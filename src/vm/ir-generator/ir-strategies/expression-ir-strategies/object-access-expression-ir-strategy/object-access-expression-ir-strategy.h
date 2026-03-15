//
// Created by Johny Georges on 2024-07-16.
//

#ifndef JETLANG_OBJECT_ACCESS_EXPRESSION_IR_STRATEGY_H
#define JETLANG_OBJECT_ACCESS_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-static-property-access-expression-node.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-object-access-expression-node.h"

class ObjectAccessExpressionIRStrategy {
public:
    IRExpressionNode* generate(ASTObjectAccessExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
};

#endif //JETLANG_OBJECT_ACCESS_EXPRESSION_IR_STRATEGY_H

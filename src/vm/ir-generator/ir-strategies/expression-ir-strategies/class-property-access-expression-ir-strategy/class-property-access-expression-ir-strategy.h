//
// Created by Johny Georges on 2024-12-14.
//

#ifndef JETLANG_CLASS_PROPERTY_ACCESS_EXPRESSION_IR_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_ACCESS_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-class-property-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-property-access-expression-node.h"

class ClassPropertyAccessExpressionIRStrategy {
public:
    std::shared_ptr<IRClassPropertyAccessExpressionNode> generate(std::shared_ptr<ASTClassPropertyAccessExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_CLASS_PROPERTY_ACCESS_EXPRESSION_IR_STRATEGY_H

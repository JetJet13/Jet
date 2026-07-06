//
// Created by Johny Georges on 2026-03-27.
//

#ifndef JETLANG_MODULE_ACCESS_EXPRESSION_IR_STRATEGY_H
#define JETLANG_MODULE_ACCESS_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-module-access-expression-node.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-module-access-expression-node.h"

class ModuleAccessExpressionIRStrategy {
public:
    std::shared_ptr<IRExpressionNode> generate(std::shared_ptr<ASTModuleAccessExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
};

#endif //JETLANG_MODULE_ACCESS_EXPRESSION_IR_STRATEGY_H

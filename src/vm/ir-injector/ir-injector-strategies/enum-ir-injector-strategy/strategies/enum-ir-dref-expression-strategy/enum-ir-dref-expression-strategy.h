//
// Created by Johny Georges on 2026-05-20.
//

#ifndef JETLANG_ENUM_IR_DREF_EXPRESSION_STRATEGY_H
#define JETLANG_ENUM_IR_DREF_EXPRESSION_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-dref-expression-node.h"

class EnumIRDrefExpressionInjectorStrategy {
public:
    llvm::Value* inject(std::shared_ptr<IRDrefExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_ENUM_IR_DREF_EXPRESSION_STRATEGY_H

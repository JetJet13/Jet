//
// Created by Johny Georges on 2025-02-18.
//

#ifndef JETLANG_ENUM_IR_INJECTOR_STRATEGY_H
#define JETLANG_ENUM_IR_INJECTOR_STRATEGY_H

#include "../ir-injector-strategy.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"


class EnumIRInjectorStrategy : public IRInjectorStrategy {
    using IRInjectorStrategy::IRInjectorStrategy;
public:
    llvm::Value* inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) override;
};

#endif //JETLANG_ENUM_IR_INJECTOR_STRATEGY_H

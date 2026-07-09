//
// Created by Johny Georges on 2025-03-08.
//

#ifndef JETLANG_LITERAL_IR_LOGICAL_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_LITERAL_IR_LOGICAL_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-logical-expression-node.h"


class LiteralIRLogicalExpressionInjectorStrategy {
public:
    llvm::Value* inject(std::shared_ptr<IRLogicalExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};


#endif //JETLANG_LITERAL_IR_LOGICAL_EXPRESSION_INJECTOR_STRATEGY_H

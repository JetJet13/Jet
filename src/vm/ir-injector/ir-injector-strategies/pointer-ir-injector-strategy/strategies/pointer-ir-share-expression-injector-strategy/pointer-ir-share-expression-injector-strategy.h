//
// Created by Johny Georges on 2026-07-13.
//

#ifndef JETLANG_POINTER_IR_SHARE_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_POINTER_IR_SHARE_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-share-expression-node.h"

class PointerIRShareExpressionInjectorStrategy {
private:
    llvm::Value* injectRawValue(std::shared_ptr<IRShareExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
public:
    llvm::Value* inject(std::shared_ptr<IRShareExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_POINTER_IR_SHARE_EXPRESSION_INJECTOR_STRATEGY_H

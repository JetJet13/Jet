//
// Created by Johny Georges on 2025-05-10.
//

#ifndef JETLANG_SHARED_PTR_IR_SHARE_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_SHARED_PTR_IR_SHARE_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-share-expression-node.h"

class SharedPtrIRShareExpressionInjectorStrategy {
private:
    llvm::Value* setupSharedPtr(llvm::Value* allocation, llvm::Value* value, llvm::Value* valueArc, std::shared_ptr<IRType> irType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IROperation> irOperation);
    llvm::Value* injectRawValue(std::shared_ptr<IRShareExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
public:
    llvm::Value* inject(std::shared_ptr<IRShareExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_SHARED_PTR_IR_SHARE_EXPRESSION_INJECTOR_STRATEGY_H

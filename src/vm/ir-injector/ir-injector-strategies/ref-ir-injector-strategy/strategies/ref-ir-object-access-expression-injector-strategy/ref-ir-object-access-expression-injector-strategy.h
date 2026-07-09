//
// Created by Johny Georges on 2025-09-20.
//

#ifndef JETLANG_REF_IR_OBJECT_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_REF_IR_OBJECT_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"

class RefIRObjectAccessExpressionInjectorStrategy {
private:
    llvm::Value* injectCopy(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
    llvm::Value* injectOperand(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
public:
    llvm::Value* inject(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_REF_IR_OBJECT_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H

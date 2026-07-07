//
// Created by Johny Georges on 2026-01-31.
//

#ifndef JETLANG_ENUM_IR_OBJECT_ACCESS_EXPRESSION_STRATEGY_H
#define JETLANG_ENUM_IR_OBJECT_ACCESS_EXPRESSION_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"

class EnumIRObjectAccessExpressionInjectorStrategy {
private:
    llvm::Value* injectCopy(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
    llvm::Value* injectOperand(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
public:
    llvm::Value* inject(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_ENUM_IR_OBJECT_ACCESS_EXPRESSION_STRATEGY_H

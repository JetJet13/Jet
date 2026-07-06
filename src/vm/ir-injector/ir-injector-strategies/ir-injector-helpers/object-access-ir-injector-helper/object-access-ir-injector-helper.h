//
// Created by Johny Georges on 2025-12-19.
//

#ifndef JETLANG_OBJECT_ACCESS_IR_INJECTOR_HELPER_H
#define JETLANG_OBJECT_ACCESS_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-tuple-access-expression-node.h"

class ObjectAccessIRInjectorHelper {
public:
    static llvm::Value* getPointerToTarget(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRObjectAccessExpressionNode> irExpression, llvm::Value* sourceValue);
    static llvm::Value* getPointerToTarget(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRTupleAccessExpressionNode> irExpression, llvm::Value* sourceValue);
};

#endif //JETLANG_OBJECT_ACCESS_IR_INJECTOR_HELPER_H

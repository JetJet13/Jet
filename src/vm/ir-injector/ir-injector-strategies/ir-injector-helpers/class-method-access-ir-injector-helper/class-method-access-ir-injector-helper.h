//
// Created by Johny Georges on 2026-08-29.
//

#ifndef JETLANG_CLASS_METHOD_ACCESS_IR_INJECTOR_HELPER_H
#define JETLANG_CLASS_METHOD_ACCESS_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-property-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-static-method-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-instance-method-access-expression-node.h"

class ClassMethodAccessIRInjectorHelper {
public:
    static llvm::Value* inject(std::shared_ptr<IRClassInstanceMethodAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation);
    static llvm::Value* inject(std::shared_ptr<IRClassStaticMethodAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_CLASS_METHOD_ACCESS_IR_INJECTOR_HELPER_H

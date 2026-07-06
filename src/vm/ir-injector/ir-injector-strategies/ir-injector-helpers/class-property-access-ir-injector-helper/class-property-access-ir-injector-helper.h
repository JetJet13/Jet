//
// Created by Johny Georges on 2025-01-02.
//

#ifndef JETLANG_CLASS_PROPERTY_ACCESS_IR_INJECTOR_HELPER_H
#define JETLANG_CLASS_PROPERTY_ACCESS_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-property-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-static-property-access-expression-node.h"

class ClassPropertyAccessIRInjectorHelper {
public:
    static llvm::Value* inject(std::shared_ptr<IRClassPropertyAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, IROperation* irOperation);
    static llvm::Value* inject(std::shared_ptr<IRClassStaticPropertyAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, IROperation* irOperation);
};

#endif //JETLANG_CLASS_PROPERTY_ACCESS_IR_INJECTOR_HELPER_H

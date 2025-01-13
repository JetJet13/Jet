//
// Created by Johny Georges on 2025-01-02.
//

#ifndef JETLANG_CLASS_PROPERTY_ACCESS_IR_INJECTOR_HELPER_H
#define JETLANG_CLASS_PROPERTY_ACCESS_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-property-access-expression-node.h"

class ClassPropertyAccessIRInjectorHelper {
public:
    static llvm::Value* inject(IRClassPropertyAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_CLASS_PROPERTY_ACCESS_IR_INJECTOR_HELPER_H

//
// Created by Johny Georges on 2025-01-02.
//

#ifndef JETLANG_CLASS_PROPERTY_ACCESS_IR_INJECTOR_HELPER_H
#define JETLANG_CLASS_PROPERTY_ACCESS_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector-map.h"

class ClassPropertyAccessIRInjectorHelper {
public:
    static llvm::Value* inject(IRClassPropertyAccessExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_CLASS_PROPERTY_ACCESS_IR_INJECTOR_HELPER_H

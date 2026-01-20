//
// Created by Johny Georges on 2025-03-19.
//

#include "struct-ir-dref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../ir-injector-helpers/dref-ir-injector-helper/dref-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StructIRDrefExpressionInjectorStrategy::inject(IRDrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto pointerToValue = DrefIRInjectorHelper::inject(irExpression, irBlock, irInjector, new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    return StructIRInjectorHelper::injectStructRefCopy(
            irBlock,
            (IRStructRefType *) irExpression->getIRType(),
            pointerToValue,
            irModule,
            irInjector
    );
}
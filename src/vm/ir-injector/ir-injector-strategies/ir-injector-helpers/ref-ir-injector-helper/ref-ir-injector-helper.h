//
// Created by Johny Georges on 2026-06-02.
//

#ifndef JETLANG_REF_IR_INJECTOR_HELPER_H
#define JETLANG_REF_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-module-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-lambda-expression-nodes/ir-lambda-expression-node.h"
#include "../../../../ir-type/ir-ref-type.h"

class RefIRInjectorHelper {
public:
    static void incrementRefCountForInvocationExpression(llvm::Value* value, std::shared_ptr<IRType> irType, IRBlockNode* irBlock, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule);
    static llvm::Value* injectForInvocationExpression(llvm::Value* value, std::shared_ptr<IRRefType> irRefType, IRBlockNode* irBlock, IROperation* irOperation);
};

#endif //JETLANG_REF_IR_INJECTOR_HELPER_H

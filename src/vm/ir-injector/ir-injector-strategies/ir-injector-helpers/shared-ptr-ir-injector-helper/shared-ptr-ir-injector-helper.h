//
// Created by Johny Georges on 2026-07-13.
//

#ifndef JETLANG_SHARED_PTR_IR_INJECTOR_HELPER_H
#define JETLANG_SHARED_PTR_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"
#include "../../../../ir-type/ir-shared-ptr-type.h"

class SharedPtrIRInjectorHelper {
public:
    static void incrementSharedPtrCountForInvocationExpression(llvm::Value* value, std::shared_ptr<IRType> irType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule);
    static llvm::Value* injectForInvocationExpression(llvm::Value* value, std::shared_ptr<IRSharedPtrType> irSharedPtrType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_SHARED_PTR_IR_INJECTOR_HELPER_H

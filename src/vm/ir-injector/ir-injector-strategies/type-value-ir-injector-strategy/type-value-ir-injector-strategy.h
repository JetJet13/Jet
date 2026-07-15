//
// Created by Johny Georges on 2025-04-12.
//

#ifndef JETLANG_TYPE_VALUE_IR_INJECTOR_STRATEGY_H
#define JETLANG_TYPE_VALUE_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-module-declaration-node.h"
#include "../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../ir-injector.h"
#include "../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-type/ir-ref-type.h"
#include "../../../ir-type/ir-new-class-instance-type.h"
#include "../../../ir-type/ir-captured-variable-type.h"
#include "../../../ir-type/ir-invocable-type.h"
#include "../../../ir-type/ir-lambda-type.h"
#include "../../../ir-type/ir-class-instance-type.h"
#include "../../../ir-type/ir-shared-ptr-type.h"

class IRInjector;

class TypeValueIRInjectorStrategy {
private:
    llvm::Value* inject(std::shared_ptr<IRArrayPointerType> irArrayPointerType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(std::shared_ptr<IRStructType> irStructType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(std::shared_ptr<IRPointerType> irPointerType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(std::shared_ptr<IRRefType> irRefType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(std::shared_ptr<IRSharedPtrType> irSharedPtrType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(std::shared_ptr<IRCapturedVariableType> irCapturedVariableType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(std::shared_ptr<IRStructRefType> irStructRefType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(std::shared_ptr<IRInvocableType> irInvocableType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(std::shared_ptr<IRLambdaType> irLambdaType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(std::shared_ptr<IRClassInstanceType> irClassInstanceType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(std::shared_ptr<IRNewClassInstanceType> irNewClassInstanceType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
public:
    llvm::Value* inject(std::shared_ptr<IRType> irType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule);
};

#endif //JETLANG_TYPE_VALUE_IR_INJECTOR_STRATEGY_H

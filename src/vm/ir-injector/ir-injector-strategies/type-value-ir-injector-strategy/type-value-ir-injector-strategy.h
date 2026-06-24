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

class IRInjector;

class TypeValueIRInjectorStrategy {
private:
    llvm::Value* inject(IRArrayPointerType* irArrayPointerType, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(IRStructType* irStructType, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(IRPointerType* irPointerType, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(IRRefType* irRefType, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(IRCapturedVariableType* irCapturedVariableType, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(IRStructRefType* irStructRefType, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(IRInvocableType* irInvocableType, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(IRLambdaType* irLambdaType, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(IRClassInstanceType* irClassInstanceType, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
    llvm::Value* inject(IRNewClassInstanceType* irNewClassInstanceType, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
public:
    llvm::Value* inject(IRType* irType, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
};

#endif //JETLANG_TYPE_VALUE_IR_INJECTOR_STRATEGY_H

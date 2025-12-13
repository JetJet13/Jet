//
// Created by Johny Georges on 2025-12-13.
//

#ifndef JETLANG_DEBUG_IR_INJECTOR_HELPER_H
#define JETLANG_DEBUG_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-dref-expression-node.h"
#include "../../../../ir-nodes/ir-function-nodes/ir-function-parameter-list-node.h"

class DebugIRInjectorHelper {
public:
    static void injectFunctionEnterLog(IRBlockNode* irBlockNode, std::string functionName, IRInjector* irInjector, IRModuleNode *irModule);
    static void injectFunctionExitLog(IRBlockNode* irBlockNode, std::string functionName, IRInjector* irInjector, IRModuleNode *irModule);
    static void injectControlFlowEnterLog(IRBlockNode* irBlockNode, int index, IRInjector* irInjector, IRModuleNode *irModule);
    static void injectControlFlowExitLog(IRBlockNode* irBlockNode, int index, IRInjector* irInjector, IRModuleNode *irModule);
    static void injectRefCountLog(IRBlockNode* irBlockNode, llvm::Value* idValue, llvm::Value* refValue, IRModuleNode *irModule);
    static void injectLog(IRBlockNode* irBlockNode, llvm::Value* log, IRInjector* irInjector, IRModuleNode *irModule);
    static void injectLog(IRBlockNode* irBlockNode, int log, IRInjector* irInjector, IRModuleNode *irModule);
    static void injectLog(IRBlockNode* irBlockNode, std::string log, IRInjector* irInjector, IRModuleNode *irModule);
};

#endif //JETLANG_DEBUG_IR_INJECTOR_HELPER_H

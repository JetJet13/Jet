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
    static bool const _debugMode = true;
    static void injectFunctionEnterLog(std::shared_ptr<IRBlockNode> irBlockNode, std::string functionName, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
    static void injectFunctionExitLog(std::shared_ptr<IRBlockNode> irBlockNode, std::string functionName, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
    static void injectControlFlowEnterLog(std::shared_ptr<IRBlockNode> irBlockNode, int index, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
    static void injectControlFlowExitLog(std::shared_ptr<IRBlockNode> irBlockNode, int index, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
    static void injectRefCountLog(std::shared_ptr<IRBlockNode> irBlockNode, llvm::Value* idValue, llvm::Value* refValue, std::shared_ptr<IRModuleNode> irModule);
    static void injectLog(std::shared_ptr<IRBlockNode> irBlockNode, llvm::Value* log, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
    static void injectLog(std::shared_ptr<IRBlockNode> irBlockNode, int log, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
    static void injectLog(std::shared_ptr<IRBlockNode> irBlockNode, std::string log, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule);
};

#endif //JETLANG_DEBUG_IR_INJECTOR_HELPER_H

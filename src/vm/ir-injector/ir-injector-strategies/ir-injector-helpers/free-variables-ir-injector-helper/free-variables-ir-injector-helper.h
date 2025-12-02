//
// Created by Johny Georges on 2025-11-24.
//

#ifndef JETLANG_FREE_VARIABLES_IR_INJECTOR_HELPER_H
#define JETLANG_FREE_VARIABLES_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-dref-expression-node.h"
#include "../../../../ir-nodes/ir-function-nodes/ir-function-parameter-list-node.h"

class FreeIRInjectorHelper {
private:
    static void freeBlockVariables(IRBlockNode* irBlockNode, std::vector<IRVariableDeclarationNode*>* variablesToFree, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope);
    static void freeBlockExpressions(IRBlockNode* irBlockNode, std::vector<IRExpressionNode*>* expressionsToFree, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope);
public:
    static void freeFunctionBlockVariables(IRBlockNode* functionBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope);
    static void freeFunctionParameters(IRBlockNode* irBlockNode, IRFunctionParameterListNode* functionParameterList, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_FREE_VARIABLES_IR_INJECTOR_HELPER_H

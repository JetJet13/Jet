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
    static void freeNodes(IRBlockNode* irBlockNode, std::vector<IRNode*>* nodesToFree, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
    static void freeVariable(IRBlockNode* irBlockNode, IRVariableDeclarationNode* variableToFree, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
    static void freeExpression(IRBlockNode* irBlockNode, IRExpressionNode* expressionToFree, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
public:
    static void freeFunctionBlockNodes(IRBlockNode* functionBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
    static void freeFunctionParameters(IRBlockNode* irBlockNode, IRFunctionParameterListNode* functionParameterList, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_FREE_VARIABLES_IR_INJECTOR_HELPER_H

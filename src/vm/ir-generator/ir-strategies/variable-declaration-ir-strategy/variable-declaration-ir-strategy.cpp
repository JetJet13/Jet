//
// Created by Johny Georges on 2024-06-25.
//

#include "variable-declaration-ir-strategy.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRVariableDeclarationNode* VariableDeclarationIRStrategy::generate(ASTVariableDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto irExpression = irGenerator->generateFor(node->getInitializerNode(), scope, irModule);
    auto variableAllocation = IRInstructionNodeFactory::create(irGenerator->generatePointerType(irExpression->getIRType()), node->getId());
    scope->insert(node->getId(), variableAllocation);
    return new IRVariableDeclarationNode(node, variableAllocation, irExpression);
}
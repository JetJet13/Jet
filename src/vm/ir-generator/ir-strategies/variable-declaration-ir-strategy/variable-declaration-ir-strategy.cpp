//
// Created by Johny Georges on 2024-06-25.
//

#include "variable-declaration-ir-strategy.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../ir-type/ir-lambda-type.h"

IRVariableDeclarationNode* VariableDeclarationIRStrategy::generate(ASTVariableDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto irExpression = irGenerator->generateFor(node->getInitializerNode(), scope, irModule, IR_COPY_ASSIGNMENT_OP);

    if (irExpression->isOneOf({ IR_LAMBDA_EXPRESSION_NODE, IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE })) {
        auto irLambdaType = (IRLambdaType*)irExpression->getIRType();
        auto variableAllocation = IRInstructionNodeFactory::create(
                irGenerator->generateIrPointerType(irLambdaType->getLambdaVariableType()), node->getId(), irExpression->getSourceAllocation()
        );
        scope->insert(node->getId(), variableAllocation);
        return new IRVariableDeclarationNode(node, variableAllocation, irExpression);
    }

    auto variableAllocation = IRInstructionNodeFactory::create(
            irGenerator->generateIrPointerType(irExpression->getIRType()->getSourceType()), node->getId(), irExpression->getSourceAllocation()
    );
    auto irGlobalVariable = std::optional<IRGlobalVariableNode*>();
    if (node->isGlobal()) {
        auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
        auto globalVariable = new llvm::GlobalVariable(
                *irModule->getModule(),
                variableAllocation->getAllocatedType(),
                false,
                linkage,
                nullptr,
                node->getId()
        );
        irGlobalVariable = new IRGlobalVariableNode(globalVariable, variableAllocation->getIRType());
        scope->insertGlobalVariable(node->getId(), irGlobalVariable.value());
    } else {
        scope->insert(node->getId(), variableAllocation);
    }

    return new IRVariableDeclarationNode(node, variableAllocation, irExpression, irGlobalVariable);
}
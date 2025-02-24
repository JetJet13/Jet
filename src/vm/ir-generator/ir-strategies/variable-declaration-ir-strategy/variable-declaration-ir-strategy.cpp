//
// Created by Johny Georges on 2024-06-25.
//

#include "variable-declaration-ir-strategy.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../ir-type/ir-lambda-type.h"
#include "../../../../shared/utils/logger/logger.h"

IRVariableDeclarationNode* VariableDeclarationIRStrategy::generate(ASTVariableDeclarationNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto operation = node->isGlobal() ? IR_COPY_GLOBAL_ASSIGNMENT_OP : IR_COPY_ASSIGNMENT_OP;
    auto irExpression = irGenerator->generateFor(node->getInitializerNode(), scope, irContext, operation);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto variableAllocation = IRInstructionNodeFactory::create(
            irGenerator->generateIrPointerType(irType), node->getId(), irExpression->getSourceAllocation()
    );

    auto irGlobalVariable = std::optional<IRInstructionNode*>();
    if (node->isGlobal() && !node->getTypeSignature()->isInvocable()) {
        auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
        auto globalVariable = new llvm::GlobalVariable(
                *irContext->getModule(),
                variableAllocation->getAllocatedType(),
                false,
                linkage,
                nullptr,
                node->getId()
        );

        irGlobalVariable = IRInstructionNodeFactory::create(
                globalVariable,
                variableAllocation->getIRType(),
                irExpression->getSourceAllocation()
        );
        variableAllocation->markAsGlobal();
        irExpression->markAsGlobal();
        irGlobalVariable.value()->markAsGlobal();
        scope->insertGlobalVariable(node->getId(), irGlobalVariable.value());
    } else {
        scope->insert(node->getId(), variableAllocation);
    }

    return new IRVariableDeclarationNode(node, variableAllocation, irExpression, irGlobalVariable);
}
//
// Created by Johny Georges on 2024-06-25.
//

#include "variable-declaration-ir-strategy.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../ir-type/ir-lambda-type.h"
#include "../../../../shared/utils/logger/logger.h"

IRVariableDeclarationNode* VariableDeclarationIRStrategy::generate(ASTVariableDeclarationNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irExpression = irGenerator->generateFor(node->getInitializerNode(), scope, irContext, IR_COPY_ASSIGNMENT_OP);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto variableAllocation = IRInstructionNodeFactory::create(
            irGenerator->generateIrPointerType(irType), node->getId(), irExpression->getSourceAllocation()
    );

    auto irGlobalVariable = std::optional<IRGlobalVariableNode*>();
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

        auto parentGlobalVariable = std::optional<llvm::GlobalVariable*>();
        if (variableAllocation->getParentAllocation()) {
            // todo: refactor array ir-generator/ir-injector strategy
            // get rid of need of referencing array/string source allocation when copying array/string values (e.g. [3 x i32])
            // instead leverage function like jet.copy.string to copy source allocation
            // using only the array pointer allocation { i32, ptr }
            parentGlobalVariable = new llvm::GlobalVariable(
                    *irContext->getModule(),
                    variableAllocation->getParentAllocation().value()->getAllocatedType(),
                    false,
                    linkage,
                    nullptr,
                    "parent." + node->getId()
            );
        }

        irGlobalVariable = new IRGlobalVariableNode(globalVariable, variableAllocation->getIRType(), parentGlobalVariable);
        scope->insertGlobalVariable(node->getId(), irGlobalVariable.value());
    } else {
        scope->insert(node->getId(), variableAllocation);
    }

    return new IRVariableDeclarationNode(node, variableAllocation, irExpression, irGlobalVariable);
}
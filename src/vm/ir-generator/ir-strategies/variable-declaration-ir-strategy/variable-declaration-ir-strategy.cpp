//
// Created by Johny Georges on 2024-06-25.
//

#include "variable-declaration-ir-strategy.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRVariableDeclarationNode> VariableDeclarationIRStrategy::generate(std::shared_ptr<ASTVariableDeclarationNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto operation = this->determineOperationType(node);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto variableAllocation = this->generateVariableAllocation(node, irGenerator, irType, irContext);

    auto irGlobalVariable = std::optional<std::shared_ptr<IRInstructionNode>>();
    if (node->isGlobal()) {
        auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
        auto globalVariable = new llvm::GlobalVariable(
                *irContext->getModule(),
                variableAllocation->getAllocatedType(),
                false,
                linkage,
                irGenerator->generatePlaceholderValueForIRType(irType),
                node->getId()
        );
        irGlobalVariable = IRInstructionNodeFactory::create(
                globalVariable,
                variableAllocation->getIRType()
        );
        variableAllocation->markAsGlobal();
        irGlobalVariable.value()->markAsGlobal();
        scope->insertGlobalVariable(node->getId(), irGlobalVariable.value());
    } else {
        scope->insert(node->getId(), variableAllocation);
    }

    auto irExpression = irGenerator->generateFor(node->getInitializerNode(), scope, irContext, operation);
    irExpression->markAsAssigned();
    if (irGlobalVariable) {
        irExpression->markAsGlobal();
        irGlobalVariable.value()->setParentAllocation(irExpression->getSourceAllocation());
    } else {
        variableAllocation->setParentAllocation(irExpression->getSourceAllocation());
    }

    auto irArc = std::optional<std::shared_ptr<IRInstructionNode>>();
    if (irType->requiresArc()) {
        irArc = irGenerator->generateArcAllocation(irContext, irType, variableAllocation->getValue(), node->getCaptureCount());
        scope->insertArc(node->getId(), irArc.value());
    } else if (node->isCaptured()) {
        irArc = irGenerator->generateArcAllocation(irContext, node->getCaptureCount());
        scope->insertArc(node->getId(), irArc.value());
    }

    return std::make_shared<IRVariableDeclarationNode>(node, variableAllocation, irExpression, irGenerator->generateRawString(node->getId()), irGlobalVariable, irArc);
}

IROperation* VariableDeclarationIRStrategy::determineOperationType(std::shared_ptr<ASTVariableDeclarationNode> node) {
    if (node->isGlobal()) {
        return node->getInitializerNode()->is(AST_REF_EXPRESSION_NODE) ? (new IROperation(IR_REF_ASSIGNMENT_OP))->markAsGlobal() : (new IROperation(IR_COPY_ASSIGNMENT_OP))->markAsGlobal();
    }
    return node->getInitializerNode()->is(AST_REF_EXPRESSION_NODE) ? new IROperation(IR_REF_ASSIGNMENT_OP) : new IROperation(IR_COPY_ASSIGNMENT_OP);
}

std::shared_ptr<IRInstructionNode> VariableDeclarationIRStrategy::generateVariableAllocation(std::shared_ptr<ASTVariableDeclarationNode> node, IRGenerator* irGenerator, std::shared_ptr<IRType> irType, IRContext* irContext) {
    if (node->isCaptured()) {
        auto malloc = llvm::CallInst::Create(
                irContext->getIRModule()->getMallocFunction(),
                { irGenerator->generateInt64Constant(1), irGenerator->generateInt64Constant(irType->getSizeInBytes()) },
                ""
        );
        return IRInstructionNodeFactory::create(malloc, irGenerator->generateIrPointerType(irType));
    }
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType), node->getId());
}
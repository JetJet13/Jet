//
// Created by Johny Georges on 2024-07-13.
//

#include "procedure-declaration-ir-strategy.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../utils/address-space-generator/address-space-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../shared/utils/function-id-generator/function-id-generator.h"

std::shared_ptr<IRProcedureDeclarationNode> ProcedureDeclarationIRStrategy::generate(std::shared_ptr<ASTProcedureDeclarationNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto procedureScope = std::make_shared<IRLookupTable>();
    procedureScope->inherit(scope);
    auto procedureTypeNode = irGenerator->generateTypeFor(node->getTypeSignature(), procedureScope, irContext);
    auto functionType = llvm::cast<llvm::FunctionType>(procedureTypeNode->getType());
    auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    auto irFunctionId = FunctionIdGenerator::generateFor(node->getId(), node->getProcedureTypeSignature());
    auto irFunction = llvm::Function::Create(functionType, linkage, 0, irFunctionId, irContext->getModule());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), procedureScope, irContext, irFunction);
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction, procedureScope);
    auto irFunctionContext = irContext->clone(functionBlock);
    for (unsigned long i = 0; i < functionType->getNumParams(); ++i) {
        auto formalParameter = functionParameterList->getParameters()->at(i);
        auto functionParameterAllocation = formalParameter->getAllocation();
        functionBlock->insert(std::make_shared<IRFunctionParameterDeclarationNode>(irFunction->getArg(i), functionParameterAllocation, formalParameter->getArc()));
    }

    for (auto statement : *node->getBlock()->getContents()) {
        functionBlock->insert(irGenerator->generateFor(statement, functionBlock->getScope(), irFunctionContext));
    }

    auto globalVariableIRType = irGenerator->generateIRInvocableType();
    auto globalVariable = new llvm::GlobalVariable(
            *irContext->getModule(),
            globalVariableIRType->getType(),
            false,
            node->isExportable()
            ? llvm::GlobalValue::ExternalLinkage
            : llvm::GlobalValue::PrivateLinkage,
            irGenerator->generatePlaceholderValueForIRType(globalVariableIRType),
            irFunctionId
    );
    auto irGlobalVariable = IRInstructionNodeFactory::create(
            globalVariable,
            irGenerator->generateIrPointerType(globalVariableIRType)
    );

    auto irProcedureDeclaration = std::make_shared<IRProcedureDeclarationNode>(node, irFunction, functionParameterList, functionBlock, irGlobalVariable);
    scope->insertGlobalVariable(irFunctionId, irGlobalVariable);

    return irProcedureDeclaration;
}
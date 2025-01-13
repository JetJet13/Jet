//
// Created by Johny Georges on 2024-07-13.
//

#include "procedure-declaration-ir-strategy.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../utils/address-space-generator/address-space-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"

IRProcedureDeclarationNode* ProcedureDeclarationIRStrategy::generate(ASTProcedureDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto procedureScope = new IRLookupTable();
    procedureScope->inherit(scope);
    auto procedureTypeNode = irGenerator->generateTypeFor(node->getTypeSignature(), procedureScope);
    auto functionType = llvm::cast<llvm::FunctionType>(procedureTypeNode->getType());
    auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    auto irFunction = llvm::Function::Create(functionType, linkage, 0, node->getId(), irModule->getModule());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), procedureScope, irModule, irFunction);
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction);

    for (int i = 0; i < functionType->getNumParams(); ++i) {
        auto parameter = functionType->params()[i];
        auto formalParameter = functionParameterList->getParameters()->at(i);
        auto irParamType = formalParameter->getParameterType()->getIRType();
        auto functionParameterAllocation = new IRInstructionNode(
            new llvm::AllocaInst(
                parameter,
                AddressSpaceGenerator::generate(irParamType),
                nullptr,
                DataAlignmentGenerator::generate(irParamType)
            ), irGenerator->generateIrPointerType(irParamType));
        procedureScope->insert(formalParameter->getParameterType()->getName(), functionParameterAllocation);
        functionBlock->insert(new IRFunctionParameterDeclarationNode(irFunction->getArg(i), functionParameterAllocation));
    }

    for (auto statement : *node->getBlock()->getContents()) {
            functionBlock->insert(irGenerator->generateFor(statement, procedureScope, irModule));
    }
    return new IRProcedureDeclarationNode(node, irFunction, functionParameterList, functionBlock, procedureScope);
}
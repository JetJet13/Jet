//
// Created by Johny Georges on 2024-07-08.
//

#include "function-declaration-ir-strategy.h"
#include "../../../utils/address-space-generator/address-space-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../shared/utils/function-id-generator/function-id-generator.h"

std::shared_ptr<IRFunctionDeclarationNode> FunctionDeclarationIRStrategy::generate(std::shared_ptr<ASTFunctionDeclarationNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto functionScope = std::make_shared<IRLookupTable>();
    functionScope->inherit(scope);
    auto functionTypeNode = irGenerator->generateTypeFor(node->getTypeSignature(), functionScope, irContext);
    auto functionType = llvm::cast<llvm::FunctionType>(functionTypeNode->getType());

    auto linkage = node->isExportable() ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;
    auto irFunctionId = FunctionIdGenerator::generateFor(node->getId(), node->getFunctionTypeSignature());
    auto irFunction = llvm::Function::Create(functionType, linkage, irFunctionId, irContext->getModule());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), functionScope, irContext, irFunction);
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction, functionScope);
    auto irFunctionContext = irContext->clone(functionBlock);
    for (uint64_t i = 0; i < functionType->getNumParams(); ++i) {
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
    auto irFunctionDeclaration = std::make_shared<IRFunctionDeclarationNode>(node, irFunction, functionParameterList, functionBlock, irGlobalVariable);
    scope->insertGlobalVariable(irFunctionId, irGlobalVariable);

    return irFunctionDeclaration;
}
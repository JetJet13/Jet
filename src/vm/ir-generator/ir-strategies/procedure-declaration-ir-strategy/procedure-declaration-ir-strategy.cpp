//
// Created by Johny Georges on 2024-07-13.
//

#include "procedure-declaration-ir-strategy.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../core/ast/ast-nodes/ast-node-utils/ast-node-utils.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../utils/address-space-generator/address-space-generator.h"

IRProcedureDeclarationNode* ProcedureDeclarationIRStrategy::generate(ASTProcedureDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto procedureTypeNode = irGenerator->generateTypeFor(node->getTypeSignature());
    auto functionType = llvm::cast<llvm::FunctionType>(procedureTypeNode->getPointerSourceIRType()->getType());
    auto irFunction = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, node->getId(), irModule->getModule());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), scope, irModule, irFunction);
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
            ), irParamType);
        scope->insert(formalParameter->getParameterType()->getName(), functionParameterAllocation);
        functionBlock->insert(new IRFunctionParameterDeclarationNode(irFunction->getArg(i), functionParameterAllocation));
    }

    for (auto statement : *node->getBlock()->getContents()) {
        if (ASTNodeUtils::isDeclarationNode(statement)) {
            functionBlock->insert(
                    irGenerator->generateFor((ASTDeclarationNode*)statement, scope, irModule)
            );
        } else if (ASTNodeUtils::isStatementNode(statement)) {
            functionBlock->insert(
                    irGenerator->generateFor((ASTStatementNode*)statement, scope, irModule)
            );
        }
    }
    return new IRProcedureDeclarationNode(node, irFunction, functionParameterList, functionBlock);
}
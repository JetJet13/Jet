//
// Created by Johny Georges on 2024-11-12.
//

#include "lambda-expression-ir-strategy.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-node-utils/ast-node-utils.h"

IRLambdaExpressionNode* LambdaExpressionIRStrategy::generate(ASTLambdaExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto functionTypeNode = irGenerator->generateTypeFor(node->getTypeSignature());
    auto functionType = llvm::cast<llvm::FunctionType>(functionTypeNode->getType());
    auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    auto irFunction = llvm::Function::Create(functionType, linkage, node->getId(), irModule->getModule());
    auto functionParameterList = irGenerator->generateFor(node->getParameters(), scope, irModule, irFunction);
    auto functionBlock = irGenerator->generateFunctionBlock(irFunction);

    auto lambdaScopeParameterType = irGenerator->generateParameterType(node->getTypeSignature()->getScopeParameter());
    auto argument = new llvm::Argument(lambdaScopeParameterType->getType(), lambdaScopeParameterType->getName(), irFunction, 0);
    functionParameterList->addScopeParameter(new IRFunctionParameterNode(argument, lambdaScopeParameterType));

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

        scope->insert(formalParameter->getParameterType()->getName(), functionParameterAllocation);
        irGenerator->getInjector()->inject(functionBlock, new IRFunctionParameterDeclarationNode(irFunction->getArg(i), functionParameterAllocation), irModule);
    }

    for (auto statement : *node->getBlock()->getContents()) {
        if (ASTNodeUtils::isDeclarationNode(statement)) {
            irGenerator->getInjector()->inject(functionBlock, irGenerator->generateFor((ASTDeclarationNode*)statement, scope, irModule), irModule);
        } else if (ASTNodeUtils::isStatementNode(statement)) {
            irGenerator->getInjector()->inject(functionBlock, irGenerator->generateFor((ASTStatementNode*)statement, scope, irModule), irModule);
        }
    }
    return new IRLambdaExpressionNode(node, irFunction, functionParameterList, functionBlock, new IRLambdaType(irFunction->getFunctionType()));
}
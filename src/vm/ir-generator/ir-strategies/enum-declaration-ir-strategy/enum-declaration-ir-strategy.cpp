//
// Created by Johny Georges on 2024-07-15.
//

#include "enum-declaration-ir-strategy.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IREnumDeclarationNode* EnumDeclarationIRStrategy::generate(ASTEnumDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto enumType = irGenerator->generateTypeFor(node->getTypeSignature());
    auto structValues = std::vector<llvm::Constant*>();
    for (int i = 0; i < node->getValues()->numParameters(); ++i) {
        auto keyValuePair = node->getValues()->getParameters()[i];
        if (keyValuePair->getValue()) {
            auto enumValue = irGenerator->generateFor(keyValuePair->getValue().value(), scope, irModule);
            structValues.push_back(enumValue->getConstantIRValue());
        } else {
            auto enumValue = irGenerator->generateIntConstant(i);
            structValues.push_back(enumValue);
        }
    }

    auto structType = llvm::cast<llvm::StructType>(enumType->getPointerSourceIRType()->getType());
    auto globalVariable = new llvm::GlobalVariable(
            *irModule->getModule(),
            enumType->getPointerSourceIRType()->getType(),
            true,
            llvm::GlobalValue::InternalLinkage,
            llvm::ConstantStruct::get(structType, structValues),
            node->getId()
    );
    auto globalVariableEnum = new IRGlobalVariableNode(
            globalVariable,
            enumType,
            IRInstructionNodeFactory::create(globalVariable)
    );
    scope->insertGlobalVariable(node->getId(), globalVariableEnum);
    return new IREnumDeclarationNode(
        node,
        globalVariableEnum
    );
}
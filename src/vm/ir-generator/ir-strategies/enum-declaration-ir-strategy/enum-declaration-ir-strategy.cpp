//
// Created by Johny Georges on 2024-07-15.
//

#include "enum-declaration-ir-strategy.h"
#include "../../../utils/address-space-generator/address-space-generator.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"

IREnumDeclarationNode* EnumDeclarationIRStrategy::generate(ASTEnumDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto enumValueType = irGenerator->generateTypeFor(node->getTypeSignature());
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
    
    return new IREnumDeclarationNode(
        node,
        new llvm::GlobalVariable(
            *irModule->getModule(),
            enumValueType->getType(),
            true,
            llvm::GlobalValue::PrivateLinkage,
            llvm::ConstantStruct::get(enumValueType->getType(), structValues),
            node->getId()
        )
    );
}
//
// Created by Johny Georges on 2024-07-15.
//

#include "enum-declaration-ir-strategy.h"
#include "../../../../shared/utils/logger/logger.h"

IREnumDeclarationNode* EnumDeclarationIRStrategy::generate(ASTEnumDeclarationNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto structValues = std::vector<llvm::Constant*>();

    if (node->getTypeSignature()->getType()->typeSourceIs(STRING_LITERAL_TYPE_SOURCE)) {
        auto stringArrayPointerType = irGenerator->generateIrStringArrayPointerType();
        for (int i = 0; i < node->getValues()->numParameters(); ++i) {
            auto keyValuePair = node->getValues()->getParameters()[i];
            auto enumValue = irGenerator->generateFor(keyValuePair->getValue().value(), scope, irContext);
            auto stringType = (IRArrayType*)enumValue->getIRType();
            auto stringValue = enumValue->getConstantIRValue();
            auto stringGlobalVariable = new llvm::GlobalVariable(
                    *irContext->getModule(),
                    stringValue->getType(),
                    true,
                    llvm::GlobalValue::InternalLinkage,
                    stringValue
            );
            structValues.push_back(
                llvm::ConstantStruct::get(
                    stringArrayPointerType->getType(),
                    {
                        irGenerator->generateIntConstant(stringType->getSize()),
                        irGenerator->generateIntConstant(1),
                        stringGlobalVariable
                    }
                )
            );
        }
    } else {
        for (int i = 0; i < node->getValues()->numParameters(); ++i) {
            auto keyValuePair = node->getValues()->getParameters()[i];
            if (keyValuePair->getValue()) {
                auto enumValue = irGenerator->generateFor(keyValuePair->getValue().value(), scope, irContext);
                structValues.push_back(enumValue->getConstantIRValue());
            } else {
                auto enumValue = irGenerator->generateIntConstant(i);
                structValues.push_back(enumValue);
            }
        }
    }

    auto enumType = irGenerator->generateTypeFor(node->getTypeSignature(), structValues, scope, irContext);
    auto structType = enumType->getType();
    auto globalVariable = new llvm::GlobalVariable(
            *irContext->getModule(),
            enumType->getType(),
            true,
            llvm::GlobalValue::InternalLinkage,
            llvm::ConstantStruct::get(structType, structValues),
            node->getId()
    );
    auto globalVariableEnum = new IRInstructionNode(
            globalVariable,
            irGenerator->generateIrPointerType(enumType)
    );
    scope->insertGlobalVariable(node->getId(), globalVariableEnum);
    return new IREnumDeclarationNode(
        node,
        globalVariableEnum
    );
}
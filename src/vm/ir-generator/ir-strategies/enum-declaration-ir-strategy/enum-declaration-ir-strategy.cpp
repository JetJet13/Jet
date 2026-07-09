//
// Created by Johny Georges on 2024-07-15.
//

#include "enum-declaration-ir-strategy.h"
#include "../../../../shared/utils/logger/logger.h"

std::shared_ptr<IREnumDeclarationNode> EnumDeclarationIRStrategy::generate(std::shared_ptr<ASTEnumDeclarationNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto structValues = std::vector<llvm::Constant*>();

    if (node->getEnumTypeSignature()->getType()->typeSourceIs(STRING_LITERAL_TYPE_SOURCE)) {
        auto stringArrayPointerType = irGenerator->generateIrStringArrayPointerType();
        for (unsigned long i = 0; i < node->getValues()->numParameters(); ++i) {
            auto keyValuePair = node->getValues()->getParameters()[i];
            auto enumValue = irGenerator->generateFor(keyValuePair->getValue().value(), scope, irContext);
            auto stringType = std::dynamic_pointer_cast<IRArrayType>(enumValue->getIRType());
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
        for (unsigned long i = 0; i < node->getValues()->numParameters(); ++i) {
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

    auto enumType = irGenerator->generateTypeFor(node->getEnumTypeSignature(), structValues, scope, irContext);
    auto structType = enumType->getType();
    auto linkage = node->isExportable() ? llvm::GlobalValue::ExternalLinkage : llvm::GlobalValue::InternalLinkage;
    auto globalVariable = new llvm::GlobalVariable(
            *irContext->getModule(),
            enumType->getType(),
            true,
            linkage,
            llvm::ConstantStruct::get(structType, structValues),
            node->getId()
    );
    auto globalVariableEnum = std::make_shared<IRInstructionNode>(
            globalVariable,
            irGenerator->generateIrPointerType(enumType)
    );
    scope->insertGlobalVariable(node->getId(), globalVariableEnum);
    return std::make_shared<IREnumDeclarationNode>(
        node,
        globalVariableEnum
    );
}
//
// Created by Johny Georges on 2024-07-11.
//

#include "class-type-signature-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"

IRClassType* ClassTypeSignatureIRStrategy::generate(ClassTypeSignature* classTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto classPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    for (auto keyValue : classTypeSignature->getProperties()->getKeyValues()) {
        auto irType = irGenerator->generateTypeFor(keyValue.second->getType(), scope, irContext);
        classPropertyTypes.push_back(irType->getType());
        keyIndexMap.insert(
                std::pair(keyValue.first, classTypeSignature->getProperties()->findKeyIndex(keyValue.first))
        );
        keyTypeMap.insert(std::pair(keyValue.first, irType));
    }
    auto classProperties = new IRStructType(llvm::StructType::get(**irContext->getContext(), classPropertyTypes), keyIndexMap, keyTypeMap);
    classProperties->setAlignmentAndSizeForIRTypes();
    classProperties->setValue(irGenerator->generateIRTypeValueFor(classProperties));

    auto constructorReturnType = irGenerator->generateVoidType()->getType();
    auto classConstructors = std::unordered_map<std::string, IRFunctionType*>();
    for (auto keyValue : classTypeSignature->getConstructors()->getKeyValues()) {
        auto constructorParameters = classTypeSignature->isClassScopeParameterNecessary()
        ? irGenerator->generateParameterList(keyValue.second->getParameterList(), scope, irContext, classTypeSignature->getClassScopeParameter())
        : irGenerator->generateParameterList(keyValue.second->getParameterList(), scope, irContext);
        classConstructors[keyValue.first] = new IRFunctionType(llvm::FunctionType::get(constructorReturnType, constructorParameters->getParameterTypes(), false));
    }

    auto classMethods = std::unordered_map<std::string, IRFunctionType*>();
    for (int i = 0; i < classTypeSignature->getMethods()->size(); ++i) {
        auto keyValue = classTypeSignature->getMethods()->getKeyValues()[i];
        auto methodReturnType = irGenerator->generateTypeFor(keyValue.second->getReturnType(), scope, irContext);
        auto methodParameters = classTypeSignature->isClassScopeParameterNecessary()
                                ? irGenerator->generateParameterList(keyValue.second->getParameters(), scope, irContext, classTypeSignature->getClassScopeParameter())
                                : irGenerator->generateParameterList(keyValue.second->getParameters(), scope, irContext);
        Logger::log("CLASS METHOD", keyValue.first);
        classMethods[keyValue.first] = new IRFunctionType(llvm::FunctionType::get(methodReturnType->getType(), methodParameters->getParameterTypes(), false));
    }

    return new IRClassType(
            classTypeSignature->getId(),
            classProperties,
            classTypeSignature->isClassScopeParameterNecessary()
            ? irGenerator->generateParameterType(classTypeSignature->getClassScopeParameter(), scope, irContext)
            : std::optional<IRParameterType*>(),
            classConstructors,
            classMethods,
            classTypeSignature->getPreConstructorName()
    );
}
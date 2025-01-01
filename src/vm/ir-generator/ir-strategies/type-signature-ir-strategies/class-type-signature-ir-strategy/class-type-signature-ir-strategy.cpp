//
// Created by Johny Georges on 2024-07-11.
//

#include "class-type-signature-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"

IRClassType* ClassTypeSignatureIRStrategy::generate(ClassTypeSignature* classTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto classPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    for (auto keyValue : classTypeSignature->getProperties()->getKeyValues()) {
        auto irType = irGenerator->generateTypeFor(keyValue.second->getType(), scope);
        classPropertyTypes.push_back(irType->getType());
        keyIndexMap.insert(
                std::pair(keyValue.first, classTypeSignature->getProperties()->findKeyIndex(keyValue.first))
        );
        keyTypeMap.insert(std::pair(keyValue.first, irType));
    }
    auto classProperties = new IRStructType(llvm::StructType::get(**context, classPropertyTypes), keyIndexMap, keyTypeMap);

    auto constructorReturnType = irGenerator->generateVoidType()->getType();
    auto classConstructors = std::unordered_map<std::string, IRFunctionType*>();
    for (auto keyValue : classTypeSignature->getConstructors()->getKeyValues()) {
        auto constructorParameters = classTypeSignature->isClassScopeParameterNecessary()
        ? irGenerator->generateParameterList(keyValue.second->getParameterList(), scope, classTypeSignature->getClassScopeParameter())
        : irGenerator->generateParameterList(keyValue.second->getParameterList(), scope);
        classConstructors[keyValue.first] = new IRFunctionType(llvm::FunctionType::get(constructorReturnType, constructorParameters->getParameterTypes(), false));
    }

    auto classMethods = std::unordered_map<std::string, IRFunctionType*>();
    for (auto keyValue : classTypeSignature->getMethods()->getKeyValues()) {
        auto methodReturnType = irGenerator->generateTypeFor(keyValue.second->getReturnType(), scope);
        auto methodParameters = classTypeSignature->isClassScopeParameterNecessary()
                ? irGenerator->generateParameterList(keyValue.second->getParameters(), scope, classTypeSignature->getClassScopeParameter())
                : irGenerator->generateParameterList(keyValue.second->getParameters(), scope);
        classMethods[keyValue.first] = new IRFunctionType(llvm::FunctionType::get(methodReturnType->getType(), methodParameters->getParameterTypes(), false));
    }

    auto irClassType = new IRClassType(
            classProperties,
            classTypeSignature->isClassScopeParameterNecessary()
            ? irGenerator->generateParameterType(classTypeSignature->getClassScopeParameter(), scope)
            : std::optional<IRParameterType*>(),
            classConstructors,
            classMethods
    );
    Logger::log("classTypeSignature->getId()", classTypeSignature->getId());
    scope->insert(classTypeSignature->getId(), irClassType);
    return irClassType;
}
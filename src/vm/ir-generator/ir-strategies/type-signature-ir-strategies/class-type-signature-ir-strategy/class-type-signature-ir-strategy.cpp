//
// Created by Johny Georges on 2024-07-11.
//

#include "class-type-signature-ir-strategy.h"
#include "../../../../../shared/utils/md5/md5.h"

IRClassType* ClassTypeSignatureIRStrategy::generate(ClassTypeSignature* classTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irClassType = (IRClassType*)scope->findGlobalType(classTypeSignature->getId()).value();
    auto classPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyTypeMap = std::unordered_map<std::string, IRType*>();
    for (auto keyValue : classTypeSignature->getProperties()->getKeyValues()) {
        auto irType = irGenerator->generateTypeFor(keyValue.second, scope, irContext);
        classPropertyTypes.push_back(irType->getType());
        keyIndexMap.insert(
                std::pair(keyValue.first, classTypeSignature->getProperties()->findKeyIndex(keyValue.first))
        );
        keyTypeMap.insert(std::pair(keyValue.first, irType));

    }
    auto classProperties = new IRStructType(llvm::StructType::get(**irContext->getContext(), classPropertyTypes), keyIndexMap, keyTypeMap);
    classProperties->setId(classTypeSignature->getId());
    classProperties->setAlignmentAndSizeForIRTypes();
    classProperties->setValue(irGenerator->generateIRTypeValueFor(classProperties, irContext));
    irClassType->setProperties(classProperties);

    auto constructorReturnType = irGenerator->getVoidType();
    auto classConstructors = std::unordered_map<std::string, IRFunctionType*>();
    for (auto keyValue : classTypeSignature->getConstructors()->getKeyValues()) {
        auto constructorParameters = classTypeSignature->isClassScopeParameterNecessary()
        ? irGenerator->generateParameterList(keyValue.second->getParameterList(), scope, irContext, classTypeSignature->getClassScopeParameter())
        : irGenerator->generateParameterList(keyValue.second->getParameterList(), scope, irContext);
        irClassType->addConstructor(
            keyValue.first,
            new IRFunctionType(llvm::FunctionType::get(constructorReturnType, constructorParameters->getParameterTypes(), false))
        );
    }

    auto classMethods = std::unordered_map<std::string, IRFunctionType*>();
    for (int i = 0; i < classTypeSignature->getMethods()->size(); ++i) {
        auto keyValue = classTypeSignature->getMethods()->getKeyValues()[i];
        auto methodReturnType = irGenerator->generateTypeFor(keyValue.second->getReturnType(), scope, irContext);
        auto methodParameters = classTypeSignature->isClassScopeParameterNecessary()
                                ? irGenerator->generateParameterList(keyValue.second->getParameters(), scope, irContext, classTypeSignature->getClassScopeParameter())
                                : irGenerator->generateParameterList(keyValue.second->getParameters(), scope, irContext);
        irClassType->addMethod(
            keyValue.first,
            new IRFunctionType(llvm::FunctionType::get(methodReturnType->getType(), methodParameters->getParameterTypes(), false))
        );
    }

    return irClassType;
}

IRClassType* ClassTypeSignatureIRStrategy::generateInitial(ClassTypeSignature* classTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irClassType = new IRClassType(
            classTypeSignature->getId(),
            irGenerator->generateIRStructType(),
            classTypeSignature->getPreConstructorName()
    );

    irClassType->setId(classTypeSignature->getId());
    scope->insertGlobalType(irClassType->getId(), irClassType);

    return irClassType;
}

IRClassType* ClassTypeSignatureIRStrategy::generatePostInitial(ClassTypeSignature* classTypeSignature, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext) {
    auto irClassType = (IRClassType*)scope->findGlobalType(classTypeSignature->getId()).value();
    auto constructorReturnType = irGenerator->getVoidType();
    for (auto keyValue : classTypeSignature->getConstructors()->getKeyValues()) {
        auto constructorParameters = classTypeSignature->isClassScopeParameterNecessary()
                                     ? irGenerator->generateParameterList(keyValue.second->getParameterList(), scope, irContext, classTypeSignature->getClassScopeParameter())
                                     : irGenerator->generateParameterList(keyValue.second->getParameterList(), scope, irContext);
        irClassType->addConstructor(
                keyValue.first,
                new IRFunctionType(llvm::FunctionType::get(constructorReturnType, constructorParameters->getParameterTypes(), false))
        );
    }

    if (classTypeSignature->isClassScopeParameterNecessary()) {
        irClassType->setClassScopeType(irGenerator->generateParameterType(classTypeSignature->getClassScopeParameter(), scope, irContext));
        auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { irGenerator->generatePointerType() }, false);
        llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, irClassType->getPreConstructorName(), irContext->getModule());
    }

    return irClassType;
}
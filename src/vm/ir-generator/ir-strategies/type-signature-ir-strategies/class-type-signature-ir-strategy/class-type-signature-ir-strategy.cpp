//
// Created by Johny Georges on 2024-07-11.
//

#include "class-type-signature-ir-strategy.h"
#include "../../../../../shared/utils/md5/md5.h"

std::shared_ptr<IRClassType> ClassTypeSignatureIRStrategy::generate(std::shared_ptr<ClassTypeSignature> classTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext) {
    auto irClassType = std::dynamic_pointer_cast<IRClassType>(scope->findGlobalType(classTypeSignature->getModuleId(), classTypeSignature->getId()).value());
    auto classPropertyTypes = std::vector<llvm::Type*>();
    auto keyIndexMap = std::unordered_map<std::string, unsigned long>();
    auto keyIdMap = std::unordered_map<unsigned long, std::string>();
    auto keyTypeMap = std::unordered_map<std::string, std::shared_ptr<IRType>>();
    for (auto keyValue : classTypeSignature->getInstanceProperties()->getKeyValues()) {
        auto irType = irGenerator->generateTypeFor(keyValue.second, scope, irContext);
        auto index = classTypeSignature->getInstanceProperties()->findKeyIndex(keyValue.first);
        classPropertyTypes.push_back(irType->getType());
        keyIndexMap.insert(std::pair(keyValue.first, index));
        keyIdMap.insert(std::pair(index, classTypeSignature->stripClassNameFromKey(keyValue.first)));
        keyTypeMap.insert(std::pair(keyValue.first, irType));
    }
    auto classProperties = irGenerator->generateIRStructRefType(std::make_shared<IRStructType>(llvm::StructType::get(**irContext->getContext(), classPropertyTypes), keyIndexMap, keyIdMap, keyTypeMap));
    classProperties->setId(classTypeSignature->getId());
    classProperties->getStructIRType()->setId(classTypeSignature->getId());
    classProperties->getStructIRType()->setAlignmentAndSizeForIRTypes();
    classProperties->getStructIRType()->setValue(irGenerator->generateIRTypeValueFor(classProperties->getStructIRType(), irContext));
    classProperties->setValue(irGenerator->generateIRTypeValueFor(classProperties, irContext));
    irClassType->setProperties(classProperties);

    auto constructorReturnType = irGenerator->getVoidType();
    for (auto keyValue : classTypeSignature->getConstructors()->getKeyValues()) {
        auto constructorParameters = classTypeSignature->isClassScopeParameterNecessary()
        ? irGenerator->generateParameterList(keyValue.second->getParameterList(), scope, irContext, classTypeSignature->getClassScopeParameter())
        : irGenerator->generateParameterList(keyValue.second->getParameterList(), scope, irContext);
        irClassType->addConstructor(
            keyValue.first,
            std::make_shared<IRFunctionType>(llvm::FunctionType::get(constructorReturnType, constructorParameters->getParameterTypes(), false))
        );
    }

    for (unsigned long i = 0; i < classTypeSignature->getInstanceMethods()->size(); ++i) {
        auto keyValue = classTypeSignature->getInstanceMethods()->getKeyValues()[i];
        auto methodReturnType = irGenerator->generateTypeFor(keyValue.second->getReturnType()->convertToVariableTypeSignature(), scope, irContext);
        auto methodParameters = classTypeSignature->isClassScopeParameterNecessary()
                                ? irGenerator->generateParameterList(keyValue.second->getParameters(), scope, irContext, classTypeSignature->getClassScopeParameter())
                                : irGenerator->generateParameterList(keyValue.second->getParameters(), scope, irContext);
        irClassType->addMethod(
            keyValue.first,
            std::make_shared<IRFunctionType>(llvm::FunctionType::get(methodReturnType->getType(), methodParameters->getParameterTypes(), false))
        );
    }

    for (auto keyValue : classTypeSignature->getStaticProperties()->getKeyValues()) {
        auto irType = irGenerator->generateTypeFor(keyValue.second, scope, irContext);
        irClassType->addStaticProperty(keyValue.first, irType);
    }

    for (auto keyValue : classTypeSignature->getStaticMethods()->getKeyValues()) {
        auto methodReturnType = irGenerator->generateTypeFor(keyValue.second->getReturnType()->convertToVariableTypeSignature(), scope, irContext);
        auto methodParameters = irGenerator->generateParameterList(keyValue.second->getParameters(), scope, irContext);
        irClassType->addStaticMethod(
                keyValue.first,
                std::make_shared<IRFunctionType>(llvm::FunctionType::get(methodReturnType->getType(), methodParameters->getParameterTypes(), false))
        );
    }

    return irClassType;
}

std::shared_ptr<IRClassType> ClassTypeSignatureIRStrategy::generateInitial(std::shared_ptr<ClassTypeSignature> classTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext) {
    auto irClassType = std::make_shared<IRClassType>(
            classTypeSignature->getId(),
            irGenerator->generateIRStructRefType(),
            classTypeSignature->getPreConstructorName()
    );
    irClassType->setId(classTypeSignature->getId());
    irClassType->getClassProperties()->setId(classTypeSignature->getId());
    irClassType->getClassProperties()->getStructIRType()->setId(classTypeSignature->getId());
    scope->insertGlobalType(irClassType->getId(), irClassType);

    return irClassType;
}

std::shared_ptr<IRClassType> ClassTypeSignatureIRStrategy::generatePostInitial(std::shared_ptr<ClassTypeSignature> classTypeSignature, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext) {
    auto irClassType = std::dynamic_pointer_cast<IRClassType>(scope->findGlobalType(classTypeSignature->getId()).value());
    auto constructorReturnType = irGenerator->getVoidType();
    for (auto keyValue : classTypeSignature->getConstructors()->getKeyValues()) {
        auto constructorParameters = classTypeSignature->isClassScopeParameterNecessary()
                                     ? irGenerator->generateParameterList(keyValue.second->getParameterList(), scope, irContext, classTypeSignature->getClassScopeParameter())
                                     : irGenerator->generateParameterList(keyValue.second->getParameterList(), scope, irContext);
        irClassType->addConstructor(
                keyValue.first,
                std::make_shared<IRFunctionType>(llvm::FunctionType::get(constructorReturnType, constructorParameters->getParameterTypes(), false))
        );
    }

    if (classTypeSignature->isClassScopeParameterNecessary()) {
        auto classScopeIRType = irGenerator->generateParameterType(classTypeSignature->getClassScopeParameter(), scope, irContext);
        auto classScopeIRStructRefType = std::dynamic_pointer_cast<IRStructRefType>(classScopeIRType->getIRType()->getSourceType());
        classScopeIRStructRefType->setId(classTypeSignature->getId());
        classScopeIRStructRefType->getStructIRType()->setId(classTypeSignature->getId());
        irClassType->setClassScopeType(classScopeIRType);
        auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { irGenerator->generatePointerType() }, false);
        llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, irClassType->getPreConstructorName(), irContext->getModule());
    }

    return irClassType;
}
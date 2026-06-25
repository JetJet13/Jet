//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_CLASS_TYPE_SIGNATURE_H
#define JETLANG_CLASS_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "../literal-type-signature/types/literal-type.h"
#include "../../lexeme/lexeme.h"
#include "class-property-type-signature/class-property-type-signature.h"
#include "class-method-type-signature/class-method-type-signature.h"
#include "class-constructor-type-signature/class-constructor-type-signature.h"
#include "../types/type-signature-map/type-signature-map.h"
#include "../interface-type-signature/interface-type-signature.h"

class ClassTypeSignature : public TypeSignature {
private:
    TypeSignatureMap<ClassConstructorTypeSignature> _constructors;
    TypeSignatureMap<ClassPropertyTypeSignature> _staticProperties;
    TypeSignatureMap<ClassPropertyTypeSignature> _instanceProperties;
    TypeSignatureMap<ClassMethodTypeSignature> _staticMethods;
    TypeSignatureMap<ClassMethodTypeSignature> _instanceMethods;
    TypeSignatureMap<TypeSignature> _implements;
    TypeSignatureMap<TypeSignature> _interface;
    ParameterListItemTypeSignature* _classScopeParameter;
public:
    ClassTypeSignature();
    ParameterListItemTypeSignature* getClassScopeParameter();
    TypeSignatureMap<ClassConstructorTypeSignature>* getConstructors();
    TypeSignatureMap<ClassPropertyTypeSignature>* getStaticProperties();
    TypeSignatureMap<ClassPropertyTypeSignature>* getInstanceProperties();
    TypeSignatureMap<ClassMethodTypeSignature>* getStaticMethods();
    TypeSignatureMap<ClassMethodTypeSignature>* getInstanceMethods();
    TypeSignatureMap<TypeSignature>* getImplements();
    TypeSignatureMap<TypeSignature>* getInterface();
    ClassTypeSignature* addConstructor(std::string key, ClassConstructorTypeSignature* classConstructorTypeSignature);
    ClassTypeSignature* addProperty(std::string key, ClassPropertyTypeSignature* classPropertyTypeSignature);
    ClassTypeSignature* addMethod(std::string key, ClassMethodTypeSignature* classMethodTypeSignature);
    ClassTypeSignature* addImplementsInterface(std::string key, TypeSignature* interfaceTypeSignature);
    void setClassScopeParameter(ParameterListItemTypeSignature* classScopeParameter);
    bool isClassScopeParameterNecessary();
    bool satisfiesImplementInterfaces();
    std::string getPreConstructorName();
    std::optional<std::pair<std::string, ClassConstructorTypeSignature*>> findConstructorForArguments(std::vector<TypeSignature*>* argumentTypeSignatures);
    std::string addClassNameToKey(std::string key);
    std::string stripClassNameFromKey(std::string key);
    TypeSignature* convertToVariableTypeSignature() override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool hasCircularReferenceWith(ClassTypeSignature* other);
    bool isEquivalentTo(TypeSignature *otherType) override;
    bool isEqualTo(TypeSignature *otherType) override;
    void copyFrom(TypeSignature* otherType) override;
    void print() override;
};

#endif //JETLANG_CLASS_TYPE_SIGNATURE_H

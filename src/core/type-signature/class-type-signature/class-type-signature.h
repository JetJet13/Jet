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

class ClassTypeSignature : public TypeSignature {
private:
    TypeSignatureMap<ClassConstructorTypeSignature> _constructors;
    TypeSignatureMap<ClassPropertyTypeSignature> _properties;
    TypeSignatureMap<ClassMethodTypeSignature> _methods;
    TypeSignatureMap<TypeSignature> _interface;
    ParameterListItemTypeSignature* _classScopeParameter;
public:
    ClassTypeSignature();
    ParameterListItemTypeSignature* getClassScopeParameter();
    TypeSignatureMap<ClassConstructorTypeSignature>* getConstructors();
    TypeSignatureMap<ClassPropertyTypeSignature>* getProperties();
    TypeSignatureMap<ClassMethodTypeSignature>* getMethods();
    TypeSignatureMap<TypeSignature>* getInterface();
    ClassTypeSignature* addConstructor(std::string key, ClassConstructorTypeSignature* classConstructorTypeSignature);
    ClassTypeSignature* addProperty(std::string key, ClassPropertyTypeSignature* classPropertyTypeSignature);
    ClassTypeSignature* addMethod(std::string key, ClassMethodTypeSignature* classMethodTypeSignature);
    void setClassScopeParameter(ParameterListItemTypeSignature* classScopeParameter);
    bool isClassScopeParameterNecessary();
    std::string getPreConstructorName();
    std::optional<std::pair<std::string, ClassConstructorTypeSignature*>> findConstructorForArguments(std::vector<TypeSignature*>* argumentTypeSignatures);
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEquivalentTo(TypeSignature *otherType) override;
    bool isEqualTo(TypeSignature *otherType) override;
    void copyFrom(TypeSignature* otherType) override;
    void print() override;
};

#endif //JETLANG_CLASS_TYPE_SIGNATURE_H

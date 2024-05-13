//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_CLASS_TYPE_SIGNATURE_H
#define JETLANG_CLASS_TYPE_SIGNATURE_H

#include "../type-signature.h"
#include "../literal-type-signature/types/literal-type.h"
#include "../../lexeme/lexeme.h"
#include "../procedure-type-signature/procedure-type-signature.h"
#include "class-property-type-signature/class-property-type-signature.h"
#include "class-method-type-signature/class-method-type-signature.h"
#include "class-constructor-type-signature/class-constructor-type-signature.h"
#include "../types/type-signature-map/type-signature-map.h"

class ClassTypeSignature : public TypeSignature {
private:
    TypeSignatureMap<ClassConstructorTypeSignature> _constructors;
    TypeSignatureMap<ClassPropertyTypeSignature> _properties;
    TypeSignatureMap<ClassMethodTypeSignature> _methods;
public:
    ClassTypeSignature();
    TypeSignatureMap<ClassConstructorTypeSignature>* getConstructors();
    TypeSignatureMap<ClassPropertyTypeSignature>* getProperties();
    TypeSignatureMap<ClassMethodTypeSignature>* getMethods();
    void addConstructor(std::string key, ClassConstructorTypeSignature* classConstructorTypeSignature);
    void addProperty(std::string key, ClassPropertyTypeSignature* classPropertyTypeSignature);
    void addMethod(std::string key, ClassMethodTypeSignature* classMethodTypeSignature);
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_CLASS_TYPE_SIGNATURE_H

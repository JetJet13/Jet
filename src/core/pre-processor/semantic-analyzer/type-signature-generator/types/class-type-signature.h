//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_CLASS_TYPE_SIGNATURE_H
#define JETLANG_CLASS_TYPE_SIGNATURE_H

#include "type-signature.h"
#include "type.h"
#include "../../../../lexeme/lexeme.h"
#include "procedure-type-signature.h"
#include "class-property-type-signature.h"
#include "class-method-type-signature.h"
#include "type-signature-map.h"

class ClassTypeSignature : public TypeSignature {
private:
    std::string _name;
    TypeSignatureMap<ProcedureTypeSignature> _constructors;
    TypeSignatureMap<ClassPropertyTypeSignature> _properties;
    TypeSignatureMap<ClassMethodTypeSignature> _methods;
public:
    ClassTypeSignature(std::string name);
    std::string getName();
    TypeSignatureMap<ProcedureTypeSignature>* getConstructors();
    TypeSignatureMap<ClassPropertyTypeSignature>* getProperties();
    TypeSignatureMap<ClassMethodTypeSignature>* getMethods();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_CLASS_TYPE_SIGNATURE_H

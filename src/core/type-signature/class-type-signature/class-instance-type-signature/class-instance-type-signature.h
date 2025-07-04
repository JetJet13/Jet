//
// Created by Johny Georges on 2024-05-15.
//

#ifndef JETLANG_CLASS_INSTANCE_TYPE_SIGNATURE_H
#define JETLANG_CLASS_INSTANCE_TYPE_SIGNATURE_H

#include "../../type-signature.h"
#include "../class-type-signature.h"

class ClassInstanceTypeSignature : public TypeSignature {
private:
    std::optional<ClassTypeSignature*> _classTypeSignature;
    std::optional<std::pair<std::string, ClassConstructorTypeSignature*>> _constructorInfo;
public:
    ClassInstanceTypeSignature();
    ClassInstanceTypeSignature(ClassTypeSignature* classTypeSignature, std::optional<std::pair<std::string, ClassConstructorTypeSignature*>> constructorInfo = {});
    ClassTypeSignature* getClassTypeSignature();
    TypeSignatureMap<TypeSignature>* getClassInterface();
    ClassConstructorTypeSignature* getConstructorTypeSignature();
    bool hasConstructorInfo();
    std::string getConstructorId();
    void setConstructorInfo(std::pair<std::string, ClassConstructorTypeSignature*> constructorInfo);
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEquivalentTo(TypeSignature *otherType) override;
    bool isEqualTo(TypeSignature *otherType) override;
    bool isInvalid() override;
    void print() override;
};


#endif //JETLANG_CLASS_INSTANCE_TYPE_SIGNATURE_H

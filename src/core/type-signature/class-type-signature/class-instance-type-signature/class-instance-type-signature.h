//
// Created by Johny Georges on 2025-12-26.
//

#ifndef JETLANG_CLASS_INSTANCE_TYPE_SIGNATURE_H
#define JETLANG_CLASS_INSTANCE_TYPE_SIGNATURE_H

#include "../../types/type-signature-map/type-signature-map.h"
#include "../../aggregate-type-signature.h"
#include "../class-type-signature.h"

class ClassInstanceTypeSignature : public AggregateTypeSignature<TypeSignature> {
private:
    ClassTypeSignature* _class;
public:
    ClassInstanceTypeSignature();
    ClassInstanceTypeSignature(ClassTypeSignature* classTypeSignature);
    bool isEmpty();
    TypeSignatureMap<ClassPropertyTypeSignature>* getProperties();
    TypeSignatureMap<TypeSignature>* getKeyValuePairs() override;
    TypeSignature* getTypeSignatureForKey(std::string key) override;
    TypeSignature* getTypeSignatureAtIndex(unsigned long index) override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    bool isEquivalentTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_CLASS_INSTANCE_TYPE_SIGNATURE_H

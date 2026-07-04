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
    std::shared_ptr<ClassTypeSignature> _class;
public:
    ClassInstanceTypeSignature();
    ClassInstanceTypeSignature(std::shared_ptr<ClassTypeSignature> classTypeSignature);
    bool isEmpty();
    std::string getClassModuleId();
    std::shared_ptr<ClassTypeSignature> getClass();
    TypeSignatureMap<std::shared_ptr<ClassPropertyTypeSignature>>* getProperties();
    TypeSignatureMap<std::shared_ptr<TypeSignature>>* getKeyValuePairs() override;
    std::shared_ptr<TypeSignature> getTypeSignatureForKey(std::string key) override;
    std::shared_ptr<TypeSignature> getTypeSignatureAtIndex(unsigned long index) override;
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_CLASS_INSTANCE_TYPE_SIGNATURE_H

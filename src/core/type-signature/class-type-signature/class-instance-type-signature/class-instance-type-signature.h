//
// Created by Johny Georges on 2024-05-15.
//

#ifndef JETLANG_CLASS_INSTANCE_TYPE_SIGNATURE_H
#define JETLANG_CLASS_INSTANCE_TYPE_SIGNATURE_H

#include "../../type-signature.h"
#include "../class-type-signature.h"

class ClassInstanceTypeSignature : public TypeSignature {
private:
    ClassTypeSignature* _classTypeSignature;
public:
    ClassInstanceTypeSignature(ClassTypeSignature* classTypeSignature);
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};


#endif //JETLANG_CLASS_INSTANCE_TYPE_SIGNATURE_H

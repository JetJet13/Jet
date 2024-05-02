//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_LITERAL_TYPE_SIGNATURE_H
#define JETLANG_LITERAL_TYPE_SIGNATURE_H

#include "type-signature.h"
#include "type.h"

class LiteralTypeSignature : public TypeSignature {
private:
    Type _coreType;
public:
    LiteralTypeSignature(Type type);
    Type getType();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_LITERAL_TYPE_SIGNATURE_H

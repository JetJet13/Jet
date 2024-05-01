//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_CLASS_TYPE_SIGNATURE_H
#define JETLANG_CLASS_TYPE_SIGNATURE_H

#include "type-signature.h"
#include "type.h"
#include "../../../../lexeme/lexeme.h"

class ClassTypeSignature : public TypeSignature {
private:
    Lexeme* _className;
public:
    ClassTypeSignature(Lexeme* className);
    Lexeme* getName();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_CLASS_TYPE_SIGNATURE_H

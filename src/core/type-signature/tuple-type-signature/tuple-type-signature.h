//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_TUPLE_TYPE_SIGNATURE_H
#define JETLANG_TUPLE_TYPE_SIGNATURE_H

#include <vector>
#include "../type-signature.h"

class TupleTypeSignature : public TypeSignature {
private:
    std::vector<TypeSignature*>* _elementTypes;
public:
    explicit TupleTypeSignature(std::vector<TypeSignature*>* elementTypes);
    explicit TupleTypeSignature(std::vector<TypeSignature*> elementTypes);
    std::vector<TypeSignature*>* getElementTypes();
    TypeSignature* getTypeSignatureAtIndex(unsigned long index);
    unsigned long size();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_TUPLE_TYPE_SIGNATURE_H

//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_TUPLE_TYPE_SIGNATURE_H
#define JETLANG_TUPLE_TYPE_SIGNATURE_H

#include <vector>
#include "../aggregate-type-signature.h"
#include "../types/type-signature-map/type-signature-map.h"

class TupleTypeSignature : public AggregateTypeSignature<TypeSignature> {
private:
    TypeSignatureMap<TypeSignature> _keyValuePairs;
public:
    TupleTypeSignature();
    explicit TupleTypeSignature(std::vector<TypeSignature*>* elementTypes);
    explicit TupleTypeSignature(std::vector<TypeSignature*> elementTypes);
    TypeSignatureMap<TypeSignature>* getKeyValuePairs() override;
    TypeSignature* getTypeSignatureForKey(std::string key) override;
    TypeSignature* getTypeSignatureAtIndex(unsigned long index) override;
    unsigned long size();
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_TUPLE_TYPE_SIGNATURE_H

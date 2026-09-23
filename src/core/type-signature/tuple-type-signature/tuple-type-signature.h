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
    TypeSignatureMap<std::shared_ptr<TypeSignature>> _keyValuePairs;
public:
    TupleTypeSignature();
    explicit TupleTypeSignature(std::vector<std::shared_ptr<TypeSignature>>* elementTypes);
    explicit TupleTypeSignature(std::vector<std::shared_ptr<TypeSignature>> elementTypes);
    TypeSignatureMap<std::shared_ptr<TypeSignature>>* getKeyValuePairs() override;
    std::shared_ptr<TypeSignature> getTypeSignatureForKey(std::string key) override;
    std::shared_ptr<TypeSignature> getTypeSignatureAtIndex(uint64_t index) override;
    uint64_t size();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_TUPLE_TYPE_SIGNATURE_H

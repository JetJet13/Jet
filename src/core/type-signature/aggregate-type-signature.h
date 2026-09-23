//
// Created by Johny Georges on 2024-07-26.
//

#ifndef JETLANG_AGGREGATE_TYPE_SIGNATURE_H
#define JETLANG_AGGREGATE_TYPE_SIGNATURE_H

#include "type-signature.h"
#include "./types/type-signature-map/type-signature-map.h"

template<class T = TypeSignature>
class AggregateTypeSignature : public TypeSignature {
public:
    virtual TypeSignatureMap<std::shared_ptr<T>>* getKeyValuePairs() = 0;
    virtual std::shared_ptr<T> getTypeSignatureForKey(std::string key) = 0;
    virtual std::shared_ptr<T> getTypeSignatureAtIndex(uint64_t index) = 0;
};

#endif //JETLANG_AGGREGATE_TYPE_SIGNATURE_H

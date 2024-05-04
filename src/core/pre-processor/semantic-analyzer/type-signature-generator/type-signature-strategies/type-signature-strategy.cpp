//
// Created by Johny Georges on 2024-05-04.
//

#include "type-signature-strategy.h"

template<class T>
TypeSignatureStrategy<T>::TypeSignatureStrategy(TokenTable* tokenTable) {
    _tokenTable = tokenTable;
}
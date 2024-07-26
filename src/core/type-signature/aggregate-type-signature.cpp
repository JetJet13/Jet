//
// Created by Johny Georges on 2024-07-26.
//

#include "aggregate-type-signature.h"
#include "literal-type-signature/literal-type-signature.h"

template class AggregateTypeSignature<LiteralTypeSignature>;
template class AggregateTypeSignature<TypeSignature>;
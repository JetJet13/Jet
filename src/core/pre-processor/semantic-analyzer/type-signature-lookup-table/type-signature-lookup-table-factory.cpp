//
// Created by Johny Georges on 2025-07-25.
//

#include "type-signature-lookup-table-factory.h"
#include "../jet-utils-type-signature-map/jet-utils-type-signature-map.h"

TypeSignatureLookupTable* TypeSignatureLookupTableFactory::createForModule() {
    auto typeSignatureLookupTable = new TypeSignatureLookupTable();
    typeSignatureLookupTable->insertGlobal(
        JetUtilsTypeSignatureMap::getPrintTypeSignatureKey(),
        JetUtilsTypeSignatureMap::getPrintTypeSignature()
    );
    typeSignatureLookupTable->insertGlobal(
        JetUtilsTypeSignatureMap::getRangeTypeSignatureKey(),
        JetUtilsTypeSignatureMap::getRangeTypeSignature()
    );
    return typeSignatureLookupTable;
}


TypeSignatureLookupTable* TypeSignatureLookupTableFactory::create() {
    return new TypeSignatureLookupTable();
}
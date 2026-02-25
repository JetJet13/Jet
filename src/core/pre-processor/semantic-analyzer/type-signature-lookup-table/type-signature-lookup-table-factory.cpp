//
// Created by Johny Georges on 2025-07-25.
//

#include "type-signature-lookup-table-factory.h"
#include "../jet-utils-type-signature-map/jet-utils-type-signature-map.h"
#include "../jet-debug-type-signature-map/jet-debug-type-signature-map.h"

TypeSignatureLookupTable* TypeSignatureLookupTableFactory::createForModule() {
    auto typeSignatureLookupTable = new TypeSignatureLookupTable();

    typeSignatureLookupTable->insertGlobalFunctionOverride(
        JetUtilsTypeSignatureMap::getPrintTypeSignatureMap()
    );
    typeSignatureLookupTable->insertGlobal(
        JetUtilsTypeSignatureMap::getRangeTypeSignatureKey(),
        JetUtilsTypeSignatureMap::getRangeTypeSignature()
    );
    typeSignatureLookupTable->insertGlobal(
            JetUtilsTypeSignatureMap::getRange2pTypeSignatureKey(),
            JetUtilsTypeSignatureMap::getRange2pTypeSignature()
    );
    typeSignatureLookupTable->insertGlobal(
            JetUtilsTypeSignatureMap::getRange3pTypeSignatureKey(),
            JetUtilsTypeSignatureMap::getRange3pTypeSignature()
    );
    typeSignatureLookupTable->insertGlobal(
            JetUtilsTypeSignatureMap::getAssertTypeSignatureKey(),
            JetUtilsTypeSignatureMap::getAssertTypeSignature()
    );
    typeSignatureLookupTable->insertGlobal(
            JetUtilsTypeSignatureMap::getAssertWithMessageTypeSignatureKey(),
            JetUtilsTypeSignatureMap::getAssertWithMessageTypeSignature()
    );
    return typeSignatureLookupTable;
}

TypeSignatureLookupTable* TypeSignatureLookupTableFactory::createForDebugModule() {
    auto typeSignatureLookupTable = TypeSignatureLookupTableFactory::createForModule();
    typeSignatureLookupTable->insertGlobal(
            JetDebugTypeSignatureMap::getAssertDebugRefCountTypeSignatureKey(),
            JetDebugTypeSignatureMap::getAssertDebugRefCountTypeSignature()
    );
    typeSignatureLookupTable->insertGlobal(
            JetDebugTypeSignatureMap::getAssertDebugStructRefCountTypeSignatureKey(),
            JetDebugTypeSignatureMap::getAssertDebugStructRefCountTypeSignature()
    );
    typeSignatureLookupTable->insertGlobal(
            JetDebugTypeSignatureMap::getAssertDebugTupleRefCountTypeSignatureKey(),
            JetDebugTypeSignatureMap::getAssertDebugTupleRefCountTypeSignature()
    );
    typeSignatureLookupTable->insertGlobal(
            JetDebugTypeSignatureMap::getAssertDebugClassRefCountTypeSignatureKey(),
            JetDebugTypeSignatureMap::getAssertDebugClassRefCountTypeSignature()
    );
    typeSignatureLookupTable->insertGlobal(
            JetDebugTypeSignatureMap::getAssertDebugLambdaRefCountTypeSignatureKey(),
            JetDebugTypeSignatureMap::getAssertDebugLambdaRefCountTypeSignature()
    );
    return typeSignatureLookupTable;
}


TypeSignatureLookupTable* TypeSignatureLookupTableFactory::create() {
    return new TypeSignatureLookupTable();
}
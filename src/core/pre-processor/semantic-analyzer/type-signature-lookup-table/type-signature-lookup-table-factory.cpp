//
// Created by Johny Georges on 2025-07-25.
//

#include "type-signature-lookup-table-factory.h"
#include "../jet-utils-type-signature-map/jet-utils-type-signature-map.h"
#include "../jet-debug-type-signature-map/jet-debug-type-signature-map.h"

std::shared_ptr<TypeSignatureLookupTable> TypeSignatureLookupTableFactory::createForModule(std::string moduleName) {
    auto typeSignatureLookupTable = std::make_shared<TypeSignatureLookupTable>(moduleName);

    typeSignatureLookupTable->insertGlobalFunctionOverride(
        JetUtilsTypeSignatureMap::getPrintTypeSignatureMap()
    );
    typeSignatureLookupTable->insertGlobalInvocable(
        JetUtilsTypeSignatureMap::getRangeTypeSignatureKey(),
        JetUtilsTypeSignatureMap::getRangeTypeSignature()
    );
    typeSignatureLookupTable->insertGlobalInvocable(
            JetUtilsTypeSignatureMap::getRange2pTypeSignatureKey(),
            JetUtilsTypeSignatureMap::getRange2pTypeSignature()
    );
    typeSignatureLookupTable->insertGlobalInvocable(
            JetUtilsTypeSignatureMap::getRange3pTypeSignatureKey(),
            JetUtilsTypeSignatureMap::getRange3pTypeSignature()
    );
    typeSignatureLookupTable->insertGlobalInvocable(
            JetUtilsTypeSignatureMap::getAssertTypeSignatureKey(),
            JetUtilsTypeSignatureMap::getAssertTypeSignature()
    );
    typeSignatureLookupTable->insertGlobalInvocable(
            JetUtilsTypeSignatureMap::getAssertWithMessageTypeSignatureKey(),
            JetUtilsTypeSignatureMap::getAssertWithMessageTypeSignature()
    );
    return typeSignatureLookupTable;
}

std::shared_ptr<TypeSignatureLookupTable> TypeSignatureLookupTableFactory::createForDebugModule(std::string moduleName) {
    auto typeSignatureLookupTable = TypeSignatureLookupTableFactory::createForModule(moduleName);
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


std::shared_ptr<TypeSignatureLookupTable> TypeSignatureLookupTableFactory::create() {
    return std::make_shared<TypeSignatureLookupTable>();
}
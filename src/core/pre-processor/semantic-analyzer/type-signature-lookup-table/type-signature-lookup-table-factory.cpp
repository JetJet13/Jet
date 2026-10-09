// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
//
// Created by Johny Georges on 2025-07-25.
//

#ifndef JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_FACTORY_H
#define JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_FACTORY_H

#include "type-signature-lookup-table.h"

class TypeSignatureLookupTableFactory {
public:
    static std::shared_ptr<TypeSignatureLookupTable> createForModule(std::string moduleName = "");
    static std::shared_ptr<TypeSignatureLookupTable> createForDebugModule(std::string moduleName = "");
    static std::shared_ptr<TypeSignatureLookupTable> create();
};

#endif //JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_FACTORY_H

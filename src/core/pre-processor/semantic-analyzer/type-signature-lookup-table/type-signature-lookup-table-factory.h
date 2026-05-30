//
// Created by Johny Georges on 2025-07-25.
//

#ifndef JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_FACTORY_H
#define JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_FACTORY_H

#include "type-signature-lookup-table.h"

class TypeSignatureLookupTableFactory {
public:
    static TypeSignatureLookupTable* createForModule(std::string moduleName = "");
    static TypeSignatureLookupTable* createForDebugModule(std::string moduleName = "");
    static TypeSignatureLookupTable* create();
};

#endif //JETLANG_TYPE_SIGNATURE_LOOKUP_TABLE_FACTORY_H

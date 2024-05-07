//
// Created by Johny Georges on 2024-05-06.
//

#include "type-source-whitelist.h"
#include <utility>

TypeSourceWhitelist::TypeSourceWhitelist(std::vector<TypeSource> whitelist) {
    _whitelist = std::move(whitelist);
}

bool TypeSourceWhitelist::hasTypeSource(TypeSource typeSource) {
    for (auto whitelistedTypeSource : _whitelist) {
        if (whitelistedTypeSource == typeSource) {
            return true;
        }
    }

    return false;
}
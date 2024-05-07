//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_TYPE_SOURCE_WHITELIST_H
#define JETLANG_TYPE_SOURCE_WHITELIST_H

#include <vector>
#include "../../../../../type-signature/types/type-source.h"

class TypeSourceWhitelist {
private:
    std::vector<TypeSource> _whitelist;
public:
    TypeSourceWhitelist(std::vector<TypeSource> whitelist);
    bool hasTypeSource(TypeSource typeSource);
};

#endif //JETLANG_TYPE_SOURCE_WHITELIST_H

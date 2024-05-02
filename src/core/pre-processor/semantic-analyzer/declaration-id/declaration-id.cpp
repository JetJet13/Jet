//
// Created by Johny Georges on 2024-05-01.
//

#include "declaration-id.h"


DeclarationId::DeclarationId(std::string id) {
    _id = id;
}

std::string DeclarationId::getId() {
    return _id;
}
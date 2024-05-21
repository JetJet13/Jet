//
// Created by Johny Georges on 2024-05-20.
//

#include "type-checker.h"

TypeChecker::TypeChecker() {
    traverser = ASTTraverser();
}

TypeCheckerResult TypeChecker::check(ASTNode* rootNode, TypeSignatureLookupTable* scope) {
    auto errors = std::vector<std::string>();
    traverser.init(rootNode);
    auto node = traverser.next();
    while (node) {

        node = traverser.next();
    }


    return {
        .ok =  errors.empty(),
        .errors =  errors
    };
}
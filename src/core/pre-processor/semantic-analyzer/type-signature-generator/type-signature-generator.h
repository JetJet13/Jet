//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_TYPE_SIGNATURE_GENERATOR_H
#define JETLANG_TYPE_SIGNATURE_GENERATOR_H

#include "../../../token/token-table.h"
#include "../../../type-signature/type-signature.h"
#include "../../../ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../../ast/ast-nodes/ast-expression-nodes/ast-this-expression-node.h"
#include "../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "../../../ast/ast-nodes/ast-expression-nodes/ast-class-property-access-expression-node.h"

class TypeSignatureGenerator {
private:
    TokenTable* _tokenTable;
public:
    TypeSignatureGenerator(TokenTable* tokenTable);
};
#endif //JETLANG_TYPE_SIGNATURE_GENERATOR_H

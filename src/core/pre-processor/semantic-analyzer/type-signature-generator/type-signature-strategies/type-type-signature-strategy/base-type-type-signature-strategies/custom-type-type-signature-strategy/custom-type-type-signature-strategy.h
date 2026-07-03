//
// Created by Johny Georges on 2024-05-09.
//

#ifndef JETLANG_CUSTOM_TYPE_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CUSTOM_TYPE_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../ast/ast-nodes/ast-type-nodes/ast-custom-type-node.h"
#include "../../../../../type-signature-lookup-table/type-signature-lookup-table.h"

class CustomTypeTypeSignatureStrategy {
public:
    void assign(ASTCustomTypeNode* node, std::shared_ptr<TypeSignatureLookupTable> typeSignatureLookupTable);
};

#endif //JETLANG_CUSTOM_TYPE_TYPE_SIGNATURE_STRATEGY_H

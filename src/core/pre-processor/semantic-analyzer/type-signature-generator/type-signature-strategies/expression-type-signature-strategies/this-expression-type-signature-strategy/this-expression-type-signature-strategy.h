//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_THIS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_THIS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-this-expression-node.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"

class ThisExpressionTypeSignatureStrategy {
public:
    void assign(ASTThisExpressionNode* thisExpression, std::shared_ptr<TypeSignatureLookupTable> typeSignatureLookupTable);
};

#endif //JETLANG_THIS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

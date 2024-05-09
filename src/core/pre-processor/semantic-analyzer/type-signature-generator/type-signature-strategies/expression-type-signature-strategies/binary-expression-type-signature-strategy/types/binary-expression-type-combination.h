//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_BINARY_EXPRESSION_TYPE_COMBINATION_H
#define JETLANG_BINARY_EXPRESSION_TYPE_COMBINATION_H

#include "../../../../../../../type-signature/types/type-source.h"
#include "../../../../../../../symbol/types/symbol-type.h"
#include "../../../../../../../ast/ast-nodes/ast-expression-nodes/ast-binary-expression-node.h"
#include "../../../../../../../type-signature/type-signature.h"

struct BinaryComboResultType;

class BinaryExpressionTypeCombination {
private:
    Symbol* _operatorSymbol;
    std::vector<BinaryComboResultType> _binaryResultTypes;
public:
    BinaryExpressionTypeCombination(Symbol* operatorSymbol, std::vector<BinaryComboResultType> binaryResultTypes);
    Symbol* getOperator();
    std::optional<TypeSignature*> match(TypeSignature* leftTypeSignature, TypeSignature* rightTypeSignature);
};

struct BinaryComboResultType {
    TypeSource leftType;
    TypeSource rightType;
    TypeSignature* resultType;
};

#endif //JETLANG_BINARY_EXPRESSION_TYPE_COMBINATION_H

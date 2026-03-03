//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_BINARY_EXPRESSION_TYPE_COMBINATION_H
#define JETLANG_BINARY_EXPRESSION_TYPE_COMBINATION_H

#include "../../../../../../../type-signature/types/type-source.h"
#include "../../../../../../../symbol/types/symbol-type.h"
#include "../../../../../../../ast/ast-nodes/ast-expression-nodes/ast-binary-arithmetic-expression-node.h"
#include "../../../../../../../type-signature/type-signature.h"

struct BinaryComboResultType;

class BinaryExpressionTypeCombination {
private:
    std::shared_ptr<Symbol> _operatorSymbol;
    std::vector<BinaryComboResultType> _binaryResultTypes;
public:
    BinaryExpressionTypeCombination(std::shared_ptr<Symbol> operatorSymbol, std::vector<BinaryComboResultType> binaryResultTypes);
    std::shared_ptr<Symbol> getOperator();
    std::optional<TypeSignature*> match(TypeSignature* leftTypeSignature, TypeSignature* rightTypeSignature);
};

struct BinaryComboResultType {
    TypeSource leftType;
    TypeSource rightType;
    TypeSignature* resultType;
};

#endif //JETLANG_BINARY_EXPRESSION_TYPE_COMBINATION_H

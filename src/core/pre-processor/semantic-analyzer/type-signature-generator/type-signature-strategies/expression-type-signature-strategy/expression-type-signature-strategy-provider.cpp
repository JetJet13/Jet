//
// Created by Johny Georges on 2024-05-06.
//

#include "expression-type-signature-strategy-provider.h"

ExpressionTypeSignatureStrategyProvider::ExpressionTypeSignatureStrategyProvider(TypeSignatureLookupTable* typeSignatureLookupTable) {
    _expressionTypeSignatureStrategyMap = new ExpressionTypeSignatureStrategyMap();
    _typeSignatureLookupTable = typeSignatureLookupTable;
}

TypeSignature*  ExpressionTypeSignatureStrategyProvider::getTypeSignatureForExpression(ASTNode* node) {
    switch (node->getNodeType()) {
        case AST_BINARY_EXPRESSION_NODE:
            return this->_expressionTypeSignatureStrategyMap
                       ->getBinaryExpressionTypeSignatureStrategy()
                       ->create((ASTBinaryExpressionNode*)node, this);
        default:
            throw std::invalid_argument("unable to locate expression type signature strategy for given ast node type");
    }
}
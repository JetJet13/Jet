//
// Created by Johny Georges on 2024-04-05.
//

#include "ast-type-node-factory.h"

namespace ASTTypeNodeFactory {
    ASTTypeNode* createCustomTypeNode(ASTIdentifierNode* identifierNode) {
        return new ASTTypeNode(new ASTCustomTypeNode(identifierNode));
    }

    ASTTypeNode* createPrimitiveTypeNode(Lexeme* lexeme) {
        return new ASTTypeNode(new ASTPrimitiveTypeNode(lexeme));
    }

    ASTTypeNode* createLambdaTypeNode(ASTLambdaTypeNode* lambdaTypeNode) {
        return new ASTTypeNode(lambdaTypeNode);
    }
}
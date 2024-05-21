//
// Created by Johny Georges on 2024-04-05.
//

#include "ast-type-node-factory.h"
#include "ast-this-type-node.h"

namespace ASTTypeNodeFactory {
    ASTTypeNode* createCustomTypeNode(Lexeme* lexeme) {
        return new ASTTypeNode(new ASTCustomTypeNode(lexeme));
    }

    ASTTypeNode* createCustomTypeNode(Lexeme* lexeme, std::string id) {
        return new ASTTypeNode(new ASTCustomTypeNode(lexeme, id));
    }

    ASTTypeNode* createPrimitiveTypeNode(Lexeme* lexeme) {
        return new ASTTypeNode(new ASTPrimitiveTypeNode(lexeme));
    }

    ASTTypeNode* createLambdaTypeNode(ASTLambdaTypeNode* lambdaTypeNode) {
        return new ASTTypeNode(lambdaTypeNode);
    }

    ASTTypeNode* createTupleTypeNode(ASTTupleTypeNode* tupleTypeNode) {
        return new ASTTypeNode(tupleTypeNode);
    }

    ASTTypeNode* createArrayTypeNode(ASTArrayTypeNode* arrayTypeNode) {
        return new ASTTypeNode(arrayTypeNode);
    }

    ASTTypeNode* createThisTypeNode(ASTThisNode* thisNode) {
        return new ASTTypeNode(new ASTThisTypeNode(thisNode));
    }
}
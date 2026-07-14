//
// Created by Johny Georges on 2024-04-05.
//

#include "ast-type-node-factory.h"
#include "ast-this-type-node.h"

namespace ASTTypeNodeFactory {

    std::shared_ptr<ASTTypeNode> createCustomTypeNode(std::shared_ptr<Lexeme> lexeme, std::string id) {
        return std::make_shared<ASTTypeNode>(std::make_shared<ASTCustomTypeNode>(lexeme, id));
    }

    std::shared_ptr<ASTTypeNode> createPrimitiveTypeNode(std::shared_ptr<Lexeme> lexeme) {
        return std::make_shared<ASTTypeNode>(std::make_shared<ASTPrimitiveTypeNode>(lexeme));
    }

    std::shared_ptr<ASTTypeNode> createLambdaTypeNode(std::shared_ptr<ASTLambdaTypeNode> lambdaTypeNode) {
        return std::make_shared<ASTTypeNode>(lambdaTypeNode);
    }

    std::shared_ptr<ASTTypeNode> createTupleTypeNode(std::shared_ptr<ASTTupleTypeNode> tupleTypeNode) {
        return std::make_shared<ASTTypeNode>(tupleTypeNode);
    }

    std::shared_ptr<ASTTypeNode> createArrayTypeNode(std::shared_ptr<ASTArrayTypeNode> arrayTypeNode) {
        return std::make_shared<ASTTypeNode>(arrayTypeNode);
    }

    std::shared_ptr<ASTTypeNode> createStructTypeNode(std::shared_ptr<ASTStructTypeNode> structTypeNode) {
        return std::make_shared<ASTTypeNode>(structTypeNode);
    }

    std::shared_ptr<ASTTypeNode> createRefTypeNode(std::shared_ptr<ASTRefTypeNode> refTypeNode) {
        return std::make_shared<ASTTypeNode>(refTypeNode);
    }

    std::shared_ptr<ASTTypeNode> createSharedTypeNode(std::shared_ptr<ASTSharedTypeNode> sharedTypeNode) {
        return std::make_shared<ASTTypeNode>(sharedTypeNode);
    }

    std::shared_ptr<ASTTypeNode> createModuleTypeNode(std::shared_ptr<ASTModuleTypeNode> moduleTypeNode) {
        return std::make_shared<ASTTypeNode>(moduleTypeNode);
    }

    std::shared_ptr<ASTTypeNode> createThisTypeNode(std::shared_ptr<ASTThisNode> thisNode) {
        return std::make_shared<ASTTypeNode>(std::make_shared<ASTThisTypeNode>(thisNode));
    }

    std::shared_ptr<ASTTypeNode> createVoidTypeNode(std::shared_ptr<ASTVoidNode> voidNode) {
        return std::make_shared<ASTTypeNode>(std::make_shared<ASTVoidTypeNode>(voidNode));
    }
}
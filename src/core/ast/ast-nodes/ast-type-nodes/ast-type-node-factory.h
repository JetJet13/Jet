//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_TYPE_NODE_FACTORY_H
#define JETLANG_AST_TYPE_NODE_FACTORY_H

#include "ast-type-node.h"
#include "ast-custom-type-node.h"
#include "ast-primitive-type-node.h"
#include "ast-array-type-nodes/ast-array-type-node.h"
#include "../ast-class-nodes/ast-this-node.h"
#include "ast-ref-type-node.h"
#include "ast-struct-type-nodes/ast-struct-type-node.h"
#include "ast-lambda-type-nodes/ast-lambda-type-node.h"
#include "ast-void-type-node.h"
#include "../ast-void-node.h"
#include "ast-tuple-type-nodes/ast-tuple-type-node.h"
#include "ast-module-type-nodes/ast-module-type-node.h"

namespace ASTTypeNodeFactory {
    std::shared_ptr<ASTTypeNode> createCustomTypeNode(std::shared_ptr<Lexeme> lexeme, std::string id);
    std::shared_ptr<ASTTypeNode> createPrimitiveTypeNode(std::shared_ptr<Lexeme> lexeme);
    std::shared_ptr<ASTTypeNode> createLambdaTypeNode(std::shared_ptr<ASTLambdaTypeNode> lambdaTypeNode);
    std::shared_ptr<ASTTypeNode> createTupleTypeNode(std::shared_ptr<ASTTupleTypeNode> tupleTypeNode);
    std::shared_ptr<ASTTypeNode> createArrayTypeNode(std::shared_ptr<ASTArrayTypeNode> arrayTypeNode);
    std::shared_ptr<ASTTypeNode> createStructTypeNode(std::shared_ptr<ASTStructTypeNode> structTypeNode);
    std::shared_ptr<ASTTypeNode> createRefTypeNode(std::shared_ptr<ASTRefTypeNode> refTypeNode);
    std::shared_ptr<ASTTypeNode> createModuleTypeNode(std::shared_ptr<ASTModuleTypeNode> moduleTypeNode);
    std::shared_ptr<ASTTypeNode> createThisTypeNode(std::shared_ptr<ASTThisNode> thisNode);
    std::shared_ptr<ASTTypeNode> createVoidTypeNode(std::shared_ptr<ASTVoidNode> voidNode);
}

#endif //JETLANG_AST_TYPE_NODE_FACTORY_H

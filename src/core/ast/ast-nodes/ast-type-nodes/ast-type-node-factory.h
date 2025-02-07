//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_TYPE_NODE_FACTORY_H
#define JETLANG_AST_TYPE_NODE_FACTORY_H

#include "ast-type-node.h"
#include "ast-custom-type-node.h"
#include "ast-primitive-type-node.h"
#include "ast-lambda-type-node.h"
#include "ast-tuple-type-node.h"
#include "ast-array-type-node.h"
#include "../ast-class-nodes/ast-this-node.h"
#include "ast-procedure-type-node.h"
#include "ast-function-type-node.h"
#include "ast-ref-type-node.h"

namespace ASTTypeNodeFactory {
    ASTTypeNode* createCustomTypeNode(Lexeme* lexeme, std::string id);
    ASTTypeNode* createPrimitiveTypeNode(Lexeme* lexeme);
    ASTTypeNode* createLambdaTypeNode(ASTLambdaTypeNode* lambdaTypeNode);
    ASTTypeNode* createProcedureTypeNode(ASTProcedureTypeNode* procedureTypeNode);
    ASTTypeNode* createFunctionTypeNode(ASTFunctionTypeNode* functionTypeNode);
    ASTTypeNode* createTupleTypeNode(ASTTupleTypeNode* tupleTypeNode);
    ASTTypeNode* createArrayTypeNode(ASTArrayTypeNode* arrayTypeNode);
    ASTTypeNode* createRefTypeNode(ASTRefTypeNode* refTypeNode);
    ASTTypeNode* createThisTypeNode(ASTThisNode* thisNode);
}

#endif //JETLANG_AST_TYPE_NODE_FACTORY_H

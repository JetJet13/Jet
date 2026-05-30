//
// Created by Johny Georges on 2025-08-02.
//

#ifndef JETLANG_FUNCTION_ID_GENERATOR_H
#define JETLANG_FUNCTION_ID_GENERATOR_H

#include <string>
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-function-invocation-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-class-method-declaration-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-object-access-invocation-expression-node.h"

class FunctionIdGenerator {
public:
    static std::string getNameFromId(std::string functionId);
    static std::string generateFor(ASTClassMethodDeclarationNode* classMethodDeclarationNode);
    static std::string generateFor(ASTFunctionDeclarationNode* functionDeclarationNode);
    static std::string generateFor(ASTProcedureDeclarationNode* procedureDeclarationNode);
    static std::string generateFor(ASTFunctionInvocationExpressionNode* functionInvocationExpressionNode);
    static std::string generateFor(ASTObjectAccessInvocationExpressionNode* objectAccessInvocationExpressionNode);
    static std::string generateFor(std::string name, InvocableTypeSignature* invocableTypeSignature);
    static std::string generateFor(std::string moduleId, std::string name, InvocableTypeSignature* invocableTypeSignature);
    static std::string generateFor(InvocableTypeSignature* invocableTypeSignature);
    static std::string generateFor(std::string functionName, std::string parameterDetailString);
};

#endif //JETLANG_FUNCTION_ID_GENERATOR_H

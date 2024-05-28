//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_CLASS_DECLARATION_TYPE_CHECKER_POLICY_H
#define JETLANG_CLASS_DECLARATION_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"

class ClassDeclarationTypeCheckerPolicy {
private:
    static void verifyAllClassProperties(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult);
    static void verifyClassPropertiesWithInitializer(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult);
    static void verifyAllClassPropertyNamesAreUnique(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult);
    static void verifyAllClassMethods(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult);
    static void verifyAllClassMethodsAreUnique(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult);
    static void verifyAllClassConstructors(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult);
    static void verifyAllClassConstructorsAreUnique(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult);
public:
    static void apply(ASTClassDeclarationNode* classDeclarationNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_CLASS_DECLARATION_TYPE_CHECKER_POLICY_H

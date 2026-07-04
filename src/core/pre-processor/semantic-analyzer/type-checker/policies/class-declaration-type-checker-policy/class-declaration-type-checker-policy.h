//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_CLASS_DECLARATION_TYPE_CHECKER_POLICY_H
#define JETLANG_CLASS_DECLARATION_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"

class ClassDeclarationTypeCheckerPolicy {
private:
    static void verifyAllClassProperties(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult);
    static void verifyClassPropertiesWithInitializer(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult);
    static void verifyAllClassPropertyNamesAreUnique(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult);
    static void verifyAllClassMethods(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult);
    static void verifyAllClassMethodsAreUnique(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult);
    static void verifyAllClassConstructors(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult);
    static void verifyAllClassConstructorsAreUnique(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult);
public:
    static void apply(std::shared_ptr<ASTClassDeclarationNode> classDeclarationNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_CLASS_DECLARATION_TYPE_CHECKER_POLICY_H

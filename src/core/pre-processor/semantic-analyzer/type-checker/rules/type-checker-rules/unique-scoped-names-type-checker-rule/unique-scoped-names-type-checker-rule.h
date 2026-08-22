//
// Created by Johny Georges on 2024-05-28.
//

#ifndef JETLANG_UNIQUE_SCOPED_NAMES_TYPE_CHECKER_RULE_H
#define JETLANG_UNIQUE_SCOPED_NAMES_TYPE_CHECKER_RULE_H

#include <set>
#include "../type-checker-rule.h"
#include "../../../../../../type-signature/type-signature.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-node.h"
#include "../../../types/type-checker-error-message-table.h"
#include "../../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-property-declaration-node.h"
#include "../../../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"
#include "../../../../../../ast/ast-nodes/ast-declaration-nodes/ast-enum-declaration-node.h"
#include "../../../../../../ast/ast-nodes/ast-type-declaration-nodes/ast-custom-type-declaration-node.h"
#include "../../../../../../ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"
#include "../../../../../../ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"

class UniqueScopedNamesTypeCheckerRule : public TypeCheckerRule {
public:
    void enforce(std::shared_ptr<ASTClassDeclarationNode> classDeclaration, TypeCheckerResult* typeCheckerResult);
    void enforce(std::vector<std::shared_ptr<ASTClassPropertyDeclarationNode>>* classProperties, TypeCheckerResult* typeCheckerResult);
    void enforce(std::vector<std::shared_ptr<ASTVariableDeclarationNode>>* names, TypeCheckerResult* typeCheckerResult);
    void enforce(std::vector<std::shared_ptr<ASTClassDeclarationNode>>* classes, TypeCheckerResult* typeCheckerResult);
    void enforce(std::vector<std::shared_ptr<ASTEnumDeclarationNode>>* enums, TypeCheckerResult* typeCheckerResult);
    void enforce(std::vector<std::shared_ptr<ASTCustomTypeDeclarationNode>>* customTypes, TypeCheckerResult* typeCheckerResult);
    void enforce(std::vector<std::shared_ptr<ASTFunctionDeclarationNode>>* functions, TypeCheckerResult* typeCheckerResult);
    void enforce(std::vector<std::shared_ptr<ASTProcedureDeclarationNode>>* procedures, TypeCheckerResult* typeCheckerResult);
    TypeCheckerRuleType getType() override;
    std::string toString() override;
    bool isEqualTo(TypeCheckerRule* other) override;
    void print() override;
};

#endif //JETLANG_UNIQUE_SCOPED_NAMES_TYPE_CHECKER_RULE_H

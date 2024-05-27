//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_RULE_PROVIDER_H
#define JETLANG_TYPE_CHECKER_RULE_PROVIDER_H

#include "type-checker-rules/no-return-expression-type-checker-rule/no-return-expression-type-checker-rule.h"
#include "type-checker-rules/required-return-expression-type-checker-rule/required-return-expression-type-checker-rule.h"
#include "type-checker-rules/all-paths-return-type-checker-rule/all-paths-return-type-checker-rule.h"
#include "type-checker-rules/defined-type-signature-type-checker-rule/defined-type-signature-type-checker-rule.h"
#include "type-checker-rules/type-signature-mismatch-type-checker-rule/type-signature-mismatch-type-checker-rule.h"
#include "type-checker-rules/iterable-type-signature-type-checker-rule/iterable-type-signature-type-checker-rule.h"

class TypeCheckerRuleProvider {
private:
    static NoReturnExpressionTypeCheckerRule* _noReturnExpressionTypeCheckerRule;
    static RequiredReturnExpressionTypeCheckerRule* _requiredReturnExpressionTypeCheckerRule;
    static AllPathsReturnTypeCheckerRule* _allPathsReturnTypeCheckerRule;
    static DefinedTypeSignatureTypeCheckerRule* _definedTypeSignatureTypeCheckerRule;
    static TypeSignatureMismatchTypeCheckerRule* _typeSignatureMismatchTypeCheckerRule;
    static IterableTypeSignatureTypeCheckerRule* _iterableTypeSignatureTypeCheckerRule;
public:
    static NoReturnExpressionTypeCheckerRule* getNoReturnExpressionTypeCheckerRule();
    static RequiredReturnExpressionTypeCheckerRule* getRequiredReturnExpressionTypeCheckerRule();
    static AllPathsReturnTypeCheckerRule* getAllPathsReturnTypeCheckerRule();
    static DefinedTypeSignatureTypeCheckerRule* getDefinedTypeSignatureTypeCheckerRule();
    static TypeSignatureMismatchTypeCheckerRule* getTypeSignatureMismatchTypeCheckerRule();
    static IterableTypeSignatureTypeCheckerRule* getIterableTypeSignatureTypeCheckerRule();
};

#endif //JETLANG_TYPE_CHECKER_RULE_PROVIDER_H

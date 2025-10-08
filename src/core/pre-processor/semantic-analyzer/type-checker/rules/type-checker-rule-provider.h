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
#include "type-checker-rules/unique-scoped-names-type-checker-rule/unique-scoped-names-type-checker-rule.h"
#include "type-checker-rules/unique-type-signature-with-id-type-checker-rule/unique-type-signature-with-id-type-checker-rule.h"
#include "type-checker-rules/unique-type-signatures-type-checker-rule/unique-type-signatures-type-checker-rule.h"
#include "type-checker-rules/return-type-signature-type-checker-rule/return-type-signature-type-checker-rule.h"
#include "type-checker-rules/match-argument-list-count-with-parameter-list-count-type-checker-rule/match-argument-list-count-with-parameter-list-count-type-checker-rule.h"
#include "type-checker-rules/argument-list-type-signature-mismatch-type-checker-rule/argument-list-type-signature-mismatch-type-checker-rule.h"
#include "type-checker-rules/dref-type-checker-rule/dref-type-checker-rule.h"
#include "type-checker-rules/sref-type-checker-rule/sref-type-checker-rule.h"
#include "type-checker-rules/ref-type-checker-rule/ref-type-checker-rule.h"
#include "type-checker-rules/unique-type-signature-keys-type-checker-rule/unique-type-signature-keys-type-checker-rule.h"
#include "type-checker-rules/invocable-type-signature-type-checker-rule/invocable-type-signature-type-checker-rule.h"

class TypeCheckerRuleProvider {
private:
    static NoReturnExpressionTypeCheckerRule* _noReturnExpressionTypeCheckerRule;
    static RequiredReturnExpressionTypeCheckerRule* _requiredReturnExpressionTypeCheckerRule;
    static AllPathsReturnTypeCheckerRule* _allPathsReturnTypeCheckerRule;
    static DefinedTypeSignatureTypeCheckerRule* _definedTypeSignatureTypeCheckerRule;
    static TypeSignatureMismatchTypeCheckerRule* _typeSignatureMismatchTypeCheckerRule;
    static IterableTypeSignatureTypeCheckerRule* _iterableTypeSignatureTypeCheckerRule;
    static InvocableTypeSignatureTypeCheckerRule* _invocableTypeSignatureTypeCheckerRule;
    static UniqueScopedNamesTypeCheckerRule* _uniqueScopedNamesTypeCheckerRule;
    static UniqueTypeSignatureKeysTypeCheckerRule* _uniqueTypeSignatureKeysTypeCheckerRule;
    static UniqueTypeSignatureWithIdTypeCheckerRule* _uniqueTypeSignatureWithIdTypeCheckerRule;
    static UniqueTypeSignaturesTypeCheckerRule* _uniqueTypeSignaturesTypeCheckerRule;
    static ReturnTypeSignatureTypeCheckerRule* _returnTypeSignatureTypeCheckerRule;
    static MatchArgumentListCountWithParameterListCountTypeCheckerRule* _matchArgumentListCountWithParameterListCountTypeCheckerRule;
    static ArgumentListTypeSignatureMismatchTypeCheckerRule* _argumentListTypeSignatureMismatchTypeCheckerRule;
    static DrefTypeSignatureTypeCheckerRule* _drefTypeSignatureTypeCheckerRule;
    static SrefTypeSignatureTypeCheckerRule* _srefTypeSignatureTypeCheckerRule;
    static RefTypeSignatureTypeCheckerRule* _refTypeSignatureTypeCheckerRule;
public:
    static NoReturnExpressionTypeCheckerRule* getNoReturnExpressionTypeCheckerRule();
    static RequiredReturnExpressionTypeCheckerRule* getRequiredReturnExpressionTypeCheckerRule();
    static AllPathsReturnTypeCheckerRule* getAllPathsReturnTypeCheckerRule();
    static DefinedTypeSignatureTypeCheckerRule* getDefinedTypeSignatureTypeCheckerRule();
    static TypeSignatureMismatchTypeCheckerRule* getTypeSignatureMismatchTypeCheckerRule();
    static IterableTypeSignatureTypeCheckerRule* getIterableTypeSignatureTypeCheckerRule();
    static InvocableTypeSignatureTypeCheckerRule* getInvocableTypeSignatureTypeCheckerRule();
    static UniqueScopedNamesTypeCheckerRule* getUniqueScopedNamesTypeCheckerRule();
    static UniqueTypeSignatureKeysTypeCheckerRule* getUniqueTypeSignatureKeysTypeCheckerRule();
    static UniqueTypeSignatureWithIdTypeCheckerRule* getUniqueTypeSignatureWithIdTypeCheckerRule();
    static UniqueTypeSignaturesTypeCheckerRule* getUniqueTypeSignaturesTypeCheckerRule();
    static ReturnTypeSignatureTypeCheckerRule* getReturnTypeSignatureTypeCheckerRule();
    static MatchArgumentListCountWithParameterListCountTypeCheckerRule* getMatchArgumentListCountWithParameterListCountTypeCheckerRule();
    static ArgumentListTypeSignatureMismatchTypeCheckerRule* getArgumentListTypeSignatureMismatchTypeCheckerRule();
    static DrefTypeSignatureTypeCheckerRule* getDrefTypeSignatureTypeCheckerRule();
    static SrefTypeSignatureTypeCheckerRule* getSrefTypeSignatureTypeCheckerRule();
    static RefTypeSignatureTypeCheckerRule* getRefTypeSignatureTypeCheckerRule();
};

#endif //JETLANG_TYPE_CHECKER_RULE_PROVIDER_H

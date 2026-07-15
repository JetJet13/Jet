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
#include "type-checker-rules/ref-type-checker-rule/ref-type-checker-rule.h"
#include "type-checker-rules/unique-type-signature-keys-type-checker-rule/unique-type-signature-keys-type-checker-rule.h"
#include "type-checker-rules/invocable-type-signature-type-checker-rule/invocable-type-signature-type-checker-rule.h"
#include "type-checker-rules/shared-value-assignment-type-checker-rule/shared-value-assignment-type-checker-rule.h"
#include "type-checker-rules/class-self-reference-type-checker-rule/class-self-reference-type-checker-rule.h"
#include "type-checker-rules/class-circular-reference-type-checker-rule/class-circular-reference-type-checker-rule.h"
#include "type-checker-rules/shared-type-checker-rule/shared-type-checker-rule.h"

class TypeCheckerRuleProvider {
private:
    static std::shared_ptr<NoReturnExpressionTypeCheckerRule> _noReturnExpressionTypeCheckerRule;
    static std::shared_ptr<RequiredReturnExpressionTypeCheckerRule> _requiredReturnExpressionTypeCheckerRule;
    static std::shared_ptr<AllPathsReturnTypeCheckerRule> _allPathsReturnTypeCheckerRule;
    static std::shared_ptr<DefinedTypeSignatureTypeCheckerRule> _definedTypeSignatureTypeCheckerRule;
    static std::shared_ptr<TypeSignatureMismatchTypeCheckerRule> _typeSignatureMismatchTypeCheckerRule;
    static std::shared_ptr<IterableTypeSignatureTypeCheckerRule> _iterableTypeSignatureTypeCheckerRule;
    static std::shared_ptr<InvocableTypeSignatureTypeCheckerRule> _invocableTypeSignatureTypeCheckerRule;
    static std::shared_ptr<UniqueScopedNamesTypeCheckerRule> _uniqueScopedNamesTypeCheckerRule;
    static std::shared_ptr<UniqueTypeSignatureKeysTypeCheckerRule> _uniqueTypeSignatureKeysTypeCheckerRule;
    static std::shared_ptr<UniqueTypeSignatureWithIdTypeCheckerRule> _uniqueTypeSignatureWithIdTypeCheckerRule;
    static std::shared_ptr<UniqueTypeSignaturesTypeCheckerRule> _uniqueTypeSignaturesTypeCheckerRule;
    static std::shared_ptr<ReturnTypeSignatureTypeCheckerRule> _returnTypeSignatureTypeCheckerRule;
    static std::shared_ptr<MatchArgumentListCountWithParameterListCountTypeCheckerRule> _matchArgumentListCountWithParameterListCountTypeCheckerRule;
    static std::shared_ptr<ArgumentListTypeSignatureMismatchTypeCheckerRule> _argumentListTypeSignatureMismatchTypeCheckerRule;
    static std::shared_ptr<DrefTypeSignatureTypeCheckerRule> _drefTypeSignatureTypeCheckerRule;
    static std::shared_ptr<RefTypeSignatureTypeCheckerRule> _refTypeSignatureTypeCheckerRule;
    static std::shared_ptr<SharedTypeSignatureTypeCheckerRule> _sharedTypeSignatureTypeCheckerRule;
    static std::shared_ptr<SharedValueAssignmentTypeCheckerRule> _sharedValueAssignmentTypeCheckerRule;
    static std::shared_ptr<ClassSelfReferenceTypeCheckerRule> _classSelfReferenceTypeCheckerRule;
    static std::shared_ptr<ClassCircularReferenceTypeCheckerRule> _classCircularReferenceTypeCheckerRule;
public:
    static std::shared_ptr<NoReturnExpressionTypeCheckerRule> getNoReturnExpressionTypeCheckerRule();
    static std::shared_ptr<RequiredReturnExpressionTypeCheckerRule> getRequiredReturnExpressionTypeCheckerRule();
    static std::shared_ptr<AllPathsReturnTypeCheckerRule> getAllPathsReturnTypeCheckerRule();
    static std::shared_ptr<DefinedTypeSignatureTypeCheckerRule> getDefinedTypeSignatureTypeCheckerRule();
    static std::shared_ptr<TypeSignatureMismatchTypeCheckerRule> getTypeSignatureMismatchTypeCheckerRule();
    static std::shared_ptr<IterableTypeSignatureTypeCheckerRule> getIterableTypeSignatureTypeCheckerRule();
    static std::shared_ptr<InvocableTypeSignatureTypeCheckerRule> getInvocableTypeSignatureTypeCheckerRule();
    static std::shared_ptr<UniqueScopedNamesTypeCheckerRule> getUniqueScopedNamesTypeCheckerRule();
    static std::shared_ptr<UniqueTypeSignatureKeysTypeCheckerRule> getUniqueTypeSignatureKeysTypeCheckerRule();
    static std::shared_ptr<UniqueTypeSignatureWithIdTypeCheckerRule> getUniqueTypeSignatureWithIdTypeCheckerRule();
    static std::shared_ptr<UniqueTypeSignaturesTypeCheckerRule> getUniqueTypeSignaturesTypeCheckerRule();
    static std::shared_ptr<ReturnTypeSignatureTypeCheckerRule> getReturnTypeSignatureTypeCheckerRule();
    static std::shared_ptr<MatchArgumentListCountWithParameterListCountTypeCheckerRule> getMatchArgumentListCountWithParameterListCountTypeCheckerRule();
    static std::shared_ptr<ArgumentListTypeSignatureMismatchTypeCheckerRule> getArgumentListTypeSignatureMismatchTypeCheckerRule();
    static std::shared_ptr<DrefTypeSignatureTypeCheckerRule> getDrefTypeSignatureTypeCheckerRule();
    static std::shared_ptr<RefTypeSignatureTypeCheckerRule> getRefTypeSignatureTypeCheckerRule();
    static std::shared_ptr<SharedTypeSignatureTypeCheckerRule> getSharedTypeSignatureTypeCheckerRule();
    static std::shared_ptr<SharedValueAssignmentTypeCheckerRule> getSharedValueAssignmentTypeCheckerRule();
    static std::shared_ptr<ClassSelfReferenceTypeCheckerRule> getClassSelfReferenceTypeCheckerRule();
    static std::shared_ptr<ClassCircularReferenceTypeCheckerRule> getClassCircularReferenceTypeCheckerRule();
};

#endif //JETLANG_TYPE_CHECKER_RULE_PROVIDER_H

//
// Created by Johny Georges on 2024-05-25.
//

#include "type-checker-rule-provider.h"

std::shared_ptr<NoReturnExpressionTypeCheckerRule> TypeCheckerRuleProvider::_noReturnExpressionTypeCheckerRule = std::make_shared<NoReturnExpressionTypeCheckerRule>();
std::shared_ptr<RequiredReturnExpressionTypeCheckerRule> TypeCheckerRuleProvider::_requiredReturnExpressionTypeCheckerRule = std::make_shared<RequiredReturnExpressionTypeCheckerRule>();
std::shared_ptr<AllPathsReturnTypeCheckerRule> TypeCheckerRuleProvider::_allPathsReturnTypeCheckerRule = std::make_shared<AllPathsReturnTypeCheckerRule>();
std::shared_ptr<DefinedTypeSignatureTypeCheckerRule> TypeCheckerRuleProvider::_definedTypeSignatureTypeCheckerRule = std::make_shared<DefinedTypeSignatureTypeCheckerRule>();
std::shared_ptr<TypeSignatureMismatchTypeCheckerRule> TypeCheckerRuleProvider::_typeSignatureMismatchTypeCheckerRule = std::make_shared<TypeSignatureMismatchTypeCheckerRule>();
std::shared_ptr<IterableTypeSignatureTypeCheckerRule> TypeCheckerRuleProvider::_iterableTypeSignatureTypeCheckerRule = std::make_shared<IterableTypeSignatureTypeCheckerRule>();
std::shared_ptr<InvocableTypeSignatureTypeCheckerRule> TypeCheckerRuleProvider::_invocableTypeSignatureTypeCheckerRule = std::make_shared<InvocableTypeSignatureTypeCheckerRule>();
std::shared_ptr<UniqueScopedNamesTypeCheckerRule> TypeCheckerRuleProvider::_uniqueScopedNamesTypeCheckerRule = std::make_shared<UniqueScopedNamesTypeCheckerRule>();
std::shared_ptr<UniqueTypeSignatureKeysTypeCheckerRule> TypeCheckerRuleProvider::_uniqueTypeSignatureKeysTypeCheckerRule = std::make_shared<UniqueTypeSignatureKeysTypeCheckerRule>();
std::shared_ptr<UniqueTypeSignatureWithIdTypeCheckerRule> TypeCheckerRuleProvider::_uniqueTypeSignatureWithIdTypeCheckerRule = std::make_shared<UniqueTypeSignatureWithIdTypeCheckerRule>();
std::shared_ptr<UniqueTypeSignaturesTypeCheckerRule> TypeCheckerRuleProvider::_uniqueTypeSignaturesTypeCheckerRule = std::make_shared<UniqueTypeSignaturesTypeCheckerRule>();
std::shared_ptr<ReturnTypeSignatureTypeCheckerRule> TypeCheckerRuleProvider::_returnTypeSignatureTypeCheckerRule = std::make_shared<ReturnTypeSignatureTypeCheckerRule>();
std::shared_ptr<MatchArgumentListCountWithParameterListCountTypeCheckerRule> TypeCheckerRuleProvider::_matchArgumentListCountWithParameterListCountTypeCheckerRule = std::make_shared<MatchArgumentListCountWithParameterListCountTypeCheckerRule>();
std::shared_ptr<ArgumentListTypeSignatureMismatchTypeCheckerRule> TypeCheckerRuleProvider::_argumentListTypeSignatureMismatchTypeCheckerRule = std::make_shared<ArgumentListTypeSignatureMismatchTypeCheckerRule>();
std::shared_ptr<DrefTypeSignatureTypeCheckerRule> TypeCheckerRuleProvider::_drefTypeSignatureTypeCheckerRule = std::make_shared<DrefTypeSignatureTypeCheckerRule>();
std::shared_ptr<SharedTypeSignatureTypeCheckerRule> TypeCheckerRuleProvider::_sharedTypeSignatureTypeCheckerRule = std::make_shared<SharedTypeSignatureTypeCheckerRule>();
std::shared_ptr<SharedValueAssignmentTypeCheckerRule> TypeCheckerRuleProvider::_sharedValueAssignmentTypeCheckerRule = std::make_shared<SharedValueAssignmentTypeCheckerRule>();
std::shared_ptr<ClassSelfReferenceTypeCheckerRule> TypeCheckerRuleProvider::_classSelfReferenceTypeCheckerRule = std::make_shared<ClassSelfReferenceTypeCheckerRule>();
std::shared_ptr<ClassCircularReferenceTypeCheckerRule> TypeCheckerRuleProvider::_classCircularReferenceTypeCheckerRule = std::make_shared<ClassCircularReferenceTypeCheckerRule>();

std::shared_ptr<NoReturnExpressionTypeCheckerRule> TypeCheckerRuleProvider::getNoReturnExpressionTypeCheckerRule() {
    return _noReturnExpressionTypeCheckerRule;
}

std::shared_ptr<RequiredReturnExpressionTypeCheckerRule> TypeCheckerRuleProvider::getRequiredReturnExpressionTypeCheckerRule() {
    return _requiredReturnExpressionTypeCheckerRule;
}

std::shared_ptr<AllPathsReturnTypeCheckerRule> TypeCheckerRuleProvider::getAllPathsReturnTypeCheckerRule() {
    return _allPathsReturnTypeCheckerRule;
}

std::shared_ptr<DefinedTypeSignatureTypeCheckerRule> TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule() {
    return _definedTypeSignatureTypeCheckerRule;
}

std::shared_ptr<TypeSignatureMismatchTypeCheckerRule> TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule() {
    return _typeSignatureMismatchTypeCheckerRule;
}

std::shared_ptr<IterableTypeSignatureTypeCheckerRule> TypeCheckerRuleProvider::getIterableTypeSignatureTypeCheckerRule() {
    return _iterableTypeSignatureTypeCheckerRule;
}

std::shared_ptr<InvocableTypeSignatureTypeCheckerRule> TypeCheckerRuleProvider::getInvocableTypeSignatureTypeCheckerRule() {
    return _invocableTypeSignatureTypeCheckerRule;
}

std::shared_ptr<UniqueScopedNamesTypeCheckerRule> TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule() {
    return _uniqueScopedNamesTypeCheckerRule;
}

std::shared_ptr<UniqueTypeSignatureKeysTypeCheckerRule> TypeCheckerRuleProvider::getUniqueTypeSignatureKeysTypeCheckerRule() {
    return _uniqueTypeSignatureKeysTypeCheckerRule;
}

std::shared_ptr<UniqueTypeSignatureWithIdTypeCheckerRule> TypeCheckerRuleProvider::getUniqueTypeSignatureWithIdTypeCheckerRule() {
    return _uniqueTypeSignatureWithIdTypeCheckerRule;
}

std::shared_ptr<UniqueTypeSignaturesTypeCheckerRule> TypeCheckerRuleProvider::getUniqueTypeSignaturesTypeCheckerRule() {
    return _uniqueTypeSignaturesTypeCheckerRule;
}

std::shared_ptr<ReturnTypeSignatureTypeCheckerRule> TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule() {
    return _returnTypeSignatureTypeCheckerRule;
}

std::shared_ptr<MatchArgumentListCountWithParameterListCountTypeCheckerRule> TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule() {
    return _matchArgumentListCountWithParameterListCountTypeCheckerRule;
}

std::shared_ptr<ArgumentListTypeSignatureMismatchTypeCheckerRule> TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule() {
    return _argumentListTypeSignatureMismatchTypeCheckerRule;
}

std::shared_ptr<DrefTypeSignatureTypeCheckerRule> TypeCheckerRuleProvider::getDrefTypeSignatureTypeCheckerRule() {
    return _drefTypeSignatureTypeCheckerRule;
}

std::shared_ptr<SharedTypeSignatureTypeCheckerRule> TypeCheckerRuleProvider::getSharedTypeSignatureTypeCheckerRule() {
    return _sharedTypeSignatureTypeCheckerRule;
}

std::shared_ptr<SharedValueAssignmentTypeCheckerRule> TypeCheckerRuleProvider::getSharedValueAssignmentTypeCheckerRule() {
    return _sharedValueAssignmentTypeCheckerRule;
}

std::shared_ptr<ClassSelfReferenceTypeCheckerRule> TypeCheckerRuleProvider::getClassSelfReferenceTypeCheckerRule() {
    return _classSelfReferenceTypeCheckerRule;
}

std::shared_ptr<ClassCircularReferenceTypeCheckerRule> TypeCheckerRuleProvider::getClassCircularReferenceTypeCheckerRule() {
    return _classCircularReferenceTypeCheckerRule;
}
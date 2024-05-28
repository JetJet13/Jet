//
// Created by Johny Georges on 2024-05-25.
//

#include "type-checker-rule-provider.h"
#include "type-checker-rules/iterable-type-signature-type-checker-rule/iterable-type-signature-type-checker-rule.h"

NoReturnExpressionTypeCheckerRule* TypeCheckerRuleProvider::_noReturnExpressionTypeCheckerRule = new NoReturnExpressionTypeCheckerRule();
RequiredReturnExpressionTypeCheckerRule* TypeCheckerRuleProvider::_requiredReturnExpressionTypeCheckerRule = new RequiredReturnExpressionTypeCheckerRule();
AllPathsReturnTypeCheckerRule* TypeCheckerRuleProvider::_allPathsReturnTypeCheckerRule = new AllPathsReturnTypeCheckerRule();
DefinedTypeSignatureTypeCheckerRule* TypeCheckerRuleProvider::_definedTypeSignatureTypeCheckerRule = new DefinedTypeSignatureTypeCheckerRule();
TypeSignatureMismatchTypeCheckerRule* TypeCheckerRuleProvider::_typeSignatureMismatchTypeCheckerRule = new TypeSignatureMismatchTypeCheckerRule();
IterableTypeSignatureTypeCheckerRule* TypeCheckerRuleProvider::_iterableTypeSignatureTypeCheckerRule = new IterableTypeSignatureTypeCheckerRule();
UniqueScopedNamesTypeCheckerRule* TypeCheckerRuleProvider::_uniqueScopedNamesTypeCheckerRule = new UniqueScopedNamesTypeCheckerRule();
UniqueTypeSignatureWithIdTypeCheckerRule* TypeCheckerRuleProvider::_uniqueTypeSignatureWithIdTypeCheckerRule = new UniqueTypeSignatureWithIdTypeCheckerRule();
UniqueTypeSignaturesTypeCheckerRule* TypeCheckerRuleProvider::_uniqueTypeSignaturesTypeCheckerRule = new UniqueTypeSignaturesTypeCheckerRule();


NoReturnExpressionTypeCheckerRule* TypeCheckerRuleProvider::getNoReturnExpressionTypeCheckerRule() {
    return _noReturnExpressionTypeCheckerRule;
}

RequiredReturnExpressionTypeCheckerRule* TypeCheckerRuleProvider::getRequiredReturnExpressionTypeCheckerRule() {
    return _requiredReturnExpressionTypeCheckerRule;
}

AllPathsReturnTypeCheckerRule* TypeCheckerRuleProvider::getAllPathsReturnTypeCheckerRule() {
    return _allPathsReturnTypeCheckerRule;
}

DefinedTypeSignatureTypeCheckerRule* TypeCheckerRuleProvider::getDefinedTypeSignatureTypeCheckerRule() {
    return _definedTypeSignatureTypeCheckerRule;
}

TypeSignatureMismatchTypeCheckerRule* TypeCheckerRuleProvider::getTypeSignatureMismatchTypeCheckerRule() {
    return _typeSignatureMismatchTypeCheckerRule;
}

IterableTypeSignatureTypeCheckerRule* TypeCheckerRuleProvider::getIterableTypeSignatureTypeCheckerRule() {
    return _iterableTypeSignatureTypeCheckerRule;
}

UniqueScopedNamesTypeCheckerRule* TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule() {
    return _uniqueScopedNamesTypeCheckerRule;
}

UniqueTypeSignatureWithIdTypeCheckerRule* TypeCheckerRuleProvider::getUniqueTypeSignatureWithIdTypeCheckerRule() {
    return _uniqueTypeSignatureWithIdTypeCheckerRule;
}

UniqueTypeSignaturesTypeCheckerRule* TypeCheckerRuleProvider::getUniqueTypeSignaturesTypeCheckerRule() {
    return _uniqueTypeSignaturesTypeCheckerRule;
}
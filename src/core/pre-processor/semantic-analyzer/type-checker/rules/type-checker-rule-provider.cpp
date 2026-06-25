//
// Created by Johny Georges on 2024-05-25.
//

#include "type-checker-rule-provider.h"

NoReturnExpressionTypeCheckerRule* TypeCheckerRuleProvider::_noReturnExpressionTypeCheckerRule = new NoReturnExpressionTypeCheckerRule();
RequiredReturnExpressionTypeCheckerRule* TypeCheckerRuleProvider::_requiredReturnExpressionTypeCheckerRule = new RequiredReturnExpressionTypeCheckerRule();
AllPathsReturnTypeCheckerRule* TypeCheckerRuleProvider::_allPathsReturnTypeCheckerRule = new AllPathsReturnTypeCheckerRule();
DefinedTypeSignatureTypeCheckerRule* TypeCheckerRuleProvider::_definedTypeSignatureTypeCheckerRule = new DefinedTypeSignatureTypeCheckerRule();
TypeSignatureMismatchTypeCheckerRule* TypeCheckerRuleProvider::_typeSignatureMismatchTypeCheckerRule = new TypeSignatureMismatchTypeCheckerRule();
IterableTypeSignatureTypeCheckerRule* TypeCheckerRuleProvider::_iterableTypeSignatureTypeCheckerRule = new IterableTypeSignatureTypeCheckerRule();
InvocableTypeSignatureTypeCheckerRule* TypeCheckerRuleProvider::_invocableTypeSignatureTypeCheckerRule = new InvocableTypeSignatureTypeCheckerRule();
UniqueScopedNamesTypeCheckerRule* TypeCheckerRuleProvider::_uniqueScopedNamesTypeCheckerRule = new UniqueScopedNamesTypeCheckerRule();
UniqueTypeSignatureKeysTypeCheckerRule* TypeCheckerRuleProvider::_uniqueTypeSignatureKeysTypeCheckerRule = new UniqueTypeSignatureKeysTypeCheckerRule();
UniqueTypeSignatureWithIdTypeCheckerRule* TypeCheckerRuleProvider::_uniqueTypeSignatureWithIdTypeCheckerRule = new UniqueTypeSignatureWithIdTypeCheckerRule();
UniqueTypeSignaturesTypeCheckerRule* TypeCheckerRuleProvider::_uniqueTypeSignaturesTypeCheckerRule = new UniqueTypeSignaturesTypeCheckerRule();
ReturnTypeSignatureTypeCheckerRule* TypeCheckerRuleProvider::_returnTypeSignatureTypeCheckerRule = new ReturnTypeSignatureTypeCheckerRule();
MatchArgumentListCountWithParameterListCountTypeCheckerRule* TypeCheckerRuleProvider::_matchArgumentListCountWithParameterListCountTypeCheckerRule = new MatchArgumentListCountWithParameterListCountTypeCheckerRule();
ArgumentListTypeSignatureMismatchTypeCheckerRule* TypeCheckerRuleProvider::_argumentListTypeSignatureMismatchTypeCheckerRule = new ArgumentListTypeSignatureMismatchTypeCheckerRule();
DrefTypeSignatureTypeCheckerRule* TypeCheckerRuleProvider::_drefTypeSignatureTypeCheckerRule = new DrefTypeSignatureTypeCheckerRule();
SrefTypeSignatureTypeCheckerRule* TypeCheckerRuleProvider::_srefTypeSignatureTypeCheckerRule = new SrefTypeSignatureTypeCheckerRule();
RefTypeSignatureTypeCheckerRule* TypeCheckerRuleProvider::_refTypeSignatureTypeCheckerRule = new RefTypeSignatureTypeCheckerRule();
RefValueAssignmentTypeCheckerRule* TypeCheckerRuleProvider::_refValueAssignmentTypeCheckerRule = new RefValueAssignmentTypeCheckerRule();
ClassSelfReferenceTypeCheckerRule* TypeCheckerRuleProvider::_classSelfReferenceTypeCheckerRule = new ClassSelfReferenceTypeCheckerRule();
ClassCircularReferenceTypeCheckerRule* TypeCheckerRuleProvider::_classCircularReferenceTypeCheckerRule = new ClassCircularReferenceTypeCheckerRule();

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

InvocableTypeSignatureTypeCheckerRule* TypeCheckerRuleProvider::getInvocableTypeSignatureTypeCheckerRule() {
    return _invocableTypeSignatureTypeCheckerRule;
}

UniqueScopedNamesTypeCheckerRule* TypeCheckerRuleProvider::getUniqueScopedNamesTypeCheckerRule() {
    return _uniqueScopedNamesTypeCheckerRule;
}

UniqueTypeSignatureKeysTypeCheckerRule* TypeCheckerRuleProvider::getUniqueTypeSignatureKeysTypeCheckerRule() {
    return _uniqueTypeSignatureKeysTypeCheckerRule;
}

UniqueTypeSignatureWithIdTypeCheckerRule* TypeCheckerRuleProvider::getUniqueTypeSignatureWithIdTypeCheckerRule() {
    return _uniqueTypeSignatureWithIdTypeCheckerRule;
}

UniqueTypeSignaturesTypeCheckerRule* TypeCheckerRuleProvider::getUniqueTypeSignaturesTypeCheckerRule() {
    return _uniqueTypeSignaturesTypeCheckerRule;
}

ReturnTypeSignatureTypeCheckerRule* TypeCheckerRuleProvider::getReturnTypeSignatureTypeCheckerRule() {
    return _returnTypeSignatureTypeCheckerRule;
}

MatchArgumentListCountWithParameterListCountTypeCheckerRule* TypeCheckerRuleProvider::getMatchArgumentListCountWithParameterListCountTypeCheckerRule() {
    return _matchArgumentListCountWithParameterListCountTypeCheckerRule;
}

ArgumentListTypeSignatureMismatchTypeCheckerRule* TypeCheckerRuleProvider::getArgumentListTypeSignatureMismatchTypeCheckerRule() {
    return _argumentListTypeSignatureMismatchTypeCheckerRule;
}

DrefTypeSignatureTypeCheckerRule* TypeCheckerRuleProvider::getDrefTypeSignatureTypeCheckerRule() {
    return _drefTypeSignatureTypeCheckerRule;
}

SrefTypeSignatureTypeCheckerRule* TypeCheckerRuleProvider::getSrefTypeSignatureTypeCheckerRule() {
    return _srefTypeSignatureTypeCheckerRule;
}

RefTypeSignatureTypeCheckerRule* TypeCheckerRuleProvider::getRefTypeSignatureTypeCheckerRule() {
    return _refTypeSignatureTypeCheckerRule;
}

RefValueAssignmentTypeCheckerRule* TypeCheckerRuleProvider::getRefValueAssignmentTypeCheckerRule() {
    return _refValueAssignmentTypeCheckerRule;
}

ClassSelfReferenceTypeCheckerRule* TypeCheckerRuleProvider::getClassSelfReferenceTypeCheckerRule() {
    return _classSelfReferenceTypeCheckerRule;
}

ClassCircularReferenceTypeCheckerRule* TypeCheckerRuleProvider::getClassCircularReferenceTypeCheckerRule() {
    return _classCircularReferenceTypeCheckerRule;
}
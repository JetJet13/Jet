//
// Created by Johny Georges on 2024-05-25.
//

#include "type-checker-rule-list.h"

TypeCheckerRuleList::TypeCheckerRuleList() {
    _rules = std::vector<TypeCheckerRule*>();
}

TypeCheckerRuleList::TypeCheckerRuleList(std::vector<TypeCheckerRule*> rules) {
    _rules = std::move(rules);
}

TypeCheckerRuleList::TypeCheckerRuleList(TypeCheckerRuleList* ruleList) {
    _rules = ruleList->getRules();
}

std::vector<TypeCheckerRule*> TypeCheckerRuleList::getRules() {
    return _rules;
}

void TypeCheckerRuleList::addRule(TypeCheckerRule* rule) {
    _rules.push_back(rule);
}

void TypeCheckerRuleList::removeRule(TypeCheckerRule* rule) {
    auto indexToDelete = -1;
    for (int i = 0; i < _rules.size(); i++) {
        if (_rules[i]->isEqualTo(rule)) {
            indexToDelete = i;
        }
    }

    if (indexToDelete != -1) {
        _rules.erase(_rules.begin() + indexToDelete);
    }
}

void TypeCheckerRuleList::removeRule(TypeCheckerRuleType type) {
    auto indexToRemove = -1;
    for (int i = 0; i < _rules.size(); i++) {
        if (_rules[i]->hasType(type)) {
            indexToRemove = i;
        }
    }

    if (indexToRemove != -1) {
        _rules.erase(_rules.begin() + indexToRemove);
    }
}

void TypeCheckerRuleList::replaceRule(TypeCheckerRule* sourceRule, TypeCheckerRule* targetRule) {
    this->removeRule(sourceRule);
    _rules.push_back(targetRule);
}

TypeCheckerRuleList* TypeCheckerRuleList::combine(TypeCheckerRuleList* other) {
    for (auto rule : other->getRules()) {
        _rules.push_back(rule);
    }
    return this;
}

std::optional<RequiredReturnExpressionTypeCheckerRule*> TypeCheckerRuleList::findRequiredReturnExpressionRule() {
    auto result = this->find(REQUIRED_RETURN_EXPRESSION_TCR);
    if (result) {
        return (RequiredReturnExpressionTypeCheckerRule*)result.value();
    }
    return {};
}

std::optional<OptionalReturnExpressionTypeCheckerRule*> TypeCheckerRuleList::findOptionalReturnExpressionRule() {
    auto result = this->find(OPTIONAL_RETURN_EXPRESSION_TCR);
    if (result) {
        return (OptionalReturnExpressionTypeCheckerRule*)result.value();
    }
    return {};
}

std::optional<NoReturnExpressionTypeCheckerRule*> TypeCheckerRuleList::findNoReturnExpressionRule() {
    auto result = this->find(NO_RETURN_EXPRESSION_TCR);
    if (result) {
        return (NoReturnExpressionTypeCheckerRule*)result.value();
    }
    return {};
}

std::optional<TypeCheckerRule*> TypeCheckerRuleList::find(TypeCheckerRuleType type) {
    for (auto typeCheckerRule: _rules) {
        if (typeCheckerRule->hasType(type)) {
            return typeCheckerRule;
        }
    }
    return {};
}
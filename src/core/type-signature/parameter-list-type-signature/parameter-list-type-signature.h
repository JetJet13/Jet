//
// Created by Johny Georges on 2024-05-03.
//

#ifndef JETLANG_PARAMETER_LIST_TYPE_SIGNATURE_H
#define JETLANG_PARAMETER_LIST_TYPE_SIGNATURE_H

#include <vector>
#include "../type-signature.h"
#include "../literal-type-signature/types/literal-type.h"
#include "parameter-list-item-type-signature/parameter-list-item-type-signature.h"
#include "../argument-list-type-signature/argument-list-type-signature.h"


class ParameterListTypeSignature : public TypeSignature {
private:
    std::vector<std::shared_ptr<ParameterListItemTypeSignature>> _parameters;
    std::vector<std::shared_ptr<TypeSignature>> _parameterTypes;
    bool _isVariableLength = false;
    uint64_t _variableLengthStartIndex = -1;
    std::optional<std::shared_ptr<ParameterListItemTypeSignature>> _variableLengthTypeSignature;
public:
    ParameterListTypeSignature();
    ParameterListTypeSignature(std::vector<std::shared_ptr<ParameterListItemTypeSignature>> parameters);
    std::vector<std::shared_ptr<ParameterListItemTypeSignature>>* getParameters();
    std::vector<std::shared_ptr<TypeSignature>>* getParameterTypes();
    std::string getId();
    uint64_t numParameters();
    void markAsVariableLength(uint64_t startIndex, std::shared_ptr<ParameterListItemTypeSignature> typeSignature);
    [[nodiscard]] bool isVariableLength() const;
    [[nodiscard]] uint64_t getVariableLengthStartIndex() const;
    std::shared_ptr<ParameterListItemTypeSignature> getVariableLengthTypeSignature();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    bool matchesWithArgumentList(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature);
    void print() override;
};

#endif //JETLANG_PARAMETER_LIST_TYPE_SIGNATURE_H

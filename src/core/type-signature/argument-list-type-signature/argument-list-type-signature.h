//
// Created by Johny Georges on 2024-12-31.
//

#ifndef JETLANG_ARGUMENT_LIST_TYPE_SIGNATURE_H
#define JETLANG_ARGUMENT_LIST_TYPE_SIGNATURE_H

#include <vector>
#include "../type-signature.h"
#include "../literal-type-signature/types/literal-type.h"

class ArgumentListTypeSignature : public TypeSignature {
private:
    std::vector<std::shared_ptr<TypeSignature>> _argumentTypes;
public:
    ArgumentListTypeSignature();
    ArgumentListTypeSignature(std::vector<std::shared_ptr<TypeSignature>> argumentTypes);
    std::vector<std::shared_ptr<TypeSignature>>* getArgumentTypes();
    uint64_t numParameters();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_ARGUMENT_LIST_TYPE_SIGNATURE_H

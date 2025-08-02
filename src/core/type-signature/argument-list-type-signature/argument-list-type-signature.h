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
    std::vector<TypeSignature*> _argumentTypes;
public:
    ArgumentListTypeSignature();
    ArgumentListTypeSignature(std::vector<TypeSignature*> argumentTypes);
    std::vector<TypeSignature*>* getArgumentTypes();
    unsigned long numParameters();
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    void print() override;
};

#endif //JETLANG_ARGUMENT_LIST_TYPE_SIGNATURE_H

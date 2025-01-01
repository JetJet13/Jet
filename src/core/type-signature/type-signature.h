//
// Created by Johny Georges on 2024-04-30.
//

#ifndef JETLANG_TYPE_SIGNATURE_H
#define JETLANG_TYPE_SIGNATURE_H

#include <vector>
#include <string>
#include "types/type-source.h"

class TypeSignature {
private:
    std::string _id;
public:
    std::string getId();
    void setId(std::string id);
    bool typeTargetIs(TypeSource other);
    bool typeSourceIs(TypeSource other);
    bool isOneOf(std::vector<TypeSource> typeSources);
    virtual bool isUnknown();
    virtual bool isInvalid();
    virtual bool isVoid();
    bool isUnknownOrInvalidOrVoid();
    virtual bool isLiteral();
    virtual bool isInvocable();
    virtual void copyFrom(TypeSignature* otherType);
    virtual TypeSource getTypeTarget();
    virtual TypeSignature* getTargetTypeSignature();
    virtual bool isEquivalentTo(TypeSignature* otherType);
    virtual TypeSignature* convertToVariableTypeSignature();
    virtual std::string toString() = 0;
    virtual TypeSource getTypeSource() = 0;
    virtual bool isEqualTo(TypeSignature* otherType) = 0;
    virtual void print() = 0;
};

#endif //JETLANG_TYPE_SIGNATURE_H

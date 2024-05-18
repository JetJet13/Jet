//
// Created by Johny Georges on 2024-05-13.
//

#include <catch2/catch_all.hpp>
#include "../../../../src/core/token/token-table.h"
#include "../../../../src/core/reserved-keywords/reserved-keywords.h"
#include "../../../../src/core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../../../../src/shared/utils/logger/logger.h"
#include "../../../../src/core/pre-processor/syntax-analyzer/syntax-analyzer.h"
#include "../../../../src/core/pre-processor/semantic-analyzer/dependency-graph/dependency-graph.h"
#include "../../../../src/core/pre-processor/semantic-analyzer/type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../../../src/core/pre-processor/semantic-analyzer/semantic-analyzer.h"
#include "resources/type-signature-factory.h"
#include "../../../../src/core/type-signature/array-type-signature/array-type-signature.h"
#include "../../../../src/core/type-signature/struct-type-signature/struct-type-signature.h"
#include "../../../../src/core/type-signature/enum-type-signature/enum-access-type-signature/enum-access-type-signature.h"
#include "../../../../src/core/type-signature/tuple-type-signature/tuple-type-signature.h"
#include "../../../../src/core/type-signature/lambda-type-signature/lambda-expression-type-signature/lambda-expression-type-signature.h"

std::unordered_map<int, TypeSignature*> expectedTypeSignature = {
        {1, TypeSignatureFactory::intLiteral},
        {2, TypeSignatureFactory::floatLiteral},
        {3, TypeSignatureFactory::stringLiteral},
        {4, TypeSignatureFactory::charLiteral},
        {5, TypeSignatureFactory::boolLiteral},
        {6, TypeSignatureFactory::boolLiteral},
        {7, TypeSignatureFactory::intLiteral},
        {8, TypeSignatureFactory::intLiteral},
        {9, TypeSignatureFactory::intLiteral},
        {10, TypeSignatureFactory::intLiteral},
        {11, TypeSignatureFactory::floatLiteral},
        {12, TypeSignatureFactory::intLiteral},
        {13, TypeSignatureFactory::stringLiteral},
        {14, TypeSignatureFactory::intLiteral},
        {15, TypeSignatureFactory::floatLiteral},
        {16, TypeSignatureFactory::intLiteral},
        {17, TypeSignatureFactory::intLiteral},
        {18, TypeSignatureFactory::intLiteral},
        {19, TypeSignatureFactory::floatLiteral},
        {20, TypeSignatureFactory::floatLiteral},
        {21, TypeSignatureFactory::intLiteral},
        {22, TypeSignatureFactory::intLiteral},
        {23, TypeSignatureFactory::intLiteral},
        {24, TypeSignatureFactory::intLiteral},
        {25, TypeSignatureFactory::floatLiteral},
        {26, TypeSignatureFactory::floatLiteral},
        {27, TypeSignatureFactory::intLiteral},
        {28, TypeSignatureFactory::boolLiteral},
        {29, TypeSignatureFactory::boolLiteral},
        {30, TypeSignatureFactory::boolLiteral},
        {31, TypeSignatureFactory::boolLiteral},
        {32, TypeSignatureFactory::boolLiteral},
        {33, TypeSignatureFactory::boolLiteral},
        {34, TypeSignatureFactory::boolLiteral},
        {35, TypeSignatureFactory::boolLiteral},
        {36, TypeSignatureFactory::boolLiteral},
        {37, TypeSignatureFactory::boolLiteral},
        {38, TypeSignatureFactory::boolLiteral},
        {39, TypeSignatureFactory::boolLiteral},
        {40, TypeSignatureFactory::boolLiteral},
        {41, TypeSignatureFactory::boolLiteral},
        {42, TypeSignatureFactory::boolLiteral},
        {43, TypeSignatureFactory::boolLiteral},
        {44, TypeSignatureFactory::boolLiteral},
        {45, TypeSignatureFactory::boolLiteral},
        {46, TypeSignatureFactory::boolLiteral},
        {47, TypeSignatureFactory::boolLiteral},
        {48, TypeSignatureFactory::boolLiteral},
        {49, TypeSignatureFactory::intLiteral},
        {50, TypeSignatureFactory::intLiteral},
        {51, TypeSignatureFactory::intLiteral},
        {52, TypeSignatureFactory::intLiteral},
        {53, TypeSignatureFactory::intLiteral},
        {54, TypeSignatureFactory::boolLiteral},
        {55, TypeSignatureFactory::boolLiteral},
        {56, TypeSignatureFactory::boolLiteral},
        {57, TypeSignatureFactory::boolLiteral},
        {58, TypeSignatureFactory::intLiteral},
        {59, TypeSignatureFactory::boolLiteral},
        {60, TypeSignatureFactory::boolLiteral},
        {61, new ArrayTypeSignature(TypeSignatureFactory::intLiteral)},
        {62, TypeSignatureFactory::intLiteral},
        {63, TypeSignatureFactory::intLiteral},
        {64, new ArrayTypeSignature(new ArrayTypeSignature(TypeSignatureFactory::intLiteral))},
        {65, new ArrayTypeSignature(new ArrayTypeSignature(TypeSignatureFactory::intLiteral))},
        {66, new ArrayTypeSignature(TypeSignatureFactory::intLiteral)},
        {67, TypeSignatureFactory::intLiteral},
        {68, TypeSignatureFactory::intLiteral},
        {69, new StructTypeSignature(
                TypeSignatureMap<TypeSignature>({
                    std::pair("i", TypeSignatureFactory::intLiteral),
                    std::pair("f", TypeSignatureFactory::floatLiteral),
                    std::pair("world", TypeSignatureFactory::boolLiteral),
                    std::pair("character", TypeSignatureFactory::boolLiteral),
                    std::pair("str", TypeSignatureFactory::boolLiteral),
                    std::pair("identifier", TypeSignatureFactory::boolLiteral),
                    std::pair("array", TypeSignatureFactory::boolLiteral),
                    std::pair("arrAccess", TypeSignatureFactory::boolLiteral),
                    std::pair("obj", new StructTypeSignature(
                        TypeSignatureMap<TypeSignature>({
                            std::pair("test", TypeSignatureFactory::intLiteral),
                            std::pair("nest", new StructTypeSignature(
                                TypeSignatureMap<TypeSignature>({
                                    std::pair("value", TypeSignatureFactory::boolLiteral),
                                })
                            )),
                        })
                    )),
                    std::pair("binary", TypeSignatureFactory::intLiteral),
                    std::pair("logical", TypeSignatureFactory::boolLiteral),
                    std::pair("unary", TypeSignatureFactory::boolLiteral),
                })
        )},
        {70, TypeSignatureFactory::boolLiteral},
        {71, TypeSignatureFactory::intLiteral},
        {72, TypeSignatureFactory::boolLiteral},
        {73, new ArrayTypeSignature(
            new StructTypeSignature(
                TypeSignatureMap({
                    std::pair("hello", TypeSignatureFactory::stringLiteral),
                    std::pair("test", TypeSignatureFactory::intLiteral),
                })
            )
        )},
        {74, TypeSignatureFactory::stringLiteral},
        {75, new StructTypeSignature(
                TypeSignatureMap({
                    std::pair("array",
                        new ArrayTypeSignature(
                            new StructTypeSignature(
                                TypeSignatureMap({
                                    std::pair("hello", TypeSignatureFactory::stringLiteral),
                                    std::pair("test", TypeSignatureFactory::intLiteral),
                                })
                        )
                    )),
                    std::pair("arrNested", new ArrayTypeSignature(
                        new ArrayTypeSignature(
                            new StructTypeSignature(
                                TypeSignatureMap({
                                    std::pair("hello", TypeSignatureFactory::stringLiteral),
                                    std::pair("test", TypeSignatureFactory::intLiteral),
                                })
                            )
                        )
                    )),
                })
        )},
        {76, TypeSignatureFactory::stringLiteral},
        {77, TypeSignatureFactory::stringLiteral},
        {78, new FunctionTypeSignature(
            new ParameterListTypeSignature({
               TypeSignatureFactory::createIntParameter("x"),
               TypeSignatureFactory::createIntParameter("y")
            }),
            TypeSignatureFactory::intLiteral
        )},
        {79, new FunctionTypeSignature(
                new ParameterListTypeSignature(),
                TypeSignatureFactory::intLiteral
        )},
        {80, new ProcedureTypeSignature(
                new ParameterListTypeSignature({
                    TypeSignatureFactory::createIntParameter("num")
                })
        )},
        {81, new ProcedureTypeSignature(
                new ParameterListTypeSignature()
        )},
        {82, new ProcedureTypeSignature(
                new ParameterListTypeSignature()
        )},
        {83, new EnumAccessTypeSignature(
                new EnumTypeSignature(
                    TypeSignatureFactory::stringLiteral,
                    TypeSignatureMap<LiteralTypeSignature>({
                        std::pair("Red", TypeSignatureFactory::stringLiteral),
                        std::pair("Blue", TypeSignatureFactory::stringLiteral),
                        std::pair("Green", TypeSignatureFactory::stringLiteral),
                })),
                "Red"
        )},
        {84, new EnumTypeSignature(
                TypeSignatureFactory::stringLiteral,
                TypeSignatureMap<LiteralTypeSignature>({
                   std::pair("Red", TypeSignatureFactory::stringLiteral),
                   std::pair("Blue", TypeSignatureFactory::stringLiteral),
                   std::pair("Green", TypeSignatureFactory::stringLiteral),
               }))
        },
        {85, new EnumTypeSignature(
                TypeSignatureFactory::charLiteral,
                TypeSignatureMap<LiteralTypeSignature>({
                   std::pair("Red", TypeSignatureFactory::charLiteral),
                   std::pair("Blue", TypeSignatureFactory::charLiteral),
                   std::pair("Green", TypeSignatureFactory::charLiteral),
               }))
        },
        {86, new EnumTypeSignature(
                TypeSignatureFactory::intLiteral,
                TypeSignatureMap<LiteralTypeSignature>({
                   std::pair("Zero", TypeSignatureFactory::intLiteral),
                   std::pair("One", TypeSignatureFactory::intLiteral),
                   std::pair("Two", TypeSignatureFactory::intLiteral),
                }))
        },
        {87, TypeSignatureFactory::boolLiteral},
        {88, TypeSignatureFactory::boolLiteral},
        {89, new TupleTypeSignature({
                TypeSignatureFactory::stringLiteral,
                TypeSignatureFactory::intLiteral,
                TypeSignatureFactory::intLiteral
        })},
        {90, new FunctionTypeSignature(
                new ParameterListTypeSignature(),
                TypeSignatureFactory::stringLiteral
        )},
        {91, new LambdaExpressionTypeSignature(
                new ParameterListTypeSignature({
                    new ParameterListItemTypeSignature(
                        "x",
                        new EnumTypeSignature(
                            TypeSignatureFactory::stringLiteral,
                            TypeSignatureMap<LiteralTypeSignature>({
                                   std::pair("Red", TypeSignatureFactory::stringLiteral),
                                   std::pair("Blue", TypeSignatureFactory::stringLiteral),
                                   std::pair("Green", TypeSignatureFactory::stringLiteral),
                       })))
        }), new EnumTypeSignature(
                TypeSignatureFactory::stringLiteral,
                TypeSignatureMap<LiteralTypeSignature>({
                   std::pair("Red", TypeSignatureFactory::stringLiteral),
                   std::pair("Blue", TypeSignatureFactory::stringLiteral),
                   std::pair("Green", TypeSignatureFactory::stringLiteral),
        })))},
        {92, new LambdaExpressionTypeSignature(
                new ParameterListTypeSignature({
                   new ParameterListItemTypeSignature("x", TypeSignatureFactory::intLiteral),
                   new ParameterListItemTypeSignature("y", TypeSignatureFactory::intLiteral),
                }),
                TypeSignatureFactory::boolLiteral
        )},
        {93, new LambdaExpressionTypeSignature(
                new ParameterListTypeSignature({
                   new ParameterListItemTypeSignature("x", TypeSignatureFactory::intLiteral),
               }),
               TypeSignatureFactory::intLiteral
       )},
        {94, new LambdaExpressionTypeSignature(
                new ParameterListTypeSignature({
                    new ParameterListItemTypeSignature("x", TypeSignatureFactory::intLiteral),
                }),
                new LambdaExpressionTypeSignature(
                    new ParameterListTypeSignature({
                       new ParameterListItemTypeSignature("y", TypeSignatureFactory::intLiteral),
                }),
                new LambdaExpressionTypeSignature(
                    new ParameterListTypeSignature({
                       new ParameterListItemTypeSignature("z", TypeSignatureFactory::intLiteral),
                    }),
                    TypeSignatureFactory::intLiteral
                ))
        )},
        {95, TypeSignatureFactory::boolLiteral},


};

TEST_CASE( "should print the expected type signatures" ) {
    std::string filePath = "./semantic-analyzer-test-file.jet";
    auto tokenTable = new TokenTable();
    auto reservedKeywords = new ReservedKeywords();
    auto lexicalAnalyzer = new LexicalAnalyzer(tokenTable, reservedKeywords);
    auto syntaxAnalyzer = SyntaxAnalyzer(tokenTable, lexicalAnalyzer);
    auto fileNodeResult = syntaxAnalyzer.analyze(filePath);
    auto dependencyGraph = new DependencyGraph();
    auto typeSignatureLookupTable = new TypeSignatureLookupTable();
    auto semanticAnalyzer = SemanticAnalyzer(dependencyGraph, tokenTable, typeSignatureLookupTable);
    semanticAnalyzer.analyze(fileNodeResult);
    Logger::log("===== TEST LOGS =====");
    typeSignatureLookupTable->dump();
//    REQUIRE(fileNodeResult->getBody()->size() == 118);
    for (int i = 0; i < 95; i++) {
        auto declaration = fileNodeResult->getBody()->getContents()[i];
        auto typeSignature = typeSignatureLookupTable->find(declaration->getId());
        Logger::log("=====", i + 1, declaration->toString(), "=====");
        Logger::log("ID -", declaration->getId());
        typeSignature->print();
        Logger::log("RESULT =", typeSignature->isEqualTo(expectedTypeSignature[i + 1]));
        REQUIRE(typeSignature->isEqualTo(expectedTypeSignature[i + 1]));
        Logger::log("====================================");
    }
}
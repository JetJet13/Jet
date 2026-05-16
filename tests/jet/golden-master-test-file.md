# Golden Master Test File

### Objective
The purpose of the `golden-master-test-file.jet` test file is to validate that every supported feature of the language works as expected.

### Language Features
1. Literals
   - [x] Integer
     - [x] Overflow
   - [x] Float
   - [x] Boolean
   - [x] Character
2. Strings
   - [x] Concatenation (`++`)
   - [x] Prototype Functions 
     - [x] `append`
     - [x] `prepend`
     - [x] `take`
     - [x] `takeLast`
     - [x] `drop`
     - [x] `dropLast`
     - [x] `size`
     - [x] `empty`
     - [x] `tail`
3. Arrays
   - [x] Concatenation (`++`)
   - [x] Prototype Functions
     - [x] `append`
     - [x] `prepend`
     - [x] `take`
     - [x] `takeLast`
     - [x] `drop`
     - [x] `dropLast`
     - [x] `size`
     - [x] `empty`
     - [x] `tail`
4. Structs
    - [x] Done
5. Tuples 
    - [x] Done
6. Classes
   - [x] Multiple Constructors
   - [x] Access Modifiers (`public`, `private`)
   - [x] Static Modifier (`static`)
7. Enums
   - [x] Literal Value
   - [x] String Value
8. References
    - [x] Prototype Functions
      - [x] `refCount`
      - [x] `sameRefAs`
   - [x] Set Ref Value (`:=`)
9. Lambdas
    - [x] Done
10. Modules
    - [x] Import
    - [x] Export
    - [x] Declaration
11. Built-In Functions
    - [x] `print(...vararg)`
    - [x] `range`
      - [x] `range(end: int)`
      - [x] `range(start: int, end: int)`
      - [x] `range(start: int, end: int, step: int)`
    - [x] `assert`
      - [x] `assert(bool)`
      - [x] `assert(bool, message)`
12. Logical Expressions
    - [x] Done
13. Arithmetic Expressions
    - [x] Order of Operations (BEDMAS)
    - [x] addition (`+`)
    - [x] subtraction (`-`)
    - [x] multiplication (`*`)
    - [x] division (`/`)
    - [x] modulo (`mod`)
14. Unary Expressions
    - [x] `+` int or float
    - [x] `-` int or float
    - [x] `!` negate 
15. Comparator Expressions
    - [x] Done
16. If Statements
    - [x] Done
17. While Statements
    - [x] Done
18. For-in Statements
    - [x] Done
19. Functions
    - [x] Function Overrides
    - [x] Recursive Functions
20. Procedures
    - [x] Procedure Overrides
21. Variables
    - [x] Constant (`const`)
    - [x] Mutable (`let`)
22. Global Variables
    - [x] Constant (`const`)
    - [x] Mutable (`let`)
23. Memory Management
    - [x] ARC (automatic reference counting)
    - [x] RAII
# Frequently Answered Questions
1. **Why Create Another Programming Language?**<br/>
A: I created Jet for 3 Reasons (not in order):
   1. To learn
   2. To contribute to OSS
   3. Accomplish a personal goal
2. **Is Jet vibe-coded?**<br/>
A: Absolutely not. Jet is 100% written by hand. It took 3 years worth of free-time on week nights and weekends to get to v0.1.0-alpha.
3. **What role did AI play in creating Jet?**<br/>
A: AI was only used for learning purposes and to help make sense of obscure LLVM errors. For example, I found it to be great resource for learning about cross-compiling C/C++ projects with Zig. It has no influence on the design of the language or the compiler. The [Jet site](https://jet-lang.com) and the documentation in this repo are also written by hand.
4. **What materials/resources did you use to help you create Jet?**<br/>
A: In order of significance:
   1. Crafting Interpreters - Robert Nystrom
   2. Compilers - Principles, Techniques, & Tools (Second Edition) - Alfred Aho, Monica Lam, Ravi Sethi, Jeffrey Ullman
   3. The Garbage Collection Handbook (Second Edition) - Richard Jones, Antony Hosking, Eliot Moss
5. **How does Jet work under the hood?**<br/>
A: Jet has a custom frontend that I wrote by hand using the shift-reduce (bottom-up) parsing technique and the backend is built using LLVM v17.
6. **Why did you write a custom frontend when tools like Yacc and Bison are proven and available?**<br/>
A. After completing the Crafting Interpreters book, I felt that I had gained enough confidence and foundational knowledge to write my own custom frontend. Had I used a tool like Yacc or Bison, it would've felt like cheating.
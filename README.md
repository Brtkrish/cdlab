# Compiler Design Lab - Programs

| File | Description |
|---|---|
| 01_lexer.c | Lexical analyzer (keywords, identifiers, numbers, symbols) |
| 02_eclosure.c | Epsilon-closure of all NFA states |
| 03_enfa2nfa.c | Convert epsilon-NFA to NFA without epsilon |
| 04_nfa2dfa.c | Convert NFA to DFA (subset construction) |
| 05_mindfa.c | Minimize a DFA (partition refinement) |
| 06_reject.l | LEX: reject strings containing first 4 chars of name (NIYA) |
| 07_variable.l, 07_variable.y | LEX+YACC: validate a variable name |
| 08_calc.l, 08_calc.y | LEX+YACC: calculator |
| 09_ast.l, 09_ast.y | LEX+YACC: BNF to YACC, builds AST (preorder print) |
| 10_forloop.l, 10_forloop.y | LEX+YACC: syntax check of C FOR statement |
| 11_opp.c | Operator precedence parser |
| 12_firstfollow.c | FIRST and FOLLOW simulation |
| 13_rdp.c | Recursive descent parser for expressions |
| 14_shiftreduce.c | Shift-reduce parser |

Build: `gcc x.c -o x` | LEX: `flex x.l && gcc lex.yy.c -o x` | LEX+YACC: `bison -dy x.y && flex x.l && gcc y.tab.c lex.yy.c -o x`

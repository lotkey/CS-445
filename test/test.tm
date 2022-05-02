* ** ** ** ** ** ** ** ** ** ** ** **
* START IO library functions
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION input
1:      ST  3,-1(1)    Store return address
2:      IN  2,0,0      Grab int input
3:      LD  3,-1(1)    Load return address
4:      LD  1,0(1)     Adjust fp
5:     JMP  7,0(3)     Return
* END FUNCTION input
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION output
6:      ST  3,-1(1)    Store return address
7:      LD  3,-2(1)    Load parameter
8:     OUT  3,0,0      Output integer
9:      LD  3,-1(1)    Load return address
10:     LD  1,0(1)     Adjust fp
11:    JMP  7,0(3)     Return
* END FUNCTION output
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputb
12:     ST  3,-1(1)    Store return address
13:    INB  2,0,0      Grab bool input
14:     LD  3,-1(1)    Load return address
15:     LD  1,0(1)     Adjust fp
16:    JMP  7,0(3)     Return
* END FUNCTION inputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputb
17:     ST  3,-1(1)    Store return address
18:     LD  3,-2(1)    Load parameter
19:   OUTB  3,0,0      Output bool
20:     LD  3,-1(1)    Load return address
21:     LD  1,0(1)     Adjust fp
22:    JMP  7,0(3)     Return
* END FUNCTION outputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputc
23:     ST  3,-1(1)    Store return address
24:    INC  2,0,0      Grab char input
25:     LD  3,-1(1)    Load return address
26:     LD  1,0(1)     Adjust fp
27:    JMP  7,0(3)     Return
* END FUNCTION inputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputc
28:     ST  3,-1(1)    Store return address
29:     LD  3,-2(1)    Load parameter
30:   OUTC  3,0,0      Output char
31:     LD  3,-1(1)    Load return address
32:     LD  1,0(1)     Adjust fp
33:    JMP  7,0(3)     Return
* END FUNCTION outputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputnl
34:     ST  3,-1(1)    Store return address
35:  OUTNL  0,0,0      Output integer
36:     LD  3,-1(1)    Load return address
37:     LD  1,0(1)     Adjust fp
38:    JMP  7,0(3)     Return
* END FUNCTION output
* ** ** ** ** ** ** ** ** ** ** ** **
* END IO library functions
* ** ** ** ** ** ** ** ** ** ** ** **
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* START User-declared functions
* START FUNCTION main
* * * TOFF set: -2
39:     ST  3,-1(1)    Store return address
* * * START COMPOUND
* * * * TOFF set: -2
* * * * COMPOUND BODY
* * * * * START BINARY ASGN
* * * * * * START CONSTANT Const 2
40:    LDC  3,2(6)     Load constant
* * * * * * END CONSTANT Const 2
41:     ST  3,-2(1)    Push index
* * * * * * TOFF dec: -3
* * * * * * START CONSTANT Const true
42:    LDC  3,1(6)     Load constant
* * * * * * END CONSTANT Const true
* * * * * * TOFF inc: -2
43:     LD  4,-2(1)    Pop index
44:    LDA  5,-1(0)    Load address of base of array x
45:    SUB  5,5,4      Compute offset of value
46:     ST  3,0(5)     Store variable x
* * * * * END BINARY ASGN
* * * * * START BINARY ASGN
* * * * * * START CONSTANT Const 1
47:    LDC  3,1(6)     Load constant
* * * * * * END CONSTANT Const 1
48:     ST  3,-2(1)    Push index
* * * * * * TOFF dec: -3
* * * * * * START CONSTANT Const false
49:    LDC  3,0(6)     Load constant
* * * * * * END CONSTANT Const false
* * * * * * TOFF inc: -2
50:     LD  4,-2(1)    Pop index
51:    LDA  5,-5(0)    Load address of base of array y
52:    SUB  5,5,4      Compute offset of value
53:     ST  3,0(5)     Store variable y
* * * * * END BINARY ASGN
* * * * * START CALL outputb
54:     ST  1,-2(1)    Store FP in ghost frame for output
* * * * * * TOFF dec: -3
* * * * * * START Params
* * * * * * TOFF dec: -4
* * * * * * Param 1
55:    LDA  3,-1(0)    Load address of base of array x
56:     ST  3,-4(1)    Push left side
* * * * * * TOFF dec: -5
* * * * * * START CONSTANT Const 2
57:    LDC  3,2(6)     Load constant
* * * * * * END CONSTANT Const 2
* * * * * * TOFF inc: -4
58:     LD  4,-4(1)    Pop left into AC1
59:    SUB  3,4,3      Compute location from index
60:     LD  3,0(3)     Load array element
61:     ST  3,-4(1)    Push left side
* * * * * * TOFF dec: -5
62:    LDA  3,-5(0)    Load address of base of array y
63:     ST  3,-5(1)    Push left side
* * * * * * TOFF dec: -6
* * * * * * START CONSTANT Const 1
64:    LDC  3,1(6)     Load constant
* * * * * * END CONSTANT Const 1
* * * * * * TOFF inc: -5
65:     LD  4,-5(1)    Pop left into AC1
66:    SUB  3,4,3      Compute location from index
67:     LD  3,0(3)     Load array element
* * * * * * TOFF inc: -4
68:     LD  4,-4(1)    Pop left into AC1
69:     OR  3,4,3      Op OR
70:     ST  3,-4(1)    Push parameter
* * * * * * END Params
* * * * * * TOFF set: -2
71:    LDA  1,-2(1)    Ghost frame becomes new active frame
72:    LDA  3,1(7)     Return address in AC
73:    JMP  7,-57(7)   CALL outputb
74:    LDA  3,0(2)     Save the result in AC
* * * * * END CALL outputb
* * * * * START CALL outnl
75:     ST  1,-2(1)    Store FP in ghost frame for output
* * * * * * TOFF dec: -3
* * * * * * START Params
* * * * * * END Params
* * * * * * TOFF set: -2
76:    LDA  1,-2(1)    Ghost frame becomes new active frame
77:    LDA  3,1(7)     Return address in AC
78:    JMP  7,-45(7)   CALL outnl
79:    LDA  3,0(2)     Save the result in AC
* * * * * END CALL outnl
* * * * END COMPOUND BODY
* * * END COMPOUND
* * * Add standard closing in case there is no return statement
80:    LDC  2,0(6)     Set return value to 0
81:     LD  3,-1(1)    Load return address
82:     LD  1,0(0)     Adjust fp
83:    JMP  7,0(3)     Return
* * END FUNCTION main
* ** ** ** ** ** ** ** ** ** ** ** **
* * END User-declared functions
* ** ** ** ** ** ** ** ** ** ** ** **
* * 
* ** ** ** ** ** ** ** ** ** ** ** **
* * START INIT
* ** ** ** ** ** ** ** ** ** ** ** **
0:     JMP  7,83(7)    Jump to init [backpatch]
84:    LDA  1,0(0)     Set first frame at end of globals
85:     ST  1,0(1)     Store old FP (point to self)
* * START GLOBALS AND STATICS
* * START VAR DECL x
86:    LDC  3,3(6)     Load size of array x
87:     ST  3,0(0)     Store size of x
* * END VAR DECL x
* * START VAR DECL y
88:    LDC  3,4(6)     Load size of array y
89:     ST  3,-4(0)    Store size of y
* * END VAR DECL y
* * END GLOBALS AND STATICS
90:    LDA  3,1(7)     Return address in AC
91:    JMP  7,-53(7)   Jump to main
92:   HALT  0,0,0      DONE!
* ** ** ** ** ** ** ** ** ** ** ** **
* * END INIT
* ** ** ** ** ** ** ** ** ** ** ** **

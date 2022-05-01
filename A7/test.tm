* ** ** ** ** ** ** ** ** ** ** ** **
* START IO library functions
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION input
1:      ST  3,-1(1)    Store return address
2:      IN  3,0,0      Grab int input
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
13:    INB  3,0,0      Grab bool input
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
24:    INC  3,0,0      Grab char input
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
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
* TOFF set: -2
39:     ST  3,-1(1)    Store return address
* COMPOUND
* TOFF set: -10
* LOCAL DECLARATIONS
40:    LDC  3,7(6)     Load size of array x
41:     ST  3,-2(0)    Store size of x
* END LOCAL DECLARATIONS
* COMPOUND BODY
42:    LDC  3,3(6)     Load constant
43:     ST  3,-10(1)   Push index
44:    LDC  3,1023(6)  Load constant
45:     LD  4,-10(1)   Pop index
46:    LDA  5,-3(1)    Load address of base of array x
47:    SUB  5,5,4      Compute offset of value
48:     ST  3,0(5)     Store variable x
* CALL output
49:     ST  1,-10(1)   Store FP in ghost frame for output
* START Params
* Param 1
50:     ST  3,-12(1)   Push parameter
* END Params
51:    LDA  1,-10(1)   Ghost frame becomes new active frame
52:    LDA  3,1(7)     Return address in AC
53:    JMP  7,-48(7)   CALL output
54:    LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
55:     ST  1,-10(1)   Store FP in ghost frame for output
* START Params
* END Params
56:    LDA  1,-10(1)   Ghost frame becomes new active frame
57:    LDA  3,1(7)     Return address in AC
58:    JMP  7,-25(7)   CALL outnl
59:    LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
60:     ST  1,-10(1)   Store FP in ghost frame for output
* START Params
* Param 1
61:     ST  3,-12(1)   Push parameter
* END Params
62:    LDA  1,-10(1)   Ghost frame becomes new active frame
63:    LDA  3,1(7)     Return address in AC
64:    JMP  7,-59(7)   CALL output
65:    LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
66:     ST  1,-10(1)   Store FP in ghost frame for output
* START Params
* END Params
67:    LDA  1,-10(1)   Ghost frame becomes new active frame
68:    LDA  3,1(7)     Return address in AC
69:    JMP  7,-36(7)   CALL outnl
70:    LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
71:     ST  1,-10(1)   Store FP in ghost frame for output
* START Params
* Param 1
72:     ST  3,-12(1)   Push parameter
* END Params
73:    LDA  1,-10(1)   Ghost frame becomes new active frame
74:    LDA  3,1(7)     Return address in AC
75:    JMP  7,-70(7)   CALL output
76:    LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
77:     ST  1,-10(1)   Store FP in ghost frame for output
* START Params
* END Params
78:    LDA  1,-10(1)   Ghost frame becomes new active frame
79:    LDA  3,1(7)     Return address in AC
80:    JMP  7,-47(7)   CALL outnl
81:    LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
82:     ST  1,-10(1)   Store FP in ghost frame for output
* START Params
* Param 1
83:     ST  3,-12(1)   Push parameter
* END Params
84:    LDA  1,-10(1)   Ghost frame becomes new active frame
85:    LDA  3,1(7)     Return address in AC
86:    JMP  7,-81(7)   CALL output
87:    LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
88:     ST  1,-10(1)   Store FP in ghost frame for output
* START Params
* END Params
89:    LDA  1,-10(1)   Ghost frame becomes new active frame
90:    LDA  3,1(7)     Return address in AC
91:    JMP  7,-58(7)   CALL outnl
92:    LDA  3,0(2)     Save the result in AC
* CALL END outnl
* END COMPOUND BODY
* END COMPOUND
* Add standard closing in case there is no return statement
93:    LDC  2,0(6)     Set return value to 0
94:     LD  3,-1(1)    Load return address
95:     LD  1,0(0)     Adjust fp
96:    JMP  7,0(3)     Return
* END FUNCTION main
* ** ** ** ** ** ** ** ** ** ** ** **
* END User-declared functions
* ** ** ** ** ** ** ** ** ** ** ** **
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* START INIT
* ** ** ** ** ** ** ** ** ** ** ** **
97:    LDA  1,0(0)     Set first frame at end of globals
98:     ST  1,0(1)     Store old FP (point to self)
* START GLOBALS AND STATICS
* END GLOBALS AND STATICS
99:    LDA  3,1(7)     Return address in AC
100:   JMP  7,7(60)    Jump to main
101:  HALT  0,0,0      DONE!
* ** ** ** ** ** ** ** ** ** ** ** **
* END INIT
* ** ** ** ** ** ** ** ** ** ** ** **

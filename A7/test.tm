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
* TOFF set: -3
* LOCAL DECLARATIONS
* END LOCAL DECLARATIONS
* COMPOUND BODY
40:    LDC  3,0(6)     Load constant
41:     ST  3,-2(1)    Store variable x
* IF
42:    LDC  3,0(6)     Load constant
* THEN
* WHILE
44:     LD  3,-2(1)    Load variable x
45:     ST  3,-3(1)    Push left side
* TOFF dec: -4
46:    LDC  3,10(6)    Load constant
* TOFF inc: -3
47:     LD  4,-3(1)    Pop left into AC1
48:    TLT  3,4,3      Op <
49:    JNZ  3,1(7)     Jump to while part
* COMPOUND
* TOFF set: -3
* COMPOUND BODY
* CALL output
51:     ST  1,-3(1)    Store FP in ghost frame for output
* TOFF dec: -4
* START Params
* TOFF dec: -5
* Param 1
52:     LD  3,-2(1)    Load variable x
53:     ST  3,-5(1)    Push parameter
* END Params
* TOFF set: -3
54:    LDA  1,-3(1)    Ghost frame becomes new active frame
55:    LDA  3,1(7)     Return address in AC
56:    JMP  7,-51(7)   CALL output
57:    LDA  3,0(2)     Save the result in AC
* CALL END output
58:     LD  3,-2(1)    Load variable x
59:     ST  3,-2(1)    Push left side
* TOFF dec: -4
60:    LDC  3,1(6)     Load constant
* TOFF inc: -3
61:     LD  4,-2(1)    Pop left into AC1
62:    ADD  3,4,3      Op +
63:     ST  3,-2(1)    Store variable x
* END COMPOUND BODY
* END COMPOUND
64:    JMP  7,-22(7)   Go to beginning of loop
50:    JMP  7,15(7)    Jump past loop [backpatch]
* END WHILE
* END THEN
43:    JZR  3,22(7)    Jump around the THEN if false [backpatch]
* ELSE
* CALL output
65:     ST  1,-3(1)    Store FP in ghost frame for output
* TOFF dec: -4
* START Params
* TOFF dec: -5
* Param 1
66:    LDC  3,666(6)   Load constant ⸸
67:     ST  3,-5(1)    Push parameter
* END Params
* TOFF set: -3
68:    LDA  1,-3(1)    Ghost frame becomes new active frame
69:    LDA  3,1(7)     Return address in AC
70:    JMP  7,-65(7)   CALL output
71:    LDA  3,0(2)     Save the result in AC
* CALL END output
* END ELSE
* END IF
72:    LDC  3,0(6)     Load constant
73:     ST  3,-2(1)    Store variable x
* IF
74:    LDC  3,1(6)     Load constant
* THEN
* WHILE
76:     LD  3,-2(1)    Load variable x
77:     ST  3,-3(1)    Push left side
* TOFF dec: -4
78:    LDC  3,10(6)    Load constant
* TOFF inc: -3
79:     LD  4,-3(1)    Pop left into AC1
80:    TLT  3,4,3      Op <
81:    JNZ  3,1(7)     Jump to while part
* COMPOUND
* TOFF set: -3
* COMPOUND BODY
* CALL output
83:     ST  1,-3(1)    Store FP in ghost frame for output
* TOFF dec: -4
* START Params
* TOFF dec: -5
* Param 1
84:     LD  3,-2(1)    Load variable x
85:     ST  3,-5(1)    Push parameter
* END Params
* TOFF set: -3
86:    LDA  1,-3(1)    Ghost frame becomes new active frame
87:    LDA  3,1(7)     Return address in AC
88:    JMP  7,-83(7)   CALL output
89:    LDA  3,0(2)     Save the result in AC
* CALL END output
90:     LD  3,-2(1)    Load variable x
91:     ST  3,-2(1)    Push left side
* TOFF dec: -4
92:    LDC  3,1(6)     Load constant
* TOFF inc: -3
93:     LD  4,-2(1)    Pop left into AC1
94:    ADD  3,4,3      Op +
95:     ST  3,-2(1)    Store variable x
* END COMPOUND BODY
* END COMPOUND
96:    JMP  7,-22(7)   Go to beginning of loop
82:    JMP  7,15(7)    Jump past loop [backpatch]
* END WHILE
* END THEN
75:    JZR  3,22(7)    Jump around the THEN if false [backpatch]
* ELSE
* CALL output
97:     ST  1,-3(1)    Store FP in ghost frame for output
* TOFF dec: -4
* START Params
* TOFF dec: -5
* Param 1
98:    LDC  3,666(6)   Load constant ⸸
99:     ST  3,-5(1)    Push parameter
* END Params
* TOFF set: -3
100:   LDA  1,-3(1)    Ghost frame becomes new active frame
101:   LDA  3,1(7)     Return address in AC
102:   JMP  7,-97(7)   CALL output
103:   LDA  3,0(2)     Save the result in AC
* CALL END output
* END ELSE
* END IF
* END COMPOUND BODY
* END COMPOUND
* Add standard closing in case there is no return statement
104:   LDC  2,0(6)     Set return value to 0
105:    LD  3,-1(1)    Load return address
106:    LD  1,0(0)     Adjust fp
107:   JMP  7,0(3)     Return
* END FUNCTION main
* ** ** ** ** ** ** ** ** ** ** ** **
* END User-declared functions
* ** ** ** ** ** ** ** ** ** ** ** **
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* START INIT
* ** ** ** ** ** ** ** ** ** ** ** **
108:   LDA  1,0(0)     Set first frame at end of globals
109:    ST  1,0(1)     Store old FP (point to self)
* START GLOBALS AND STATICS
* END GLOBALS AND STATICS
110:   LDA  3,1(7)     Return address in AC
111:   JMP  7,7(71)    Jump to main
112:  HALT  0,0,0      DONE!
* ** ** ** ** ** ** ** ** ** ** ** **
* END INIT
* ** ** ** ** ** ** ** ** ** ** ** **

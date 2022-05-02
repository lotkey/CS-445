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
* ** ** ** ** ** ** ** ** ** ** ** **
* START FUNCTION dog
* * * TOFF set: -3
39:     ST  3,-1(1)    Store return address
* * * START COMPOUND
* * * * TOFF set: -3
* * * * COMPOUND BODY
* * * * * START CALL output
40:     ST  1,-3(1)    Store FP in ghost frame for output
* * * * * * TOFF dec: -4
* * * * * * START Params
* * * * * * TOFF dec: -5
* * * * * * Param 1
41:    LDA  3,-2(1)    Load address of base of array x
42:     ST  3,-5(1)    Push left side
* * * * * * TOFF dec: -6
* * * * * * START CONSTANT Const 3
43:    LDC  3,3(6)     Load constant
* * * * * * END CONSTANT Const 3
* * * * * * TOFF inc: -5
44:     LD  4,-5(1)    Pop left into AC1
45:    SUB  3,4,3      Compute location from index
46:     LD  3,0(3)     Load array element
47:    LDA  3,1(3)     Increment value of x
48:     ST  3,0(5)     
49:     ST  3,-5(1)    Push parameter
* * * * * * END Params
* * * * * * TOFF set: -3
50:    LDA  1,-3(1)    Ghost frame becomes new active frame
51:    LDA  3,1(7)     Return address in AC
52:    JMP  7,-47(7)   CALL output
53:    LDA  3,0(2)     Save the result in AC
* * * * * END CALL output
* * * * * START CALL outnl
54:     ST  1,-3(1)    Store FP in ghost frame for output
* * * * * * TOFF dec: -4
* * * * * * START Params
* * * * * * END Params
* * * * * * TOFF set: -3
55:    LDA  1,-3(1)    Ghost frame becomes new active frame
56:    LDA  3,1(7)     Return address in AC
57:    JMP  7,-24(7)   CALL outnl
58:    LDA  3,0(2)     Save the result in AC
* * * * * END CALL outnl
* * * * * START CALL output
59:     ST  1,-3(1)    Store FP in ghost frame for output
* * * * * * TOFF dec: -4
* * * * * * START Params
* * * * * * TOFF dec: -5
* * * * * * Param 1
60:    LDA  3,-2(1)    Load address of base of array x
61:     ST  3,-5(1)    Push left side
* * * * * * TOFF dec: -6
* * * * * * START CONSTANT Const 3
62:    LDC  3,3(6)     Load constant
* * * * * * END CONSTANT Const 3
* * * * * * TOFF inc: -5
63:     LD  4,-5(1)    Pop left into AC1
64:    SUB  3,4,3      Compute location from index
65:     LD  3,0(3)     Load array element
66:     ST  3,-5(1)    Push parameter
* * * * * * END Params
* * * * * * TOFF set: -3
67:    LDA  1,-3(1)    Ghost frame becomes new active frame
68:    LDA  3,1(7)     Return address in AC
69:    JMP  7,-64(7)   CALL output
70:    LDA  3,0(2)     Save the result in AC
* * * * * END CALL output
* * * * * START CALL outnl
71:     ST  1,-3(1)    Store FP in ghost frame for output
* * * * * * TOFF dec: -4
* * * * * * START Params
* * * * * * END Params
* * * * * * TOFF set: -3
72:    LDA  1,-3(1)    Ghost frame becomes new active frame
73:    LDA  3,1(7)     Return address in AC
74:    JMP  7,-41(7)   CALL outnl
75:    LDA  3,0(2)     Save the result in AC
* * * * * END CALL outnl
* * * * * START CALL output
76:     ST  1,-3(1)    Store FP in ghost frame for output
* * * * * * TOFF dec: -4
* * * * * * START Params
* * * * * * TOFF dec: -5
* * * * * * Param 1
77:    LDA  3,-2(1)    Load address of base of array x
78:     ST  3,-5(1)    Push left side
* * * * * * TOFF dec: -6
* * * * * * START CONSTANT Const 3
79:    LDC  3,3(6)     Load constant
* * * * * * END CONSTANT Const 3
* * * * * * TOFF inc: -5
80:     LD  4,-5(1)    Pop left into AC1
81:    SUB  3,4,3      Compute location from index
82:     LD  3,0(3)     Load array element
83:    LDA  3,-1(3)    Decrement value of x
84:     ST  3,0(5)     
85:     ST  3,-5(1)    Push parameter
* * * * * * END Params
* * * * * * TOFF set: -3
86:    LDA  1,-3(1)    Ghost frame becomes new active frame
87:    LDA  3,1(7)     Return address in AC
88:    JMP  7,-83(7)   CALL output
89:    LDA  3,0(2)     Save the result in AC
* * * * * END CALL output
* * * * * START CALL outnl
90:     ST  1,-3(1)    Store FP in ghost frame for output
* * * * * * TOFF dec: -4
* * * * * * START Params
* * * * * * END Params
* * * * * * TOFF set: -3
91:    LDA  1,-3(1)    Ghost frame becomes new active frame
92:    LDA  3,1(7)     Return address in AC
93:    JMP  7,-60(7)   CALL outnl
94:    LDA  3,0(2)     Save the result in AC
* * * * * END CALL outnl
* * * * * START CALL output
95:     ST  1,-3(1)    Store FP in ghost frame for output
* * * * * * TOFF dec: -4
* * * * * * START Params
* * * * * * TOFF dec: -5
* * * * * * Param 1
96:    LDA  3,-2(1)    Load address of base of array x
97:     ST  3,-5(1)    Push left side
* * * * * * TOFF dec: -6
* * * * * * START CONSTANT Const 3
98:    LDC  3,3(6)     Load constant
* * * * * * END CONSTANT Const 3
* * * * * * TOFF inc: -5
99:     LD  4,-5(1)    Pop left into AC1
100:   SUB  3,4,3      Compute location from index
101:    LD  3,0(3)     Load array element
102:    ST  3,-5(1)    Push parameter
* * * * * * END Params
* * * * * * TOFF set: -3
103:   LDA  1,-3(1)    Ghost frame becomes new active frame
104:   LDA  3,1(7)     Return address in AC
105:   JMP  7,-100(7)  CALL output
106:   LDA  3,0(2)     Save the result in AC
* * * * * END CALL output
* * * * * START CALL outnl
107:    ST  1,-3(1)    Store FP in ghost frame for output
* * * * * * TOFF dec: -4
* * * * * * START Params
* * * * * * END Params
* * * * * * TOFF set: -3
108:   LDA  1,-3(1)    Ghost frame becomes new active frame
109:   LDA  3,1(7)     Return address in AC
110:   JMP  7,-77(7)   CALL outnl
111:   LDA  3,0(2)     Save the result in AC
* * * * * END CALL outnl
* * * * END COMPOUND BODY
* * * END COMPOUND
* * * Add standard closing in case there is no return statement
112:   LDC  2,0(6)     Set return value to 0
113:    LD  3,-1(1)    Load return address
114:    LD  1,0(1)     Adjust fp
115:   JMP  7,0(3)     Return
* * END FUNCTION dog
* * 
* ** ** ** ** ** ** ** ** ** ** ** **
* * START FUNCTION main
* * * * TOFF set: -2
116:    ST  3,-1(1)    Store return address
* * * * START COMPOUND
* * * * * TOFF set: -10
* * * * * LOCAL DECLARATIONS
* * * * * * START VAR DECL x
117:   LDC  3,7(6)     Load size of array x
118:    ST  3,-2(0)    Store size of x
* * * * * * END VAR DECL x
* * * * * END LOCAL DECLARATIONS
* * * * * COMPOUND BODY
* * * * * * START BINARY ASGN
* * * * * * * START CONSTANT Const 3
119:   LDC  3,3(6)     Load constant
* * * * * * * END CONSTANT Const 3
120:    ST  3,-10(1)   Push index
* * * * * * * TOFF dec: -11
* * * * * * * START CONSTANT Const 1023
121:   LDC  3,1023(6)  Load constant
* * * * * * * END CONSTANT Const 1023
* * * * * * * TOFF inc: -10
122:    LD  4,-10(1)   Pop index
123:   LDA  5,-3(1)    Load address of base of array x
124:   SUB  5,5,4      Compute offset of value
125:    ST  3,0(5)     Store variable x
* * * * * * END BINARY ASGN
* * * * * * START CALL dog
126:    ST  1,-10(1)   Store FP in ghost frame for output
* * * * * * * TOFF dec: -11
* * * * * * * START Params
* * * * * * * TOFF dec: -12
* * * * * * * Param 1
* * * * * * * START ID x
127:   LDA  3,-3(1)    Load address of base of array x
* * * * * * * END ID x
128:    ST  3,-12(1)   Push parameter
* * * * * * * END Params
* * * * * * * TOFF set: -10
129:   LDA  1,-10(1)   Ghost frame becomes new active frame
130:   LDA  3,1(7)     Return address in AC
131:   JMP  7,-93(7)   CALL dog
132:   LDA  3,0(2)     Save the result in AC
* * * * * * END CALL dog
* * * * * * START CALL output
133:    ST  1,-10(1)   Store FP in ghost frame for output
* * * * * * * TOFF dec: -11
* * * * * * * START Params
* * * * * * * TOFF dec: -12
* * * * * * * Param 1
134:   LDA  3,-3(1)    Load address of base of array x
135:    ST  3,-12(1)   Push left side
* * * * * * * TOFF dec: -13
* * * * * * * START CONSTANT Const 3
136:   LDC  3,3(6)     Load constant
* * * * * * * END CONSTANT Const 3
* * * * * * * TOFF inc: -12
137:    LD  4,-12(1)   Pop left into AC1
138:   SUB  3,4,3      Compute location from index
139:    LD  3,0(3)     Load array element
140:    ST  3,-12(1)   Push parameter
* * * * * * * END Params
* * * * * * * TOFF set: -10
141:   LDA  1,-10(1)   Ghost frame becomes new active frame
142:   LDA  3,1(7)     Return address in AC
143:   JMP  7,-138(7)  CALL output
144:   LDA  3,0(2)     Save the result in AC
* * * * * * END CALL output
* * * * * END COMPOUND BODY
* * * * END COMPOUND
* * * * Add standard closing in case there is no return statement
145:   LDC  2,0(6)     Set return value to 0
146:    LD  3,-1(1)    Load return address
147:    LD  1,0(1)     Adjust fp
148:   JMP  7,0(3)     Return
* * * END FUNCTION main
* ** ** ** ** ** ** ** ** ** ** ** **
* * * END User-declared functions
* ** ** ** ** ** ** ** ** ** ** ** **
* * * 
* ** ** ** ** ** ** ** ** ** ** ** **
* * * START INIT
* ** ** ** ** ** ** ** ** ** ** ** **
0:     JMP  7,148(7)   Jump to init [backpatch]
149:   LDA  1,0(0)     Set first frame at end of globals
150:    ST  1,0(1)     Store old FP (point to self)
* * * START GLOBALS AND STATICS
* * * END GLOBALS AND STATICS
151:   LDA  3,1(7)     Return address in AC
152:   JMP  7,-37(7)   Jump to main
153:  HALT  0,0,0      DONE!
* ** ** ** ** ** ** ** ** ** ** ** **
* * * END INIT
* ** ** ** ** ** ** ** ** ** ** ** **

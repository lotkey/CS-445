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
* TOFF set: -2
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
* TOFF set: -2
39:     ST  3,-1(1)    Store return address
* TOFF set: -2
* COMPOUND
* TOFF set: -2
* COMPOUND BODY
40:    LDC  3,5(6)     Load constant
41:     ST  3,-2(1)    Push index
* TOFF dec: -3
42:    LDC  3,333(6)   Load constant
* TOFF inc: -2
43:     LD  4,-2(1)    Pop index
44:    LDA  5,-1(1)    Load address of base of array x
45:    SUB  5,5,4      Compute offset of value
46:     ST  3,0(5)     Store variable x
47:    LDC  3,7(6)     Load constant
48:     ST  3,-2(1)    Push index
* TOFF dec: -3
49:    LDC  3,444(6)   Load constant
* TOFF inc: -2
50:     LD  4,-2(1)    Pop index
51:    LDA  5,-9(1)    Load address of base of array y
52:    SUB  5,5,4      Compute offset of value
53:     ST  3,0(5)     Store variable y
54:    LDC  3,5(6)     Load constant
55:     ST  3,-2(1)    Push index
* TOFF dec: -3
56:    LDA  3,-9(0)    Load address of base of array y
57:     ST  3,-3(1)    Push left side
* TOFF dec: -4
58:    LDC  3,7(6)     Load constant
* TOFF inc: -3
59:     LD  4,-3(1)    Pop left into AC1
60:    SUB  3,4,3      Compute location from index
61:     LD  3,0(3)     Load array element
* TOFF inc: -2
62:     LD  4,-2(1)    Pop index
63:    LDA  5,-1(1)    Load address of base of array x
64:    SUB  5,5,4      Compute offset of value
65:     LD  4,0(5)     Load lhs variable x
66:    ADD  3,4,3      Op +=
67:     ST  3,0(5)     Store variable x
68:    LDC  3,5(6)     Load constant
69:     ST  3,-2(1)    Push index
* TOFF dec: -3
70:    LDA  3,-9(0)    Load address of base of array y
71:     ST  3,-3(1)    Push left side
* TOFF dec: -4
72:    LDC  3,7(6)     Load constant
* TOFF inc: -3
73:     LD  4,-3(1)    Pop left into AC1
74:    SUB  3,4,3      Compute location from index
75:     LD  3,0(3)     Load array element
* TOFF inc: -2
76:     LD  4,-2(1)    Pop index
77:    LDA  5,-1(1)    Load address of base of array x
78:    SUB  5,5,4      Compute offset of value
79:     ST  3,0(5)     Store variable x
* CALL output
80:     ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
81:    LDA  3,-1(0)    Load address of base of array x
82:     ST  3,-4(1)    Push left side
* TOFF dec: -5
83:    LDC  3,5(6)     Load constant
* TOFF inc: -4
84:     LD  4,-4(1)    Pop left into AC1
85:    SUB  3,4,3      Compute location from index
86:     LD  3,0(3)     Load array element
87:     ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
88:    LDA  1,-2(1)    Ghost frame becomes new active frame
89:    LDA  3,1(7)     Return address in AC
90:    JMP  7,-85(7)   CALL output
91:    LDA  3,0(2)     Save the result in AC
* CALL END output
92:    LDC  3,7(6)     Load constant
93:     ST  3,-2(1)    Push index
* TOFF dec: -3
94:    LDA  3,-1(0)    Load address of base of array x
95:     ST  3,-3(1)    Push left side
* TOFF dec: -4
96:    LDC  3,5(6)     Load constant
* TOFF inc: -3
97:     LD  4,-3(1)    Pop left into AC1
98:    SUB  3,4,3      Compute location from index
99:     LD  3,0(3)     Load array element
* TOFF inc: -2
100:    LD  4,-2(1)    Pop index
101:   LDA  5,-9(1)    Load address of base of array y
102:   SUB  5,5,4      Compute offset of value
103:    LD  4,0(5)     Load lhs variable y
104:   DIV  3,4,3      Op /=
105:    ST  3,0(5)     Store variable y
106:   LDC  3,7(6)     Load constant
107:    ST  3,-2(1)    Push index
* TOFF dec: -3
108:   LDA  3,-1(0)    Load address of base of array x
109:    ST  3,-3(1)    Push left side
* TOFF dec: -4
110:   LDC  3,5(6)     Load constant
* TOFF inc: -3
111:    LD  4,-3(1)    Pop left into AC1
112:   SUB  3,4,3      Compute location from index
113:    LD  3,0(3)     Load array element
* TOFF inc: -2
114:    LD  4,-2(1)    Pop index
115:   LDA  5,-9(1)    Load address of base of array y
116:   SUB  5,5,4      Compute offset of value
117:    ST  3,0(5)     Store variable y
* CALL output
118:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
119:   LDA  3,-9(0)    Load address of base of array y
120:    ST  3,-4(1)    Push left side
* TOFF dec: -5
121:   LDC  3,7(6)     Load constant
* TOFF inc: -4
122:    LD  4,-4(1)    Pop left into AC1
123:   SUB  3,4,3      Compute location from index
124:    LD  3,0(3)     Load array element
125:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
126:   LDA  1,-2(1)    Ghost frame becomes new active frame
127:   LDA  3,1(7)     Return address in AC
128:   JMP  7,-123(7)  CALL output
129:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
130:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
131:   LDA  1,-2(1)    Ghost frame becomes new active frame
132:   LDA  3,1(7)     Return address in AC
133:   JMP  7,-100(7)  CALL outnl
134:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* END COMPOUND BODY
* END COMPOUND
* Add standard closing in case there is no return statement
135:   LDC  2,0(6)     Set return value to 0
136:    LD  3,-1(1)    Load return address
137:    LD  1,0(0)     Adjust fp
138:   JMP  7,0(3)     Return
* END FUNCTION main
* ** ** ** ** ** ** ** ** ** ** ** **
* END User-declared functions
* ** ** ** ** ** ** ** ** ** ** ** **
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* START INIT
* ** ** ** ** ** ** ** ** ** ** ** **
139:   LDA  1,0(0)     Set first frame at end of globals
140:    ST  1,0(1)     Store old FP (point to self)
* START GLOBALS AND STATICS
141:   LDC  3,7(6)     Load size of array x
142:    ST  3,0(0)     Store size of x
143:   LDC  3,9(6)     Load size of array y
144:    ST  3,-8(0)    Store size of y
* END GLOBALS AND STATICS
145:   LDA  3,1(7)     Return address in AC
146:   JMP  7,7(106)   Jump to main
147:  HALT  0,0,0      DONE!
* ** ** ** ** ** ** ** ** ** ** ** **
* END INIT
* ** ** ** ** ** ** ** ** ** ** ** **

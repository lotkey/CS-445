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
* TOFF set: -2
* COMPOUND BODY
* CALL outputb
40:     ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
41:    LDC  3,1(6)     Load constant
42:     ST  3,-4(1)    Push left side
* TOFF dec: -5
43:    LDC  3,1(6)     Load constant
* TOFF inc: -4
44:     LD  4,-4(1)    Pop left into AC1
45:     OR  3,4,3      Op OR
46:     ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
47:    LDA  1,-2(1)    Ghost frame becomes new active frame
48:    LDA  3,1(7)     Return address in AC
49:    JMP  7,-33(7)   CALL outputb
50:    LDA  3,0(2)     Save the result in AC
* CALL END outputb
* CALL outputb
51:     ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
52:    LDC  3,1(6)     Load constant
53:     ST  3,-4(1)    Push left side
* TOFF dec: -5
54:    LDC  3,0(6)     Load constant
* TOFF inc: -4
55:     LD  4,-4(1)    Pop left into AC1
56:     OR  3,4,3      Op OR
57:     ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
58:    LDA  1,-2(1)    Ghost frame becomes new active frame
59:    LDA  3,1(7)     Return address in AC
60:    JMP  7,-44(7)   CALL outputb
61:    LDA  3,0(2)     Save the result in AC
* CALL END outputb
* CALL outputb
62:     ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
63:    LDC  3,0(6)     Load constant
64:     ST  3,-4(1)    Push left side
* TOFF dec: -5
65:    LDC  3,1(6)     Load constant
* TOFF inc: -4
66:     LD  4,-4(1)    Pop left into AC1
67:     OR  3,4,3      Op OR
68:     ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
69:    LDA  1,-2(1)    Ghost frame becomes new active frame
70:    LDA  3,1(7)     Return address in AC
71:    JMP  7,-55(7)   CALL outputb
72:    LDA  3,0(2)     Save the result in AC
* CALL END outputb
* CALL outputb
73:     ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
74:    LDC  3,0(6)     Load constant
75:     ST  3,-4(1)    Push left side
* TOFF dec: -5
76:    LDC  3,0(6)     Load constant
* TOFF inc: -4
77:     LD  4,-4(1)    Pop left into AC1
78:     OR  3,4,3      Op OR
79:     ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
80:    LDA  1,-2(1)    Ghost frame becomes new active frame
81:    LDA  3,1(7)     Return address in AC
82:    JMP  7,-66(7)   CALL outputb
83:    LDA  3,0(2)     Save the result in AC
* CALL END outputb
* CALL outnl
84:     ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
85:    LDA  1,-2(1)    Ghost frame becomes new active frame
86:    LDA  3,1(7)     Return address in AC
87:    JMP  7,-54(7)   CALL outnl
88:    LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outputb
89:     ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
90:    LDC  3,1(6)     Load constant
91:     ST  3,-4(1)    Push left side
* TOFF dec: -5
92:    LDC  3,1(6)     Load constant
* TOFF inc: -4
93:     LD  4,-4(1)    Pop left into AC1
94:    AND  3,4,3      Op AND
95:     ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
96:    LDA  1,-2(1)    Ghost frame becomes new active frame
97:    LDA  3,1(7)     Return address in AC
98:    JMP  7,-82(7)   CALL outputb
99:    LDA  3,0(2)     Save the result in AC
* CALL END outputb
* CALL outputb
100:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
101:   LDC  3,1(6)     Load constant
102:    ST  3,-4(1)    Push left side
* TOFF dec: -5
103:   LDC  3,0(6)     Load constant
* TOFF inc: -4
104:    LD  4,-4(1)    Pop left into AC1
105:   AND  3,4,3      Op AND
106:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
107:   LDA  1,-2(1)    Ghost frame becomes new active frame
108:   LDA  3,1(7)     Return address in AC
109:   JMP  7,-93(7)   CALL outputb
110:   LDA  3,0(2)     Save the result in AC
* CALL END outputb
* CALL outputb
111:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
112:   LDC  3,0(6)     Load constant
113:    ST  3,-4(1)    Push left side
* TOFF dec: -5
114:   LDC  3,1(6)     Load constant
* TOFF inc: -4
115:    LD  4,-4(1)    Pop left into AC1
116:   AND  3,4,3      Op AND
117:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
118:   LDA  1,-2(1)    Ghost frame becomes new active frame
119:   LDA  3,1(7)     Return address in AC
120:   JMP  7,-104(7)  CALL outputb
121:   LDA  3,0(2)     Save the result in AC
* CALL END outputb
* CALL outputb
122:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
123:   LDC  3,0(6)     Load constant
124:    ST  3,-4(1)    Push left side
* TOFF dec: -5
125:   LDC  3,0(6)     Load constant
* TOFF inc: -4
126:    LD  4,-4(1)    Pop left into AC1
127:   AND  3,4,3      Op AND
128:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
129:   LDA  1,-2(1)    Ghost frame becomes new active frame
130:   LDA  3,1(7)     Return address in AC
131:   JMP  7,-115(7)  CALL outputb
132:   LDA  3,0(2)     Save the result in AC
* CALL END outputb
* CALL outnl
133:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
134:   LDA  1,-2(1)    Ghost frame becomes new active frame
135:   LDA  3,1(7)     Return address in AC
136:   JMP  7,-103(7)  CALL outnl
137:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outputb
138:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
139:   LDC  3,1(6)     Load constant
140:   LDC  4,1(6)     Load 1
141:   XOR  3,3,4      Op XOR to get logical not
142:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
143:   LDA  1,-2(1)    Ghost frame becomes new active frame
144:   LDA  3,1(7)     Return address in AC
145:   JMP  7,-129(7)  CALL outputb
146:   LDA  3,0(2)     Save the result in AC
* CALL END outputb
* CALL outputb
147:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
148:   LDC  3,0(6)     Load constant
149:   LDC  4,1(6)     Load 1
150:   XOR  3,3,4      Op XOR to get logical not
151:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
152:   LDA  1,-2(1)    Ghost frame becomes new active frame
153:   LDA  3,1(7)     Return address in AC
154:   JMP  7,-138(7)  CALL outputb
155:   LDA  3,0(2)     Save the result in AC
* CALL END outputb
* CALL outnl
156:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
157:   LDA  1,-2(1)    Ghost frame becomes new active frame
158:   LDA  3,1(7)     Return address in AC
159:   JMP  7,-126(7)  CALL outnl
160:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* END COMPOUND BODY
* END COMPOUND
* Add standard closing in case there is no return statement
161:   LDC  2,0(6)     Set return value to 0
162:    LD  3,-1(1)    Load return address
163:    LD  1,0(0)     Adjust fp
164:   JMP  7,0(3)     Return
* END FUNCTION main
* ** ** ** ** ** ** ** ** ** ** ** **
* END User-declared functions
* ** ** ** ** ** ** ** ** ** ** ** **
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* START INIT
* ** ** ** ** ** ** ** ** ** ** ** **
0:     JMP  7,164(7)   Jump to init [backpatch]
165:   LDA  1,0(0)     Set first frame at end of globals
166:    ST  1,0(1)     Store old FP (point to self)
* START GLOBALS AND STATICS
* END GLOBALS AND STATICS
167:   LDA  3,1(7)     Return address in AC
168:   JMP  7,-130(7)  Jump to main
169:  HALT  0,0,0      DONE!
* ** ** ** ** ** ** ** ** ** ** ** **
* END INIT
* ** ** ** ** ** ** ** ** ** ** ** **

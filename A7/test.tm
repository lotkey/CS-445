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
* COMPOUND
* TOFF set: -3
* LOCAL DECLARATIONS
40:    LDC  3,0(6)     Load constant
41:     ST  3,-2(0)    Store variable ss
* END LOCAL DECLARATIONS
* COMPOUND BODY
* CALL outputb
42:     ST  1,-3(1)    Store FP in ghost frame for output
* TOFF dec: -4
* START Params
* TOFF dec: -5
* Param 1
43:     LD  3,-2(1)    Load variable ss
44:     ST  3,-5(1)    Push parameter
* END Params
* TOFF set: -3
45:    LDA  1,-3(1)    Ghost frame becomes new active frame
46:    LDA  3,1(7)     Return address in AC
47:    JMP  7,-31(7)   CALL outputb
48:    LDA  3,0(2)     Save the result in AC
* CALL END outputb
* END COMPOUND BODY
* END COMPOUND
* END COMPOUND BODY
* END COMPOUND
* Add standard closing in case there is no return statement
49:    LDC  2,0(6)     Set return value to 0
50:     LD  3,-1(1)    Load return address
51:     LD  1,0(0)     Adjust fp
52:    JMP  7,0(3)     Return
* END FUNCTION main
* ** ** ** ** ** ** ** ** ** ** ** **
* END User-declared functions
* ** ** ** ** ** ** ** ** ** ** ** **
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* START INIT
* ** ** ** ** ** ** ** ** ** ** ** **
0:     JMP  7,52(7)    Jump to init [backpatch]
53:    LDA  1,0(0)     Set first frame at end of globals
54:     ST  1,0(1)     Store old FP (point to self)
* START GLOBALS AND STATICS
* END GLOBALS AND STATICS
55:    LDA  3,1(7)     Return address in AC
56:    JMP  7,7(16)    Jump to main
57:   HALT  0,0,0      DONE!
* ** ** ** ** ** ** ** ** ** ** ** **
* END INIT
* ** ** ** ** ** ** ** ** ** ** ** **

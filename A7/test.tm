* ** ** ** ** ** ** ** ** ** ** ** **
* START IO library functions
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION input
 1:      ST  3,-1(1)    Store return address
 2:      IN  2,2,2      Grab int input
 3:      LD  3,-1(1)    Load return address
 4:      LD  1,0(1)     Adjust fp
 5:     JMP  7,0(3)     Return
* END FUNCTION input
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION output
 6:      ST  3,-1(1)    Store return address
 7:      LD  3,-2(1)    Load parameter
 8:     OUT  3,3,3      Output integer
 9:      LD  3,-1(1)    Load return address
 10:     LD  1,0(1)     Adjust fp
 11:    JMP  7,0(3)     Return
* END FUNCTION output
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputb
 12:     ST  3,-1(1)    Store return address
 13:    INB  2,2,2      Grab bool input
 14:     LD  3,-1(1)    Load return address
 15:     LD  1,0(1)     Adjust fp
 16:    JMP  7,0(3)     Return
* END FUNCTION inputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputb
 17:     ST  3,-1(1)    Store return address
 18:     LD  3,-2(1)    Load parameter
 19:   OUTB  3,3,3      Output bool
 20:     LD  3,-1(1)    Load return address
 21:     LD  1,0(1)     Adjust fp
 22:    JMP  7,0(3)     Return
* END FUNCTION outputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputc
 23:     ST  3,-1(1)    Store return address
 24:    INC  2,2,2      Grab char input
 25:     LD  3,-1(1)    Load return address
 26:     LD  1,0(1)     Adjust fp
 27:    JMP  7,0(3)     Return
* END FUNCTION inputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputc
 28:     ST  3,-1(1)    Store return address
 29:     LD  3,-2(1)    Load parameter
 30:   OUTC  3,3,3      Output char
 31:     LD  3,-1(1)    Load return address
 32:     LD  1,0(1)     Adjust fp
 33:    JMP  7,0(3)     Return
* END FUNCTION outputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputnl
 34:     ST  3,-1(1)    Store return address
 35:  OUTNL  3,3,3      Output integer
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
* START FUNCTION cat
* * * TOFF set: -3
 39:     ST  3,-1(1)    Store return address
* * * START COMPOUND
* * * * TOFF set: -4
* * * * LOCAL DECLARATIONS
* * * * * START VAR DECL q
* * * * * * START CONSTANT Const 9999
 40:    LDC  3,9999(6)  Load constant
* * * * * * END CONSTANT Const 9999
 41:     ST  3,-3(1)    Store variable q
* * * * * END VAR DECL q
* * * * END LOCAL DECLARATIONS
* * * * COMPOUND BODY
* * * * * START CALL output
 42:     ST  1,-4(1)    Store FP in ghost frame for output
* * * * * * TOFF dec: -5
* * * * * * START Params
* * * * * * TOFF dec: -6
* * * * * * Param 1
 43:     LD  3,-2(1)    Load address of base of array x
 44:     ST  3,-6(1)    Push left side
* * * * * * TOFF dec: -7
* * * * * * START CONSTANT Const 1
 45:    LDC  3,1(6)     Load constant
* * * * * * END CONSTANT Const 1
* * * * * * TOFF inc: -6
 46:     LD  4,-6(1)    Pop left into AC1
 47:    SUB  3,4,3      Compute location from index
 48:     LD  3,0(3)     Load array element
 49:     ST  3,-6(1)    Push parameter
* * * * * * END Params
* * * * * * TOFF set: -4
 50:    LDA  1,-4(1)    Ghost frame becomes new active frame
 51:    LDA  3,1(7)     Return address in AC
 52:    JMP  7,-47(7)   CALL output
 53:    LDA  3,0(2)     Save the result in AC
* * * * * END CALL output
* * * * END COMPOUND BODY
* * * END COMPOUND
* * * Add standard closing in case there is no return statement
 54:    LDC  2,0(6)     Set return value to 0
 55:     LD  3,-1(1)    Load return address
 56:     LD  1,0(1)     Adjust fp
 57:    JMP  7,0(3)     Return
* * END FUNCTION cat
* * 
* ** ** ** ** ** ** ** ** ** ** ** **
* * START FUNCTION dog
* * * * TOFF set: -3
 58:     ST  3,-1(1)    Store return address
* * * * START COMPOUND
* * * * * TOFF set: -4
* * * * * LOCAL DECLARATIONS
* * * * * * START VAR DECL q
* * * * * * * START CONSTANT Const 9999
 59:    LDC  3,9999(6)  Load constant
* * * * * * * END CONSTANT Const 9999
 60:     ST  3,-3(1)    Store variable q
* * * * * * END VAR DECL q
* * * * * END LOCAL DECLARATIONS
* * * * * COMPOUND BODY
* * * * * * START CALL cat
 61:     ST  1,-4(1)    Store FP in ghost frame for output
* * * * * * * TOFF dec: -5
* * * * * * * START Params
* * * * * * * TOFF dec: -6
* * * * * * * Param 1
* * * * * * * START ID y
 62:     LD  3,-2(1)    Load address of base of array y
* * * * * * * END ID y
 63:     ST  3,-6(1)    Push parameter
* * * * * * * END Params
* * * * * * * TOFF set: -4
 64:    LDA  1,-4(1)    Ghost frame becomes new active frame
 65:    LDA  3,1(7)     Return address in AC
 66:    JMP  7,-28(7)   CALL cat
 67:    LDA  3,0(2)     Save the result in AC
* * * * * * END CALL cat
* * * * * END COMPOUND BODY
* * * * END COMPOUND
* * * * Add standard closing in case there is no return statement
 68:    LDC  2,0(6)     Set return value to 0
 69:     LD  3,-1(1)    Load return address
 70:     LD  1,0(1)     Adjust fp
 71:    JMP  7,0(3)     Return
* * * END FUNCTION dog
* * * 
* ** ** ** ** ** ** ** ** ** ** ** **
* * * START FUNCTION main
* * * * * TOFF set: -2
 72:     ST  3,-1(1)    Store return address
* * * * * START COMPOUND
* * * * * * TOFF set: -14
* * * * * * LOCAL DECLARATIONS
* * * * * * * START VAR DECL q
* * * * * * * * START CONSTANT Const 9999
 73:    LDC  3,9999(6)  Load constant
* * * * * * * * END CONSTANT Const 9999
 74:     ST  3,-2(1)    Store variable q
* * * * * * * END VAR DECL q
* * * * * * * START VAR DECL z
 75:    LDC  3,10(6)    Load size of array z
 76:     ST  3,-3(1)    Store size of z
* * * * * * * END VAR DECL z
* * * * * * END LOCAL DECLARATIONS
* * * * * * COMPOUND BODY
* * * * * * * START BINARY ASGN
* * * * * * * * START CONSTANT Const 1
 77:    LDC  3,1(6)     Load constant
* * * * * * * * END CONSTANT Const 1
 78:     ST  3,-14(1)   Push index
* * * * * * * * TOFF dec: -15
* * * * * * * * START CONSTANT Const 777
 79:    LDC  3,777(6)   Load constant
* * * * * * * * END CONSTANT Const 777
* * * * * * * * TOFF inc: -14
 80:     LD  4,-14(1)   Pop index
 81:    LDA  5,-4(1)    Load address of base of array z
 82:    SUB  5,5,4      Compute offset of value
 83:     ST  3,0(5)     Store variable z
* * * * * * * END BINARY ASGN
* * * * * * * START CALL dog
 84:     ST  1,-14(1)   Store FP in ghost frame for output
* * * * * * * * TOFF dec: -15
* * * * * * * * START Params
* * * * * * * * TOFF dec: -16
* * * * * * * * Param 1
* * * * * * * * START ID z
 85:    LDA  3,-4(1)    Load address of base of array z
* * * * * * * * END ID z
 86:     ST  3,-16(1)   Push parameter
* * * * * * * * END Params
* * * * * * * * TOFF set: -14
 87:    LDA  1,-14(1)   Ghost frame becomes new active frame
 88:    LDA  3,1(7)     Return address in AC
 89:    JMP  7,-32(7)   CALL dog
 90:    LDA  3,0(2)     Save the result in AC
* * * * * * * END CALL dog
* * * * * * END COMPOUND BODY
* * * * * END COMPOUND
* * * * * Add standard closing in case there is no return statement
 91:    LDC  2,0(6)     Set return value to 0
 92:     LD  3,-1(1)    Load return address
 93:     LD  1,0(1)     Adjust fp
 94:    JMP  7,0(3)     Return
* * * * END FUNCTION main
* ** ** ** ** ** ** ** ** ** ** ** **
* * * * END User-declared functions
* ** ** ** ** ** ** ** ** ** ** ** **
* * * * 
* ** ** ** ** ** ** ** ** ** ** ** **
* * * * START INIT
* ** ** ** ** ** ** ** ** ** ** ** **
 0:     JMP  7,94(7)    Jump to init [backpatch]
 95:    LDA  1,0(0)     Set first frame at end of globals
 96:     ST  1,0(1)     Store old FP (point to self)
* * * * START GLOBALS AND STATICS
* * * * END GLOBALS AND STATICS
 97:    LDA  3,1(7)     Return address in AC
 98:    JMP  7,-27(7)   Jump to main
 99:   HALT  0,0,0      DONE!
* ** ** ** ** ** ** ** ** ** ** ** **
* * * * END INIT
* ** ** ** ** ** ** ** ** ** ** ** **

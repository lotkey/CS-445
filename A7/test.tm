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
44:    LDA  5,-1(0)    Load address of base of array x
45:    SUB  5,5,4      Compute offset of value
46:     ST  3,0(5)     Store variable x
47:    LDC  3,7(6)     Load constant
48:     ST  3,-2(1)    Push index
* TOFF dec: -3
49:    LDC  3,444(6)   Load constant
* TOFF inc: -2
50:     LD  4,-2(1)    Pop index
51:    LDA  5,-9(0)    Load address of base of array y
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
63:    LDA  5,-1(0)    Load address of base of array x
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
77:    LDA  5,-1(0)    Load address of base of array x
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
101:   LDA  5,-9(0)    Load address of base of array y
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
115:   LDA  5,-9(0)    Load address of base of array y
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
* CALL outnl
135:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
136:   LDA  1,-2(1)    Ghost frame becomes new active frame
137:   LDA  3,1(7)     Return address in AC
138:   JMP  7,-105(7)  CALL outnl
139:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
140:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
141:   LDA  3,-9(0)    Load address of base of array y
142:    ST  3,-4(1)    Push left side
* TOFF dec: -5
143:   LDC  3,7(6)     Load constant
* TOFF inc: -4
144:    LD  4,-4(1)    Pop left into AC1
145:   SUB  3,4,3      Compute location from index
146:    LD  3,0(3)     Load array element
147:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
148:   LDA  1,-2(1)    Ghost frame becomes new active frame
149:   LDA  3,1(7)     Return address in AC
150:   JMP  7,-145(7)  CALL output
151:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
152:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
153:   LDA  1,-2(1)    Ghost frame becomes new active frame
154:   LDA  3,1(7)     Return address in AC
155:   JMP  7,-122(7)  CALL outnl
156:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
157:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
158:   LDA  1,-2(1)    Ghost frame becomes new active frame
159:   LDA  3,1(7)     Return address in AC
160:   JMP  7,-127(7)  CALL outnl
161:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
162:   LDC  3,7(6)     Load constant
163:    ST  3,-2(1)    Push index
* TOFF dec: -3
164:   LDA  3,-1(0)    Load address of base of array x
165:    ST  3,-3(1)    Push left side
* TOFF dec: -4
166:   LDC  3,5(6)     Load constant
* TOFF inc: -3
167:    LD  4,-3(1)    Pop left into AC1
168:   SUB  3,4,3      Compute location from index
169:    LD  3,0(3)     Load array element
* TOFF inc: -2
170:    LD  4,-2(1)    Pop index
171:   LDA  5,-9(0)    Load address of base of array y
172:   SUB  5,5,4      Compute offset of value
173:    LD  4,0(5)     Load lhs variable y
174:   DIV  3,4,3      Op /=
175:    ST  3,0(5)     Store variable y
176:   LDC  3,7(6)     Load constant
177:    ST  3,-2(1)    Push index
* TOFF dec: -3
178:   LDA  3,-1(0)    Load address of base of array x
179:    ST  3,-3(1)    Push left side
* TOFF dec: -4
180:   LDC  3,5(6)     Load constant
* TOFF inc: -3
181:    LD  4,-3(1)    Pop left into AC1
182:   SUB  3,4,3      Compute location from index
183:    LD  3,0(3)     Load array element
* TOFF inc: -2
184:    LD  4,-2(1)    Pop index
185:   LDA  5,-9(0)    Load address of base of array y
186:   SUB  5,5,4      Compute offset of value
187:    ST  3,0(5)     Store variable y
* CALL output
188:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
189:   LDA  3,-9(0)    Load address of base of array y
190:    ST  3,-4(1)    Push left side
* TOFF dec: -5
191:   LDC  3,7(6)     Load constant
* TOFF inc: -4
192:    LD  4,-4(1)    Pop left into AC1
193:   SUB  3,4,3      Compute location from index
194:    LD  3,0(3)     Load array element
195:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
196:   LDA  1,-2(1)    Ghost frame becomes new active frame
197:   LDA  3,1(7)     Return address in AC
198:   JMP  7,-193(7)  CALL output
199:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
200:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
201:   LDA  1,-2(1)    Ghost frame becomes new active frame
202:   LDA  3,1(7)     Return address in AC
203:   JMP  7,-170(7)  CALL outnl
204:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
205:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
206:   LDA  1,-2(1)    Ghost frame becomes new active frame
207:   LDA  3,1(7)     Return address in AC
208:   JMP  7,-175(7)  CALL outnl
209:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
210:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
211:   LDA  3,-9(0)    Load address of base of array y
212:    ST  3,-4(1)    Push left side
* TOFF dec: -5
213:   LDC  3,7(6)     Load constant
* TOFF inc: -4
214:    LD  4,-4(1)    Pop left into AC1
215:   SUB  3,4,3      Compute location from index
216:    LD  3,0(3)     Load array element
217:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
218:   LDA  1,-2(1)    Ghost frame becomes new active frame
219:   LDA  3,1(7)     Return address in AC
220:   JMP  7,-215(7)  CALL output
221:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
222:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
223:   LDA  1,-2(1)    Ghost frame becomes new active frame
224:   LDA  3,1(7)     Return address in AC
225:   JMP  7,-192(7)  CALL outnl
226:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
227:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
228:   LDA  1,-2(1)    Ghost frame becomes new active frame
229:   LDA  3,1(7)     Return address in AC
230:   JMP  7,-197(7)  CALL outnl
231:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
232:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
233:   LDA  3,-1(0)    Load address of base of array x
234:    ST  3,-4(1)    Push left side
* TOFF dec: -5
235:   LDC  3,5(6)     Load constant
* TOFF inc: -4
236:    LD  4,-4(1)    Pop left into AC1
237:   SUB  3,4,3      Compute location from index
238:    LD  3,0(3)     Load array element
239:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
240:   LDA  1,-2(1)    Ghost frame becomes new active frame
241:   LDA  3,1(7)     Return address in AC
242:   JMP  7,-237(7)  CALL output
243:   LDA  3,0(2)     Save the result in AC
* CALL END output
244:   LDC  3,7(6)     Load constant
245:    ST  3,-2(1)    Push index
* TOFF dec: -3
246:   LDA  3,-1(0)    Load address of base of array x
247:    ST  3,-3(1)    Push left side
* TOFF dec: -4
248:   LDC  3,5(6)     Load constant
* TOFF inc: -3
249:    LD  4,-3(1)    Pop left into AC1
250:   SUB  3,4,3      Compute location from index
251:    LD  3,0(3)     Load array element
* TOFF inc: -2
252:    LD  4,-2(1)    Pop index
253:   LDA  5,-9(0)    Load address of base of array y
254:   SUB  5,5,4      Compute offset of value
255:    LD  4,0(5)     Load lhs variable y
256:   DIV  3,4,3      Op /=
257:    ST  3,0(5)     Store variable y
258:   LDC  3,7(6)     Load constant
259:    ST  3,-2(1)    Push index
* TOFF dec: -3
260:   LDA  3,-1(0)    Load address of base of array x
261:    ST  3,-3(1)    Push left side
* TOFF dec: -4
262:   LDC  3,5(6)     Load constant
* TOFF inc: -3
263:    LD  4,-3(1)    Pop left into AC1
264:   SUB  3,4,3      Compute location from index
265:    LD  3,0(3)     Load array element
* TOFF inc: -2
266:    LD  4,-2(1)    Pop index
267:   LDA  5,-9(0)    Load address of base of array y
268:   SUB  5,5,4      Compute offset of value
269:    ST  3,0(5)     Store variable y
* CALL output
270:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
271:   LDA  3,-9(0)    Load address of base of array y
272:    ST  3,-4(1)    Push left side
* TOFF dec: -5
273:   LDC  3,7(6)     Load constant
* TOFF inc: -4
274:    LD  4,-4(1)    Pop left into AC1
275:   SUB  3,4,3      Compute location from index
276:    LD  3,0(3)     Load array element
277:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
278:   LDA  1,-2(1)    Ghost frame becomes new active frame
279:   LDA  3,1(7)     Return address in AC
280:   JMP  7,-275(7)  CALL output
281:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
282:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
283:   LDA  1,-2(1)    Ghost frame becomes new active frame
284:   LDA  3,1(7)     Return address in AC
285:   JMP  7,-252(7)  CALL outnl
286:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
287:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
288:   LDA  1,-2(1)    Ghost frame becomes new active frame
289:   LDA  3,1(7)     Return address in AC
290:   JMP  7,-257(7)  CALL outnl
291:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
292:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
293:   LDA  3,-9(0)    Load address of base of array y
294:    ST  3,-4(1)    Push left side
* TOFF dec: -5
295:   LDC  3,7(6)     Load constant
* TOFF inc: -4
296:    LD  4,-4(1)    Pop left into AC1
297:   SUB  3,4,3      Compute location from index
298:    LD  3,0(3)     Load array element
299:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
300:   LDA  1,-2(1)    Ghost frame becomes new active frame
301:   LDA  3,1(7)     Return address in AC
302:   JMP  7,-297(7)  CALL output
303:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
304:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
305:   LDA  1,-2(1)    Ghost frame becomes new active frame
306:   LDA  3,1(7)     Return address in AC
307:   JMP  7,-274(7)  CALL outnl
308:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
309:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
310:   LDA  1,-2(1)    Ghost frame becomes new active frame
311:   LDA  3,1(7)     Return address in AC
312:   JMP  7,-279(7)  CALL outnl
313:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
314:   LDC  3,7(6)     Load constant
315:    ST  3,-2(1)    Push index
* TOFF dec: -3
316:   LDA  3,-1(0)    Load address of base of array x
317:    ST  3,-3(1)    Push left side
* TOFF dec: -4
318:   LDC  3,5(6)     Load constant
* TOFF inc: -3
319:    LD  4,-3(1)    Pop left into AC1
320:   SUB  3,4,3      Compute location from index
321:    LD  3,0(3)     Load array element
* TOFF inc: -2
322:    LD  4,-2(1)    Pop index
323:   LDA  5,-9(0)    Load address of base of array y
324:   SUB  5,5,4      Compute offset of value
325:    LD  4,0(5)     Load lhs variable y
326:   DIV  3,4,3      Op /=
327:    ST  3,0(5)     Store variable y
328:   LDC  3,7(6)     Load constant
329:    ST  3,-2(1)    Push index
* TOFF dec: -3
330:   LDA  3,-1(0)    Load address of base of array x
331:    ST  3,-3(1)    Push left side
* TOFF dec: -4
332:   LDC  3,5(6)     Load constant
* TOFF inc: -3
333:    LD  4,-3(1)    Pop left into AC1
334:   SUB  3,4,3      Compute location from index
335:    LD  3,0(3)     Load array element
* TOFF inc: -2
336:    LD  4,-2(1)    Pop index
337:   LDA  5,-9(0)    Load address of base of array y
338:   SUB  5,5,4      Compute offset of value
339:    ST  3,0(5)     Store variable y
* CALL output
340:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
341:   LDA  3,-9(0)    Load address of base of array y
342:    ST  3,-4(1)    Push left side
* TOFF dec: -5
343:   LDC  3,7(6)     Load constant
* TOFF inc: -4
344:    LD  4,-4(1)    Pop left into AC1
345:   SUB  3,4,3      Compute location from index
346:    LD  3,0(3)     Load array element
347:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
348:   LDA  1,-2(1)    Ghost frame becomes new active frame
349:   LDA  3,1(7)     Return address in AC
350:   JMP  7,-345(7)  CALL output
351:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
352:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
353:   LDA  1,-2(1)    Ghost frame becomes new active frame
354:   LDA  3,1(7)     Return address in AC
355:   JMP  7,-322(7)  CALL outnl
356:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
357:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
358:   LDA  1,-2(1)    Ghost frame becomes new active frame
359:   LDA  3,1(7)     Return address in AC
360:   JMP  7,-327(7)  CALL outnl
361:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
362:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
363:   LDA  3,-9(0)    Load address of base of array y
364:    ST  3,-4(1)    Push left side
* TOFF dec: -5
365:   LDC  3,7(6)     Load constant
* TOFF inc: -4
366:    LD  4,-4(1)    Pop left into AC1
367:   SUB  3,4,3      Compute location from index
368:    LD  3,0(3)     Load array element
369:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
370:   LDA  1,-2(1)    Ghost frame becomes new active frame
371:   LDA  3,1(7)     Return address in AC
372:   JMP  7,-367(7)  CALL output
373:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
374:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
375:   LDA  1,-2(1)    Ghost frame becomes new active frame
376:   LDA  3,1(7)     Return address in AC
377:   JMP  7,-344(7)  CALL outnl
378:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
379:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
380:   LDA  1,-2(1)    Ghost frame becomes new active frame
381:   LDA  3,1(7)     Return address in AC
382:   JMP  7,-349(7)  CALL outnl
383:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
384:   LDC  3,5(6)     Load constant
385:    ST  3,-2(1)    Push index
* TOFF dec: -3
386:   LDA  3,-9(0)    Load address of base of array y
387:    ST  3,-3(1)    Push left side
* TOFF dec: -4
388:   LDC  3,7(6)     Load constant
* TOFF inc: -3
389:    LD  4,-3(1)    Pop left into AC1
390:   SUB  3,4,3      Compute location from index
391:    LD  3,0(3)     Load array element
* TOFF inc: -2
392:    LD  4,-2(1)    Pop index
393:   LDA  5,-1(0)    Load address of base of array x
394:   SUB  5,5,4      Compute offset of value
395:    LD  4,0(5)     Load lhs variable x
396:   ADD  3,4,3      Op +=
397:    ST  3,0(5)     Store variable x
398:   LDC  3,5(6)     Load constant
399:    ST  3,-2(1)    Push index
* TOFF dec: -3
400:   LDA  3,-9(0)    Load address of base of array y
401:    ST  3,-3(1)    Push left side
* TOFF dec: -4
402:   LDC  3,7(6)     Load constant
* TOFF inc: -3
403:    LD  4,-3(1)    Pop left into AC1
404:   SUB  3,4,3      Compute location from index
405:    LD  3,0(3)     Load array element
* TOFF inc: -2
406:    LD  4,-2(1)    Pop index
407:   LDA  5,-1(0)    Load address of base of array x
408:   SUB  5,5,4      Compute offset of value
409:    ST  3,0(5)     Store variable x
* CALL output
410:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
411:   LDA  3,-1(0)    Load address of base of array x
412:    ST  3,-4(1)    Push left side
* TOFF dec: -5
413:   LDC  3,5(6)     Load constant
* TOFF inc: -4
414:    LD  4,-4(1)    Pop left into AC1
415:   SUB  3,4,3      Compute location from index
416:    LD  3,0(3)     Load array element
417:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
418:   LDA  1,-2(1)    Ghost frame becomes new active frame
419:   LDA  3,1(7)     Return address in AC
420:   JMP  7,-415(7)  CALL output
421:   LDA  3,0(2)     Save the result in AC
* CALL END output
422:   LDC  3,7(6)     Load constant
423:    ST  3,-2(1)    Push index
* TOFF dec: -3
424:   LDA  3,-1(0)    Load address of base of array x
425:    ST  3,-3(1)    Push left side
* TOFF dec: -4
426:   LDC  3,5(6)     Load constant
* TOFF inc: -3
427:    LD  4,-3(1)    Pop left into AC1
428:   SUB  3,4,3      Compute location from index
429:    LD  3,0(3)     Load array element
* TOFF inc: -2
430:    LD  4,-2(1)    Pop index
431:   LDA  5,-9(0)    Load address of base of array y
432:   SUB  5,5,4      Compute offset of value
433:    LD  4,0(5)     Load lhs variable y
434:   DIV  3,4,3      Op /=
435:    ST  3,0(5)     Store variable y
436:   LDC  3,7(6)     Load constant
437:    ST  3,-2(1)    Push index
* TOFF dec: -3
438:   LDA  3,-1(0)    Load address of base of array x
439:    ST  3,-3(1)    Push left side
* TOFF dec: -4
440:   LDC  3,5(6)     Load constant
* TOFF inc: -3
441:    LD  4,-3(1)    Pop left into AC1
442:   SUB  3,4,3      Compute location from index
443:    LD  3,0(3)     Load array element
* TOFF inc: -2
444:    LD  4,-2(1)    Pop index
445:   LDA  5,-9(0)    Load address of base of array y
446:   SUB  5,5,4      Compute offset of value
447:    ST  3,0(5)     Store variable y
* CALL output
448:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
449:   LDA  3,-9(0)    Load address of base of array y
450:    ST  3,-4(1)    Push left side
* TOFF dec: -5
451:   LDC  3,7(6)     Load constant
* TOFF inc: -4
452:    LD  4,-4(1)    Pop left into AC1
453:   SUB  3,4,3      Compute location from index
454:    LD  3,0(3)     Load array element
455:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
456:   LDA  1,-2(1)    Ghost frame becomes new active frame
457:   LDA  3,1(7)     Return address in AC
458:   JMP  7,-453(7)  CALL output
459:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
460:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
461:   LDA  1,-2(1)    Ghost frame becomes new active frame
462:   LDA  3,1(7)     Return address in AC
463:   JMP  7,-430(7)  CALL outnl
464:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
465:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
466:   LDA  1,-2(1)    Ghost frame becomes new active frame
467:   LDA  3,1(7)     Return address in AC
468:   JMP  7,-435(7)  CALL outnl
469:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
470:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
471:   LDA  3,-9(0)    Load address of base of array y
472:    ST  3,-4(1)    Push left side
* TOFF dec: -5
473:   LDC  3,7(6)     Load constant
* TOFF inc: -4
474:    LD  4,-4(1)    Pop left into AC1
475:   SUB  3,4,3      Compute location from index
476:    LD  3,0(3)     Load array element
477:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
478:   LDA  1,-2(1)    Ghost frame becomes new active frame
479:   LDA  3,1(7)     Return address in AC
480:   JMP  7,-475(7)  CALL output
481:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
482:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
483:   LDA  1,-2(1)    Ghost frame becomes new active frame
484:   LDA  3,1(7)     Return address in AC
485:   JMP  7,-452(7)  CALL outnl
486:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
487:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
488:   LDA  1,-2(1)    Ghost frame becomes new active frame
489:   LDA  3,1(7)     Return address in AC
490:   JMP  7,-457(7)  CALL outnl
491:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
492:   LDC  3,7(6)     Load constant
493:    ST  3,-2(1)    Push index
* TOFF dec: -3
494:   LDA  3,-1(0)    Load address of base of array x
495:    ST  3,-3(1)    Push left side
* TOFF dec: -4
496:   LDC  3,5(6)     Load constant
* TOFF inc: -3
497:    LD  4,-3(1)    Pop left into AC1
498:   SUB  3,4,3      Compute location from index
499:    LD  3,0(3)     Load array element
* TOFF inc: -2
500:    LD  4,-2(1)    Pop index
501:   LDA  5,-9(0)    Load address of base of array y
502:   SUB  5,5,4      Compute offset of value
503:    LD  4,0(5)     Load lhs variable y
504:   DIV  3,4,3      Op /=
505:    ST  3,0(5)     Store variable y
506:   LDC  3,7(6)     Load constant
507:    ST  3,-2(1)    Push index
* TOFF dec: -3
508:   LDA  3,-1(0)    Load address of base of array x
509:    ST  3,-3(1)    Push left side
* TOFF dec: -4
510:   LDC  3,5(6)     Load constant
* TOFF inc: -3
511:    LD  4,-3(1)    Pop left into AC1
512:   SUB  3,4,3      Compute location from index
513:    LD  3,0(3)     Load array element
* TOFF inc: -2
514:    LD  4,-2(1)    Pop index
515:   LDA  5,-9(0)    Load address of base of array y
516:   SUB  5,5,4      Compute offset of value
517:    ST  3,0(5)     Store variable y
* CALL output
518:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
519:   LDA  3,-9(0)    Load address of base of array y
520:    ST  3,-4(1)    Push left side
* TOFF dec: -5
521:   LDC  3,7(6)     Load constant
* TOFF inc: -4
522:    LD  4,-4(1)    Pop left into AC1
523:   SUB  3,4,3      Compute location from index
524:    LD  3,0(3)     Load array element
525:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
526:   LDA  1,-2(1)    Ghost frame becomes new active frame
527:   LDA  3,1(7)     Return address in AC
528:   JMP  7,-523(7)  CALL output
529:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
530:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
531:   LDA  1,-2(1)    Ghost frame becomes new active frame
532:   LDA  3,1(7)     Return address in AC
533:   JMP  7,-500(7)  CALL outnl
534:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
535:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
536:   LDA  1,-2(1)    Ghost frame becomes new active frame
537:   LDA  3,1(7)     Return address in AC
538:   JMP  7,-505(7)  CALL outnl
539:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
540:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
541:   LDA  3,-9(0)    Load address of base of array y
542:    ST  3,-4(1)    Push left side
* TOFF dec: -5
543:   LDC  3,7(6)     Load constant
* TOFF inc: -4
544:    LD  4,-4(1)    Pop left into AC1
545:   SUB  3,4,3      Compute location from index
546:    LD  3,0(3)     Load array element
547:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
548:   LDA  1,-2(1)    Ghost frame becomes new active frame
549:   LDA  3,1(7)     Return address in AC
550:   JMP  7,-545(7)  CALL output
551:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
552:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
553:   LDA  1,-2(1)    Ghost frame becomes new active frame
554:   LDA  3,1(7)     Return address in AC
555:   JMP  7,-522(7)  CALL outnl
556:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
557:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
558:   LDA  1,-2(1)    Ghost frame becomes new active frame
559:   LDA  3,1(7)     Return address in AC
560:   JMP  7,-527(7)  CALL outnl
561:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
562:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
563:   LDA  3,-1(0)    Load address of base of array x
564:    ST  3,-4(1)    Push left side
* TOFF dec: -5
565:   LDC  3,5(6)     Load constant
* TOFF inc: -4
566:    LD  4,-4(1)    Pop left into AC1
567:   SUB  3,4,3      Compute location from index
568:    LD  3,0(3)     Load array element
569:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
570:   LDA  1,-2(1)    Ghost frame becomes new active frame
571:   LDA  3,1(7)     Return address in AC
572:   JMP  7,-567(7)  CALL output
573:   LDA  3,0(2)     Save the result in AC
* CALL END output
574:   LDC  3,7(6)     Load constant
575:    ST  3,-2(1)    Push index
* TOFF dec: -3
576:   LDA  3,-1(0)    Load address of base of array x
577:    ST  3,-3(1)    Push left side
* TOFF dec: -4
578:   LDC  3,5(6)     Load constant
* TOFF inc: -3
579:    LD  4,-3(1)    Pop left into AC1
580:   SUB  3,4,3      Compute location from index
581:    LD  3,0(3)     Load array element
* TOFF inc: -2
582:    LD  4,-2(1)    Pop index
583:   LDA  5,-9(0)    Load address of base of array y
584:   SUB  5,5,4      Compute offset of value
585:    LD  4,0(5)     Load lhs variable y
586:   DIV  3,4,3      Op /=
587:    ST  3,0(5)     Store variable y
588:   LDC  3,7(6)     Load constant
589:    ST  3,-2(1)    Push index
* TOFF dec: -3
590:   LDA  3,-1(0)    Load address of base of array x
591:    ST  3,-3(1)    Push left side
* TOFF dec: -4
592:   LDC  3,5(6)     Load constant
* TOFF inc: -3
593:    LD  4,-3(1)    Pop left into AC1
594:   SUB  3,4,3      Compute location from index
595:    LD  3,0(3)     Load array element
* TOFF inc: -2
596:    LD  4,-2(1)    Pop index
597:   LDA  5,-9(0)    Load address of base of array y
598:   SUB  5,5,4      Compute offset of value
599:    ST  3,0(5)     Store variable y
* CALL output
600:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
601:   LDA  3,-9(0)    Load address of base of array y
602:    ST  3,-4(1)    Push left side
* TOFF dec: -5
603:   LDC  3,7(6)     Load constant
* TOFF inc: -4
604:    LD  4,-4(1)    Pop left into AC1
605:   SUB  3,4,3      Compute location from index
606:    LD  3,0(3)     Load array element
607:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
608:   LDA  1,-2(1)    Ghost frame becomes new active frame
609:   LDA  3,1(7)     Return address in AC
610:   JMP  7,-605(7)  CALL output
611:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
612:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
613:   LDA  1,-2(1)    Ghost frame becomes new active frame
614:   LDA  3,1(7)     Return address in AC
615:   JMP  7,-582(7)  CALL outnl
616:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
617:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
618:   LDA  1,-2(1)    Ghost frame becomes new active frame
619:   LDA  3,1(7)     Return address in AC
620:   JMP  7,-587(7)  CALL outnl
621:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
622:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
623:   LDA  3,-9(0)    Load address of base of array y
624:    ST  3,-4(1)    Push left side
* TOFF dec: -5
625:   LDC  3,7(6)     Load constant
* TOFF inc: -4
626:    LD  4,-4(1)    Pop left into AC1
627:   SUB  3,4,3      Compute location from index
628:    LD  3,0(3)     Load array element
629:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
630:   LDA  1,-2(1)    Ghost frame becomes new active frame
631:   LDA  3,1(7)     Return address in AC
632:   JMP  7,-627(7)  CALL output
633:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
634:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
635:   LDA  1,-2(1)    Ghost frame becomes new active frame
636:   LDA  3,1(7)     Return address in AC
637:   JMP  7,-604(7)  CALL outnl
638:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
639:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
640:   LDA  1,-2(1)    Ghost frame becomes new active frame
641:   LDA  3,1(7)     Return address in AC
642:   JMP  7,-609(7)  CALL outnl
643:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
644:   LDC  3,7(6)     Load constant
645:    ST  3,-2(1)    Push index
* TOFF dec: -3
646:   LDA  3,-1(0)    Load address of base of array x
647:    ST  3,-3(1)    Push left side
* TOFF dec: -4
648:   LDC  3,5(6)     Load constant
* TOFF inc: -3
649:    LD  4,-3(1)    Pop left into AC1
650:   SUB  3,4,3      Compute location from index
651:    LD  3,0(3)     Load array element
* TOFF inc: -2
652:    LD  4,-2(1)    Pop index
653:   LDA  5,-9(0)    Load address of base of array y
654:   SUB  5,5,4      Compute offset of value
655:    LD  4,0(5)     Load lhs variable y
656:   DIV  3,4,3      Op /=
657:    ST  3,0(5)     Store variable y
658:   LDC  3,7(6)     Load constant
659:    ST  3,-2(1)    Push index
* TOFF dec: -3
660:   LDA  3,-1(0)    Load address of base of array x
661:    ST  3,-3(1)    Push left side
* TOFF dec: -4
662:   LDC  3,5(6)     Load constant
* TOFF inc: -3
663:    LD  4,-3(1)    Pop left into AC1
664:   SUB  3,4,3      Compute location from index
665:    LD  3,0(3)     Load array element
* TOFF inc: -2
666:    LD  4,-2(1)    Pop index
667:   LDA  5,-9(0)    Load address of base of array y
668:   SUB  5,5,4      Compute offset of value
669:    ST  3,0(5)     Store variable y
* CALL output
670:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
671:   LDA  3,-9(0)    Load address of base of array y
672:    ST  3,-4(1)    Push left side
* TOFF dec: -5
673:   LDC  3,7(6)     Load constant
* TOFF inc: -4
674:    LD  4,-4(1)    Pop left into AC1
675:   SUB  3,4,3      Compute location from index
676:    LD  3,0(3)     Load array element
677:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
678:   LDA  1,-2(1)    Ghost frame becomes new active frame
679:   LDA  3,1(7)     Return address in AC
680:   JMP  7,-675(7)  CALL output
681:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
682:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
683:   LDA  1,-2(1)    Ghost frame becomes new active frame
684:   LDA  3,1(7)     Return address in AC
685:   JMP  7,-652(7)  CALL outnl
686:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
687:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
688:   LDA  1,-2(1)    Ghost frame becomes new active frame
689:   LDA  3,1(7)     Return address in AC
690:   JMP  7,-657(7)  CALL outnl
691:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
692:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
693:   LDA  3,-9(0)    Load address of base of array y
694:    ST  3,-4(1)    Push left side
* TOFF dec: -5
695:   LDC  3,7(6)     Load constant
* TOFF inc: -4
696:    LD  4,-4(1)    Pop left into AC1
697:   SUB  3,4,3      Compute location from index
698:    LD  3,0(3)     Load array element
699:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
700:   LDA  1,-2(1)    Ghost frame becomes new active frame
701:   LDA  3,1(7)     Return address in AC
702:   JMP  7,-697(7)  CALL output
703:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
704:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
705:   LDA  1,-2(1)    Ghost frame becomes new active frame
706:   LDA  3,1(7)     Return address in AC
707:   JMP  7,-674(7)  CALL outnl
708:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
709:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
710:   LDA  1,-2(1)    Ghost frame becomes new active frame
711:   LDA  3,1(7)     Return address in AC
712:   JMP  7,-679(7)  CALL outnl
713:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
714:   LDC  3,7(6)     Load constant
715:    ST  3,-2(1)    Push index
* TOFF dec: -3
716:   LDC  3,444(6)   Load constant
* TOFF inc: -2
717:    LD  4,-2(1)    Pop index
718:   LDA  5,-9(0)    Load address of base of array y
719:   SUB  5,5,4      Compute offset of value
720:    ST  3,0(5)     Store variable y
721:   LDC  3,5(6)     Load constant
722:    ST  3,-2(1)    Push index
* TOFF dec: -3
723:   LDA  3,-9(0)    Load address of base of array y
724:    ST  3,-3(1)    Push left side
* TOFF dec: -4
725:   LDC  3,7(6)     Load constant
* TOFF inc: -3
726:    LD  4,-3(1)    Pop left into AC1
727:   SUB  3,4,3      Compute location from index
728:    LD  3,0(3)     Load array element
* TOFF inc: -2
729:    LD  4,-2(1)    Pop index
730:   LDA  5,-1(0)    Load address of base of array x
731:   SUB  5,5,4      Compute offset of value
732:    LD  4,0(5)     Load lhs variable x
733:   ADD  3,4,3      Op +=
734:    ST  3,0(5)     Store variable x
735:   LDC  3,5(6)     Load constant
736:    ST  3,-2(1)    Push index
* TOFF dec: -3
737:   LDA  3,-9(0)    Load address of base of array y
738:    ST  3,-3(1)    Push left side
* TOFF dec: -4
739:   LDC  3,7(6)     Load constant
* TOFF inc: -3
740:    LD  4,-3(1)    Pop left into AC1
741:   SUB  3,4,3      Compute location from index
742:    LD  3,0(3)     Load array element
* TOFF inc: -2
743:    LD  4,-2(1)    Pop index
744:   LDA  5,-1(0)    Load address of base of array x
745:   SUB  5,5,4      Compute offset of value
746:    ST  3,0(5)     Store variable x
* CALL output
747:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
748:   LDA  3,-1(0)    Load address of base of array x
749:    ST  3,-4(1)    Push left side
* TOFF dec: -5
750:   LDC  3,5(6)     Load constant
* TOFF inc: -4
751:    LD  4,-4(1)    Pop left into AC1
752:   SUB  3,4,3      Compute location from index
753:    LD  3,0(3)     Load array element
754:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
755:   LDA  1,-2(1)    Ghost frame becomes new active frame
756:   LDA  3,1(7)     Return address in AC
757:   JMP  7,-752(7)  CALL output
758:   LDA  3,0(2)     Save the result in AC
* CALL END output
759:   LDC  3,7(6)     Load constant
760:    ST  3,-2(1)    Push index
* TOFF dec: -3
761:   LDA  3,-1(0)    Load address of base of array x
762:    ST  3,-3(1)    Push left side
* TOFF dec: -4
763:   LDC  3,5(6)     Load constant
* TOFF inc: -3
764:    LD  4,-3(1)    Pop left into AC1
765:   SUB  3,4,3      Compute location from index
766:    LD  3,0(3)     Load array element
* TOFF inc: -2
767:    LD  4,-2(1)    Pop index
768:   LDA  5,-9(0)    Load address of base of array y
769:   SUB  5,5,4      Compute offset of value
770:    LD  4,0(5)     Load lhs variable y
771:   DIV  3,4,3      Op /=
772:    ST  3,0(5)     Store variable y
773:   LDC  3,7(6)     Load constant
774:    ST  3,-2(1)    Push index
* TOFF dec: -3
775:   LDA  3,-1(0)    Load address of base of array x
776:    ST  3,-3(1)    Push left side
* TOFF dec: -4
777:   LDC  3,5(6)     Load constant
* TOFF inc: -3
778:    LD  4,-3(1)    Pop left into AC1
779:   SUB  3,4,3      Compute location from index
780:    LD  3,0(3)     Load array element
* TOFF inc: -2
781:    LD  4,-2(1)    Pop index
782:   LDA  5,-9(0)    Load address of base of array y
783:   SUB  5,5,4      Compute offset of value
784:    ST  3,0(5)     Store variable y
* CALL output
785:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
786:   LDA  3,-9(0)    Load address of base of array y
787:    ST  3,-4(1)    Push left side
* TOFF dec: -5
788:   LDC  3,7(6)     Load constant
* TOFF inc: -4
789:    LD  4,-4(1)    Pop left into AC1
790:   SUB  3,4,3      Compute location from index
791:    LD  3,0(3)     Load array element
792:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
793:   LDA  1,-2(1)    Ghost frame becomes new active frame
794:   LDA  3,1(7)     Return address in AC
795:   JMP  7,-790(7)  CALL output
796:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
797:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
798:   LDA  1,-2(1)    Ghost frame becomes new active frame
799:   LDA  3,1(7)     Return address in AC
800:   JMP  7,-767(7)  CALL outnl
801:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
802:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
803:   LDA  1,-2(1)    Ghost frame becomes new active frame
804:   LDA  3,1(7)     Return address in AC
805:   JMP  7,-772(7)  CALL outnl
806:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
807:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
808:   LDA  3,-9(0)    Load address of base of array y
809:    ST  3,-4(1)    Push left side
* TOFF dec: -5
810:   LDC  3,7(6)     Load constant
* TOFF inc: -4
811:    LD  4,-4(1)    Pop left into AC1
812:   SUB  3,4,3      Compute location from index
813:    LD  3,0(3)     Load array element
814:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
815:   LDA  1,-2(1)    Ghost frame becomes new active frame
816:   LDA  3,1(7)     Return address in AC
817:   JMP  7,-812(7)  CALL output
818:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
819:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
820:   LDA  1,-2(1)    Ghost frame becomes new active frame
821:   LDA  3,1(7)     Return address in AC
822:   JMP  7,-789(7)  CALL outnl
823:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
824:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
825:   LDA  1,-2(1)    Ghost frame becomes new active frame
826:   LDA  3,1(7)     Return address in AC
827:   JMP  7,-794(7)  CALL outnl
828:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
829:   LDC  3,7(6)     Load constant
830:    ST  3,-2(1)    Push index
* TOFF dec: -3
831:   LDA  3,-1(0)    Load address of base of array x
832:    ST  3,-3(1)    Push left side
* TOFF dec: -4
833:   LDC  3,5(6)     Load constant
* TOFF inc: -3
834:    LD  4,-3(1)    Pop left into AC1
835:   SUB  3,4,3      Compute location from index
836:    LD  3,0(3)     Load array element
* TOFF inc: -2
837:    LD  4,-2(1)    Pop index
838:   LDA  5,-9(0)    Load address of base of array y
839:   SUB  5,5,4      Compute offset of value
840:    LD  4,0(5)     Load lhs variable y
841:   DIV  3,4,3      Op /=
842:    ST  3,0(5)     Store variable y
843:   LDC  3,7(6)     Load constant
844:    ST  3,-2(1)    Push index
* TOFF dec: -3
845:   LDA  3,-1(0)    Load address of base of array x
846:    ST  3,-3(1)    Push left side
* TOFF dec: -4
847:   LDC  3,5(6)     Load constant
* TOFF inc: -3
848:    LD  4,-3(1)    Pop left into AC1
849:   SUB  3,4,3      Compute location from index
850:    LD  3,0(3)     Load array element
* TOFF inc: -2
851:    LD  4,-2(1)    Pop index
852:   LDA  5,-9(0)    Load address of base of array y
853:   SUB  5,5,4      Compute offset of value
854:    ST  3,0(5)     Store variable y
* CALL output
855:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
856:   LDA  3,-9(0)    Load address of base of array y
857:    ST  3,-4(1)    Push left side
* TOFF dec: -5
858:   LDC  3,7(6)     Load constant
* TOFF inc: -4
859:    LD  4,-4(1)    Pop left into AC1
860:   SUB  3,4,3      Compute location from index
861:    LD  3,0(3)     Load array element
862:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
863:   LDA  1,-2(1)    Ghost frame becomes new active frame
864:   LDA  3,1(7)     Return address in AC
865:   JMP  7,-860(7)  CALL output
866:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
867:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
868:   LDA  1,-2(1)    Ghost frame becomes new active frame
869:   LDA  3,1(7)     Return address in AC
870:   JMP  7,-837(7)  CALL outnl
871:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
872:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
873:   LDA  1,-2(1)    Ghost frame becomes new active frame
874:   LDA  3,1(7)     Return address in AC
875:   JMP  7,-842(7)  CALL outnl
876:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
877:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
878:   LDA  3,-9(0)    Load address of base of array y
879:    ST  3,-4(1)    Push left side
* TOFF dec: -5
880:   LDC  3,7(6)     Load constant
* TOFF inc: -4
881:    LD  4,-4(1)    Pop left into AC1
882:   SUB  3,4,3      Compute location from index
883:    LD  3,0(3)     Load array element
884:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
885:   LDA  1,-2(1)    Ghost frame becomes new active frame
886:   LDA  3,1(7)     Return address in AC
887:   JMP  7,-882(7)  CALL output
888:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
889:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
890:   LDA  1,-2(1)    Ghost frame becomes new active frame
891:   LDA  3,1(7)     Return address in AC
892:   JMP  7,-859(7)  CALL outnl
893:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
894:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
895:   LDA  1,-2(1)    Ghost frame becomes new active frame
896:   LDA  3,1(7)     Return address in AC
897:   JMP  7,-864(7)  CALL outnl
898:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
899:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
900:   LDA  3,-1(0)    Load address of base of array x
901:    ST  3,-4(1)    Push left side
* TOFF dec: -5
902:   LDC  3,5(6)     Load constant
* TOFF inc: -4
903:    LD  4,-4(1)    Pop left into AC1
904:   SUB  3,4,3      Compute location from index
905:    LD  3,0(3)     Load array element
906:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
907:   LDA  1,-2(1)    Ghost frame becomes new active frame
908:   LDA  3,1(7)     Return address in AC
909:   JMP  7,-904(7)  CALL output
910:   LDA  3,0(2)     Save the result in AC
* CALL END output
911:   LDC  3,7(6)     Load constant
912:    ST  3,-2(1)    Push index
* TOFF dec: -3
913:   LDA  3,-1(0)    Load address of base of array x
914:    ST  3,-3(1)    Push left side
* TOFF dec: -4
915:   LDC  3,5(6)     Load constant
* TOFF inc: -3
916:    LD  4,-3(1)    Pop left into AC1
917:   SUB  3,4,3      Compute location from index
918:    LD  3,0(3)     Load array element
* TOFF inc: -2
919:    LD  4,-2(1)    Pop index
920:   LDA  5,-9(0)    Load address of base of array y
921:   SUB  5,5,4      Compute offset of value
922:    LD  4,0(5)     Load lhs variable y
923:   DIV  3,4,3      Op /=
924:    ST  3,0(5)     Store variable y
925:   LDC  3,7(6)     Load constant
926:    ST  3,-2(1)    Push index
* TOFF dec: -3
927:   LDA  3,-1(0)    Load address of base of array x
928:    ST  3,-3(1)    Push left side
* TOFF dec: -4
929:   LDC  3,5(6)     Load constant
* TOFF inc: -3
930:    LD  4,-3(1)    Pop left into AC1
931:   SUB  3,4,3      Compute location from index
932:    LD  3,0(3)     Load array element
* TOFF inc: -2
933:    LD  4,-2(1)    Pop index
934:   LDA  5,-9(0)    Load address of base of array y
935:   SUB  5,5,4      Compute offset of value
936:    ST  3,0(5)     Store variable y
* CALL output
937:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
938:   LDA  3,-9(0)    Load address of base of array y
939:    ST  3,-4(1)    Push left side
* TOFF dec: -5
940:   LDC  3,7(6)     Load constant
* TOFF inc: -4
941:    LD  4,-4(1)    Pop left into AC1
942:   SUB  3,4,3      Compute location from index
943:    LD  3,0(3)     Load array element
944:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
945:   LDA  1,-2(1)    Ghost frame becomes new active frame
946:   LDA  3,1(7)     Return address in AC
947:   JMP  7,-942(7)  CALL output
948:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
949:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
950:   LDA  1,-2(1)    Ghost frame becomes new active frame
951:   LDA  3,1(7)     Return address in AC
952:   JMP  7,-919(7)  CALL outnl
953:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
954:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
955:   LDA  1,-2(1)    Ghost frame becomes new active frame
956:   LDA  3,1(7)     Return address in AC
957:   JMP  7,-924(7)  CALL outnl
958:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
959:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
960:   LDA  3,-9(0)    Load address of base of array y
961:    ST  3,-4(1)    Push left side
* TOFF dec: -5
962:   LDC  3,7(6)     Load constant
* TOFF inc: -4
963:    LD  4,-4(1)    Pop left into AC1
964:   SUB  3,4,3      Compute location from index
965:    LD  3,0(3)     Load array element
966:    ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
967:   LDA  1,-2(1)    Ghost frame becomes new active frame
968:   LDA  3,1(7)     Return address in AC
969:   JMP  7,-964(7)  CALL output
970:   LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
971:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
972:   LDA  1,-2(1)    Ghost frame becomes new active frame
973:   LDA  3,1(7)     Return address in AC
974:   JMP  7,-941(7)  CALL outnl
975:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
976:    ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
977:   LDA  1,-2(1)    Ghost frame becomes new active frame
978:   LDA  3,1(7)     Return address in AC
979:   JMP  7,-946(7)  CALL outnl
980:   LDA  3,0(2)     Save the result in AC
* CALL END outnl
981:   LDC  3,7(6)     Load constant
982:    ST  3,-2(1)    Push index
* TOFF dec: -3
983:   LDA  3,-1(0)    Load address of base of array x
984:    ST  3,-3(1)    Push left side
* TOFF dec: -4
985:   LDC  3,5(6)     Load constant
* TOFF inc: -3
986:    LD  4,-3(1)    Pop left into AC1
987:   SUB  3,4,3      Compute location from index
988:    LD  3,0(3)     Load array element
* TOFF inc: -2
989:    LD  4,-2(1)    Pop index
990:   LDA  5,-9(0)    Load address of base of array y
991:   SUB  5,5,4      Compute offset of value
992:    LD  4,0(5)     Load lhs variable y
993:   DIV  3,4,3      Op /=
994:    ST  3,0(5)     Store variable y
995:   LDC  3,7(6)     Load constant
996:    ST  3,-2(1)    Push index
* TOFF dec: -3
997:   LDA  3,-1(0)    Load address of base of array x
998:    ST  3,-3(1)    Push left side
* TOFF dec: -4
999:   LDC  3,5(6)     Load constant
* TOFF inc: -3
1000:   LD  4,-3(1)    Pop left into AC1
1001:  SUB  3,4,3      Compute location from index
1002:   LD  3,0(3)     Load array element
* TOFF inc: -2
1003:   LD  4,-2(1)    Pop index
1004:  LDA  5,-9(0)    Load address of base of array y
1005:  SUB  5,5,4      Compute offset of value
1006:   ST  3,0(5)     Store variable y
* CALL output
1007:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
1008:  LDA  3,-9(0)    Load address of base of array y
1009:   ST  3,-4(1)    Push left side
* TOFF dec: -5
1010:  LDC  3,7(6)     Load constant
* TOFF inc: -4
1011:   LD  4,-4(1)    Pop left into AC1
1012:  SUB  3,4,3      Compute location from index
1013:   LD  3,0(3)     Load array element
1014:   ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
1015:  LDA  1,-2(1)    Ghost frame becomes new active frame
1016:  LDA  3,1(7)     Return address in AC
1017:  JMP  7,-1012(7) CALL output
1018:  LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
1019:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1020:  LDA  1,-2(1)    Ghost frame becomes new active frame
1021:  LDA  3,1(7)     Return address in AC
1022:  JMP  7,-989(7)  CALL outnl
1023:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
1024:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1025:  LDA  1,-2(1)    Ghost frame becomes new active frame
1026:  LDA  3,1(7)     Return address in AC
1027:  JMP  7,-994(7)  CALL outnl
1028:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
1029:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
1030:  LDA  3,-9(0)    Load address of base of array y
1031:   ST  3,-4(1)    Push left side
* TOFF dec: -5
1032:  LDC  3,7(6)     Load constant
* TOFF inc: -4
1033:   LD  4,-4(1)    Pop left into AC1
1034:  SUB  3,4,3      Compute location from index
1035:   LD  3,0(3)     Load array element
1036:   ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
1037:  LDA  1,-2(1)    Ghost frame becomes new active frame
1038:  LDA  3,1(7)     Return address in AC
1039:  JMP  7,-1034(7) CALL output
1040:  LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
1041:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1042:  LDA  1,-2(1)    Ghost frame becomes new active frame
1043:  LDA  3,1(7)     Return address in AC
1044:  JMP  7,-1011(7) CALL outnl
1045:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
1046:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1047:  LDA  1,-2(1)    Ghost frame becomes new active frame
1048:  LDA  3,1(7)     Return address in AC
1049:  JMP  7,-1016(7) CALL outnl
1050:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
1051:  LDC  3,5(6)     Load constant
1052:   ST  3,-2(1)    Push index
* TOFF dec: -3
1053:  LDA  3,-9(0)    Load address of base of array y
1054:   ST  3,-3(1)    Push left side
* TOFF dec: -4
1055:  LDC  3,7(6)     Load constant
* TOFF inc: -3
1056:   LD  4,-3(1)    Pop left into AC1
1057:  SUB  3,4,3      Compute location from index
1058:   LD  3,0(3)     Load array element
* TOFF inc: -2
1059:   LD  4,-2(1)    Pop index
1060:  LDA  5,-1(0)    Load address of base of array x
1061:  SUB  5,5,4      Compute offset of value
1062:   LD  4,0(5)     Load lhs variable x
1063:  ADD  3,4,3      Op +=
1064:   ST  3,0(5)     Store variable x
1065:  LDC  3,5(6)     Load constant
1066:   ST  3,-2(1)    Push index
* TOFF dec: -3
1067:  LDA  3,-9(0)    Load address of base of array y
1068:   ST  3,-3(1)    Push left side
* TOFF dec: -4
1069:  LDC  3,7(6)     Load constant
* TOFF inc: -3
1070:   LD  4,-3(1)    Pop left into AC1
1071:  SUB  3,4,3      Compute location from index
1072:   LD  3,0(3)     Load array element
* TOFF inc: -2
1073:   LD  4,-2(1)    Pop index
1074:  LDA  5,-1(0)    Load address of base of array x
1075:  SUB  5,5,4      Compute offset of value
1076:   ST  3,0(5)     Store variable x
* CALL output
1077:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
1078:  LDA  3,-1(0)    Load address of base of array x
1079:   ST  3,-4(1)    Push left side
* TOFF dec: -5
1080:  LDC  3,5(6)     Load constant
* TOFF inc: -4
1081:   LD  4,-4(1)    Pop left into AC1
1082:  SUB  3,4,3      Compute location from index
1083:   LD  3,0(3)     Load array element
1084:   ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
1085:  LDA  1,-2(1)    Ghost frame becomes new active frame
1086:  LDA  3,1(7)     Return address in AC
1087:  JMP  7,-1082(7) CALL output
1088:  LDA  3,0(2)     Save the result in AC
* CALL END output
1089:  LDC  3,7(6)     Load constant
1090:   ST  3,-2(1)    Push index
* TOFF dec: -3
1091:  LDA  3,-1(0)    Load address of base of array x
1092:   ST  3,-3(1)    Push left side
* TOFF dec: -4
1093:  LDC  3,5(6)     Load constant
* TOFF inc: -3
1094:   LD  4,-3(1)    Pop left into AC1
1095:  SUB  3,4,3      Compute location from index
1096:   LD  3,0(3)     Load array element
* TOFF inc: -2
1097:   LD  4,-2(1)    Pop index
1098:  LDA  5,-9(0)    Load address of base of array y
1099:  SUB  5,5,4      Compute offset of value
1100:   LD  4,0(5)     Load lhs variable y
1101:  DIV  3,4,3      Op /=
1102:   ST  3,0(5)     Store variable y
1103:  LDC  3,7(6)     Load constant
1104:   ST  3,-2(1)    Push index
* TOFF dec: -3
1105:  LDA  3,-1(0)    Load address of base of array x
1106:   ST  3,-3(1)    Push left side
* TOFF dec: -4
1107:  LDC  3,5(6)     Load constant
* TOFF inc: -3
1108:   LD  4,-3(1)    Pop left into AC1
1109:  SUB  3,4,3      Compute location from index
1110:   LD  3,0(3)     Load array element
* TOFF inc: -2
1111:   LD  4,-2(1)    Pop index
1112:  LDA  5,-9(0)    Load address of base of array y
1113:  SUB  5,5,4      Compute offset of value
1114:   ST  3,0(5)     Store variable y
* CALL output
1115:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
1116:  LDA  3,-9(0)    Load address of base of array y
1117:   ST  3,-4(1)    Push left side
* TOFF dec: -5
1118:  LDC  3,7(6)     Load constant
* TOFF inc: -4
1119:   LD  4,-4(1)    Pop left into AC1
1120:  SUB  3,4,3      Compute location from index
1121:   LD  3,0(3)     Load array element
1122:   ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
1123:  LDA  1,-2(1)    Ghost frame becomes new active frame
1124:  LDA  3,1(7)     Return address in AC
1125:  JMP  7,-1120(7) CALL output
1126:  LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
1127:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1128:  LDA  1,-2(1)    Ghost frame becomes new active frame
1129:  LDA  3,1(7)     Return address in AC
1130:  JMP  7,-1097(7) CALL outnl
1131:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
1132:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1133:  LDA  1,-2(1)    Ghost frame becomes new active frame
1134:  LDA  3,1(7)     Return address in AC
1135:  JMP  7,-1102(7) CALL outnl
1136:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
1137:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
1138:  LDA  3,-9(0)    Load address of base of array y
1139:   ST  3,-4(1)    Push left side
* TOFF dec: -5
1140:  LDC  3,7(6)     Load constant
* TOFF inc: -4
1141:   LD  4,-4(1)    Pop left into AC1
1142:  SUB  3,4,3      Compute location from index
1143:   LD  3,0(3)     Load array element
1144:   ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
1145:  LDA  1,-2(1)    Ghost frame becomes new active frame
1146:  LDA  3,1(7)     Return address in AC
1147:  JMP  7,-1142(7) CALL output
1148:  LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
1149:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1150:  LDA  1,-2(1)    Ghost frame becomes new active frame
1151:  LDA  3,1(7)     Return address in AC
1152:  JMP  7,-1119(7) CALL outnl
1153:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
1154:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1155:  LDA  1,-2(1)    Ghost frame becomes new active frame
1156:  LDA  3,1(7)     Return address in AC
1157:  JMP  7,-1124(7) CALL outnl
1158:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
1159:  LDC  3,7(6)     Load constant
1160:   ST  3,-2(1)    Push index
* TOFF dec: -3
1161:  LDA  3,-1(0)    Load address of base of array x
1162:   ST  3,-3(1)    Push left side
* TOFF dec: -4
1163:  LDC  3,5(6)     Load constant
* TOFF inc: -3
1164:   LD  4,-3(1)    Pop left into AC1
1165:  SUB  3,4,3      Compute location from index
1166:   LD  3,0(3)     Load array element
* TOFF inc: -2
1167:   LD  4,-2(1)    Pop index
1168:  LDA  5,-9(0)    Load address of base of array y
1169:  SUB  5,5,4      Compute offset of value
1170:   LD  4,0(5)     Load lhs variable y
1171:  DIV  3,4,3      Op /=
1172:   ST  3,0(5)     Store variable y
1173:  LDC  3,7(6)     Load constant
1174:   ST  3,-2(1)    Push index
* TOFF dec: -3
1175:  LDA  3,-1(0)    Load address of base of array x
1176:   ST  3,-3(1)    Push left side
* TOFF dec: -4
1177:  LDC  3,5(6)     Load constant
* TOFF inc: -3
1178:   LD  4,-3(1)    Pop left into AC1
1179:  SUB  3,4,3      Compute location from index
1180:   LD  3,0(3)     Load array element
* TOFF inc: -2
1181:   LD  4,-2(1)    Pop index
1182:  LDA  5,-9(0)    Load address of base of array y
1183:  SUB  5,5,4      Compute offset of value
1184:   ST  3,0(5)     Store variable y
* CALL output
1185:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
1186:  LDA  3,-9(0)    Load address of base of array y
1187:   ST  3,-4(1)    Push left side
* TOFF dec: -5
1188:  LDC  3,7(6)     Load constant
* TOFF inc: -4
1189:   LD  4,-4(1)    Pop left into AC1
1190:  SUB  3,4,3      Compute location from index
1191:   LD  3,0(3)     Load array element
1192:   ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
1193:  LDA  1,-2(1)    Ghost frame becomes new active frame
1194:  LDA  3,1(7)     Return address in AC
1195:  JMP  7,-1190(7) CALL output
1196:  LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
1197:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1198:  LDA  1,-2(1)    Ghost frame becomes new active frame
1199:  LDA  3,1(7)     Return address in AC
1200:  JMP  7,-1167(7) CALL outnl
1201:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
1202:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1203:  LDA  1,-2(1)    Ghost frame becomes new active frame
1204:  LDA  3,1(7)     Return address in AC
1205:  JMP  7,-1172(7) CALL outnl
1206:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
1207:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
1208:  LDA  3,-9(0)    Load address of base of array y
1209:   ST  3,-4(1)    Push left side
* TOFF dec: -5
1210:  LDC  3,7(6)     Load constant
* TOFF inc: -4
1211:   LD  4,-4(1)    Pop left into AC1
1212:  SUB  3,4,3      Compute location from index
1213:   LD  3,0(3)     Load array element
1214:   ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
1215:  LDA  1,-2(1)    Ghost frame becomes new active frame
1216:  LDA  3,1(7)     Return address in AC
1217:  JMP  7,-1212(7) CALL output
1218:  LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
1219:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1220:  LDA  1,-2(1)    Ghost frame becomes new active frame
1221:  LDA  3,1(7)     Return address in AC
1222:  JMP  7,-1189(7) CALL outnl
1223:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
1224:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1225:  LDA  1,-2(1)    Ghost frame becomes new active frame
1226:  LDA  3,1(7)     Return address in AC
1227:  JMP  7,-1194(7) CALL outnl
1228:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
1229:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
1230:  LDA  3,-1(0)    Load address of base of array x
1231:   ST  3,-4(1)    Push left side
* TOFF dec: -5
1232:  LDC  3,5(6)     Load constant
* TOFF inc: -4
1233:   LD  4,-4(1)    Pop left into AC1
1234:  SUB  3,4,3      Compute location from index
1235:   LD  3,0(3)     Load array element
1236:   ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
1237:  LDA  1,-2(1)    Ghost frame becomes new active frame
1238:  LDA  3,1(7)     Return address in AC
1239:  JMP  7,-1234(7) CALL output
1240:  LDA  3,0(2)     Save the result in AC
* CALL END output
1241:  LDC  3,7(6)     Load constant
1242:   ST  3,-2(1)    Push index
* TOFF dec: -3
1243:  LDA  3,-1(0)    Load address of base of array x
1244:   ST  3,-3(1)    Push left side
* TOFF dec: -4
1245:  LDC  3,5(6)     Load constant
* TOFF inc: -3
1246:   LD  4,-3(1)    Pop left into AC1
1247:  SUB  3,4,3      Compute location from index
1248:   LD  3,0(3)     Load array element
* TOFF inc: -2
1249:   LD  4,-2(1)    Pop index
1250:  LDA  5,-9(0)    Load address of base of array y
1251:  SUB  5,5,4      Compute offset of value
1252:   LD  4,0(5)     Load lhs variable y
1253:  DIV  3,4,3      Op /=
1254:   ST  3,0(5)     Store variable y
1255:  LDC  3,7(6)     Load constant
1256:   ST  3,-2(1)    Push index
* TOFF dec: -3
1257:  LDA  3,-1(0)    Load address of base of array x
1258:   ST  3,-3(1)    Push left side
* TOFF dec: -4
1259:  LDC  3,5(6)     Load constant
* TOFF inc: -3
1260:   LD  4,-3(1)    Pop left into AC1
1261:  SUB  3,4,3      Compute location from index
1262:   LD  3,0(3)     Load array element
* TOFF inc: -2
1263:   LD  4,-2(1)    Pop index
1264:  LDA  5,-9(0)    Load address of base of array y
1265:  SUB  5,5,4      Compute offset of value
1266:   ST  3,0(5)     Store variable y
* CALL output
1267:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
1268:  LDA  3,-9(0)    Load address of base of array y
1269:   ST  3,-4(1)    Push left side
* TOFF dec: -5
1270:  LDC  3,7(6)     Load constant
* TOFF inc: -4
1271:   LD  4,-4(1)    Pop left into AC1
1272:  SUB  3,4,3      Compute location from index
1273:   LD  3,0(3)     Load array element
1274:   ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
1275:  LDA  1,-2(1)    Ghost frame becomes new active frame
1276:  LDA  3,1(7)     Return address in AC
1277:  JMP  7,-1272(7) CALL output
1278:  LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
1279:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1280:  LDA  1,-2(1)    Ghost frame becomes new active frame
1281:  LDA  3,1(7)     Return address in AC
1282:  JMP  7,-1249(7) CALL outnl
1283:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
1284:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1285:  LDA  1,-2(1)    Ghost frame becomes new active frame
1286:  LDA  3,1(7)     Return address in AC
1287:  JMP  7,-1254(7) CALL outnl
1288:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
1289:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
1290:  LDA  3,-9(0)    Load address of base of array y
1291:   ST  3,-4(1)    Push left side
* TOFF dec: -5
1292:  LDC  3,7(6)     Load constant
* TOFF inc: -4
1293:   LD  4,-4(1)    Pop left into AC1
1294:  SUB  3,4,3      Compute location from index
1295:   LD  3,0(3)     Load array element
1296:   ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
1297:  LDA  1,-2(1)    Ghost frame becomes new active frame
1298:  LDA  3,1(7)     Return address in AC
1299:  JMP  7,-1294(7) CALL output
1300:  LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
1301:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1302:  LDA  1,-2(1)    Ghost frame becomes new active frame
1303:  LDA  3,1(7)     Return address in AC
1304:  JMP  7,-1271(7) CALL outnl
1305:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
1306:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1307:  LDA  1,-2(1)    Ghost frame becomes new active frame
1308:  LDA  3,1(7)     Return address in AC
1309:  JMP  7,-1276(7) CALL outnl
1310:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
1311:  LDC  3,7(6)     Load constant
1312:   ST  3,-2(1)    Push index
* TOFF dec: -3
1313:  LDA  3,-1(0)    Load address of base of array x
1314:   ST  3,-3(1)    Push left side
* TOFF dec: -4
1315:  LDC  3,5(6)     Load constant
* TOFF inc: -3
1316:   LD  4,-3(1)    Pop left into AC1
1317:  SUB  3,4,3      Compute location from index
1318:   LD  3,0(3)     Load array element
* TOFF inc: -2
1319:   LD  4,-2(1)    Pop index
1320:  LDA  5,-9(0)    Load address of base of array y
1321:  SUB  5,5,4      Compute offset of value
1322:   LD  4,0(5)     Load lhs variable y
1323:  DIV  3,4,3      Op /=
1324:   ST  3,0(5)     Store variable y
1325:  LDC  3,7(6)     Load constant
1326:   ST  3,-2(1)    Push index
* TOFF dec: -3
1327:  LDA  3,-1(0)    Load address of base of array x
1328:   ST  3,-3(1)    Push left side
* TOFF dec: -4
1329:  LDC  3,5(6)     Load constant
* TOFF inc: -3
1330:   LD  4,-3(1)    Pop left into AC1
1331:  SUB  3,4,3      Compute location from index
1332:   LD  3,0(3)     Load array element
* TOFF inc: -2
1333:   LD  4,-2(1)    Pop index
1334:  LDA  5,-9(0)    Load address of base of array y
1335:  SUB  5,5,4      Compute offset of value
1336:   ST  3,0(5)     Store variable y
* CALL output
1337:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
1338:  LDA  3,-9(0)    Load address of base of array y
1339:   ST  3,-4(1)    Push left side
* TOFF dec: -5
1340:  LDC  3,7(6)     Load constant
* TOFF inc: -4
1341:   LD  4,-4(1)    Pop left into AC1
1342:  SUB  3,4,3      Compute location from index
1343:   LD  3,0(3)     Load array element
1344:   ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
1345:  LDA  1,-2(1)    Ghost frame becomes new active frame
1346:  LDA  3,1(7)     Return address in AC
1347:  JMP  7,-1342(7) CALL output
1348:  LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
1349:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1350:  LDA  1,-2(1)    Ghost frame becomes new active frame
1351:  LDA  3,1(7)     Return address in AC
1352:  JMP  7,-1319(7) CALL outnl
1353:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
1354:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1355:  LDA  1,-2(1)    Ghost frame becomes new active frame
1356:  LDA  3,1(7)     Return address in AC
1357:  JMP  7,-1324(7) CALL outnl
1358:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL output
1359:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* TOFF dec: -4
* Param 1
1360:  LDA  3,-9(0)    Load address of base of array y
1361:   ST  3,-4(1)    Push left side
* TOFF dec: -5
1362:  LDC  3,7(6)     Load constant
* TOFF inc: -4
1363:   LD  4,-4(1)    Pop left into AC1
1364:  SUB  3,4,3      Compute location from index
1365:   LD  3,0(3)     Load array element
1366:   ST  3,-4(1)    Push parameter
* END Params
* TOFF set: -2
1367:  LDA  1,-2(1)    Ghost frame becomes new active frame
1368:  LDA  3,1(7)     Return address in AC
1369:  JMP  7,-1364(7) CALL output
1370:  LDA  3,0(2)     Save the result in AC
* CALL END output
* CALL outnl
1371:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1372:  LDA  1,-2(1)    Ghost frame becomes new active frame
1373:  LDA  3,1(7)     Return address in AC
1374:  JMP  7,-1341(7) CALL outnl
1375:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* CALL outnl
1376:   ST  1,-2(1)    Store FP in ghost frame for output
* TOFF dec: -3
* START Params
* END Params
* TOFF set: -2
1377:  LDA  1,-2(1)    Ghost frame becomes new active frame
1378:  LDA  3,1(7)     Return address in AC
1379:  JMP  7,-1346(7) CALL outnl
1380:  LDA  3,0(2)     Save the result in AC
* CALL END outnl
* END COMPOUND BODY
* END COMPOUND
* Add standard closing in case there is no return statement
1381:  LDC  2,0(6)     Set return value to 0
1382:   LD  3,-1(1)    Load return address
1383:   LD  1,0(0)     Adjust fp
1384:  JMP  7,0(3)     Return
* END FUNCTION main
* ** ** ** ** ** ** ** ** ** ** ** **
* END User-declared functions
* ** ** ** ** ** ** ** ** ** ** ** **
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* START INIT
* ** ** ** ** ** ** ** ** ** ** ** **
1385:  LDA  1,0(0)     Set first frame at end of globals
1386:   ST  1,0(1)     Store old FP (point to self)
* START GLOBALS AND STATICS
1387:  LDC  3,7(6)     Load size of array x
1388:   ST  3,0(0)     Store size of x
1389:  LDC  3,9(6)     Load size of array y
1390:   ST  3,-8(0)    Store size of y
* END GLOBALS AND STATICS
1391:  LDA  3,1(7)     Return address in AC
1392:  JMP  7,7(1352)  Jump to main
1393: HALT  0,0,0      DONE!
* ** ** ** ** ** ** ** ** ** ** ** **
* END INIT
* ** ** ** ** ** ** ** ** ** ** ** **

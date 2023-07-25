
data segment
var1 db 10101b
var2 dw 1a2bh
var3 dd 1921393
x db -128
y dw 0ffffh
z db 11111111b
q dd 12345678h

data ends

code1 segment
assume cs:code1, ds:data
std
jna lbl1
lbl1:
jna lbl1
push ebx,eax
pop gs:var3
jna lbl1
jna lbl2
adc ds:x
jmp far ptr lbl3
lbl2:
sbb dl, 5
sbb eax, esp
imul ebx, fs:var3[esi*4]
adc q[ebp*2], 10101111b
adc es:q[ebp*2], 0ffh
adc ss:q[ebp*4], 0ff112233h
code1 ends

code2 segment
assume cs:code2, ds:data
lbl3:
cmp ds:var1[edx*2], dl
cmp var3[eax*4], ebx
adc var1, -1
adc var1, 10101b
adc var3[ebx*8], 3fh
adc var3, 77777
jmp far ptr lbl1
code2 ends
end
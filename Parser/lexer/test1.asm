data segment
var1 db 10101b
var2 dw 1a2bh
var3 dd 1921393
data ends

code1 segment
assume cs:code1, ds:data
std
lbl1:
push ebx
pop gs:var3
jna lbl1
jna lbl2
jmp far ptr lbl3
lbl2:
sbb dl, cl
sbb eax, esp
imul ebx, fs:var3[esi*4]
code1 ends

code2 segment
assume cs:code2, ds:data
lbl3:
cmp var1[edx*2], dl
cmp var3[eax*4], ebx
adc var1, -1
adc var1, 10101b
adc var3[ebx*8], 3fh
adc var3, 77777
jmp far ptr lbl2
code2 ends
end
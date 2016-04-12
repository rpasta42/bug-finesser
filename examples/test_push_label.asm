mov %0 #5
mov %1 #6
add %0 %1

push 'test
pop %0
jmp %0

mov %1 #11
halt

label 'test
mov %1 #10

halt


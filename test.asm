; return on register 16
; push argument (10) and return address on stack
push 'exithalt
; next test with 10
push #20
jmp 'fib

label 'exithalt
halt

label 'fib
; pop argument into %0
pop %0
; if argument is 2 go to ifeq which returns 1
cmp %0 #2
je 'basedone

; if argument is 1 go to ifeq which returns 1
cmp %0 #1
je 'basedone

; otherwise recurse
sub %0 #1
; save argument because fib will overwrite
push %0
; push return value
push 'retrecurse1
; push as argument
push %0
jmp 'fib

label 'retrecurse1
; original argument - 1
pop %0
; subtract one more (n - 2)
sub %0 #1

; push return of first recursive call
push %16
push 'retrecurse2
; push argument to stack
push %0
jmp 'fib

label 'retrecurse2
; result of second and first
pop %14
add %16 %14
; get return
pop %0
jmp %0
jmp 'exithalt

label 'basedone
; mov %3 %0
mov %16 #1
; pop return address
pop %1
jmp %1


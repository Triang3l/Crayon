section .rodata align=16

	align 16
	Start_Widths: dd 80, 0, 32, 0
	Start_Heights: dd 16, 0, 32, 0

	Start_FileName: db "Report.bin", 0

section .bss align=8

	align 8
	Start_StackAlignmentTest: resq 1

section .text align=32

global _start
align 32
_start:
	; Terminate stack tracing in debuggers.
	xor rbp, rbp

	; Copy the stack pointer to the variable.
	mov [rel Start_StackAlignmentTest], rsp

	; Initially RSP % 16 == 0.
	; [rsp+0] = vector for writing to the file.
	sub rsp, 16

	; Multiply the two vectors and store the result on the stack.
	movdqa xmm0, [rel Start_Widths]
	pmuldq xmm0, [rel Start_Heights]
	movdqa [rsp], xmm0

	; Open the file, exit if failed.
	lea rdi, [rel Start_FileName]
	mov esi, 0o101
	mov edx, 0o666
	mov rax, 2
	syscall
	cmp eax, 0
	jl Start_Error

	; Save the file handle to the nonvolatile register EBX.
	mov ebx, eax

	; Write the vector to the file (the handle is still in EAX).
	mov edi, eax
	mov rsi, rsp
	mov rdx, 16
	mov rax, 1
	syscall

	; Write the initial stack pointer to the file.
	mov edi, ebx
	lea rsi, [rel Start_StackAlignmentTest]
	mov rdx, 8
	mov rax, 1
	syscall

	; Close the file.
	mov edi, ebx
	mov rax, 3
	syscall

	; Exit.
	xor edi, edi
	mov rax, 60
	syscall

	Start_Error:
		mov edi, 1
		mov rax, 60
		syscall

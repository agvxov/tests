section .data
	greeting db "Hello World!\n"
	greeting_len equ $ - greeting

global _main
section .text
_main:
	mov eax, 4
	mov ebx, 1
	mov ecx, greeting
	mov edx, greeting_len
	

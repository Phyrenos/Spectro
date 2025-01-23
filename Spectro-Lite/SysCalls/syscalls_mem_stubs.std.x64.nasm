[SECTION .data]
currentHash:    dd  0

[SECTION .text]

BITS 64
DEFAULT REL

global NtProtectVirtualMemory
global NtWriteVirtualMemory
global NtReadVirtualMemory

global WhisperMain
extern SW2_GetSyscallNumber
    
WhisperMain:
    pop rax
    mov [rsp+ 8], rcx              ; Save registers.
    mov [rsp+16], rdx
    mov [rsp+24], r8
    mov [rsp+32], r9
    sub rsp, 28h
    mov ecx, dword [currentHash]
    call SW2_GetSyscallNumber
    add rsp, 28h
    mov rcx, [rsp+ 8]              ; Restore registers.
    mov rdx, [rsp+16]
    mov r8, [rsp+24]
    mov r9, [rsp+32]
    mov r10, rcx
    syscall                        ; Issue syscall
    ret

NtProtectVirtualMemory:
    mov dword [currentHash], 00F9D151Fh    ; Load function hash into global variable.
    call WhisperMain                       ; Resolve function hash into syscall number and make the call

NtWriteVirtualMemory:
    mov dword [currentHash], 00B99071Dh    ; Load function hash into global variable.
    call WhisperMain                       ; Resolve function hash into syscall number and make the call

NtReadVirtualMemory:
    mov dword [currentHash], 0199B0D17h    ; Load function hash into global variable.
    call WhisperMain                       ; Resolve function hash into syscall number and make the call


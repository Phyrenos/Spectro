.intel_syntax noprefix
.data
currentHash:    .long   0

.text
.global NtProtectVirtualMemory
.global NtWriteVirtualMemory
.global NtReadVirtualMemory

.global WhisperMain
.extern SW2_GetSyscallNumber
    
WhisperMain:
    pop rax
    mov [rsp+ 8], rcx              # Save registers.
    mov [rsp+16], rdx
    mov [rsp+24], r8
    mov [rsp+32], r9
    sub rsp, 0x28
    mov ecx, dword ptr [currentHash + RIP]
    call SW2_GetSyscallNumber
    add rsp, 0x28
    mov rcx, [rsp+ 8]              # Restore registers.
    mov rdx, [rsp+16]
    mov r8, [rsp+24]
    mov r9, [rsp+32]
    mov r10, rcx
    syscall                        # Issue syscall
    ret

NtProtectVirtualMemory:
    mov dword ptr [currentHash + RIP], 0x00F9D151F   # Load function hash into global variable.
    call WhisperMain                           # Resolve function hash into syscall number and make the call


NtWriteVirtualMemory:
    mov dword ptr [currentHash + RIP], 0x00B99071D   # Load function hash into global variable.
    call WhisperMain                           # Resolve function hash into syscall number and make the call


NtReadVirtualMemory:
    mov dword ptr [currentHash + RIP], 0x0199B0D17   # Load function hash into global variable.
    call WhisperMain                           # Resolve function hash into syscall number and make the call



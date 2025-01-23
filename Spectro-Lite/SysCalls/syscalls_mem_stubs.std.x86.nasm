[SECTION .data]

global _NtProtectVirtualMemory
global _NtWriteVirtualMemory
global _NtReadVirtualMemory

global _WhisperMain
extern _SW2_GetSyscallNumber

[SECTION .text]

BITS 32
DEFAULT REL

_WhisperMain:
    pop eax                        ; Remove return address from CALL instruction
    call _SW2_GetSyscallNumber     ; Resolve function hash into syscall number
    add esp, 4                     ; Restore ESP
    mov ecx, [fs:0c0h]
    test ecx, ecx
    jne _wow64
    lea edx, [esp+4h]
    INT 02eh
    ret
_wow64:
    xor ecx, ecx
    lea edx, [esp+4h]
    call dword [fs:0c0h]
    ret

_NtProtectVirtualMemory:
    push 00F9D151Fh
    call _WhisperMain

_NtWriteVirtualMemory:
    push 00B99071Dh
    call _WhisperMain

_NtReadVirtualMemory:
    push 0199B0D17h
    call _WhisperMain


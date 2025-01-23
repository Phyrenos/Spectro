.intel_syntax noprefix

.text
.global _NtProtectVirtualMemory
.global _NtWriteVirtualMemory
.global _NtReadVirtualMemory

.global _WhisperMain

_WhisperMain:
    pop eax                        # Remove return address from CALL instruction
    call _SW2_GetSyscallNumber     # Resolve function hash into syscall number
    add esp, 4                     # Restore ESP
    mov ecx, dword ptr fs:0xc0
    test ecx, ecx
    jne _wow64
    lea edx, dword ptr [esp+0x04]
    INT 0x02e
    ret
_wow64:
    xor ecx, ecx
    lea edx, dword ptr [esp+0x04]
    call dword ptr fs:0xc0
    ret

_NtProtectVirtualMemory:
    push 0x0F9D151F
    call _WhisperMain

_NtWriteVirtualMemory:
    push 0x0B99071D
    call _WhisperMain

_NtReadVirtualMemory:
    push 0x199B0D17
    call _WhisperMain


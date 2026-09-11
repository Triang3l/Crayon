%ifndef cray_Included_Utility_x64_Linux
%define cray_Included_Utility_x64_Linux

; `O_*`.
cray_Util_Linux_FileModeFlags_ReadOnly equ 0b00
cray_Util_Linux_FileModeFlags_WriteOnly equ 0b01
cray_Util_Linux_FileModeFlags_ReadWrite equ 0b10
cray_Util_Linux_FileModeFlag_Create equ 1 << 6
cray_Util_Linux_FileModeFlags_CreateWriteOnly equ \
    cray_Util_Linux_FileModeFlags_WriteOnly | cray_Util_Linux_FileModeFlag_Create

; `struct stat`.
struc cray_Util_Linux_Stat
    ; All fields are unsigned.
	.Device: resq 1
	.Inode: resq 1
	.Mode: resw 1
	.LinkCount: resw 1
	.UID: resw 1
	.GID: resw 1
	.RepresentedDevice: resq 1
	.Size: resq 1
	.BlockSize: resq 1
	.BlockCount: resq 1
	.AccessTime: resq 1
	.AccessTimeNanoseconds: resq 1
	.ModificationTime: resq 1
	.ModificationTimeNanoseconds: resq 1
	.StatusChangeTime: resq 1
	.StatusChangeTimeNanoseconds: resq 1
	.Padding: resq 2
endstruc

; `PROT_*`.
cray_Util_Linux_MemoryProtectionFlag_Read equ 1 << 0
cray_Util_Linux_MemoryProtectionFlag_Write equ 1 << 1
cray_Util_Linux_MemoryProtectionFlag_Execute equ 1 << 2
cray_Util_Linux_MemoryProtectionFlags_ReadWrite equ \
    cray_Util_Linux_MemoryProtectionFlag_Read | cray_Util_Linux_MemoryProtectionFlag_Write

; `MAP_*`.
cray_Util_Linux_MemoryMappingFlag_Anonymous equ 1 << 5

; System calls.
; The system call number must be placed in RAX. The rest of the calling convention follows the System V ABI.
; The numbers are from `/usr/include/x86_64-linux-gnu/asm/unistd_64.h`.

; (int fd, void const buffer[count], size_t count) -> ssize_t written
cray_Util_Linux_SysCall_write equ 1
; (char const * path, int flags, ... mode_t mode) -> int fd
cray_Util_Linux_SysCall_open equ 2
; (int fd) -> int result
cray_Util_Linux_SysCall_close equ 3
; (int fd, struct stat * stat_buffer) -> int result
cray_Util_Linux_SysCall_fstat equ 5
; (void address[length], size_t length, int protection, int flags, int fd, off_t offset) -> void * memory
cray_Util_Linux_SysCall_mmap equ 9
; (void address[length], size_t length) -> int result
cray_Util_Linux_SysCall_munmap equ 11
; (int status)
cray_Util_Linux_SysCall_exit_group equ 231

%endif

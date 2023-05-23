
section .text


global hf_crc32_opt_3
hf_crc32_opt_3:

    push rcx


    xor rax, rax
    mov eax, -1

    crc_32_opt_3_next_byte:
        mov ch, [rdi]
        cmp ch, 0
        je crc_32_opt_3_exit

        crc32 eax, ch
        inc rdi
        jmp crc_32_opt_3_next_byte

    crc_32_opt_3_exit:

    pop rcx
    ret



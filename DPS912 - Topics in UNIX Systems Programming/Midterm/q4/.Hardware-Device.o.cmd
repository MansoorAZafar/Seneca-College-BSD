savedcmd_Hardware-Device.o := ld -m elf_x86_64 -z noexecstack --no-warn-rwx-segments   -r -o Hardware-Device.o @Hardware-Device.mod  ; /usr/src/linux-headers-7.0.0-22-generic/tools/objtool/objtool --hacks=jump_label --hacks=noinstr --hacks=skylake --retpoline --rethunk --sls --stackval --static-call --uaccess --prefix=16  --link  --module Hardware-Device.o

Hardware-Device.o: $(wildcard /usr/src/linux-headers-7.0.0-22-generic/tools/objtool/objtool)

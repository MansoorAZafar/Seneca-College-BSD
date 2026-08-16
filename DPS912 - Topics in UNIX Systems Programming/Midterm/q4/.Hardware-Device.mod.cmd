savedcmd_Hardware-Device.mod := printf '%s\n'   dps912_Midt_mansoor.o | awk '!x[$$0]++ { print("./"$$0) }' > Hardware-Device.mod

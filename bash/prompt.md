printf "%`tput cols`s`tput cr`" "Hello"
printf "%`tput cols`s\r" "Hello"

#carriage return tput cr
#carriage return printf "\r"


#------------------------------
preprompt() {
  rc=$?
  c=31
  [ $rc -eq 0 ] && c=32

  PS1="\[$(color $c)\]$rc\[$(color 0)\] \t \w \$ "
  # right "prompt"
  # We cannot use $COLUMNS here, since in new shells the first prompt
  # will get garbled then. Seems like the correct value of COLUMNS is
  # in the shell init.
  printf "%`tput cols`s`tput cr`" "${USER}@${HOST}"
}

PROMPT_COMMAND=preprompt
#------------------------------

echo $?	// แสดง EXIT STATUS ของคำสั่งล่าสุด ถ้าเป็น 0 แสดงว่าสำเร็จ ถ้าไม่ใช่ 0 แปลว่าคำสั่งล่าสุด failed
เช่น
# date
Tue, Dec  6, 2022  4:36:43 PM
# echo $?
0
# sehsicheks -xyzkd
-bash: sehsicheks: command not found
# echo $?
127
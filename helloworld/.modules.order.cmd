cmd_/home/xiangyi/code/driver/helloworld/modules.order := {   echo /home/xiangyi/code/driver/helloworld/hello.ko; :; } | awk '!x[$$0]++' - > /home/xiangyi/code/driver/helloworld/modules.order

cmd_/home/xiangyi/code/driver/helloworld/Module.symvers := sed 's/\.ko$$/\.o/' /home/xiangyi/code/driver/helloworld/modules.order | scripts/mod/modpost  -a  -o /home/xiangyi/code/driver/helloworld/Module.symvers -e -i Module.symvers  -N -T -
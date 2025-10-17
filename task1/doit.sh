#!/bin/sh

# cleanup
rm -rf obj_dir
rm -f counter.vcd

# run verilator to translate verilog into c++ with testbench
verilator -Wall --cc --trace counter.sv --exe counter_tb.cpp

# build c++ project via make
make -j -C obj_dir/ -f Vcounter.mk Vcounter

# run generated executable
obj_dir/Vcounter
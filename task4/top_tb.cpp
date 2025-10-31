#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

inline int allHex(int val) {
}

int main(int argc, char** argv, char** env) {
    int i, clk;

    Verilated::commandArgs(argc, argv);
    Vtop* top = new Vtop;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("top.vcd");

    if (vbdOpen() != 1) return -1;
    vbdHeader("Lab 1: BCD");
    vbdSetMode(1);

    top->clk = 1;
    top->rst = 1;

    for (i = 0; i < 300; i++) {
        for (clk = 0; clk < 2; clk++) {
            tfp->dump(2 * i + clk);
            top->clk = !top->clk;
            top->eval();
        }
        
        vbdHex(4, top->bcd >> 16 & 0xf);
        vbdHex(3, top->bcd >> 8 & 0xf);
        vbdHex(2, top->bcd >> 4 & 0xf);
        vbdHex(1, top->bcd & 0xf);

        top->rst = 0;
        top->en = 1;

        while (vbdFlag() == 0) { }

        if (Verilated::gotFinish()) exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}
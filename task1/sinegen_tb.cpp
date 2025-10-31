#include "Vsinegen.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char** argv, char** env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);

    Vsinegen* top = new Vsinegen;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("sinegen.vcd");

    if (vbdOpen() != 1) return -1;
    vbdHeader("Lab 2: sinegen");

    top->clk = 1;
    top->rst = 1;
    top->en = 1;
    top->incr = 1;

    for (i = 0; i < 1'000'000; i++) {
        for (clk = 0; clk < 2; clk++) {
            tfp->dump(2 * i + clk);
            top->clk = !top->clk;
            top->eval();
        }
        top->incr = vbdValue();
        top->rst = 0;

        vbdPlot(top->dout, 0, 255);

        if (Verilated::gotFinish() || vbdGetkey() == 'q') exit(0);
    }
    tfp->close();
    exit(0);
}
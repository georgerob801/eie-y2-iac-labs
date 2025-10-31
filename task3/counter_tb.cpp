#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char** argv, char** env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);

    Vcounter* top = new Vcounter;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");

    // vbuddy initialisation
    if (vbdOpen() != 1) return (-1);
    vbdHeader("Lab 1: Counter");
    vbdSetMode(1);

    top->clk = 1;
    top->rst = 1;
    top->v = 127;

    for (i = 0; i < 3000; i++) {
        for (clk = 0; clk < 2; clk++) {
            tfp->dump(2 * i + clk);
            top->clk = !top->clk;
            top->eval();
        }

        top->ld = 0;

        if (vbdFlag() == 1) {
            top->v = vbdValue();
            top->ld = 1;
        }

        // send count value to vbuddy
        // vbdHex(4, (int(top->count) >> 16) & 0xf);
        // vbdHex(3, (int(top->count) >> 8) & 0xf);
        // vbdHex(2, (int(top->count) >> 4) & 0xf);
        // vbdHex(1, int(top->count) & 0xf);
        vbdPlot(int(top->count), 0, 255);
        top->rst = 0;
        if (Verilated::gotFinish()) exit(0);
    }

    vbdClose();

    tfp->close();
    exit(0);
}
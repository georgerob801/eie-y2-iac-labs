#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vsigdelay.h"
#include "vbuddy.cpp"

#define MAX_SIM_CYC 1'000'000
#define ADDRESS_WIDTH 9
#define RAM_SIZE pow(2, ADDRESS_WIDTH)

int main (int argc, char** argv, char** env) {
    int simcyc, tick;

    Verilated::commandArgs(argc, argv);
    Vsigdelay* top = new Vsigdelay;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("sigdelay.vcd");

    if (vbdOpen() != 1) return -1;
    vbdHeader("Lab 2: Delay");

    top->clk = 1;
    top->rst = 0;
    top->wrEn = 1;

    vbdInitMicIn(RAM_SIZE);

    for (simcyc = 0; simcyc < MAX_SIM_CYC; simcyc++) {
        for (tick = 0; tick < 2; tick++) {
            tfp->dump(2 * simcyc + tick);
            top->clk = !top->clk;
            top->eval();
        }

        top->sample = vbdMicValue();
        top->offset = vbdValue();

        vbdPlot((top->sample / 2) + 127, 0, 255);
        vbdPlot((top->dout / 2), 0, 255);
        vbdCycle(vbdValue());

        if (Verilated::gotFinish() || vbdGetkey() == 'q') exit(0);
    }

    vbdClose();
    tfp->close();
    printf("Exiting...\n");
    exit(0);
}
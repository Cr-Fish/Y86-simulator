#include "Y86.h"
#include "tool.h"
using std::cout;    using std::endl;
using std::cin;     using std::vector;
using std::string;

int main()
{
    CPU cpu = CPU();
    cpu.read();
    cpu.prep();

    while (1)
    {
        cpu.cod = char2Int(cpu.MEM[cpu.PC * 2]);
        cpu.B1fn = char2Int(cpu.MEM[cpu.PC * 2 + 1]);
        int valP = fetch(cpu.cod);
        cpu.PCnxt = cpu.PC + valP;
        switch (cpu.cod)
        {
        case 0x0:
            cpu.halt();
            break;
        case 0x1:
            cpu.nop();
            break;
        case 0x2:
            cpu.cmovXX();
            break;
        case 0x3:
            cpu.irmovq();
            break;
        case 0x4:
            cpu.rmmovq();
            break;
        case 0x5:
            cpu.mrmovq();
            break;
        case 0x6:
            cpu.OPq();
            break;
        case 0x7:
            cpu.jXX();
            break;
        case 0x8:
            cpu.call();
            break;
        case 0x9:
            cpu.ret();
            break;
        case 0xA:
            cpu.pushq();
            break;
        case 0xB:
            cpu.popq();
            break;
        case 0xc:
            cpu.iaddq();
            break;
        default:
            cout << "***************no function*****************" << endl;
            break;
        }
        if (cpu.Stat == AOK)
            cpu.PC = cpu.PCnxt;
        cout << "- PC: " << cpu.PC << endl;
        cpu.printReg();
        cpu.printMem();
        cpu.printCC();
        if (cpu.Stat != AOK)
            break;
    }

    return 0;
}
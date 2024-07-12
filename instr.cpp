#include"Y86.h"
#include"tool.h"
using std::cout;    using std::endl;
using std::cin;     using std::vector;
using std::string;

CPU::CPU():PC(0), Stat(AOK), OF(0), SF(0), ZF(1){}
void CPU::prep()
{
    memset(MEM, '0', 10000 * sizeof(char));
    int i = 0;
    while (i < instr.size())
    {
        int pos = getPos(&instr[i][0]);
        for (int j = 7; j < instr[i].size(); j++)
        {
            *(MEM + pos * 2 + j - 7) = instr[i][j];
        }
        i++;
    }
}
void CPU::read()
{
    // instr valid: 28
    string temp;
    while (getline(cin, temp))
    {
        if (temp[0] != ' ')
        {
            instr.push_back(temp);
            for (int k = 7; k < 28; k++)
            {
                int i = instr.size() - 1;
                if (instr[i][k] == ' ')
                {
                    instr[i].erase(instr[i].begin() + k, instr[i].end());
                    break;
                }
            }
        }
    }
}
void CPU::printReg()
{
    cout << "  REG:" << endl;
    cout << "    rax: " << REG[0] << endl;
    cout << "    rcx: " << REG[1] << endl;
    cout << "    rdx: " << REG[2] << endl;
    cout << "    rbx: " << REG[3] << endl;
    cout << "    rsp: " << REG[4] << endl;
    cout << "    rbp: " << REG[5] << endl;
    cout << "    rsi: " << REG[6] << endl;
    cout << "    rdi: " << REG[7] << endl;
    cout << "    r8: " << REG[8] << endl;
    cout << "    r9: " << REG[9] << endl;
    cout << "    r10: " << REG[10] << endl;
    cout << "    r11: " << REG[11] << endl;
    cout << "    r12: " << REG[12] << endl;
    cout << "    r13: " << REG[13] << endl;
    cout << "    r14: " << REG[14] << endl;
}
void CPU::printMem()
{
    cout << "  MEM:" << endl;
    int i = 0;
    while (i < 150)
    {
        string tem;
        for (int j = 0; j < 16; j++)
        {
            tem.push_back(MEM[16 * i + j]);
        }
        long long int val = getVal(tem);
        if (val != 0)
        {
            cout << "    " << 8 * i << ": ";
            cout << val << endl;
        }
        i++;
    }
}
void CPU::printCC()
{
    cout << "  CC:" << endl;
    cout << "    ZF: " << ZF << endl;
    cout << "    SF: " << SF << endl;
    cout << "    OF: " << OF << endl;
    cout << "  STAT: " << Stat << endl;
}
void CPU::halt()
{
    Stat = HLT;
}
void CPU::nop()
{
}
void CPU::rrmovq()
{
    int rA = char2Int(MEM[PC * 2 + 2]);
    int rB = char2Int(MEM[PC * 2 + 3]);
    REG[rB] = REG[rA];
}
void CPU::irmovq()
{
    string value;
    for (int i = 4; i <= 19; i++)
    {
        value.push_back(MEM[PC * 2 + i]);
    }

    REG[char2Int(MEM[PC * 2 + 3])] = getVal(value);
}
void CPU::rmmovq()
{
    string value;
    for (int i = 4; i <= 19; i++)
    {
        value.push_back(MEM[PC * 2 + i]);
    }
    int rA = char2Int(MEM[PC * 2 + 2]);
    int rB = char2Int(MEM[PC * 2 + 3]);

    string haha = laVteg(REG[rA]);
    for (int i = 0; i < 16; ++i)
        MEM[(REG[rB] + getVal(value)) * 2 + i] = haha[i];
}
void CPU::mrmovq()
{
    string value;
    for (int i = 4; i <= 19; i++)
    {
        value.push_back(MEM[PC * 2 + i]);
    }
    int rA = char2Int(MEM[PC * 2 + 2]);
    int rB = char2Int(MEM[PC * 2 + 3]);

    string horn;
    for (int i = 0; i < 16; ++i)
    {
        horn.push_back(MEM[(REG[rB] + getVal(value)) * 2 + i]);
    }
    REG[rA] = getVal(horn);
}
void CPU::OPq()
{
    int b;
    int rA = char2Int(MEM[PC * 2 + 2]);
    int rB = char2Int(MEM[PC * 2 + 3]);
    switch (B1fn)
    {
    case 0:
        b = REG[rB];
        REG[rB] += REG[rA];
        if (REG[rB] == 0)
            ZF = 1;
        else
            ZF = 0;
        if (REG[rB] < 0)
            SF = 1;
        else
            SF = 0;
        if ((REG[rA] < 0 == b < 0) && (REG[rB] < 0 != REG[rA] < 0))
            OF = 1;
        else
            OF = 0;
        break;
        // addq
    case 1:
        b = REG[rB];
        REG[rB] -= REG[rA];
        if (REG[rB] == 0)
            ZF = 1;
        else
            ZF = 0;
        if (REG[rB] < 0)
            SF = 1;
        else
            SF = 0;
        if ((REG[rA] > 0 && b < 0 && REG[rB] > 0) || (REG[rA] < 0 && b > 0 && REG[rB] < 0))
            OF = 1;
        else
            OF = 0;
        break;
        // subq
    case 2:
        b = REG[rB];
        REG[rB] = REG[rA] & REG[rB];
        if (REG[rB] == 0)
            ZF = 1;
        else
            ZF = 0;
        if (REG[rB] < 0)
            SF = 1;
        else
            SF = 0;
        break;
        //  andq
    case 3:
        b = REG[rB];
        REG[rB] = REG[rA] ^ REG[rB];
        if (REG[rB] == 0)
            ZF = 1;
        else
            ZF = 0;
        if (REG[rB] < 0)
            SF = 1;
        else
            SF = 0;
        break;
        // xorq
    }
}
void CPU::jXX()
{
    string value;
    for (int i = 2; i <= 17; i++)
    {
        value.push_back(MEM[PC * 2 + i]);
    }
    int Dest = getVal(value);
    switch (B1fn)
    {
    case 0:
        PCnxt = Dest;
        break;
    // jmp
    case 1:
        if ((SF ^ OF) | ZF)
            PCnxt = Dest;
        break;
    // jle
    case 2:
        if (SF ^ OF)
            PCnxt = Dest;
        break;
    // jl
    case 3:
        if (ZF)
            PCnxt = Dest;
        break;
    // je
    case 4:
        if (!ZF)
            PCnxt = Dest;
        break;
    // jne
    case 5:
        if (!(SF ^ OF))
            PCnxt = Dest;
        break;
    // jge
    case 6:
        if ((!(SF ^ OF)) & (!ZF))
            PCnxt = Dest;
        break;
        // jg default:
    }
}
void CPU::cmovXX()
{
    switch (B1fn)
    {
    case 0:
        rrmovq();
        break;
    case 1:
        if ((SF ^ OF) | ZF)
            rrmovq();
        break;
    case 2:
        if (SF ^ OF)
            rrmovq();
        break;
    case 3:
        if (ZF)
            rrmovq();
        break;
    case 4:
        if (!ZF)
            rrmovq();
        break;
    case 5:
        if (!(SF ^ OF))
            rrmovq();
        break;
    case 6:
        if ((!(SF ^ OF)) & (!ZF))
            rrmovq();
        break;
    }
}
void CPU::call()
{
    string value;
    for (int i = 2; i <= 17; i++)
    {
        value.push_back(MEM[PC * 2 + i]);
    }
    PCcall = getVal(value);
    int valE = REG[4] - 8;
    REG[4] = valE;
    string eulav = laVteg(PCnxt);
    for (int i = 0; i < 16; ++i)
    {
        MEM[valE * 2 + i] = eulav[i];
    }
    PCnxt = PCcall;
}
void CPU::ret()
{
    int valA = REG[4];
    string value;
    for (int i = 0; i <= 15; i++)
    {
        value.push_back(MEM[valA * 2 + i]);
    }
    REG[4] += 8;
    PCnxt = getVal(value);
}
void CPU::pushq()
{
    int rA = char2Int(MEM[PC * 2 + 2]);
    string haha = laVteg((REG[rA]));
    REG[4] -= 8;
    if (REG[4] < 0)
    {
        Stat = ADR;
        return;
    }
    for (int i = 0; i < 16; i++)
    {
        MEM[REG[4] * 2 + i] = haha[i];
    }
}
void CPU::popq()
{
    int rA = char2Int(MEM[PC * 2 + 2]);
    string haha;
    for (int i = 0; i < 16; i++)
    {
        haha.push_back(MEM[REG[4] * 2 + i]);
    }
    REG[4] += 8;
    REG[rA] = getVal(haha);
}
void CPU::iaddq()
{
    string value;
    for (int i = 4; i <= 19; i++)
    {
        value.push_back(MEM[PC * 2 + i]);
    }
    int rB = char2Int(MEM[PC * 2 + 3]);
    int b = REG[rB];
    int val = getVal(value);
    REG[rB] += val;
    if (REG[rB] == 0)
        ZF = 1;
    else
        ZF = 0;
    if (REG[rB] < 0)
        SF = 1;
    if ((val < 0 == b < 0) && (REG[rB] < 0 != val < 0))
        OF = 1;
}
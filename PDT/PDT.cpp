/**********************************************************************************
* PDT.cpp (Codigo Fonte)
* Autor: Thiago Silva
* Criacao:            26 Julho 2024
* Ultima Modificacao: 26 julho 2024
* Compilador:         Microsoft Visual C++ 2022
* Descricao: Implementacao da classe PDT, esta classe foi criada para fazer uma analise DC de um circuito de polarizacao por divisor de tensao.
**********************************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include "PDT.h"
using namespace std;

// POLARIZACAO POR DIVISOR DE TENSAO
PDT::PDT(double r1, double r2, double rc, double re, double vcc, double beta)
    : R1(r1), R2(r2), RC(rc), RE(re), VCC(vcc), BETA(beta)
{
    VBE = 0.7;
    MethodDefiner();
}

// Comeca a Analise
void PDT::Start()
{
    system("cls");
    
    // Cabecalho
    string decorator = "-----------------------------------------------------";
    cout << decorator << endl;
    cout << "\033[1;31m   Analise DC | Polarizacao por Divisor de Tensao\033[0m" << endl;
    cout << decorator << endl;
    cout << " M: 10e6 | k: 10e3 | m: 10e-3 | u: 10e-6 | n: 10e-9" << endl;
    cout << decorator << endl << endl;
    
    // Chama o metodo
    if (method == "exact")
    {
        cout << "\033[1;32mMetodo Exato\033[0m" << endl;
        ExactMethod();
    }
    else
    {
        cout << "\033[1;32mMetodo Simplificado\033[0m" << endl;
        SimplifiedMethod();
    }
}

// Define qual metodo usar com base em R1 || R1 <= 10% * BETA * RE
void PDT::MethodDefiner()
{
    RTH = (R1 * R2) / (R1 + R2);
    if (RTH <= (0.1 * BETA * RE))
    {
        method = "simplified";
    }
    else
    {
        method = "exact";
    }
}

void PDT::ExactMethod()
{
    // Tensao na Base
    VBB = (R2 / (R1 + R2)) * VCC;
    // Corrente na Base
    IB = (VBB - VBE) / (RTH + RE * (BETA + 1));
    // Corrente no Coletor
    IC = BETA * IB;
    // Tensao no Coletor
    VC = VCC - (RC * IC);
    // Corrente no Emissor
    IE = IC;
    // Tensao no Emissor
    VE = RE * IE;
    // Tensao Coletor Emissor
    VCE = VC - VE;
    
    Show();
}

// Metodo Simplificado
void PDT::SimplifiedMethod()
{
    // Tensao da base
    VBB = (R2 / (R1 + R2)) * VCC;
    // Tensao no Emissor
    VE = VBB - VBE;
    // Corrente no Emissor
    IE = VE / RE;
    // Corrente no Coletor
    IC = IE;
    // Corrente na Base
    IB = IC / BETA;
    // Tensao no Coletor
    VC = VCC - (RC * IC);
    // Tensao Coletor - Emissor
    VCE = VC - VE;
    
    Show();
}

// Regulariza os dados e retorna uma string com o multiplo embutido
string PDT::Regulate(double n)
{
    stringstream text;
    text << setprecision(2) << fixed;

    // Mega
    if (n >= 1000000)
    {
        text << n / 1000000 << " M";
    }
    // Kilo
    else if (n >= 1000)
    {
        text << n / 1000 << " k";
    }
    // Normal
    else if (n >= 1)
    {
        text << n << " ";
    }
    // Mili
    else if (n >= 0.001)
    {
        text << n / 0.001 << " m";
    }
    // Micro
    else if (n >= 0.000001)
    {
        text << n / 0.000001 << " u";
    }
    // Nano
    else if (n >= 0.000000001)
    {
        text << n / 0.000000001 << " n";
    }
    
    // Valor com seu multiplo
    return text.str();
}

// Mostra os Valores com seus multiplos e unidades
void PDT::Show()
{
    // Tensoes
    cout << "\nTensoes" << endl;
    cout << "VBB: " << Regulate(VBB) << "V" << endl;
    cout << "VCC: " << Regulate(VCC) << "V" << endl;
    cout << "VBE: " << Regulate(VBE) << "V" << endl;
    cout << "\033[1;32mVCE: " << Regulate(VCE) << "V\033[0m" << endl;
    cout << "VC: " << Regulate(VC) << "V" << endl;
    cout << "VE: " << Regulate(VE) << "V" << endl;

    // Correntes
    cout << "\nCorrentes" << endl;
    cout << "IE: " << Regulate(IE) << "A" << endl;
    cout << "\033[1;32mIC: " << Regulate(IC) << "A\033[0m" << endl;
    cout << "IB: " << Regulate(IB) << "A" << endl;

    // Resistencias
    cout << "\nResistencias" << endl;
    cout << "R1: " << Regulate(R1) << "\xE2\x84\xA6" << endl;
    cout << "R2: " << Regulate(R2) << "\xE2\x84\xA6" << endl;
    cout << "RC: " << Regulate(RC) << "\xE2\x84\xA6" << endl;
    cout << "RE: " << Regulate(RE) << "\xE2\x84\xA6" << endl;
    cout << "RTH: " << Regulate(RTH) << "\xE2\x84\xA6" << endl;
}

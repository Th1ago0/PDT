/**********************************************************************************
* main.cpp (Codigo Fonte)
* Autor: Thiago Silva
* Criacao:            26 Julho 2024
* Ultima Modificacao: 26 julho 2024
* Compilador:         Microsoft Visual C++ 2022
* Descricao: Implementacao da funcao quantify para quantificar os dados, e a Implementacao da funcao principal. 
**********************************************************************************/

#include <iostream>
#include <string>
#include <algorithm>
#include <Windows.h>
#include "PDT.h"
using namespace std;

double quantify();

int main(int argc, char *argv[])
{
    // Dizendo ao console para usar UTF-8
    SetConsoleOutputCP(CP_UTF8);

    while (true)
    {
        system("cls");

        string decorator = "-----------------------------------------------------";
        cout << decorator << endl;
        cout << "   Analise DC | Polarizacao por Divisor de Tensao" << endl;
        cout << decorator << endl;
        cout << " M: 10e6 | k: 10e3 | m: 10e-3 | u: 10e-6 | n: 10e-9" << endl;
        cout << decorator << endl << endl;

        // Recebe os valores e quantifica
        double R1, R2, RC, RE, VCC, BETA;
        cout << "R1 (\xE2\x84\xA6): ";
        R1 = quantify();

        cout << "R2 (\xE2\x84\xA6): ";
        R2 = quantify();

        cout << "RC (\xE2\x84\xA6): ";
        RC = quantify();

        cout << "RE (\xE2\x84\xA6): ";
        RE = quantify();

        cout << "BETA: ";
        BETA = quantify();

        cout << "VCC (V): ";
        VCC = quantify();

        PDT pdt(R1, R2, RC, RE, VCC, BETA);
        pdt.Start();

        system("pause");
    }
    
    return 0;
}

// Recebe um valor com seu multiplo (M, k, m, u, n) usando cin, quantifica ele e retorna o resultado
double quantify()
{
    string args;
    double multiplier = 1.0;
    cin >> args;

    if (args.find("k") != string::npos)
    {
        replace(args.begin(), args.end(), 'k', ' ');
        multiplier = 1e3;
    }
    else if (args.find("m") != string::npos)
    {
        replace(args.begin(), args.end(), 'm', ' ');
        multiplier = 1e-3;
    }
    else if (args.find("u") != string::npos)
    {
        replace(args.begin(), args.end(), 'u', ' ');
        multiplier = 1e-6;
    }
    else if (args.find("n") != string::npos)
    {
        replace(args.begin(), args.end(), 'n', ' ');
        multiplier = 1e-9;
    }
    else if (args.find("M") != string::npos)
    {
        replace(args.begin(), args.end(), 'M', ' ');
        multiplier = 1e6;
    }

    double value = stod(args);
    return value * multiplier;
}

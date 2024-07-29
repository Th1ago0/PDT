/**********************************************************************************
* PDT.h (Cabecalho)
* Autor: Thiago Silva
* Criacao:            26 Julho 2024
* Ultima Modificacao: 26 julho 2024
* Compilador:         Microsoft Visual C++ 2022
* Descricao: Definicao da classe PDT que representa os valores de um circuito amplificador com transistor.
**********************************************************************************/

#include <string>

// POLARIZACAO POR DIVISOR DE TENSAO
class PDT
{
private:
    std::string method;
    double R1, R2, RC, RE, VCC, BETA;
    double VBB, VBE, VCE, VC, VE, IC, IB, IE, RTH;
    
    void ExactMethod();
    void SimplifiedMethod();
    void MethodDefiner();
    std::string Regulate(double n);

public:
    PDT(double r1, double r2, double rc, double re, double vcc, double beta);
    void Start();
    void Show();
};
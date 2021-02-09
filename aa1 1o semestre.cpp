#include <iostream>
#include <iomanip>
#include <locale.h> // Biblioteca que ativa acentos em português
using namespace std;

int main() {
    int no_voluntarios, no_protegidos;
    float eficacia, razao_efeitos;
    string decisao;
    bool x = true;
    
    setlocale(LC_ALL, "Portuguese"); // Comando que ativa acentos em português
    
    /* Enquanto o 'x' for verdadeiro, o programa
    continuará fazendo testes, até que a vacina
    seja aprovada */
    while(x) {
        cin >> no_voluntarios;
        cin >> no_protegidos;
        cout << "Houve algum efeito colateral incomum? (S/N) ";
        cin >> decisao;
        eficacia = ((float) no_protegidos / (float) no_voluntarios) * 100;
        cout << fixed << setprecision(2) << endl;
    
        // Há contagem de casos com efeito colateral
        if(decisao == "S") {
            int efeitos_colaterais[5], qtd_efeitos = 0;
            for(int i = 0; i < 5; i++) {
                cin >> efeitos_colaterais[i];
                qtd_efeitos += efeitos_colaterais[i];
            }
            razao_efeitos = (float) qtd_efeitos / (float) no_voluntarios;
            if(razao_efeitos >= 0.5) {
                cout << "Vacina foi reprovada por ter muitos efeitos colaterais." << endl;
                cout << "Eficácia: " << eficacia << " %" << endl;
                cout << "Casos de efeito colateral: " << qtd_efeitos << endl << endl;
            } else {
                if(eficacia >= 70) {
                    cout << "Vacina foi aprovada!" << endl;
                    cout << "Eficácia: " << eficacia << " %" << endl;
                    cout << "Casos de efeito colateral: " << qtd_efeitos << endl;
                    x = false;
                } else {
                    cout << "Vacina foi reprovada por não imunizar o suficiente." << endl;
                    cout << "Eficácia: " << eficacia << " %" << endl;
                    cout << "Casos de efeito colateral: " << qtd_efeitos << endl << endl;
                    no_voluntarios = no_protegidos = eficacia = 0;
                }
            }
        } else { // Não há contagem de casos com efeito colateral
            if(eficacia >= 70) {
                cout << "Vacina foi aprovada!" << endl;
                cout << "Eficácia: " << eficacia << " %" << endl;
                x = false;
            } else {
                cout << "Vacina foi reprovada por não imunizar o suficiente." << endl;
                cout << "Eficácia: " << eficacia << " %" << endl << endl;
                no_voluntarios = no_protegidos = eficacia = 0;
            }
        }
    }
    
    return 0;
}

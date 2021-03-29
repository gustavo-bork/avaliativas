#include <bits/stdc++.h>
#include <fstream>
using namespace std;
using std::ios;
struct Data {
	int dia;
	int mes;
	int ano;
};
struct BancoDados {
	int id;
	char tipo;
	char nome[40] = "";
	Data data;
	float saldo;
};
enum Escolhas : int {IMPRIMIRCONTAS = 1, NOVACONTA};
void ExportarDados(BancoDados cadastro, fstream& incluirContas) {
	cout << "ID da conta: "; cin >> cadastro.id;
	cout << "Tipo de conta: "; cin >> cadastro.tipo;
	cout << "Nome do titular: "; cin >> cadastro.nome;
	cout << "Data do cadastro: "; cin >> cadastro.data.dia >> cadastro.data.mes >> cadastro.data.ano;
	cout << "Saldo da conta: "; cin >> cadastro.saldo;
	incluirContas << cadastro.id << ", "
		<< cadastro.tipo << ", "
		<< cadastro.nome << ", "
		<< cadastro.data.dia << "/ "
		<< cadastro.data.mes << "/"
		<< cadastro.data.ano << ", "
		<< cadastro.saldo;
}
BancoDados IncluirContas(vector<BancoDados>& bancoDados, vector<string>& dados, fstream& arquivo, BancoDados cadastro) {
	string dado;
	while(getline(arquivo, dado)) {
		stringstream ss(dado);
		while(getline(ss, dado, ',')) {
			dados.push_back(dado);
		}
	}
	string::size_type sz;
	int j = 0; bool passou1vez = true;
	for(int i = 0; i < dados.size() / 5; i++) {
		for(j; j < dados.size(); j++) {
			if(j % 5 == 0 && j > 0 && passou1vez) {
				passou1vez = false;
				break;
			} else {
				passou1vez = true;
			}
			if(j % 5 == 0) {
				cadastro.id = stoi(dados[j], &sz);
			} else if(j % 5 == 1) {
				dados[j].copy(&cadastro.tipo, dados[j].length(), 0);
			} else if(j % 5 == 2) {
				dados[j].copy(cadastro.nome, dados[j].length(), 0);
			} else if(j % 5 == 3) {
				int barra1 = dados[j].find_first_of("/", 0);
				cadastro.data.dia = stoi(dados[j].substr(0, barra1), &sz);
				int barra2 = dados[j].find_last_of("/", dados[j].length());
				cadastro.data.mes = stoi(dados[j].substr(barra1 + 1, barra1), &sz);
				cadastro.data.ano = stoi(dados[j].substr(barra2 + 1), &sz);
			} else if(j % 5 == 4) {
				cadastro.saldo = stof(dados[j], &sz);
			}
		}
		bancoDados.push_back(cadastro);
		memset(&cadastro.nome, 0, 40);
	}
	for(int i = 0; i < bancoDados.size(); i++) return bancoDados[i];
}
void ListarContas(BancoDados bancoDados) {
	cout << setprecision(2) << fixed;
	cout << bancoDados.id << " "
		<< bancoDados.tipo << " "
		<< bancoDados.nome << " " 
		<< bancoDados.data.dia << "/" 
		<< bancoDados.data.mes << "/"  
		<< bancoDados.data.ano << " "
		<< bancoDados.saldo << endl;
}
int main() {
	fstream arquivo, incluirContas;
	arquivo.open("bancodados.csv", ios::in | ios::out | ios::app);
	incluirContas.open("contasIncluir.csv", ios::out | ios::app);
	BancoDados cadastro; 
	int escolha;
	vector<BancoDados> bancoDados; vector<string> dados;
	
	IncluirContas(bancoDados, dados, arquivo, cadastro);

	cout << "Menu\n"
		<< "1 - Listar as contas\n"
		<< "2 - Fazer uma nova conta\n" 
		<< "Opcao: "; cin >> escolha;
	switch(escolha) {
	case IMPRIMIRCONTAS: 
		cout << "ID Conta" << setw(10) 
			<< "Tipo" << setw(20) 
			<< "Titular da conta" << setw(30) 
			<< "Data de abertura" << setw(10) 
			<< "Saldo\n";
		for(int i = 0; i < bancoDados.size(); i++) {
			ListarContas(bancoDados[i]);
		}
		break;
	case NOVACONTA:
		ExportarDados(cadastro, incluirContas);
		break;
	}
	
	

	arquivo.close();
	return 0;
}

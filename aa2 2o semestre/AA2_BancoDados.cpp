#include <bits/stdc++.h>
#include <fstream>
#include <time.h>
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

time_t ttime = time(0);
struct tm tempoAgr;
string::size_type sz;
enum Escolhas : int {IMPRIMIRCONTAS = 1, NOVACONTA};
void ExportarDados(BancoDados cadastro, fstream& incluirContas, vector<BancoDados> bancoDados) {
	string nome_temp;
	localtime_s(&tempoAgr, &ttime);
	cadastro.data.dia = tempoAgr.tm_mday;
	cadastro.data.mes = tempoAgr.tm_mon + 1;
	cadastro.data.ano = tempoAgr.tm_year + 1900;
	cadastro.id = bancoDados.at(bancoDados.size() - 1).id + 1;
	cout << "Tipo de conta: "; cin >> cadastro.tipo;
	cout << "Nome do titular: "; cin.get(); getline(cin, nome_temp);
	cout << "Saldo da conta: "; cin >> cadastro.saldo;
	strcpy_s(cadastro.nome, nome_temp.c_str());
	cout << setprecision(2) << fixed;
	incluirContas << cadastro.id << ","
		<< cadastro.tipo << ","
		<< cadastro.nome << ","
		<< cadastro.data.dia << "/"
		<< cadastro.data.mes << "/"
		<< cadastro.data.ano << ","
		<< cadastro.saldo << "\n";
}
void TaxaContaCorrente(vector<BancoDados> &bancoDados, fstream& taxaCorrente) {
	string dadoArquivo; vector<string> dadosArquivo;
	vector<float> taxas;
	while(getline(taxaCorrente, dadoArquivo)) {
		stringstream ss(dadoArquivo);
		while(getline(ss, dadoArquivo, ' ')) {
			taxas.push_back(stof(dadoArquivo));
		}
	}
	for(int i = 0; i < bancoDados.size(); i++) {
		bool msmDia = !((bancoDados[i].data.mes == tempoAgr.tm_mon + 1) && (bancoDados[i].data.ano == tempoAgr.tm_year + 1900));
		if(bancoDados.at(i).tipo == 'C') {
			if(bancoDados.at(i).data.dia == tempoAgr.tm_mday && msmDia) {
				if(bancoDados.at(i).saldo <= 1500) {
					bancoDados.at(i).saldo -= taxas.at(0) * bancoDados.at(i).saldo;
				} else if(bancoDados.at(i).saldo > 1500 && bancoDados.at(i).saldo <= 3000) {
					bancoDados.at(i).saldo -= taxas.at(1) * bancoDados.at(i).saldo;
				} else if(bancoDados.at(i).saldo > 3000 && bancoDados.at(i).saldo <= 4500) {
					bancoDados.at(i).saldo -= taxas.at(2) * bancoDados.at(i).saldo;
				} else if(bancoDados.at(i).saldo > 4500 && bancoDados.at(i).saldo <= 6000) {
					bancoDados.at(i).saldo -= taxas.at(3) * bancoDados.at(i).saldo;
				} else {
					bancoDados.at(i).saldo -= taxas.at(4) * bancoDados.at(i).saldo;
				}
				msmDia = true;
			}
		}
	}
}
void AtualizarSaldoPoupanca(vector<BancoDados> &bancoDados, fstream& taxaPoupanca) {
	string taxa;
	taxaPoupanca >> taxa;
	localtime_s(&tempoAgr, &ttime);
	float taxaNum = stof(taxa) / 100;
	for(int i = 0; i < bancoDados.size(); i++) {
		bool msmDia = !((bancoDados[i].data.mes == tempoAgr.tm_mon + 1) && (bancoDados[i].data.ano == tempoAgr.tm_year + 1900));
		if(bancoDados.at(i).tipo == 'P') {
			if(bancoDados.at(i).data.dia == tempoAgr.tm_mday && msmDia) {
				bancoDados.at(i).saldo *= (1 + taxaNum);
				msmDia = true;
			}
		}
	}
}
BancoDados IncluirContas(vector<BancoDados>& bancoDados, vector<string>& dados, fstream& arquivo, BancoDados cadastro) {
	string dado;
	while(getline(arquivo, dado)) {
		stringstream ss(dado);
		while(getline(ss, dado, ',')) {
			dados.push_back(dado);
		}
	}

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
				cadastro.id = stoi(dados[j]);
			} else if(j % 5 == 1) {
				dados[j].copy(&cadastro.tipo, dados[j].length(), 0);
			} else if(j % 5 == 2) {
				dados[j].copy(cadastro.nome, dados[j].length(), 0);
			} else if(j % 5 == 3) {
				int barra1 = dados[j].find_first_of("/", 0);
				cadastro.data.dia = stoi(dados[j].substr(0, barra1));
				int barra2 = dados[j].find_last_of("/", dados[j].length());
				cadastro.data.mes = stoi(dados[j].substr(barra1 + 1, barra1));
				cadastro.data.ano = stoi(dados[j].substr(barra2 + 1));
			} else if(j % 5 == 4) {
				cadastro.saldo = stof(dados[j], &sz);
			}
		}
		bancoDados.push_back(cadastro);
		fill(begin(cadastro.nome), end(cadastro.nome), 0);
	}
	for(int i = 0; i < bancoDados.size(); i++) return bancoDados[i];
}
void ListarContas(vector<BancoDados> bancoDados) {
	cout << "ID Conta" << setw(10)
		<< "Tipo" << setw(20)
		<< "Titular da conta" << setw(30)
		<< "Data de abertura" << setw(10)
		<< "Saldo\n";
	cout << setprecision(2) << fixed;
	for(int i = 0; i < bancoDados.size(); i++) {
		cout << bancoDados.at(i).id << setw(11)
			<< bancoDados.at(i).tipo << setw(24)
			<< bancoDados.at(i).nome << setw(14)
			<< bancoDados.at(i).data.dia << "/"
			<< bancoDados.at(i).data.mes << "/"
			<< bancoDados.at(i).data.ano << setw(18)
			<< bancoDados.at(i).saldo << "\n";
	}
}
int main() {
	fstream arquivo, incluirContas, taxaPoupanca, taxaContaCorrente;
	arquivo.open("bancodados.csv", ios::in | ios::out | ios::app);
	incluirContas.open("contasIncluir.csv", ios::out | ios::app);
	taxaPoupanca.open("saldoatualizar.txt", ios::in);
	taxaContaCorrente.open("tarifas.txt", ios::in);
	BancoDados cadastro;
	int escolha;
	vector<BancoDados> bancoDados; vector<string> dados;
	
	IncluirContas(bancoDados, dados, arquivo, cadastro);
	AtualizarSaldoPoupanca(bancoDados, taxaPoupanca);
	TaxaContaCorrente(bancoDados, taxaContaCorrente);
	cout << "Menu\n"
		<< "1 - Listar as contas\n"
		<< "2 - Fazer uma nova conta\n" 
		<< "Opcao: "; cin >> escolha;
	switch(escolha) {
	case IMPRIMIRCONTAS: 
		ListarContas(bancoDados);
		break;
	case NOVACONTA:
		ExportarDados(cadastro, incluirContas, bancoDados);
		break;
	}

	arquivo.close();
	return 0;
}

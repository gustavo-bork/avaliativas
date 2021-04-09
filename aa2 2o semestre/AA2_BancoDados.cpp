#include <bits/stdc++.h>
#include <windows.h>
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
fstream arquivo;

enum Escolhas : int {IMPRIMIRCONTAS = 1, NOVACONTA, SAIR};
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
	incluirContas << cadastro.id << " "
		<< cadastro.tipo << " "
		<< cadastro.nome << " "
		<< cadastro.data.dia << "/"
		<< cadastro.data.mes << "/"
		<< cadastro.data.ano << " "
		<< cadastro.saldo << "\n";
	cout << "Conta exportada com sucesso!" << endl;
	incluirContas.close();
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
			auto saldoAntigo = bancoDados.at(i).saldo;
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
	arquivo.open("bancodados.csv", ios::out | ios::in | ios::app);
	for(int i = 0; i < bancoDados.size(); i++) {
		arquivo << bancoDados[i].id << ","
			<< bancoDados[i].tipo << ","
			<< bancoDados[i].nome << ","
			<< bancoDados[i].data.dia << "/"
			<< bancoDados[i].data.mes << "/"
			<< bancoDados[i].data.ano << ","
			<< bancoDados[i].saldo << "\n";
	}
	arquivo.close();
	taxaCorrente.close();
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
	taxaPoupanca.close();
}
BancoDados IncluirContas(vector<BancoDados>& bancoDados, vector<string>& dados, BancoDados cadastro) {
	arquivo.open("bancodados.csv", ios::in);
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
	arquivo.close();
}
void ListarContas(vector<BancoDados> bancoDados) {
	cout << "ID Conta" << setw(10)
		<< "Tipo" << setw(20)
		<< "Titular da conta" << setw(30)
		<< "Data de abertura" << setw(10)
		<< "Saldo\n";
	cout << setprecision(2) << fixed;
	for(int i = 0; i < bancoDados.size(); i++) {
		cout << left << setw(14) <<
			bancoDados[i].id << left << setw(8)
			<< bancoDados[i].tipo << left << setw(30)
			<< bancoDados[i].nome 
			<< bancoDados[i].data.dia << "/"
			<< bancoDados[i].data.mes << "/" << left << setw(16)
			<< bancoDados[i].data.ano 
			<< bancoDados[i].saldo << "\n";
	}
	cout << "\n\n";
}
int main() {
	fstream incluirContas, taxaPoupanca, taxaContaCorrente;
	incluirContas.open("contasIncluir.dat", ios::out | ios::app);
	taxaPoupanca.open("saldoatualizar.txt", ios::in);
	taxaContaCorrente.open("tarifas.txt", ios::in);
	BancoDados cadastro;
	int escolha;
	vector<BancoDados> bancoDados; vector<string> dados;
	bool x = true;
	IncluirContas(bancoDados, dados, cadastro);
	AtualizarSaldoPoupanca(bancoDados, taxaPoupanca);
	TaxaContaCorrente(bancoDados, taxaContaCorrente);
	while(x) {
		cout << "Menu\n"
			<< "1 - Listar as contas\n"
			<< "2 - Fazer uma nova conta\n" 
			<< "3 - Sair\n"
			<< "Opcao: "; cin >> escolha; cout << "\n";
		switch(escolha) {
		case IMPRIMIRCONTAS:
			ListarContas(bancoDados);
			break;
		case NOVACONTA:
			ExportarDados(cadastro, incluirContas, bancoDados);
			Sleep(1000);
			system("cls");
			break;
		case SAIR:
			x = false;
			break;
		default:
			cout << "Erro: Opcao invalida\n" << endl;
			Sleep(2000);
			system("cls");
			break;
		}
		
	}
	
	arquivo.close();
	return 0;
}

#include <bits/stdc++.h>
#include <windows.h>
#define I 8
#define J 20
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int num_trilha, num_dado;
int casa_magia[I/4][J/5] = {0}, pontos[I/4][J/5] = {0};
char trilha[I][J+6] = {'O'};
bool x = true;

int dado() {
	srand(time(NULL));
	int sorteio = rand() % 6 + 1;
	cout << "Dado: ";
	return sorteio;
}
void CasasMagicas (char trilha[I][J+6], int pontos[I/4][J/5], int casa_magia[I/4][J/5], int &no_trilha, string jogador_um, string jogador_dois) {
	for(int j = 0; j < J/5; j++) {
		if(j % 2 == 0) {
			if(pontos[0][j] == casa_magia[0][j]) {
				SetConsoleTextAttribute(hConsole, 11);
				cout << jogador_um; 
				SetConsoleTextAttribute(hConsole, 7);
				cout << " parou em uma casa abençoada!" << endl << "Avance 2 casas" << endl << endl;
				Sleep(2000);
				trilha[(no_trilha - 1) * 2][pontos[0][no_trilha - 1]] = 'O';
				pontos[0][no_trilha - 1] += 2;
				trilha[(no_trilha - 1) * 2][pontos[0][no_trilha - 1]] = 'X';
			}
		} else {
			if(pontos[0][j] == casa_magia[0][j]) {
				SetConsoleTextAttribute(hConsole, 11);
				cout << jogador_um; 
				SetConsoleTextAttribute(hConsole, 7);
				cout << " parou em uma casa amaldiçoada!" << endl << "Volte 3 casas" << endl << endl;
				Sleep(2000);
				trilha[(no_trilha - 1) * 2][pontos[0][no_trilha - 1]] = 'O';
				pontos[0][no_trilha - 1] -= 3;
				trilha[(no_trilha - 1) * 2][pontos[0][no_trilha - 1]] = 'X';	
			}
		}
	}
	for(int j = 0; j < J/5; j++) {
		if(j % 2 == 0) {
			if(pontos[1][j] == casa_magia[1][j]) {
				SetConsoleTextAttribute(hConsole, 12); 
				cout << jogador_dois; 
				SetConsoleTextAttribute(hConsole, 7);
				cout << " parou em uma casa abençoada!" << endl << "Avance 2 casas" << endl << endl;
				Sleep(2000);
				trilha[1 + ((no_trilha - 1) * 2)][pontos[1][no_trilha - 1]] = 'O';
				pontos[1][no_trilha - 1] += 2;
				trilha[1 + ((no_trilha - 1) * 2)][pontos[1][no_trilha - 1]] = 'X';
			}
		} else {
			if(pontos[1][j] == casa_magia[1][j]) {
				SetConsoleTextAttribute(hConsole, 12); 
				cout << jogador_dois; 
				SetConsoleTextAttribute(hConsole, 7);
				cout << " parou em uma casa amaldiçoada!" << endl << "Volte 3 casas" << endl << endl;
				Sleep(2000);
				trilha[1 + ((no_trilha - 1) * 2)][pontos[1][no_trilha - 1]] = 'O';
				pontos[1][no_trilha - 1] -= 3;
				trilha[1 + ((no_trilha - 1) * 2)][pontos[1][no_trilha - 1]] = 'X';	
			}
		}
	}
}
void FimPartida(char trilha[I][J+6], string jogador_um, string jogador_dois, int &dado) {
	if(trilha[0][J-1] == 'X' && trilha[2][J-1] == 'X' && trilha[4][J-1] == 'X' && trilha[6][J-1] == 'X')  {
		cout << "Fim da partida" << "\n" << "\n";
		SetConsoleTextAttribute(hConsole, 11);
		cout << jogador_um << " ";
		SetConsoleTextAttribute(hConsole, 7);
		cout << "ganhou!" << "\n" << "\n";
		Sleep(2000);
		x = false;
	} else {
		if(trilha[1][J-1] == 'X' && trilha[3][J-1] == 'X' && trilha[5][J-1] == 'X' && trilha[7][J-1] == 'X') {
			cout << "Fim da partida" << "\n";
			SetConsoleTextAttribute(hConsole, 12);
			cout << jogador_dois << " ";
			SetConsoleTextAttribute(hConsole, 7);
			cout << "ganhou!" << "\n" << "\n";
			Sleep(2000);
			x = false;
		}
	} 
}
void TrilhaCompleta1(char trilha[I][J+6], int pontos[I/4][J/5], int &no_trilha, int &dado, string jogador_um) {
	if(pontos[0][num_trilha - 1] >= J - 1) {
		SetConsoleTextAttribute(hConsole, 11);
		cout << jogador_um; 
		SetConsoleTextAttribute(hConsole, 7);
		cout << " completou uma trilha!" << endl << endl;
		Sleep(2000);
		trilha[(no_trilha - 1) * 2][pontos[0][no_trilha - 1] - dado] = 'O';
		trilha[(no_trilha - 1) * 2][J - 1] = 'X';
	} 
}
void TrilhaCompleta2(char trilha[I][J+6], int pontos[I/4][J/5], int &no_trilha, int &dado, string jogador_dois) {
	if(pontos[1][num_trilha - 1] >= J - 1) {
		SetConsoleTextAttribute(hConsole, 12); 
		cout << jogador_dois; 
		SetConsoleTextAttribute(hConsole, 7);
		cout << " completou uma trilha!" << endl << endl;
		Sleep(2000);
		trilha[1 + ((no_trilha - 1) * 2)][pontos[1][no_trilha - 1] - dado] = 'O';
		trilha[1 + ((no_trilha - 1) * 2)][J - 1] = 'X';
	}
}
void VoltaInicio1 (char trilha[I][J+6], int pontos[I/4][J/5], int &no_trilha) {
	trilha[1 + (no_trilha - 1) * 2][pontos[1][no_trilha - 1]] = 'O';
	pontos[1][no_trilha - 1] = 0;
	trilha[1 + (no_trilha - 1) * 2][pontos[1][no_trilha - 1]] = 'X';
}
void VoltaInicio2 (char trilha[I][J+6], int pontos[I/4][J/5], int &no_trilha) {
	trilha[(no_trilha - 1) * 2][pontos[no_trilha - 1][0]] = 'O';
	pontos[no_trilha - 1][0] = 0;
	trilha[(no_trilha - 1) * 2][pontos[no_trilha - 1][0]] = 'X';
}
void MoverPeaoJogador1 (char trilha[I][J+6], int pontos[I/4][J/5], int &no_trilha, int &dado) {
	trilha[(no_trilha - 1) * 2][pontos[0][no_trilha - 1]] = 'O';
	trilha[(no_trilha - 1) * 2][pontos[0][no_trilha - 1] + dado] = 'X';
	pontos[0][no_trilha - 1] += dado;
}
void MoverPeaoJogador2 (char trilha[I][J+6], int pontos[I/4][J/5], int &no_trilha, int &dado) {
	trilha[1 + ((no_trilha - 1) * 2)][pontos[1][no_trilha - 1]] = 'O';
	trilha[1 + ((no_trilha - 1) * 2)][pontos[1][no_trilha - 1] + dado] = 'X';
	pontos[1][no_trilha - 1] += dado;
}
void MostrarPontos(int pontos[I/4][J/5], string jogador1, string jogador2) {
	int tabelaPontos[J/5][I/4] = {0};
	for(int i = 0; i < J/5; i++) {
		for(int j = 0; j < I/4; j++) {
			tabelaPontos[i][j] = pontos[j][i];
		}
	}
	cout << "Pontuação " << " ";
	SetConsoleTextAttribute(hConsole, 11);
	cout << "\t" << jogador1 << "\t";
	SetConsoleTextAttribute(hConsole, 12);
	cout << jogador2 << "\n" << "\n";
	SetConsoleTextAttribute(hConsole, 7);
	for(int i = 0; i < J/5; i++) {
		cout << "Trilha " << i + 1 << ": " << "\t";
		for(int j = 0; j < I/4; j++) {
			if(j == 0) {
				SetConsoleTextAttribute(hConsole, 11);
				cout << tabelaPontos[i][j] + 1 << "\t";
				SetConsoleTextAttribute(hConsole, 7);
			} else {
				SetConsoleTextAttribute(hConsole, 12);
				cout << tabelaPontos[i][j] + 1 << "\n\n";
				SetConsoleTextAttribute(hConsole, 7);
			}
		}
	}
}
void MostrarTrilha(char trilha[I][J+6]) {
	for(int i = 0; i < I; i++) { 
			for(int j = 0; j < J; j++) { 
				if(i % 2 == 0) { 
					SetConsoleTextAttribute(hConsole, 11); 
					cout << trilha[i][j] << " "; 
					SetConsoleTextAttribute(hConsole, 7); 
				} else { 
					SetConsoleTextAttribute(hConsole, 12); 
					cout << trilha[i][j] << " "; 
					SetConsoleTextAttribute(hConsole, 7); 
				} 
			}	 
		if(i % 2 == 1) { 
			cout << "\n"; 
		} 
		cout << "\n"; 
	}
}

int main() {
	string jogador1, jogador2;
	srand(time(NULL));
	setlocale(LC_ALL, "Portuguese");
	
	for(int i = 0; i < I/4; i++) { /*Inicialização das casas mágicas*/
		for(int j = 0; j < J/5; j++) {
			casa_magia[i][j] = rand() % 8 + 7;
		}
	}
	for(int i = 0; i < I; i++) { /*Inicialização da pontuação*/
		for(int j = 0; j < J; j++) {
			pontos[i][j] = 0;
		}
	}
	for(int i = 0; i < I; i++) { /*Inicialização do tabuleiro*/
		for(int j = 0; j < J; j++) {
			j == 0? trilha[i][j] = 'X': trilha[i][j] = 'O';
		}
	}
	cout << "Nome dos jogadores: ";
	getline(cin, jogador1); getline(cin, jogador2);
	cout << endl;
	
	while(x) {
		num_dado = dado();
		cout << num_dado << "\n";
		cout << "Trilha do(a) ";
		SetConsoleTextAttribute(hConsole, 11);
		cout << jogador1; 
		SetConsoleTextAttribute(hConsole, 7);
		cout << ": ";
		cin >> num_trilha;
		cout << "\n";
		MoverPeaoJogador1(trilha, pontos, num_trilha, num_dado);
		TrilhaCompleta1(trilha, pontos, num_trilha, num_dado, jogador1);
		if(pontos[0][num_trilha - 1] == pontos[1][num_trilha - 1] && pontos[0][num_trilha-1] != J - 1) {
			VoltaInicio1(trilha, pontos, num_trilha);
		}
		
		num_dado = dado();
		cout << num_dado << "\n";
		cout << "Trilha do(a) ";
		SetConsoleTextAttribute(hConsole, 12); 
		cout << jogador2; 
		SetConsoleTextAttribute(hConsole, 7);
		cout << ": ";
		cin >> num_trilha;
		cout << "\n";
		MoverPeaoJogador2(trilha, pontos, num_trilha, num_dado);
		if(pontos[1][num_trilha - 1] == pontos[0][num_trilha - 1] && pontos[1][num_trilha-1] != J - 1) {
			VoltaInicio2(trilha, pontos, num_trilha);
		}
		TrilhaCompleta2(trilha, pontos, num_trilha, num_dado, jogador2);
		
		CasasMagicas(trilha, pontos, casa_magia, num_trilha, jogador1, jogador2);
		system("cls");
		MostrarTrilha(trilha);
		FimPartida(trilha, jogador1, jogador2, num_dado);
	}
	MostrarPontos(pontos, jogador1, jogador2);
	return 0;
}

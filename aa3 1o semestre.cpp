#include <iostream>  
#include <windows.h> 
#include <locale.h>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#define I 8 
#define J 20 
#define K 26
using namespace std;  

int main() {    
	int dado, no_trilha;
	int pontos[J/5][I/4] = {0}, casa_magia[I/4][J/5] = {0};
	char trilha[I][K] = {'O'};
	bool x = true;
	string jogador_um, jogador_dois; 
	
	setlocale(LC_ALL, "Portuguese");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));
	
	cout << "Nome dos jogadores: ";
	cin >> jogador_um >> jogador_dois;
	cout << endl;
	
	for(int i = 0; i < I; i++) { 
		for(int j = 0; j < J; j++) { 
			trilha[i][j] = 'O'; 
		} 
	}
	for(int i = 0; i < I; i++) {
		trilha[i][0] = 'X';
	} 
	for(int i = 0; i < I/4; i++) { 
		for(int j = 0; j < J/5; j++) { 
			casa_magia[i][j] = rand() % 8 + 7;
		} 
	} 
	for(int i = 0; i < J/5; i++) {
		for(int j = 0; j < I/4; j++) {
			pontos[i][j] = 0;
		}
	}
	while(x) {
		dado = rand() % 6 + 1;
		cout << "Dado: " << dado << endl;
		cout << "Trilha do(a) ";
		SetConsoleTextAttribute(hConsole, 11);
		cout << jogador_um; 
		SetConsoleTextAttribute(hConsole, 7);
		cout << ": ";
		cin >> no_trilha;
		trilha[(no_trilha - 1) * 2][pontos[no_trilha - 1][0]] = 'O';
		trilha[(no_trilha - 1) * 2][pontos[no_trilha - 1][0] + dado] = 'X';
		pontos[no_trilha - 1][0] += dado;
		dado = 0;
		cout << endl;
		if(pontos[no_trilha - 1][0] == pontos[no_trilha - 1][1] && pontos[no_trilha - 1][1] <= J) {
			trilha[1 + (no_trilha - 1) * 2][pontos[no_trilha - 1][1]] = 'O';
			pontos[no_trilha - 1][1] = 0;
			trilha[1 + (no_trilha - 1) * 2][pontos[no_trilha - 1][1]] = 'X';
		}
		if(pontos[no_trilha - 1][0] >= J) {
			SetConsoleTextAttribute(hConsole, 11);
			cout << jogador_um; 
			SetConsoleTextAttribute(hConsole, 7);
			cout << " completou uma trilha!" << endl << endl;
			Sleep(2000);
			trilha[(no_trilha - 1) * 2][pontos[no_trilha - 1][0] - dado] = 'O';
			trilha[(no_trilha - 1) * 2][J - 1] = 'X';
		}
		for(int j = 0; j < J/5; j++) {
			if(j % 2 == 0) {
				if(pontos[j][0] == casa_magia[0][j]) {
					SetConsoleTextAttribute(hConsole, 11);
					cout << jogador_um; 
					SetConsoleTextAttribute(hConsole, 7);
					cout << " parou em uma casa abençoada!" << endl << "Avance 2 casas" << endl << endl;
					Sleep(2000);
					trilha[(no_trilha - 1) * 2][pontos[no_trilha - 1][0]] = 'O';
					pontos[no_trilha - 1][0] += 2;
					trilha[(no_trilha - 1) * 2][pontos[no_trilha - 1][0]] = 'X';
				}
			} else {
				if(pontos[j][0] == casa_magia[0][j]) {
					SetConsoleTextAttribute(hConsole, 11);
					cout << jogador_um; 
					SetConsoleTextAttribute(hConsole, 7);
					cout << " parou em uma casa amaldiçoada!" << endl << "Volte 3 casas" << endl << endl;
					Sleep(2000);
					trilha[(no_trilha - 1) * 2][pontos[no_trilha - 1][0]] = 'O';
					pontos[no_trilha - 1][0] -= 3;
					trilha[(no_trilha - 1) * 2][pontos[no_trilha - 1][0]] = 'X';	
				}
			}
		}
		
		dado = rand() % 6 + 1;
		cout << "Dado: " << dado << endl;
		cout << "Trilha do(a) ";
		SetConsoleTextAttribute(hConsole, 12); 
		cout << jogador_dois; 
		SetConsoleTextAttribute(hConsole, 7);
		cout << ": ";
		cin >> no_trilha;
		trilha[1 + ((no_trilha - 1) * 2)][pontos[no_trilha - 1][1]] = 'O';
		trilha[1 + ((no_trilha - 1) * 2)][pontos[no_trilha - 1][1] + dado] = 'X';
		pontos[no_trilha - 1][1] += dado;
		dado = 0;
		cout << endl;
		
		if(pontos[no_trilha - 1][1] == pontos[no_trilha - 1][0] && pontos[no_trilha - 1][0] <= J) {
			trilha[(no_trilha - 1) * 2][pontos[no_trilha - 1][0]] = 'O';
			pontos[no_trilha - 1][0] = 0;
			trilha[(no_trilha - 1) * 2][pontos[no_trilha - 1][0]] = 'X';
		}
		if(pontos[no_trilha - 1][1] >= J) {
			SetConsoleTextAttribute(hConsole, 12); 
			cout << jogador_dois; 
			SetConsoleTextAttribute(hConsole, 7);
			cout << " completou uma trilha!" << endl << endl;
			Sleep(2000);
			trilha[1 + ((no_trilha - 1) * 2)][pontos[no_trilha - 1][1] - dado] = 'O';
			trilha[1 + ((no_trilha - 1) * 2)][J - 1] = 'X';
		}
		for(int j = 0; j < J/5; j++) {
			if(j % 2 == 0) {
				if(pontos[j][1] == casa_magia[1][j]) {
					SetConsoleTextAttribute(hConsole, 12); 
					cout << jogador_dois; 
					SetConsoleTextAttribute(hConsole, 7);
					cout << " parou em uma casa abençoada!" << endl << "Avance 2 casas" << endl << endl;
					Sleep(2000);
					trilha[1 + ((no_trilha - 1) * 2)][pontos[no_trilha - 1][1]] = 'O';
					pontos[no_trilha - 1][1] += 2;
					trilha[1 + ((no_trilha - 1) * 2)][pontos[no_trilha - 1][1]] = 'X';
				}
			} else {
				if(pontos[j][0] == casa_magia[1][j]) {
					SetConsoleTextAttribute(hConsole, 12); 
					cout << jogador_dois; 
					SetConsoleTextAttribute(hConsole, 7);
					cout << " parou em uma casa amaldiçoada!" << endl << "Volte 3 casas" << endl << endl;
					Sleep(2000);
					trilha[(no_trilha - 1) * 2][pontos[no_trilha - 1][1]] = 'O';
					pontos[no_trilha - 1][1] -= 3;
					trilha[1 + ((no_trilha - 1) * 2)][pontos[no_trilha - 1][1]] = 'X';	
				}
			}
		}
		
		system("cls");
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
				cout << endl; 
			} 
			cout << endl; 
		}
		
		if(pontos[0][0] >= J && pontos[1][0] >= J && pontos[2][0] >= J && pontos[3][0] >= J)  {
			cout << "Fim da partida" << "\n" << "\n";
			SetConsoleTextAttribute(hConsole, 11);
			cout << jogador_um << " ";
			SetConsoleTextAttribute(hConsole, 7);
			cout << "ganhou!" << "\n" << "\n";
			Sleep(2000);
			x = false;
		} else {
			if(pontos[0][1] >= J && pontos[1][1] >= J && pontos[2][1] >= J && pontos[3][1] >= J) {
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
	
	cout << "Pontuação " << " ";
	SetConsoleTextAttribute(hConsole, 11);
	cout << "\t" << jogador_um << "\t";
	SetConsoleTextAttribute(hConsole, 12);
	cout << jogador_dois << "\n" << "\n";
	SetConsoleTextAttribute(hConsole, 7);
	for(int i = 0; i < J/5; i++) {
		cout << "Trilha " << i + 1 << ": " << "\t";
		for(int j = 0; j < I/4; j++) {
			if(j == 0) {
				SetConsoleTextAttribute(hConsole, 11);
				cout << pontos[i][j] << "\t";
				SetConsoleTextAttribute(hConsole, 7);
			} else {
				SetConsoleTextAttribute(hConsole, 12);
				cout << pontos[i][j] << "\n" << "\n";
				SetConsoleTextAttribute(hConsole, 7);
			}
		}
	}

	system("pause");
	return 0;	 
}

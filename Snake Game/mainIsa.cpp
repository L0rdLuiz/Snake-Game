#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int main()
{
    ///ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, A SEGUIR.
    //INICIO: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
    //FIM: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
    //INICIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
    short int CX = 0, CY = 0;
    COORD coord;
    coord.X = CX;
    coord.Y = CY;
    //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
    ///ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, ACIMA.

    int menu;
    int repetir = 0;

    do {
        //Colocar nome do jogo
        //Colocar as opções no cout: jogar 1, sobre o jogo 2, rank 3, e sair no 4

        cin >> menu;
        switch (menu) {
            case 1: //Jogo
                system("cls");
                do {
                    bool jogo = true;

                    int m[15][17] = {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                    };

                    //Posicao inicial do personagem no console
                    int x = 5, y = 5;
                    //Variavel para tecla precionada
                    char tecla;

                    while (jogo == true) {
                        ///Posiciona a escrita no inicio do console
                        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

                        ///Imprime o jogo: mapa e personagem.
                        for (int i = 0; i < 15; i++) {
                            for (int j = 0; j < 17; j++) {
                                if (i == x && j == y) {
                                    cout << char(36); //personagem
                                } else {
                                    switch (m[i][j]) {
                                        case 0: cout << " "; break; //caminho
                                        case 1: cout << char(219); break; //parede
                                        //default: cout << "-"; //erro
                                    } //fim switch
                                }
                            }
                            cout << "\n";
                        } //fim for mapa

                        ///executa os movimentos
                        if (_kbhit()) {
                            tecla = getch();
                            switch (tecla) {
                                case 72: case 'w': ///cima
                                    x--;
                                    break;
                                case 80: case 's': ///baixo
                                    x++;
                                    break;
                                case 75: case 'a': ///esquerda
                                    y--;
                                    break;
                                case 77: case 'd': ///direita
                                    y++;
                                    break;
                            }
                        }
                    }; //fim do laco do jogo
                } while (repetir == 1);
                break;
            case 2: //Sobre o jogo

                break;
            case 3: //Rank

                break;
            case 4: // Obrigado por jogar

                break;
            default:
                cout << "Esta opcao nao e aceita digite outro numero";
                break;
        }
    } while (menu != 4);

    return 0;
} //fim main

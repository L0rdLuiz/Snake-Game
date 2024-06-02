#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

bool contemApenasLetras(const string& str)   /// verifica se o nome contém apenas letras
{
    for (char c : str)
    {
        if (!isalpha(c))
        {
            return false;
        }
    }
    return true;
}

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
    string nome;
    int repetir = 0;

    do
    {
        cout << "   ____ , __     ___  |   ,   ___         ___.   ___  , _ , _     ___" << endl;
        cout << "  (     |'  `.  /   ` |  /  .'   `      .'   `  /   ` |' `|' `. .'   `" << endl;
        cout << "  `--.  |    | |    | |-<   |----'      |    | |    | |   |   | |----'" << endl;
        cout << " \\___.' /    | `.__/| /  \\_ `.___,       `---| `.__/| /   '   / `.___," <<endl;
        cout << "                                         \\___/" << endl << endl << endl << endl<< endl;

        cout <<"                          ______________________________ " << endl;
        cout << "                         |                              |" << endl;
        cout << "                         |         1 - COMECAR          |" << endl;
        cout << "                         |         2 - TUTORIAL         |" << endl;
        cout << "                         |         3 - RANKING          |" << endl;
        cout << "                         |         4 - SAIR             |" << endl;
        cout << "                         |______________________________|" << endl;


        cin >> menu;
        switch (menu)
        {
        case 1: //Jogo
            cout << "digite seu nome: " << endl; //nome do jogador para o rank
            cin >> nome;
            if (!contemApenasLetras(nome))
            {
                cout << "Erro: O nome deve conter apenas letras." << endl;
                cout << "digite seu nome:" << endl;
                cin >> nome;
            }

            system("cls");
            do
            {
                bool jogo = true;

                int m[15][17] =
                {
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

                while (jogo == true)
                {
                    ///Posiciona a escrita no inicio do console
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

                    ///Imprime o jogo: mapa e personagem.
                    for (int i = 0; i < 15; i++)
                    {
                        for (int j = 0; j < 17; j++)
                        {
                            if (i == x && j == y)
                            {
                                cout << char(36); //personagem
                            }
                            else
                            {
                                switch (m[i][j])
                                {
                                case 0:
                                    cout << " ";
                                    break; //caminho
                                case 1:
                                    cout << char(219);
                                    break; //parede
                                    //default: cout << "-"; //erro
                                } //fim switch
                            }
                        }
                        cout << "\n";
                    } //fim for mapa

                    ///executa os movimentos
                    if (_kbhit())
                    {
                        tecla = getch();
                        switch (tecla)
                        {
                        case 72:
                        case 'w': ///cima
                            x--;
                            break;
                        case 80:
                        case 's': ///baixo
                            x++;
                            break;
                        case 75:
                        case 'a': ///esquerda
                            y--;
                            break;
                        case 77:
                        case 'd': ///direita
                            y++;
                            break;
                        }
                    }
                }; //fim do laco do jogo
            }
            while (repetir == 1);
            break;
        case 2: //Sobre o jogo
            system ("cls");


            cout<< "                                                                  " << endl;

            cout<< "                                                                  " << endl;

            cout << "OBJETIVO: Coma 100 macas sem colidir com a parede ou com a cobra." << endl;
            cout << "MOVIMENTO: Use W, A, S e D para mover a cobra que se move sempre para frente" << endl;
            cout << "MACAS: Mova-se em direcao as macas para come-las e crescer." << endl;
            cout << "EVITAR COLISOES: Evite colidir com a parede ou com o corpo da cobra." << endl;
            cout << "VITORIA: Ao comer 100 macas sem colisoes, voce vence o jogo!" << endl<< endl;
            cout << "BOA SORTE!" << endl << endl;
            system("pause");
            system ("cls");
            break;
        case 3: //Rank
            system ("cls");

            system("pause");
            system ("cls");
            break;
        case 4: // Obrigado por jogar

            break;
        default:
            cout << "Esta opcao nao e aceita digite outro numero";
            break;
        }
    }
    while (menu != 4);

    return 0;
} //fim main

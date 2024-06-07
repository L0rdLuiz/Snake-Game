#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <chrono>
#include <mmsystem.h> //musica
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <fstream>
#include <string>


using namespace std;
using namespace std::chrono;


struct Snake {
    int x, y;
    bool vivo;
    int comeu;
};

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

void MovimentoCobra(vector <Snake> &Cobra){
    for(int i = Cobra.size()-1;i>0;i--){
        Cobra[i]=Cobra[i-1];
        }
    }

bool ColisaoCorpoCobra(const vector<Snake>& Cobra){
    for(int i =1;i<Cobra.size();i++){
        if(Cobra[0].x==Cobra[i].x&&Cobra[0].y==Cobra[i].y){
            return true;
        }
    }
    return false;
}

void geraMaca(int m[15][17], bool& macaNoJogo, const vector<Snake>& Cobra) {
    if (!macaNoJogo) {
        int mx, my;
        bool posicaoValida;
        do {
            mx = rand() % 15;
            my = rand() % 17;

            // Verificar se a posição está ocupada pelo corpo da cobra
            posicaoValida = true;
            for (int i = 0; i < Cobra.size(); i++) {
                if (Cobra[i].x == mx && Cobra[i].y == my) {
                    posicaoValida = false;
                    break;
                }
            }
        } while (m[mx][my] == 1 || !posicaoValida);

        m[mx][my] = 2;
        macaNoJogo = true;
    }
}

void IncrementoDaCobra (vector <Snake>&Cobra){
    Snake Cauda = Cobra.back();
    Cobra.push_back(Cauda);
}

void salvarRanking(const string& nome, int &pontuacao,  int tempoEmSegundos)        //salva a pontuacao no arquivo
{
    ofstream arquivoS;
    arquivoS.open("ranking.txt", std::ios_base::app);
    if (arquivoS.is_open()){
        time_t tempoAtual = time(nullptr); // tempo atual em segundos
        char dataFormatada[80];
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y %H:%M:%S", localtime(&tempoAtual));
        arquivoS << "Nome: " << nome <<  endl;
        arquivoS << "Pontuacao: " << pontuacao <<  endl;
        arquivoS << "Tempo de Jogo: " << tempoEmSegundos << " segundos" << endl;
        arquivoS << "Data: " << dataFormatada << endl << endl;
        arquivoS << endl;
        arquivoS.close();}


        }

        ///recursividade (ordenando rank)

void exibirRankingRecursivo(vector<pair<int, string>>& ranking, int esquerda, int direita)
{
    if (esquerda < direita)
    {
        int pivo = ranking[direita].first;
        int i = esquerda - 1;
        for (int j = esquerda; j <= direita - 1; j++)
        {
            if (ranking[j].first > pivo)
            {
                i++;
                swap(ranking[i], ranking[j]);
            }
        }
        swap(ranking[i + 1], ranking[direita]);
        int indice = i + 1;
        exibirRankingRecursivo(ranking, esquerda, indice - 1);
        exibirRankingRecursivo(ranking, indice + 1, direita);
    }
}

void exibirRanking() ///exibi rank ordenado em tela
{
    ifstream arquivoS;
    string linha;
    vector<pair<int, string>> ranking;
    arquivoS.open("ranking.txt");
    if (arquivoS.is_open())
    {
        int pontos;
        string nome;
        while (arquivoS >> linha)
        {
            if (linha == "Pontuacao:")
            {
                arquivoS >> pontos;
                ranking.push_back(make_pair(pontos, nome));
            }
            else if (linha == "Nome:")
            {
                arquivoS >> nome;
            }
        }
        arquivoS.close();

        exibirRankingRecursivo(ranking, 0, ranking.size() - 1);

        cout << "Ranking:" << endl;
        for (const auto& pair : ranking)
        {
            cout << pair.second << " - " << pair.first << endl;
        }
    }
    else
    {
        cout << "Erro ao abrir o arquivo de ranking." << endl;
    }
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
    int pontuacao = 0;
    exibirRanking();
    int repetir = 0;
    int TamanhoCobra = 3;
    vector <Snake> Cobra;
    //Posicao inicial do personagem no console
    Cobra.push_back({5,5});
    Cobra.push_back({5,4});
    Cobra.push_back({5,3});
    ///VERIFICAÇÃO COBRA NA HORIZONTAL OU VERTICAL
    bool CobraHorizontal = false;
    bool CobraVertical   = false;
    ///ONDE A COBRA ESTA OLHANDO
    bool CabecaCima = false;
    bool CabecaBaixo = false;
    bool CabecaDireita = false;
    bool CabecaEsquerda = false;
    //Variavel para tecla pressionada
    char tecla;
    //Variavel para contagem de tempo em tela
    auto inicio = steady_clock::now();
    auto final = steady_clock::now();
    int tempoEmSegundos;
    //Gerador de Maçã
    srand (time(NULL));
    bool macaNoJogo = false;
    //Cobra viva
    Snake CobraViva;
    milliseconds diminuirVelocidade(45);

    do
    {
        PlaySound(TEXT("menu.wav"), NULL, SND_ASYNC); //musica menu
        system("cls");
         cout << "                           _____             _        " << endl;
        cout << "                          /  ___|           | |       " << endl;
        cout << "                          \\ `--. _ __   __ _| | _____ " << endl;
        cout << "                           `--. \\ '_ \\ / _` | |/ / _ \\" << endl;
        cout << "                          /\\__/ / | | | (_| |   <  __/" << endl;
        cout << "                          \\____/|_| |_|\\__,_|_|\\_\\___|" << endl;
        cout << "                                                      " << endl<<endl;

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
        case 1:{ //Jogo

            cout << "digite seu nome: " << endl; //nome do jogador para o rank
            cin >> nome;
            if (!contemApenasLetras(nome))
            {
                cout << "Erro: O nome deve conter apenas letras." << endl;
                cout << "digite seu nome:" << endl;
                cin >> nome;
            }

            system("cls");
            auto inicio = steady_clock::now();


            do
            {
                //Botar coisas para repetir aqui
                PlaySound(TEXT("trilha.wav"), NULL, SND_ASYNC); //musica
                bool jogo = true;
                CobraViva.vivo = true;
                CobraViva.comeu = 0;
                bool macaNoJogo = false;
                bool aumentoVelocidade = false;
                auto inicio = steady_clock::now();
                milliseconds velocidade(750);
                milliseconds velocidadeTecla(500);
                auto inicioCobra = high_resolution_clock::now();
                auto inicioCobraMovimento = high_resolution_clock::now(); //Bloqueio de tecla
                CobraHorizontal = true;
                CabecaDireita= true;

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




                while (jogo == true)
                {
                    ///Posiciona a escrita no inicio do console
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

                    ///Imprime o jogo: mapa e personagem.
                    for (int i = 0; i < 15; i++)
                    {
                        for (int j = 0; j < 17; j++)
                        {
                            bool CobraOn = false;
                            if(i==Cobra[0].x&&j==Cobra[0].y){
                                cout<<char (79);
                            }else{
                            for(auto const &Snake:Cobra)
                            {
                                if(i==Snake.x&&j==Snake.y){
                                cout << char(111); //personagem
                                CobraOn = true;
                                break;
                                }
                            }

                            if(!CobraOn){
                                switch (m[i][j])
                                {
                                case 0: cout << " "; break; //caminho
                                case 1: cout << char(219); break; //parede
                                case 2: cout<<char(162); break; //maçã
                                //default: cout << "-"; //erro
                                }

                                } //fim switch
                            }
                        }
                        cout << "\n";
                    } //fim for mapa

                    auto agoraCobra = high_resolution_clock::now();
                    auto passouCobra = duration_cast<milliseconds>(agoraCobra - inicioCobra);
                    if(ColisaoCorpoCobra(Cobra)){
                            CobraViva.vivo = false;
                        }
                    if (passouCobra >= velocidade) {
                        if (CabecaCima == true) {
                            MovimentoCobra(Cobra);
                            Cobra[0].x--;
                        }
                        if (CabecaBaixo == true) {
                            MovimentoCobra(Cobra);
                            Cobra[0].x++;
                        }
                        if (CabecaDireita == true) {
                            MovimentoCobra(Cobra);
                            Cobra[0].y++;
                        }
                        if (CabecaEsquerda == true) {
                            MovimentoCobra(Cobra);
                            Cobra[0].y--;
                        }
                        inicioCobra = agoraCobra;
                    }

                    auto agoraCobraMovimento = high_resolution_clock::now();
                    auto passouCobraMovimento = duration_cast<milliseconds>(agoraCobraMovimento - inicioCobraMovimento);

                    ///executa os movimentos
                    if (_kbhit())
                    {
                        tecla = getch();
                        switch (tecla)
                        {
                        case 72:
                        case 'w': ///cima
                            if(CobraHorizontal==true && passouCobraMovimento >= velocidadeTecla){
                                MovimentoCobra(Cobra);
                                Cobra[0].x--;
                                CobraVertical=true;
                                CobraHorizontal=false;
                                CabecaCima = true;
                                CabecaBaixo = CabecaDireita = CabecaEsquerda = false;
                                inicioCobraMovimento = agoraCobraMovimento;
                                inicioCobra = agoraCobraMovimento;
                            }
                            break;
                        case 80:
                        case 's': ///baixo
                            if(CobraHorizontal==true && passouCobraMovimento >= velocidadeTecla){
                                MovimentoCobra(Cobra);
                                Cobra[0].x++;
                                CobraVertical=true;
                                CobraHorizontal=false;
                                CabecaBaixo = true;
                                CabecaCima = CabecaDireita = CabecaEsquerda = false;
                                inicioCobraMovimento = agoraCobraMovimento;
                                inicioCobra = agoraCobraMovimento;
                            }
                            break;
                        case 75:
                        case 'a': ///esquerda
                            if(CobraVertical==true && passouCobraMovimento >= velocidadeTecla){
                                MovimentoCobra(Cobra);
                                Cobra[0].y--;
                                CobraVertical=false;
                                CobraHorizontal=true;
                                CabecaEsquerda = true;
                                CabecaCima = CabecaBaixo = CabecaDireita = false;
                                inicioCobraMovimento = agoraCobraMovimento;
                                inicioCobra = agoraCobraMovimento;
                            }
                            break;
                        case 77:
                        case 'd': ///direita
                            if(CobraVertical==true && passouCobraMovimento >= velocidadeTecla){
                                MovimentoCobra(Cobra);
                                Cobra[0].y++;
                                CobraVertical=false;
                                CobraHorizontal=true;
                                CabecaDireita = true;
                                CabecaCima = CabecaBaixo = CabecaEsquerda = false;
                                inicioCobraMovimento = agoraCobraMovimento;
                                inicioCobra = agoraCobraMovimento;
                            }
                            break;
                            case 'o':
                            IncrementoDaCobra(Cobra);
                            break;
                        }


                    }

                    //tempo em tela

                    final = steady_clock::now();
                    auto tempo = final - inicio;


                    cout << "   TEMPO: " << duration_cast<seconds>(tempo).count() << endl;
                    cout << " PONTUACAO: " << pontuacao << endl; //pontuacao em tela

                    geraMaca(m, macaNoJogo, Cobra);

                    if (m[Cobra[0].x][Cobra[0].y] == 2) {
                        m[Cobra[0].x][Cobra[0].y] = 0;
                        IncrementoDaCobra(Cobra);
                        macaNoJogo = false;
                        pontuacao+=10; //somando 10 à pontuacao
                        CobraViva.comeu += 1; //Contador de maçãs comidas
                    }

                    if (CobraViva.vivo == true && m[Cobra[0].x][Cobra[0].y] == 1) {
                        CobraViva.vivo = false;
                        Cobra.clear();
                        Cobra.push_back({5,5});
                        Cobra.push_back({5,4});
                        Cobra.push_back({5,3});
                        CabecaDireita= true;
                        CabecaBaixo = false;
                        CabecaEsquerda = false;
                        CabecaCima = false;
                        jogo = false;
                    }
                    if(!CobraViva.vivo){
                        jogo = false;
                    }

                    if (CobraViva.comeu % 5 == 0 && CobraViva.comeu != 0 && aumentoVelocidade == false) {
                        velocidade -= diminuirVelocidade;
                        aumentoVelocidade = true;
                    } else if (CobraViva.comeu % 5 != 0 && aumentoVelocidade == true) {
                        aumentoVelocidade = false;
                    }

                }; //fim do laco do jogo
                if(CobraViva.vivo == false){
                   PlaySound(TEXT("morreu.wav"), NULL, SND_ASYNC); //som morte cobra
                }
                if (CobraViva.vivo == false) {
                    system ("cls");
                    auto tempo = final - inicio;
                    int tempoEmSegundos = duration_cast<seconds>(tempo).count(); //tempo no arquivo
                    salvarRanking(nome,pontuacao, tempoEmSegundos);
                    exibirRanking();
                    cout<< endl << "Voce perdeu o jogo"<<endl;
                    cout<<"Jogo feito por:"<<endl<<"Luiz Antonio Haenisch"<<endl<<"Carlos Henrique Okarenski Ramos Depieri"<<endl<<"Isabela Silverio Cardoso Pereira"<<endl;
                    cout<<"Professor: Alex Luciano"<<endl;
                    cout<<"Quer jogar novamente?"<<endl;
                    cout<<"Digite 1 para jogar de novo ou 0 retornar ao menu"<<endl;
                    cin>>repetir;

                    system ("cls");
                }
            }
            while (repetir == 1);
            break;}
        case 2: //Sobre o jogo
            system ("cls");


            cout<< "                                                                  " << endl;

            cout<< "                                                                  " << endl;

            cout << "OBJETIVO: Coma 100 macas sem colidir com a parede ou com a cobra." << endl;
            cout << "MOVIMENTO: Use W, A, S e D para mover a cobra que se move sempre para frente" << endl;
            cout << "MACAS: Mova-se em direcao as macas para come-las e crescer." << endl;
            cout << "EVITAR COLISOES: Evite colidir com a parede ou com o corpo da cobra." << endl;
            cout << "PONTUACAO: A cada maca coletada o jogador recebe 10 pontos." << endl;
            cout << "VITORIA: Ao comer 100 macas sem colisoes, voce vence o jogo!" << endl<< endl;
            cout << "BOA SORTE!" << endl << endl;
            system("pause");
            system ("cls");
            break;
        case 3: //Rank

            system("cls");
            exibirRanking();
            system("pause");
            break;
        case 4: // Obrigado por jogar

            break;
        default:
            cout << "Esta opcao nao e aceita digite outro numero"<<endl;
            system("pause");
            break;
        }
    }
    while (menu != 4);

    return 0;
} //fim main

// Instituto Federal de Educação do Amazonas – IFAM
// Professor: Sergio Augusto Coelho Bezerra
// Aluno: Eduardo Bandeira Oliveira

#include <stdio.h>
#include <windows.h>
#include <conio.h> 

#define N 6
#define M 5

#define COR_VERDE 10
#define COR_AZUL_CLARO 11
#define COR_VERMELHO 12
#define COR_AMARELO 14
#define COR_BRANCO 7 

float preco_inteira = 50.0;
float preco_meia = 25.0;
float preco_pcd = 20.0;

// Struct(Agrupamento de Variaveis)
// (Struct removida)

// Função pra colocar cores no console
void setCor(int cor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

// Função gotoxy (Definir posições)
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// MenuInicial (Mostra o menu inicial para entrar no programa)
void MenuInicial() {
    int x = 20; 
    int y = 5;  
    system("cls"); 
    gotoxy(x, y);
    printf("+---------------------------------+");
    y++; 
    gotoxy(x, y);
    printf("|Seja Bem Vindo a rede CineBandas!|");
    y++; 
    gotoxy(x, y);
    printf("+---------------------------------+");
    y += 2; 
    gotoxy(x, y);
    printf(" Carregando o sistema, aguarde...");
    Sleep(2500); 
}

void definirPrecos() {
    system("cls");
    setCor(COR_BRANCO);
    gotoxy(10, 5);
    printf("===== CONFIGURACAO DE PRECOS =====\n");
    gotoxy(10, 7);
    printf("Digite o valor do ingresso [Inteira]: R$ ");
    scanf("%f", &preco_inteira);
    gotoxy(10, 8);
    printf("Digite o valor do ingresso [Meia]:   R$ ");
    scanf("%f", &preco_meia);
    gotoxy(10, 9);
    printf("Digite o valor do ingresso [PCD]:    R$ ");
    scanf("%f", &preco_pcd);
    gotoxy(10, 11);
    printf("Precos atualizados com sucesso!");
    Sleep(1500);
}

// limpar_texto (limpa o texto)
void limpar_texto() {
    int i;
    for (i = 0; i < 10; i++) { 
        gotoxy(0, 18 + i); 
        printf("                                                                                ");
    }
    gotoxy(0, 18); 
}

// Construção das poltronas e sala de cinema
void Sala(char status_assentos[N][M]) {
    int x = 20;
    int y = 0;
    int i, j;
    char fileiras = 'F';

    system("cls"); 

    setCor(COR_BRANCO); 
    
    // Numeração das Colunas 
    gotoxy(x, y);
    printf("     1    2    3    4    5   ");
    y++; // y  1
    
    // Topo da sala
    gotoxy(x, y);
    printf("+-----------------------------+");
    y++; // y  2

    // Numeração das Fileiras 
    for (i = 0; i < N; i++) {
        gotoxy(18, y + i);
        printf("%c", fileiras - i); 
    }

    // Poltronas com matriz 
    for (i = 0; i < N; i++) { 
        gotoxy(x, y);
        printf("|   "); 
        for (j = 0; j < M; j++) { 
            
            if (status_assentos[i][j] == 'X') {
                setCor(COR_VERMELHO); 
            } else if (status_assentos[i][j] == 'R') {
                setCor(COR_AZUL_CLARO); 
            } else { // 'o'
                setCor(COR_VERDE); 
            }
            
            printf("[%c]", status_assentos[i][j]); 
            
            setCor(COR_BRANCO); 
            if (j < M - 1) {
                printf("  "); 
            }
        }
        printf("   |"); 
        y++; 
    }
    // y  8

    setCor(COR_BRANCO); 
    
    // Espaço abaixo das poltronas 
    gotoxy(x, y);
    printf("|                             |");
    y++; // y  9

    // Título da Tela 
    setCor(COR_AMARELO); 
    gotoxy(x, y);
    printf("|           TELA              |"); 
    y++; // y 10
    
    // Topo da Tela 
    gotoxy(x, y);
    printf("|   -----------------------   |"); 
    y++; // y 11

    // Meio da tela 
    gotoxy(x, y);
    printf("|  |                       |  |"); 
    y++; // y 12

    // Meio da tela 
    gotoxy(x, y);
    printf("|  |                       |  |"); 
    y++; // y 13

    // Fim da tela 
    gotoxy(x, y);
    printf("|   -----------------------   |"); 
    y++; // y 14

    setCor(COR_BRANCO); 
    
    // Fim da sala 
    gotoxy(x, y); 
    printf("+-----------------------------+");
}

// reservarAssento (Função para reservar o assento)
void reservarAssento(char status_assentos[N][M], int tipo_assentos[N][M], float valor_assentos[N][M]) {
    char fileira;
    int coluna, tipo_escolhido;
    int i, j;
    float novo_valor = 0.0;

    limpar_texto(); 
    setCor(COR_BRANCO);

    printf("Digite a fileira (A-F): ");
    scanf(" %c", &fileira);
    
    if (fileira >= 'a' && fileira <= 'z') {
        fileira = fileira - 32;
    }

    gotoxy(0, 19);
    printf("Digite a coluna (1-5): ");
    scanf(" %d", &coluna);

    if (fileira < 'A' || fileira > 'F' || coluna < 1 || coluna > 5) {
        gotoxy(0, 21); 
        printf("Assento invalido. Tente novamente.");
        Sleep(1500); 
        return; 
    }

    i = 'F' - fileira; 
    j = coluna - 1;     

    gotoxy(0, 21);
    
    if (status_assentos[i][j] == 'o' || status_assentos[i][j] == 'R') {
        
        gotoxy(0, 22);
        printf("Selecione o tipo de ingresso:\n");
        printf(" (1) Inteira [R$ %.2f]\n", preco_inteira);
        printf(" (2) Meia    [R$ %.2f]\n", preco_meia);
        printf(" (3) PCD     [R$ %.2f] (Apenas fileira A)\n", preco_pcd);
        printf("Opcao: ");
        scanf("%d", &tipo_escolhido);

        if (tipo_escolhido < 1 || tipo_escolhido > 3) {
            printf("Tipo de ingresso invalido. Reserva cancelada.");
            Sleep(1500);
            return;
        }

        if (tipo_escolhido == 3 && status_assentos[i][j] != 'R') {
            printf("Erro: Ingresso PCD permitido apenas nos assentos [R].");
            Sleep(2500);
            return; 
        }

        if (tipo_escolhido == 1) novo_valor = preco_inteira;
        else if (tipo_escolhido == 2) novo_valor = preco_meia;
        else if (tipo_escolhido == 3) novo_valor = preco_pcd;

        status_assentos[i][j] = 'X'; 
        tipo_assentos[i][j] = tipo_escolhido;
        valor_assentos[i][j] = novo_valor;

        printf("Assento %c%d reservado com sucesso!", fileira, coluna);
        Sleep(1500); 

    } else if (status_assentos[i][j] == 'X') {
        printf("Assento %c%d ja esta ocupado.", fileira, coluna);
        Sleep(1500); 
    }
}

// removerAssento (Função para remover assento anteriormente escolhido)
void removerAssento(char status_assentos[N][M], int tipo_assentos[N][M], float valor_assentos[N][M]) {
    char fileira;
    int coluna;
    int i, j; 

    limpar_texto(); 
    setCor(COR_BRANCO);

    printf("Digite a fileira (A-F): ");
    scanf(" %c", &fileira);
    
    if (fileira >= 'a' && fileira <= 'z') {
        fileira = fileira - 32;
    }

    gotoxy(0, 19);
    printf("Digite a coluna (1-5): ");
    scanf(" %d", &coluna);

    if (fileira < 'A' || fileira > 'F' || coluna < 1 || coluna > 5) {
        gotoxy(0, 21); 
        printf("Assento invalido. Tente novamente.");
        Sleep(1500); 
        return; 
    }

    i = 'F' - fileira; 
    j = coluna - 1;     

    gotoxy(0, 21); 
    
    if (status_assentos[i][j] == 'X') {
        
        if (i == 5) { 
            status_assentos[i][j] = 'R'; 
        } else {
            status_assentos[i][j] = 'o'; 
        }
        tipo_assentos[i][j] = 0;
        valor_assentos[i][j] = 0.0;
        
        printf("Assento %c%d removido com sucesso!", fileira, coluna);
        Sleep(1500); 
        
    } else { 
        printf("Assento %c%d nao esta ocupado.", fileira, coluna);
        Sleep(1500); 
    }
}

// IngressosVendidos (Função que mostra toda os ingressos comprados, com valores e grafico informando quantidade)
void IngressosVendidos(char status_assentos[N][M], int tipo_assentos[N][M], float valor_assentos[N][M]) {
    int i, j, k;
    int total_inteira = 0, total_meia = 0, total_pcd = 0;
    float valor_inteira = 0.0, valor_meia = 0.0, valor_pcd = 0.0;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (status_assentos[i][j] == 'X') {
                if (tipo_assentos[i][j] == 1) {
                    total_inteira++;
                    valor_inteira += valor_assentos[i][j];
                } else if (tipo_assentos[i][j] == 2) {
                    total_meia++;
                    valor_meia += valor_assentos[i][j];
                } else if (tipo_assentos[i][j] == 3) {
                    total_pcd++;
                    valor_pcd += valor_assentos[i][j];
                }
            }
        }
    }
    int total_ingressos = total_inteira + total_meia + total_pcd;
    float total_arrecadado = valor_inteira + valor_meia + valor_pcd;

    limpar_texto();
    setCor(COR_BRANCO);
    
    printf("===== RELATORIO DE VENDAS =====\n\n");
    printf("%-7s | %-10s | %3s | %14s\n", "Tipo", "Preco", "Qtd", "Valor Arrecadado");
    printf("-------------------------------------------------\n");
    printf("%-7s | %3d | R$ %11.2f\n", "Inteira", total_inteira, valor_inteira);
    printf("%-7s | %3d | R$ %11.2f\n", "Meia", total_meia, valor_meia);
    printf("%-7s | %3d | R$ %11.2f\n", "PCD", total_pcd, valor_pcd);
    printf("-------------------------------------------------\n");
    printf("%-7s |            | %3d | R$ %11.2f\n", "TOTAL", total_ingressos, total_arrecadado);
    
    printf("\n----- Grafico de Vendas (Qtd) -----\n");
    printf("Inteira: ");
    for(k = 0; k < total_inteira; k++) { printf("#"); }
    printf("\n");
    
    printf("Meia...: ");
    for(k = 0; k < total_meia; k++) { printf("#"); }
    printf("\n");
    
    printf("PCD....: ");
    for(k = 0; k < total_pcd; k++) { printf("#"); }
    printf("\n");
    
    printf("\n\nPressione qualquer tecla para voltar...");
    getch(); 
}

// Main, onde tudo será executado
int main() {
    char status_assentos[N][M];
    int tipo_assentos[N][M];
    float valor_assentos[N][M];
    
    int i, j;
    int opcao = -1;

    // Chamamos a função do menu
    MenuInicial();

    definirPrecos();

    // Declarando os assentos vazios e de PCD
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (i == 5) { 
                status_assentos[i][j] = 'R'; 
            } else { 
                status_assentos[i][j] = 'o'; 
            }
            tipo_assentos[i][j] = 0; 
            valor_assentos[i][j] = 0.0;       
        }
    }
    // Aqui vai o switch para escolher o que for necessário
    do {
        Sala(status_assentos); // puxa-se a função da sala para mostrar ao usuario

        setCor(COR_BRANCO); 

        gotoxy(0, 18);
        printf("===============================\n");
        printf("   RESERVE AQUI SEU INGRESSO     \n"); 
        printf("===============================\n");
        printf("1. Reservar Assento\n");
        printf("2. Remover Assento \n");
        printf("3. Ver Ingressos Vendidos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        setCor(COR_BRANCO); 

        switch (opcao) { 
            case 1:
                reservarAssento(status_assentos, tipo_assentos, valor_assentos); // Puxa-se a função de reserva
                break;
            case 2:
                removerAssento(status_assentos, tipo_assentos, valor_assentos); // Puxa-se a função de remoção de reserva
                break; 
            case 3:
                IngressosVendidos(status_assentos, tipo_assentos, valor_assentos);  // Puxa-se a função de mostrar os ingressos vendidos
                break;
            case 0:
                system("cls");
                printf("Ate a proxima e Bom Filme!\n");
                Sleep(1500);
                break;
            default:
                limpar_texto(); 
                printf("Opcao invalida. Tente novamente.");
                Sleep(1500);
                break;
        }

    } while (opcao != 0); 

    setCor(COR_BRANCO); 
    return 0;
}
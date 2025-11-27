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
struct Vaga {
    char status;
    int tipo_veiculo;
    float valor;
};

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
    printf("+---------------------------------------------------+");
    y++; 
    gotoxy(x, y);
    printf("|Seja Bem Vindo a rede de Estacionamentos do Bandas!|");
    y++; 
    gotoxy(x, y);
    printf("+---------------------------------------------------+");
    y += 2; 
    gotoxy(x, y);
    printf("        Carregando o sistema, aguarde...");
    Sleep(2500); 
}

void definirPrecos() {
    system("cls");
    setCor(COR_BRANCO);
    gotoxy(10, 5);
    printf("===== CONFIGURACAO DE PRECOS =====\n");
    
    int c; // Para limpar o buffer

    gotoxy(10, 7);
    printf("Digite o valor da hora para carros:  R$ ");
    while (scanf("%f", &preco_inteira) != 1) { 
        setCor(COR_VERMELHO);
        gotoxy(10, 11);
        printf("Valor invalido. Digite apenas numeros.");
        setCor(COR_BRANCO);
        gotoxy(45, 7); 
        printf("                "); 
        gotoxy(45, 7);
        while ((c = getchar()) != '\n' && c != EOF); 
    }
    gotoxy(10, 11); 
    printf("                                       ");

    gotoxy(10, 8);
    printf("Digite o valor da hora para motos:   R$ ");
    while (scanf("%f", &preco_meia) != 1) {
        setCor(COR_VERMELHO);
        gotoxy(10, 11);
        printf("Valor invalido. Digite apenas numeros.");
        setCor(COR_BRANCO);
        gotoxy(45, 8);
        printf("                ");
        gotoxy(45, 8);
        while ((c = getchar()) != '\n' && c != EOF);
    }
    gotoxy(10, 11);
    printf("                                       ");

    gotoxy(10, 9);
    printf("Digite o valor da hora para [PCD]:   R$ ");
    while (scanf("%f", &preco_pcd) != 1) {
        setCor(COR_VERMELHO);
        gotoxy(10, 11);
        printf("Valor invalido. Digite apenas numeros.");
        setCor(COR_BRANCO);
        gotoxy(45, 9);
        printf("                ");
        gotoxy(45, 9);
        while ((c = getchar()) != '\n' && c != EOF);
    }

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
void Sala(struct Vaga vagas[N][M]) {
    int x = 20;
    int y = 0;
    int i, j;
    char fileiras = 'F';

    // Vamos definir a altura total da sala (6 fileiras de poltronas + 3 de parede)
    int altura_total_sala = N ; // 6 + 3 = 9

    system("cls"); 

    setCor(COR_BRANCO); 
    
    // Numeração das Colunas (Largura 39)
    gotoxy(x, y);
    printf("      1      2      3      4      5    ");
    y++; // y  1
    
    // Topo da sala (Largura 39)
    gotoxy(x, y);
    printf("+-------------------------------------+");
    y++; // y  2

    // ===================================
    // <<< LOOP UNICO PARA SALA INTEIRA >>>
    // ===================================
    // Este loop roda 9 vezes (i de 0 a 8)
    for (i = 0; i < altura_total_sala; i++) { 
        
        // Verifica se 'i' ainda está na parte das poltronas (i < 6)
        if (i < N) {
            // --- PARTE QUE DESENHA AS POLTRONAS ---
            
            // 1. Desenha a letra da fileira
            gotoxy(18, y); // Desenha a letra na linha 'y'
            printf("%c", fileiras - i); 

            // 2. Desenha a fileira de poltronas
            gotoxy(x, y);
            printf("|"); 
            
            for (j = 0; j < M; j++) { 
                
                if (vagas[i][j].status == 'X') {
                    setCor(COR_VERMELHO); 
                    printf("[XX] "); // 5 caracteres
                } else if (vagas[i][j].status == 'R') {
                    setCor(COR_AZUL_CLARO); 
                    printf("[RR] "); // 5 caracteres
                } else { // 'o'
                    setCor(COR_VERDE); 
                    printf("[==] "); // 5 caracteres
                }
                
                setCor(COR_BRANCO); 
                if (j < M - 1) {
                    printf(" | "); // 3 caracteres de espaço
                }
            }
            printf("|"); 
            
            // 3. --- CORREÇÃO DOS BURACOS ---
            //    Desenha a parede na linha de espaçamento
            y++; // Move para a linha de baixo (a linha "par")
            gotoxy(x, y);
            printf("|      |       |       |       |      |");
            y++; // Pula para a próxima linha de poltrona
        }
    }
    // Loop termina. 'y' agora vale 17 (2 + (6*2) + 3 = 17)

    setCor(COR_BRANCO); 
    
    // Fim da sala (Largura 39)
    gotoxy(x, y); // Desenha na linha 17
    printf("+-------------------------------------+");
}

// reservarAssento (Função para reservar o assento)
void reservarAssento(struct Vaga vagas[N][M]) {
    char fileira;
    int coluna, tipo_escolhido;
    int i, j;
    int horas;
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
    
    if (vagas[i][j].status == 'o' || vagas[i][j].status == 'R') {
        
        gotoxy(0, 22);
        printf("Selecione o tipo de veiculos:\n");
        printf(" (1) Carro     [R$ %.2f] por hora\n", preco_inteira);
        printf(" (2) Moto      [R$ %.2f] por hora\n", preco_meia);
        printf(" (3) PCD/Idoso [R$ %.2f] por hora (Apenas Vaga Especial)\n", preco_pcd);
        printf("Opcao: ");
        scanf("%d", &tipo_escolhido);

        if (tipo_escolhido < 1 || tipo_escolhido > 3) {
            printf("Tipo de veiculo invalido. Reserva cancelada.");
            Sleep(1500);
            return;
        }

        if (tipo_escolhido == 3 && vagas[i][j].status != 'R') {
            printf("Erro: Valor para PCD permitido apenas nos assentos [RR].");
            Sleep(2500);
            return; 
        }
        printf("Quantas horas: ");
        scanf("%d", &horas);
        if (tipo_escolhido == 1) novo_valor = preco_inteira * horas;
        else if (tipo_escolhido == 2) novo_valor = preco_meia * horas;
        else if (tipo_escolhido == 3) novo_valor = preco_pcd * horas;

        vagas[i][j].status = 'X'; 
        vagas[i][j].tipo_veiculo = tipo_escolhido;
        vagas[i][j].valor = novo_valor;

        printf("Assento %c%d reservado com sucesso!", fileira, coluna);
        Sleep(1500); 

    } else if (vagas[i][j].status == 'X') {
        printf("Assento %c%d ja esta ocupado.", fileira, coluna);
        Sleep(1500); 
    }
}

// removerAssento (Função para remover assento anteriormente escolhido)
void removerAssento(struct Vaga vagas[N][M]) {
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
    
    if (vagas[i][j].status == 'X') {
        
        if (j == 0) { 
            vagas[i][j].status = 'R'; 
        } else {
            vagas[i][j].status = 'o'; 
        }
        vagas[i][j].tipo_veiculo = 0;
        vagas[i][j].valor = 0.0;
        
        printf("Assento %c%d removido com sucesso!", fileira, coluna);
        Sleep(1500); 
        
    } else { 
        printf("Assento %c%d nao esta ocupado.", fileira, coluna);
        Sleep(1500); 
    }
}

// IngressosVendidos (Função que mostra toda os ingressos comprados, com valores e grafico informando quantidade)
void IngressosVendidos(struct Vaga vagas[N][M]) {
    int i, j, k;
    int total_inteira = 0, total_meia = 0, total_pcd = 0;
    float valor_inteira = 0.0, valor_meia = 0.0, valor_pcd = 0.0;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (vagas[i][j].status == 'X') {
                if (vagas[i][j].tipo_veiculo == 1) {
                    total_inteira++;
                    valor_inteira += vagas[i][j].valor;
                } else if (vagas[i][j].tipo_veiculo == 2) {
                    total_meia++;
                    valor_meia += vagas[i][j].valor;
                } else if (vagas[i][j].tipo_veiculo == 3) {
                    total_pcd++;
                    valor_pcd += vagas[i][j].valor;
                }
            }
        }
    }
    int total_ingressos = total_inteira + total_meia + total_pcd;
    float total_arrecadado = valor_inteira + valor_meia + valor_pcd;

    limpar_texto();
    setCor(COR_BRANCO);
    
    printf("===== RELATORIO DE FATURAMENTO =====\n\n");
    printf("%-7s | %-10s | %3s\n", "Tipo", "Qtd Veiculos", "Valor Arrecadado");
    printf("-------------------------------------------\n");
    printf("%-7s | %3d          | R$ %11.2f\n", "Carro", total_inteira, valor_inteira);
    printf("%-7s | %3d          | R$ %11.2f\n", "Moto", total_meia, valor_meia);
    printf("%-7s | %3d          | R$ %11.2f\n", "PCD", total_pcd, valor_pcd);
    printf("-------------------------------------------\n");
    printf("%-7s | %3d          | R$ %11.2f\n", "TOTAL", total_ingressos, total_arrecadado);
    
    printf("\n----- Grafico de Vendas (Qtd) -----\n");
    printf("Carro....: ");
    for(k = 0; k < total_inteira; k++) { printf("#"); }
    printf("\n");
    
    printf("Moto.....: ");
    for(k = 0; k < total_meia; k++) { printf("#"); }
    printf("\n");
    
    printf("PCD/Idoso: ");
    for(k = 0; k < total_pcd; k++) { printf("#"); }
    printf("\n");
    
    printf("\n\nPressione qualquer tecla para voltar...");
    getch(); 
}

// Main, onde tudo será executado
int main() {
    struct Vaga vagas[N][M];
    
    int i, j;
    int opcao = -1;

    // Chamamos a função do menu
    MenuInicial();

    definirPrecos();

    // Declarando os assentos vazios e de PCD
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (j == 0) { 
                vagas[i][j].status = 'R'; 
            } else { 
                vagas[i][j].status = 'o'; 
            }
            vagas[i][j].tipo_veiculo = 0; 
            vagas[i][j].valor = 0.0;       
        }
    }
    // Aqui vai o switch para escolher o que for necessário
    do {
        Sala(vagas); // puxa-se a função da sala para mostrar ao usuario

        setCor(COR_BRANCO); 

        gotoxy(0, 18);
        printf("===============================\n");
        printf("   RESERVE AQUI SUA VAGA!      \n"); 
        printf("===============================\n");
        printf("1. Reservar Vaga\n");
        printf("2. Remover Vaga \n");
        printf("3. Ver Vagas Vendidas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
        int c; 
        if (scanf("%d", &opcao) != 1) {
            opcao = -1; 
            while ((c = getchar()) != '\n' && c != EOF);
        }
        
        setCor(COR_BRANCO); 

        switch (opcao) { 
            case 1:
                reservarAssento(vagas); // Puxa-se a função de reserva
                break;
            case 2:
                removerAssento(vagas); // Puxa-se a função de remoção de reserva
                break; 
            case 3:
                IngressosVendidos(vagas);  // Puxa-se a função de mostrar os ingressos vendidos
                break;
            case 0:
                system("cls");
                printf("Ate a proxima, Obrigado pela confianca!\n");
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
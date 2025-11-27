// Instituto Federal de Educação do Amazonas – IFAM
// Professor: Sergio Augusto Coelho Bezerra
// Aluno: Eduardo Bandeira Oliveira

#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX_CLIENTES 100
#define MAX_PROFISSIONAIS 20
#define MAX_PROFISSOES 10
#define MAX_ATENDIMENTOS 200

// --- STRUCTS ---

typedef struct { // Struct para definir a data
    int dia;
    int mes;
    int ano;
} Data;

typedef struct { // Struct das caracteristicas de um cliente
    int codigo;
    char nome[100];
    Data dataNasc; // uso da struct data para puxa dia/mes/ano para definir data de nasc
    int idade; 
    char email[100];
    char fone[20];
    char celular[20];
    char logradouro[150];
    int numero;
    char bairro[100];
    char cidade[100];
    char estado[3];
    char cep[10];
} Cliente;

typedef struct{ // Definir uma profissao(se é medico, pediatra etc)
    int codigo;
    char nome[100];
    char sigla[10];
} Profissao;

typedef struct{ // Struct das caracteristicas de um profissional
    Data dataNasc;
    int Prof_codigo; 
    int matricula;
    char tipo[50];
    char cpf[15];
    char nome[100];
    char email[100];
    char fone[20];
    char numRP[20]; 
} Profissional;

typedef struct { // Struct para as caracteristicas um atendimento
    Data dataAtendimento;
    int Prof_matricula; 
    int Cliente_codigo; 
    int numero;
    char descricao[500];
} Atendimento;

// --- GLOBAIS ---

// Funcoes que vao receber a quatnidade total de todos os tipos

Cliente listaClientes[MAX_CLIENTES];
int totalClientes = 0;

Profissional listaProfissionais[MAX_PROFISSIONAIS];
int totalProfissionais = 0;

Profissao listaProfissoes[MAX_PROFISSOES];
int totalProfissoes = 0;

Atendimento listaAtendimentos[MAX_ATENDIMENTOS];
int totalAtendimentos = 0;

// --- FUNÇÕES AUXILIARES ---

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

long transformarData(Data d) {
    return (d.ano * 10000) + (d.mes * 100) + d.dia;
}

// Função gotoxy (Definir posições na tela)
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void MenuInicial() {
    int x = 20; 
    int y = 5;  
    system("cls"); 
    gotoxy(x, y);
    printf("+---------------------------------------------------------------+");
    y++; 
    gotoxy(x, y);
    printf("|Seja Bem Vindo ao Sistema de Atendimento Profissional de Saude!|");
    y++; 
    gotoxy(x, y);
    printf("+---------------------------------------------------------------+");
    y += 2; 
    x += 15;
    gotoxy(x, y);
    printf(" Carregando o sistema, aguarde...");
    Sleep(2500); 
}

// --- FUNÇÕES DETETIVE (BUSCA) ---

// Procura se um codigo de cliente existe
int buscarIndiceCliente(int codigo) {
    for (int i = 0; i < totalClientes; i++){
        if (listaClientes[i].codigo == codigo){
            return i;
        }
    }
    return -1;
}

// Procura se um codigo de profissional existe
int buscarIndiceProfissional(int matricula){
    for (int i = 0; i < totalProfissionais;i++){
        if (listaProfissionais[i].matricula == matricula){
            return i;
        }
    }
    return -1;
}

// Procura se um codigo de um atendimento existe
int buscarIndiceAtendimento(int numero) {
    for (int i = 0; i < totalAtendimentos; i++){
        if (listaAtendimentos[i].numero == numero){
            return i;
        }
    }
    return -1;
}

// Procura se um codigo de profissao existe
int buscarIndiceTipoProfissao(int codigo) {
    for (int i = 0; i < totalProfissoes; i++){
        if (listaProfissoes[i].codigo == codigo){
            return i;
        }
    }
    return -1;
}

// --- FUNÇÕES DE CADASTRO ---

// Funcao para cadastro do cliente
void cadastrarCliente() {
    system("cls"); 
    printf("--- TELA DE CADASTRO DE CLIENTE ---\n\n");
    if (totalClientes >= MAX_CLIENTES) {
        printf("ERRO: Limite maximo de clientes atingido!\n");
        printf("\n\nPressione Enter para voltar ao menu...");
        limparBufferEntrada();
        getchar();
        return;
    }

    Cliente novoCliente; // Chama a struct fazendo uma nova variavel novoCliente

// -- Leitura das caracteristicas do cliente --
    printf("Digite o Codigo: ");
    scanf("%d", &novoCliente.codigo);

    printf("Digite o Nome: ");
    scanf(" %[^\n]", novoCliente.nome);

    printf("Digite o Email: ");
    scanf(" %[^\n]", novoCliente.email);
    
    printf("Digite o Telefone-Fixo: ");
    scanf(" %[^\n]", novoCliente.fone);
    
    printf("Digite o Celular: ");
    scanf(" %[^\n]", novoCliente.celular);

    printf("Digite a Data de Nascimento (DD MM AAAA): ");
    scanf("%d %d %d", &novoCliente.dataNasc.dia, 
                      &novoCliente.dataNasc.mes, 
                      &novoCliente.dataNasc.ano);
    
    printf("Digite a sua Idade: ");
    scanf("%d", &novoCliente.idade);

    printf("Digite seu Estado: ");
    scanf(" %[^\n]", novoCliente.estado);
    
    printf("Digite sua Cidade: ");
    scanf(" %[^\n]", novoCliente.cidade);

    printf("Digite seu CEP: ");
    scanf(" %[^\n]", novoCliente.cep);

    printf("Digite seu Bairro: ");
    scanf(" %[^\n]",novoCliente.bairro);

    printf("Digite seu Logradouro(Rua): ");
    scanf(" %[^\n]", novoCliente.logradouro);

    printf("Digite o Numero da sua Casa: ");
    scanf(" %d", &novoCliente.numero);

    listaClientes[totalClientes] = novoCliente;
    totalClientes++;

    printf("\n>>> Cliente cadastrado com sucesso! <<<\n");
    printf("\n\nPressione Enter para voltar ao menu...");
    limparBufferEntrada();
    getchar();
} 

// Funcao para cadastro do profissional

void cadastrarProfissional() {
    system("cls"); 
    printf("--- TELA DE CADASTRO DE PROFISSIONAL ---\n\n");
    
    if (totalProfissionais >= MAX_PROFISSIONAIS) {
        printf("ERRO: Limite maximo de profissionais atingido!\n");
        printf("\n\nPressione Enter para voltar...");
        limparBufferEntrada(); 
        getchar();
        return;
    }

    Profissional novoProfissional; // Chama a struct fazendo uma nova variavel novoProfissional

    // Validação da Profissão
    int codigoProfissaoTemp;
    
    // Mostra as profissoes disponiveis antes de pedir
    if (totalProfissoes > 0) {
        printf("--- Profissoes Disponiveis ---\n");
        for(int i=0; i<totalProfissoes; i++) {
            printf("[%d] %s\n", listaProfissoes[i].codigo, listaProfissoes[i].nome);
        }
        printf("------------------------------\n");
    } else {
        printf("AVISO: Nenhuma profissao cadastrada ainda (Opcao 2 no menu)!\n");
    }

    printf("Digite o Codigo da Profissao: ");
    scanf("%d", &codigoProfissaoTemp);

    // Verifica se existe
    int indiceProfissao = buscarIndiceTipoProfissao(codigoProfissaoTemp);

    if (indiceProfissao == -1) {
        printf("\nERRO: O codigo de profissao %d nao existe!\n", codigoProfissaoTemp);
        printf("Por favor, cadastre o TIPO DE PROFISSAO primeiro (Opcao 2).\n");
        printf("\nCadastro cancelado. Pressione Enter...");
        limparBufferEntrada();
        getchar();
        return; 
    }

    // Se passou atribui o código valido
    novoProfissional.Prof_codigo = codigoProfissaoTemp;
    
    // Puxa o nome da profissão automaticamente para o campo 'tipo'
    strcpy(novoProfissional.tipo, listaProfissoes[indiceProfissao].nome);

    // -- Leitura das caracteristicas do profissional --

    printf("Digite a Matricula: ");
    scanf("%d", &novoProfissional.matricula);

    printf("Digte o CPF: ");
    scanf(" %[^\n]", novoProfissional.cpf);

    printf("Digite o Nome: ");
    scanf(" %[^\n]", novoProfissional.nome); 

    printf("Digite o Numero do Registro (NRP, ex: 12345-AM): ");
    scanf(" %[^\n]", novoProfissional.numRP); 

    printf("Digite a data de nascimento (DD MM AAAA): ");
    scanf("%d %d %d", &novoProfissional.dataNasc.dia, 
                      &novoProfissional.dataNasc.mes, 
                      &novoProfissional.dataNasc.ano);

    printf("Digite o Email: ");
    scanf(" %[^\n]", novoProfissional.email);
    
    printf("Digite o Numero para Contato: ");
    scanf(" %[^\n]", novoProfissional.fone);

    listaProfissionais[totalProfissionais] = novoProfissional;
    totalProfissionais++;

    printf("\n>>> Profissional cadastrado com sucesso! <<<\n");
    printf("\n\nPressione Enter para voltar ao menu...");
    limparBufferEntrada();
    getchar();
}

// Funcao para cadastrar uma profissao
void cadastrarProfissao() {
    system("cls");
    printf("--- CADASTRO DE TIPO DE PROFISSAO ---\n\n");

    if (totalProfissoes >= MAX_PROFISSOES) {
        printf("ERRO: Limite de profissoes atingido!\n");
        printf("\n\nPressione Enter para voltar...");
        limparBufferEntrada();
        getchar();
        return;
    }

    Profissao novaProfissao; // Chama a struct fazendo uma nova variavel novaProfissao
    int codigoTemp;

    printf("Digite o Codigo (ID) da Profissao: ");
    scanf("%d", &codigoTemp);

    // Verifica se ja nao tem outro com o mesmo codigo
    if (buscarIndiceTipoProfissao(codigoTemp) != -1) {
        printf("\nERRO CRITICO: O codigo %d ja esta sendo usado por outra profissao!\n", codigoTemp);
        printf("Cadastro cancelado.\n");
        printf("\n\nPressione Enter para voltar ao menu...");
        limparBufferEntrada();
        getchar();
        return;
    }

    novaProfissao.codigo = codigoTemp;
// -- Leitura das caracteristicas da Profissao --
    printf("Digite o Nome (ex: Medico, Dentista): ");
    scanf(" %[^\n]", novaProfissao.nome);

    printf("Digite a Sigla do Conselho (ex: CRM, CRO): ");
    scanf(" %[^\n]", novaProfissao.sigla);

    listaProfissoes[totalProfissoes] = novaProfissao;
    totalProfissoes++;

    printf("\n>>> Profissao cadastrada com sucesso! <<<\n");
    printf("\n\nPressione Enter para voltar ao menu...");
    limparBufferEntrada();
    getchar();
}

// Funcao para cadastrar um Atendimento
void cadastrarAtendimento(){
    system("cls");
    printf("--- TELA DE CADASTRO DE ATENDIMENTO ---\n\n");
    
    if (totalAtendimentos >= MAX_ATENDIMENTOS) {
        printf("ERRO: Limite maximo de atendimentos atingido!\n");
        printf("\n\nPressione Enter para voltar ao menu...");
        limparBufferEntrada();
        getchar();
        return;
    }
    Atendimento novoAtendimento; // Chama a struct fazendo uma nova variavel novaAtendimento

    // -- Leitura das caracteristicas do Atendimento --
    printf("Insira o Numero do Atendimento (ID): ");
    scanf("%d", &novoAtendimento.numero);

    printf("Insira o codigo do cliente: ");
    scanf("%d", &novoAtendimento.Cliente_codigo);

    printf("Insira a matricula do profissional: ");
    scanf("%d", &novoAtendimento.Prof_matricula);

    printf("Digite a data do atendimento (DD MM AAAA): ");
    scanf("%d %d %d", &novoAtendimento.dataAtendimento.dia, 
                      &novoAtendimento.dataAtendimento.mes, 
                      &novoAtendimento.dataAtendimento.ano);

    printf("Insira uma descricao para o atendimento: \n");
    scanf(" %[^\n]", novoAtendimento.descricao);

    listaAtendimentos[totalAtendimentos] = novoAtendimento;
    totalAtendimentos++;

    printf("\n>>> Atendimento cadastrado com sucesso! <<<\n");
    printf("\n\nPressione Enter para voltar ao menu...");
    limparBufferEntrada();
    getchar();
}

// --- FUNÇÕES DE EXCLUSÃO ---

void excluirCliente() {
    system("cls");
    printf("--- EXCLUSAO DE CLIENTE ---\n\n");

    if (totalClientes == 0) {
        printf("Erro: Nao ha clientes para excluir.\n");
        printf("\n\nPressione Enter para voltar...");
        limparBufferEntrada();
        getchar();
        return;
    }

    printf("Clientes Disponiveis:\n");
    printf("CODIGO | NOME\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i < totalClientes; i++) {
        printf("%-6d | %s\n", listaClientes[i].codigo, listaClientes[i].nome);
    }
    printf("------------------------------------------------\n");

    int codigo;
    printf("Digite o CODIGO do cliente que deseja excluir: ");
    scanf("%d", &codigo);

    int indice = buscarIndiceCliente(codigo);

    if (indice == -1) {
        printf("\nErro: Cliente com codigo %d nao encontrado.\n", codigo);
    } else {
        printf("\nCliente encontrado: %s\n", listaClientes[indice].nome);
        printf("Tem certeza que deseja excluir? (1-Sim / 2-Nao): ");
        int confirmacao;
        scanf("%d", &confirmacao);

        if (confirmacao == 1) {
            for (int i = indice; i < totalClientes - 1; i++) {
                listaClientes[i] = listaClientes[i + 1];
            }
            totalClientes--;
            printf("\n>>> Cliente excluido com sucesso! <<<\n");
        } else {
            printf("\nOperacao cancelada.\n");
        }
    }

    printf("\n\nPressione Enter para voltar ao menu...");
    limparBufferEntrada();
    getchar();
}

void excluirProfissional() {
    system("cls");
    printf("--- EXCLUSAO DE PROFISSIONAL ---\n\n");

    if (totalProfissionais == 0) {
        printf("Erro: Nao ha profissionais para excluir.\n");
        printf("\n\nPressione Enter para voltar...");
        limparBufferEntrada();
        getchar();
        return;
    }

    printf("Profissionais Disponiveis:\n");
    printf("MATR.  | NOME                 | TIPO\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < totalProfissionais; i++) {
        printf("%-6d | %-20s | %s\n", 
               listaProfissionais[i].matricula, 
               listaProfissionais[i].nome,
               listaProfissionais[i].tipo);
    }
    printf("--------------------------------------------------\n\n");

    int matricula;
    printf("Digite a MATRICULA do profissional que deseja excluir: ");
    scanf("%d", &matricula);

    int indice = buscarIndiceProfissional(matricula);

    if (indice == -1) {
        printf("\nErro: Profissional com matricula %d nao encontrado.\n", matricula);
    } else {
        printf("\nProfissional encontrado: %s\n", listaProfissionais[indice].nome);
        printf("Tem certeza que deseja excluir? (1-Sim / 2-Nao): ");
        int confirmacao;
        scanf("%d", &confirmacao);

        if (confirmacao == 1) {
            for (int i = indice; i < totalProfissionais - 1; i++) {
                listaProfissionais[i] = listaProfissionais[i + 1];
            }
            totalProfissionais--;
            printf("\n>>> Profissional excluido com sucesso! <<<\n");
        } else {
            printf("\nOperacao cancelada.\n");
        }
    }
    printf("\n\nPressione Enter para voltar ao menu...");
    limparBufferEntrada();
    getchar();
}

void excluirAtendimento() {
    system("cls");
    printf("--- EXCLUSAO DE ATENDIMENTO ---\n\n");

    if (totalAtendimentos == 0) {
        printf("Erro: Nao ha atendimentos para excluir.\n");
        printf("\n\nPressione Enter para voltar...");
        limparBufferEntrada();
        getchar();
        return;
    }

    printf("Atendimentos Cadastrados:\n");
    printf("ID   | DATA       | CLIENTE              | PROFISSIONAL\n");
    printf("--------------------------------------------------------------\n");
    
    for (int i = 0; i < totalAtendimentos; i++) {
        int idxCli = buscarIndiceCliente(listaAtendimentos[i].Cliente_codigo);
        int idxProf = buscarIndiceProfissional(listaAtendimentos[i].Prof_matricula);
        
        char *nomeCli = (idxCli != -1) ? listaClientes[idxCli].nome : "[Excluido]";
        char *nomeProf = (idxProf != -1) ? listaProfissionais[idxProf].nome : "[Excluido]";

        printf("%-4d | %02d/%02d/%04d | %-20.20s | %-20.20s\n", 
               listaAtendimentos[i].numero,
               listaAtendimentos[i].dataAtendimento.dia,
               listaAtendimentos[i].dataAtendimento.mes,
               listaAtendimentos[i].dataAtendimento.ano,
               nomeCli,
               nomeProf);
    }
    printf("--------------------------------------------------------------\n\n");

    int numero;
    printf("Digite o NUMERO do atendimento que deseja excluir: ");
    scanf("%d", &numero);

    int indice = buscarIndiceAtendimento(numero);

    if (indice == -1) {
        printf("\nErro: Atendimento numero %d nao encontrado.\n", numero);
    } else {
        printf("\nAtendimento encontrado (Cliente Cod: %d, Prof Mat: %d)\n", 
               listaAtendimentos[indice].Cliente_codigo, 
               listaAtendimentos[indice].Prof_matricula);
        printf("Tem certeza que deseja excluir? (1-Sim / 2-Nao): ");
        int confirmacao;
        scanf("%d", &confirmacao);

        if (confirmacao == 1) {
            for (int i = indice; i < totalAtendimentos - 1; i++) {
                listaAtendimentos[i] = listaAtendimentos[i + 1];
            }
            totalAtendimentos--;
            printf("\n>>> Atendimento excluido com sucesso! <<<\n");
        } else {
            printf("\nOperacao cancelada.\n");
        }
    }
    printf("\n\nPressione Enter para voltar ao menu...");
    limparBufferEntrada();
    getchar();
}

// --- FUNÇÕES DE LISTAGEM ---

void exibirCliente(Cliente c) {
    printf("---------------------------------------------------------------------------\n");
    printf("Codigo: %d\n", c.codigo);
    printf("Nome: %s\n", c.nome);
    printf("Telefone: %s | Celular: %s\n", c.fone, c.celular);
    printf("Email: %s\n", c.email);
    printf("Nascimento: %d/%d/%d (%d anos)\n", c.dataNasc.dia, c.dataNasc.mes, c.dataNasc.ano, c.idade);
    printf("Endereco: %s, %d - %s, %s - %s\n", c.logradouro, c.numero, c.bairro, c.cidade, c.estado);
    printf("---------------------------------------------------------------------------\n");
}

void listarClientes() {
    system("cls");
    printf("--- LISTA DE CLIENTES CADASTRADOS ---\n\n");
    if (totalClientes == 0) {
        printf(">>> Nenhum cliente cadastrado no sistema.\n");
    } else {
        for (int i = 0; i < totalClientes; i++) {
            exibirCliente(listaClientes[i]);
        }
        printf("\nTotal de clientes: %d\n", totalClientes);
    }
    printf("\n\nPressione Enter para voltar ao menu...");
    limparBufferEntrada();
    getchar();
}

void listarProfissionais() {
    system("cls");
    printf("--- LISTA DE PROFISSIONAIS CADASTRADOS ---\n\n");
    if (totalProfissionais == 0) {
        printf(">>> Nenhum profissional cadastrado no sistema.\n");
    } else {
        printf("%-10s | %-25s | %-15s | %-10s | %-15s\n", 
               "MATRICULA", "NOME", "TIPO", "REGISTRO", "FONE");
        printf("--------------------------------------------------------------------------------------\n");
        for (int i = 0; i < totalProfissionais; i++) {
            printf("%-10d | %-25s | %-15s | %-10s | %-15s\n", 
                   listaProfissionais[i].matricula, 
                   listaProfissionais[i].nome, 
                   listaProfissionais[i].tipo,
                   listaProfissionais[i].numRP,
                   listaProfissionais[i].fone);
        }
        printf("--------------------------------------------------------------------------------------\n");
        printf("Total: %d profissionais cadastrados.\n", totalProfissionais);
    }
    printf("\n\nPressione Enter para voltar ao menu...");
    limparBufferEntrada(); 
    getchar();
}

void listarProfissoes() {
    system("cls");
    printf("--- LISTA DE PROFISSOES CADASTRADAS ---\n\n");
    if (totalProfissoes == 0) {
        printf(">>> Nenhuma profissao cadastrada.\n");
    } else {
        printf("CODIGO \t| SIGLA \t| NOME\n");
        printf("------------------------------------------------\n");
        for (int i = 0; i < totalProfissoes; i++) {
            printf("%d \t| %s \t\t| %s\n", 
                   listaProfissoes[i].codigo, 
                   listaProfissoes[i].sigla, 
                   listaProfissoes[i].nome);
        }
        printf("------------------------------------------------\n");
        printf("Total: %d profissoes\n", totalProfissoes);
    }
    printf("\n\nPressione Enter para voltar ao menu...");
    limparBufferEntrada();
    getchar();
}

void listarAtendimentoGeral() {
    system("cls");
    printf("--- RELATORIO: ATENDIMENTO GERAL ---\n\n");

    if (totalAtendimentos == 0) {
        printf(">>> Nenhum atendimento cadastrado no sistema.\n");
    } else {
        for (int i = 0; i < totalAtendimentos; i++) {
            Atendimento att = listaAtendimentos[i];
            int clienteID = att.Cliente_codigo;
            int profID = att.Prof_matricula;
            
            int indiceCliente = buscarIndiceCliente(clienteID);
            int indiceProf = buscarIndiceProfissional(profID);

            printf("--------------------------------------------------------------------------\n");
            printf("Atendimento Numero: %d\n", att.numero);
            printf("Data: %02d/%02d/%d\n", att.dataAtendimento.dia,
                                           att.dataAtendimento.mes,
                                           att.dataAtendimento.ano);

            if (indiceCliente == -1) {
                printf("Cliente: [Codigo %d Nao Encontrado]\n", clienteID);
            } else {
                printf("Cliente: %s\n", listaClientes[indiceCliente].nome);
            }

            if (indiceProf == -1) {
                printf("Profissional: [Matricula %d Nao Encontrada]\n", profID);
            } else {
                printf("Profissional: %s\n", listaProfissionais[indiceProf].nome);
            } 
            printf("Descricao: %s\n", att.descricao);   
        }
        printf("--------------------------------------------------------------------------\n");
        printf("\nTotal de Atendimentos: %d\n", totalAtendimentos);
    }
    printf("\n\nPressione Enter para voltar ao menu...");
    limparBufferEntrada(); 
    getchar();
}   

void listarAniversariantesPorMes() {
    system("cls");
    int mesEscolhido;
    printf("Digite o mes que deseja consultar (1-12): ");
    scanf("%d", &mesEscolhido);
    limparBufferEntrada(); 

    if (mesEscolhido < 1 || mesEscolhido > 12) {
        printf("ERRO: Mes invalido. Digite um numero entre 1 e 12.\n");
        printf("\n\nPressione Enter para voltar ao menu...");
        getchar(); 
        return;
    }

    printf("\n--- ANIVERSARIANTES DO MES %d ---\n\n", mesEscolhido);
    int encontrados = 0;

    printf("=== CLIENTES ===\n");
    int clientesEncontrados = 0;
    for (int i = 0; i < totalClientes; i++) {
        if (listaClientes[i].dataNasc.mes == mesEscolhido) {
            printf("-> COD: %d | NOME: %s\n", listaClientes[i].codigo, listaClientes[i].nome);
            printf("   Dia: %02d | Fone: %s | Cel: %s\n", 
                   listaClientes[i].dataNasc.dia, 
                   listaClientes[i].fone, 
                   listaClientes[i].celular);
            printf("   Email: %s\n", listaClientes[i].email);
            printf("   --------------------------------------------------\n");
            
            encontrados++;
            clientesEncontrados++;
        }
    }
    if (clientesEncontrados == 0) {
        printf("Nenhum cliente aniversariante neste mes.\n");
    }

    printf("\n=== PROFISSIONAIS ===\n");
    int profEncontrados = 0;
    for (int i = 0; i < totalProfissionais; i++) {
        if (listaProfissionais[i].dataNasc.mes == mesEscolhido) {
            printf("-> MATR: %d | NOME: %s\n", listaProfissionais[i].matricula, listaProfissionais[i].nome);
            printf("   Dia: %02d | Fone: %s\n", 
                   listaProfissionais[i].dataNasc.dia, 
                   listaProfissionais[i].fone);
            printf("   Email: %s\n", listaProfissionais[i].email);
            printf("   --------------------------------------------------\n");

            encontrados++;
            profEncontrados++;
        }
    }
    if (profEncontrados == 0) {
        printf("Nenhum profissional aniversariante neste mes.\n");
    }
    
    printf("\n==================================================\n");
    if (encontrados == 0) {
        printf("Total: Nenhum aniversariante encontrado no mes %d.\n", mesEscolhido);
    } else {
        printf("Total Geral: %d aniversariante(s) encontrado(s).\n", encontrados);
    }

    printf("\n\nPressione Enter para voltar ao menu...");
    getchar();
}

void relatorioEstatistica() {
    system("cls");
    printf("--- ESTATISTICA DE ATENDIMENTOS POR PROFISSIONAL ---\n\n");

    if (totalAtendimentos == 0) {
        printf(">>> Nao ha atendimentos cadastrados para gerar estatistica.\n");
        printf("\n\nPressione Enter para voltar ao menu...");
        limparBufferEntrada();
        getchar();
        return;
    }

    Data dInicio, dFim;
    printf("Digite a DATA INICIAL do periodo (DD MM AAAA): ");
    scanf("%d %d %d", &dInicio.dia, &dInicio.mes, &dInicio.ano);
    
    printf("Digite a DATA FINAL do periodo (DD MM AAAA): ");
    scanf("%d %d %d", &dFim.dia, &dFim.mes, &dFim.ano);

    long inicioNum = transformarData(dInicio);
    long fimNum = transformarData(dFim);

    printf("\n------------------------------------------------------\n");
    printf("RESULTADO (Periodo: %02d/%02d/%d ate %02d/%02d/%d)\n", 
           dInicio.dia, dInicio.mes, dInicio.ano, 
           dFim.dia, dFim.mes, dFim.ano);
    printf("--------------------------------------------------------\n");

    int totalGeralNoPeriodo = 0;

    for (int i = 0; i < totalProfissionais; i++) {
        int contador = 0;
        int matriculaAtual = listaProfissionais[i].matricula;

        for (int j = 0; j < totalAtendimentos; j++) {
            if (listaAtendimentos[j].Prof_matricula == matriculaAtual) {
                long dataAtendimentoNum = transformarData(listaAtendimentos[j].dataAtendimento);
                if (dataAtendimentoNum >= inicioNum && dataAtendimentoNum <= fimNum) {
                    contador++;
                }
            }
        }
        printf("Profissional: %-20s | Atendimentos: %d\n", 
               listaProfissionais[i].nome, contador);
        totalGeralNoPeriodo += contador;
    }

    printf("--------------------------------------------------------\n");
    printf("TOTAL GERAL NO PERIODO: %d\n", totalGeralNoPeriodo);

    printf("\n\nPressione Enter para voltar ao menu...");
    limparBufferEntrada();
    getchar();
}

void relatorioAtendimentosPorMes() {
    system("cls");
    printf("--- RELATORIO: ATENDIMENTOS POR MES EM UM ANO ---\n\n");

    if (totalAtendimentos == 0) {
        printf(">>> Nao ha atendimentos cadastrados.\n");
        printf("\n\nPressione Enter para voltar ao menu...");
        limparBufferEntrada();
        getchar();
        return;
    }

    int ano;
    printf("Digite o ANO que deseja consultar (ex: 2025): ");
    scanf("%d", &ano);

    printf("\nAno Base: %d\n", ano);
    printf("MES\t| QUANTIDADE\n");
    printf("--------------------\n");

    int totalAno = 0;
    for (int m = 1; m <= 12; m++) {
        int qtdMes = 0;
        for (int i = 0; i < totalAtendimentos; i++) {
            if (listaAtendimentos[i].dataAtendimento.ano == ano &&
                listaAtendimentos[i].dataAtendimento.mes == m) {
                qtdMes++;
            }
        }
        printf("%02d\t| %d\n", m, qtdMes);
        totalAno += qtdMes;
    }
    printf("--------------------\n");
    printf("TOTAL\t| %d\n", totalAno);

    printf("\n\nPressione Enter para voltar ao menu...");
    limparBufferEntrada();
    getchar();
}

void alterarCliente() {
    system("cls");
    printf("--- ALTERACAO DE DADOS DO CLIENTE ---\n\n");

    if (totalClientes == 0) {
        printf("Erro: Nao ha clientes cadastrados.\n");
        printf("\n\nPressione Enter para voltar...");
        limparBufferEntrada();
        getchar();
        return;
    }

    int codigo;
    printf("Digite o CODIGO do cliente que deseja alterar: ");
    scanf("%d", &codigo);

    int i = buscarIndiceCliente(codigo);

    if (i == -1) {
        printf("\nErro: Cliente com codigo %d nao encontrado.\n", codigo);
    } else {
        printf("\nCliente encontrado: %s\n", listaClientes[i].nome);
        printf("------------------------------------------------\n");
        printf("ATENCAO: Digite os novos dados (O Codigo nao pode ser mudado).\n\n");

        // Aqui trocamos os dados na posição [i]
        printf("Novo Nome (Atual: %s): ", listaClientes[i].nome);
        scanf(" %[^\n]", listaClientes[i].nome);

        printf("Novo Email (Atual: %s): ", listaClientes[i].email);
        scanf(" %[^\n]", listaClientes[i].email);
        
        printf("Novo Fone (Atual: %s): ", listaClientes[i].fone);
        scanf(" %[^\n]", listaClientes[i].fone);
        
        printf("Novo Celular (Atual: %s): ", listaClientes[i].celular);
        scanf(" %[^\n]", listaClientes[i].celular);

        printf("Nova Data Nasc (DD MM AAAA): ");
        scanf("%d %d %d", &listaClientes[i].dataNasc.dia, 
                          &listaClientes[i].dataNasc.mes, 
                          &listaClientes[i].dataNasc.ano);
        
        printf("Nova Idade: ");
        scanf("%d", &listaClientes[i].idade);

        printf("Novo Estado: ");
        scanf(" %[^\n]", listaClientes[i].estado);
        
        printf("Nova Cidade: ");
        scanf(" %[^\n]", listaClientes[i].cidade);

        printf("Novo CEP: ");
        scanf(" %[^\n]", listaClientes[i].cep);

        printf("Novo Bairro: ");
        scanf(" %[^\n]",listaClientes[i].bairro);

        printf("Novo Logradouro: ");
        scanf(" %[^\n]", listaClientes[i].logradouro);

        printf("Novo Numero da Casa: ");
        scanf(" %d", &listaClientes[i].numero);

        printf("\n>>> Dados alterados com sucesso! <<<\n");
    }

    printf("\n\nPressione Enter para voltar ao menu...");
    limparBufferEntrada();
    getchar();
}

void alterarProfissional() {
    system("cls");
    printf("--- ALTERACAO DE DADOS DO PROFISSIONAL ---\n\n");

    if (totalProfissionais == 0) {
        printf("Erro: Nao ha profissionais cadastrados.\n");
        printf("\n\nPressione Enter para voltar...");
        limparBufferEntrada();
        getchar();
        return;
    }

    int matricula;
    printf("Digite a MATRICULA do profissional que deseja alterar: ");
    scanf("%d", &matricula);

    int i = buscarIndiceProfissional(matricula);

    if (i == -1) {
        printf("\nErro: Profissional com matricula %d nao encontrado.\n", matricula);
    } else {
        printf("\nProfissional encontrado: %s\n", listaProfissionais[i].nome);
        printf("------------------------------------------------\n");
        printf("ATENCAO: Digite os novos dados.\n\n");

        // Validacao rapida do tipo de profissao
        int codigoProfissaoTemp;
        printf("Novo Codigo da Profissao (Atual: %d): ", listaProfissionais[i].Prof_codigo);
        scanf("%d", &codigoProfissaoTemp);
        
        int idxTipo = buscarIndiceTipoProfissao(codigoProfissaoTemp);
        if (idxTipo != -1) {
            listaProfissionais[i].Prof_codigo = codigoProfissaoTemp;
            strcpy(listaProfissionais[i].tipo, listaProfissoes[idxTipo].nome); 
        } else {
            printf("AVISO: Codigo de profissao invalido. Mantendo o anterior.\n");
        }

        printf("Novo CPF (Atual: %s): ", listaProfissionais[i].cpf);
        scanf(" %[^\n]", listaProfissionais[i].cpf);

        printf("Novo Nome (Atual: %s): ", listaProfissionais[i].nome);
        scanf(" %[^\n]", listaProfissionais[i].nome); 

        printf("Novo Num Registro (Atual: %s): ", listaProfissionais[i].numRP);
        scanf(" %[^\n]", listaProfissionais[i].numRP); 

        printf("Nova Data Nasc (DD MM AAAA): ");
        scanf("%d %d %d", &listaProfissionais[i].dataNasc.dia, 
                          &listaProfissionais[i].dataNasc.mes, 
                          &listaProfissionais[i].dataNasc.ano);

        printf("Novo Email (Atual: %s): ", listaProfissionais[i].email);
        scanf(" %[^\n]", listaProfissionais[i].email);
        
        printf("Novo Fone (Atual: %s): ", listaProfissionais[i].fone);
        scanf(" %[^\n]", listaProfissionais[i].fone);

        printf("\n>>> Dados alterados com sucesso! <<<\n");
    }

    printf("\n\nPressione Enter para voltar ao menu...");
    limparBufferEntrada();
    getchar();
}

void alterarAtendimento() {
    system("cls");
    printf("--- ALTERACAO DE ATENDIMENTO ---\n\n");

    if (totalAtendimentos == 0) {
        printf("Erro: Nao ha atendimentos para alterar.\n");
        printf("\n\nPressione Enter para voltar...");
        limparBufferEntrada();
        getchar();
        return;
    }

    int numero;
    printf("Digite o NUMERO (ID) do atendimento que deseja alterar: ");
    scanf("%d", &numero);

    int i = buscarIndiceAtendimento(numero);

    if (i == -1) {
        printf("\nErro: Atendimento numero %d nao encontrado.\n", numero);
    } else {
        printf("\nAtendimento encontrado.\n");
        printf("------------------------------------------------\n");
        
        printf("Novo Codigo do Cliente (Atual: %d): ", listaAtendimentos[i].Cliente_codigo);
        scanf("%d", &listaAtendimentos[i].Cliente_codigo);

        printf("Nova Matricula Profissional (Atual: %d): ", listaAtendimentos[i].Prof_matricula);
        scanf("%d", &listaAtendimentos[i].Prof_matricula);

        printf("Nova Data (DD MM AAAA): ");
        scanf("%d %d %d", &listaAtendimentos[i].dataAtendimento.dia, 
                          &listaAtendimentos[i].dataAtendimento.mes, 
                          &listaAtendimentos[i].dataAtendimento.ano);

        printf("Nova Descricao: ");
        scanf(" %[^\n]", listaAtendimentos[i].descricao);

        printf("\n>>> Atendimento alterado com sucesso! <<<\n");
    }

    printf("\n\nPressione Enter para voltar ao menu...");
    limparBufferEntrada();
    getchar();
}

// --- FUNÇÃO MAIN ---

int main(){
    int opcao;
    MenuInicial(); 
    do {
        system("cls");
        printf("====== Sistema de Gestao de Saude ======\n");
        
        printf("--- CADASTROS ---\n");
        printf("(1) Cadastrar Cliente\n");
        printf("(2) Cadastrar Tipo de Profissao\n"); 
        printf("(3) Cadastrar Profissional\n");
        printf("(4) Cadastrar Atendimento\n");
        
        printf("\n--- RELATORIOS ---\n");
        printf("(5) Listar Profissionais (Tabela)\n");
        printf("(6) Listar Atendimentos (Geral)\n");
        printf("(7) Listar Clientes\n");
        printf("(8) Listar Tipos de Profissao\n");
        printf("(9) Aniversariantes por Mes\n");
        printf("(10) Estatistica de Atendimentos (Periodo)\n");
        printf("(11) Atendimentos por Mes (Ano)\n"); 
        
        printf("\n--- EXCLUSAO ---\n");
        printf("(12) Excluir Cliente\n");
        printf("(13) Excluir Profissional\n");
        printf("(14) Excluir Atendimento\n");

        printf("\n--- ALTERACAO (EDICAO) ---\n"); 
        printf("(15) Alterar Cliente\n");
        printf("(16) Alterar Profissional\n");
        printf("(17) Alterar Atendimento\n");
        
        printf("\n(0) Sair\n");
        printf("========================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao){
            // --- CADASTROS ---
            case 1: 
                cadastrarCliente();
                break;
            case 2:
                cadastrarProfissao();
                break;
            case 3:
                cadastrarProfissional();
                break;
            case 4:
                cadastrarAtendimento();
                break; 
            
            // --- RELATORIOS ---
            case 5:
                listarProfissionais(); 
                break;  
            case 6:
                listarAtendimentoGeral();
                break;
            case 7:
                listarClientes();
                break;
            case 8:
                listarProfissoes();
                break;
            case 9:
                listarAniversariantesPorMes();
                break;
            case 10:
                relatorioEstatistica();
                break;
            case 11:
                relatorioAtendimentosPorMes();
                break;

            // --- EXCLUSAO ---
            case 12:
                excluirCliente();
                break;
            case 13:
                excluirProfissional();
                break;
            case 14:
                excluirAtendimento();
                break;

            // --- ALTERACAO ---
            case 15:
                alterarCliente();
                break;
            case 16:
                alterarProfissional();
                break;
            case 17:
                alterarAtendimento();
                break;

            // --- SAIDA ---
            case 0:
                printf("Saindo do sistema...\n");
                Sleep(1000);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                Sleep(1000);
                break;
        }
    } while (opcao != 0);

    return 0;
}
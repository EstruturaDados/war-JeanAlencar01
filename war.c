// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_COR 20

typedef struct {
    char nome[MAX_NOME];
    char corExercito[MAX_COR];
    int numeroTropas;
} Territorio;

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
void cadastrarTerritorios(Territorio *territorios);
void exibirTerritorios(const Territorio *territorios);
void simularBatalha(Territorio *territorios, int atacante, int defensor);
void realizarAtaque(Territorio *territorios);
int verificarMissao(const Territorio *territorios);

// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:


int verificarMissao(const Territorio *territorios) {
    int territoriosConquistados = 0;
    int exercitoVerdeDestruido = 1;
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        if (strcmp(territorios[i].corExercito, "Verde") == 0 && territorios[i].numeroTropas > 0) {
            exercitoVerdeDestruido = 0;
        }
        if (territorios[i].numeroTropas > 5) {
            territoriosConquistados++;
        }
    }
    if (exercitoVerdeDestruido && territoriosConquistados >= 3) {
        return 1;
    }
    return 0;
}

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    srand(time(NULL)); // Inicializa a semente para geração de números aleatórios
    Territorio territorios[MAX_TERRITORIOS];

    cadastrarTerritorios(territorios);
    
    int opcao;
    do {
        printf("Menu:\n");
        printf("1. Exibir territórios\n");
        printf("2. Realizar ataque\n");
        printf("3. Verificar missão\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Consumir o caractere newline

        switch (opcao) {
            case 1:
                exibirTerritorios(territorios);
                break;
            case 2:
                realizarAtaque(territorios);
                exibirTerritorios(territorios);
                if (verificarMissao(territorios)) {
                    printf("Missão cumprida! Você venceu!\n");
                    opcao = 0;
                }
                break;
            case 3:
                if (verificarMissao(territorios)) {
                    printf("Missão cumprida! Você venceu!\n");
                    opcao = 0;
                } else {
                    printf("Missão ainda não cumprida.\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    return 0;
}

void cadastrarTerritorios(Territorio *territorios) {
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Digite o nome do território %d: ", i + 1);
        fgets(territorios[i].nome, MAX_NOME, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0;

        printf("Digite a cor do exército dominante no território %d: ", i + 1);
        fgets(territorios[i].corExercito, MAX_COR, stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = 0;

        printf("Digite o número de tropas no território %d: ", i + 1);
        scanf("%d", &territorios[i].numeroTropas);
        getchar(); // Limpa o buffer de entrada
    }

}

void exibirTerritorios(const Territorio *territorios) {
    printf("Estado atual do mapa:\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército dominante: %s\n", territorios[i].corExercito);
        printf("Número de tropas: %d\n", territorios[i].numeroTropas);
        printf("\n");
    }

    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.
}


void realizarAtaque(Territorio *territorios) {
    int atacante, defensor;
    printf("Digite o número do território atacante (1-%d): ", MAX_TERRITORIOS);
    scanf("%d", &atacante);
    printf("Digite o número do território defensor (1-%d): ", MAX_TERRITORIOS);
    scanf("%d", &defensor);
    getchar(); // Limpa o buffer de entrada

    if (atacante < 1 || atacante > MAX_TERRITORIOS || defensor < 1 || defensor > MAX_TERRITORIOS) {
        printf("Número de território inválido!\n");
        return;
    }


        simularBatalha(territorios, atacante - 1, defensor - 1);
}

void simularBatalha(Territorio *territorios, int atacante, int defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado do atacante (%s): %d\n", territorios[atacante].nome, dadoAtacante);
    printf("Dado do defensor (%s): %d\n", territorios[defensor].nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        territorios[defensor].numeroTropas--;
        printf("O atacante venceu! O defensor perde uma tropa.\n");
    } else if (dadoAtacante < dadoDefensor) {
        territorios[atacante].numeroTropas--;
        printf("O defensor venceu! O atacante perde uma tropa.\n");
    } else {
        printf("Empate! Nenhuma tropa perdeu tropas.\n");
    }

    if (territorios[defensor].numeroTropas <= 0) {
        printf("O território %s foi conquistado!\n", territorios[defensor].nome);
    }
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INSTRUCOES 100
#define MAX_LINE_LENGTH 50

// Estrutura para representar uma instrução
typedef struct {
    char assembly[MAX_LINE_LENGTH];
    char binario[33];
    char sinais_de_controle[200];
} Instrucao;

Instrucao instrucoes[MAX_INSTRUCOES];
int instrucao_count = 0;

// Função para definir sinais de controle e saída formatada
void set_sinais_de_controle(const char *assembly, char *sinais_de_controle) {
    if (strncmp(assembly, "addi", 4) == 0) {
        strcpy(sinais_de_controle, "ALUOp: 10; RegDst: 0; ALUScr: 1; MemtoReg: 0; Reg-Write: 1; Mem-Read: 0; Mem-Write: 0; Branch: 0;\n");
    } else if (strncmp(assembly, "add", 3) == 0) {
        strcpy(sinais_de_controle, "ALUOp: 10; RegDst: 1; ALUScr: 0; MemtoReg: 0; Reg-Write: 1; Mem-Read: 0; Mem-Write: 0; Branch: 0;\n");
    } else if (strncmp(assembly, "sub", 3) == 0) {
        strcpy(sinais_de_controle, "ALUOp: 10; RegDst: 1; ALUScr: 0; MemtoReg: 0; Reg-Write: 1; Mem-Read: 0; Mem-Write: 0; Branch: 0;\n");
    } else if (strncmp(assembly, "beq", 3) == 0) {
        strcpy(sinais_de_controle, "ALUOp: 01; RegDst: X; ALUScr: 0; MemtoReg: X; Reg-Write: 0; Mem-Read: 0; Mem-Write: 0; Branch: 1;\n");
    } else if (strncmp(assembly, "lw", 2) == 0) {
        strcpy(sinais_de_controle, "ALUOp: 00; RegDst: 0; ALUScr: 1; MemtoReg: 1; Reg-Write: 1; Mem-Read: 1; Mem-Write: 0; Branch: 0;\n");
    } else if (strncmp(assembly, "sw", 2) == 0) {
        strcpy(sinais_de_controle, "ALUOp: 00; RegDst: X; ALUScr: 1; MemtoReg: X; Reg-Write: 0; Mem-Read: 0; Mem-Write: 1; Branch: 0;\n");
    } else if (strncmp(assembly, "j", 1) == 0) {
        strcpy(sinais_de_controle, "ALUOp: XX; RegDst: X; ALUScr: X; MemtoReg: X; Reg-Write: 0; Mem-Read: 0; Mem-Write: 0; Branch: X;\n");
    } else {
        strcpy(sinais_de_controle, "ERRO: Instrucao nao suportada\n");
    }
}

// Função para ler um arquivo e processar instruções
void ler_arquivo(const char *nomearquivo) {
    FILE *file = fopen(nomearquivo, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    
    while (fgets(instrucoes[instrucao_count].assembly, MAX_LINE_LENGTH, file)) {
        instrucoes[instrucao_count].assembly[strcspn(instrucoes[instrucao_count].assembly, "\n")] = 0;
        set_sinais_de_controle(instrucoes[instrucao_count].assembly, instrucoes[instrucao_count].sinais_de_controle);
        instrucao_count++;
    }
    
    fclose(file);
}

// Função para simular a execução das instruções
void simular() {
    int pc = 0;
    for (int i = 0; i < instrucao_count; i++) {
        printf("%s: PC = PC + 4;\n%s\n", instrucoes[i].assembly, instrucoes[i].sinais_de_controle);
        pc += 4;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo_de_instrucoes>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    ler_arquivo(argv[1]);
    simular();
    
    return EXIT_SUCCESS;
}

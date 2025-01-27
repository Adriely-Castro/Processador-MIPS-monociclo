#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INSTRUCTIONS 100
#define MAX_LINE_LENGTH 50

// Estrutura para representar uma instrução
typedef struct {
    char assembly[MAX_LINE_LENGTH];
    char binary[33];
    char control_signals[200];
} Instruction;

Instruction instructions[MAX_INSTRUCTIONS];
int instruction_count = 0;

// Função para definir sinais de controle e saída formatada
void set_control_signals(const char *assembly, char *control_signals) {
    if (strncmp(assembly, "addi", 4) == 0) {
        strcpy(control_signals, "ALUOp: 10; RegDst: 0; ALUScr: 1; MemtoReg: 0; Reg-Write: 1; Mem-Read: 0; Mem-Write: 0; Branch: 0;\n");
    } else if (strncmp(assembly, "add", 3) == 0) {
        strcpy(control_signals, "ALUOp: 10; RegDst: 1; ALUScr: 0; MemtoReg: 0; Reg-Write: 1; Mem-Read: 0; Mem-Write: 0; Branch: 0;\n");
    } else if (strncmp(assembly, "sub", 3) == 0) {
        strcpy(control_signals, "ALUOp: 10; RegDst: 1; ALUScr: 0; MemtoReg: 0; Reg-Write: 1; Mem-Read: 0; Mem-Write: 0; Branch: 0;\n");
    } else if (strncmp(assembly, "beq", 3) == 0) {
        strcpy(control_signals, "ALUOp: 01; RegDst: X; ALUScr: 0; MemtoReg: X; Reg-Write: 0; Mem-Read: 0; Mem-Write: 0; Branch: 1;\n");
    } else if (strncmp(assembly, "lw", 2) == 0) {
        strcpy(control_signals, "ALUOp: 00; RegDst: 0; ALUScr: 1; MemtoReg: 1; Reg-Write: 1; Mem-Read: 1; Mem-Write: 0; Branch: 0;\n");
    } else if (strncmp(assembly, "sw", 2) == 0) {
        strcpy(control_signals, "ALUOp: 00; RegDst: X; ALUScr: 1; MemtoReg: X; Reg-Write: 0; Mem-Read: 0; Mem-Write: 1; Branch: 0;\n");
    } else if (strncmp(assembly, "j", 1) == 0) {
        strcpy(control_signals, "ALUOp: XX; RegDst: X; ALUScr: X; MemtoReg: X; Reg-Write: 0; Mem-Read: 0; Mem-Write: 0; Branch: X;\n");
    } else {
        strcpy(control_signals, "ERRO: Instrucao nao suportada\n");
    }
}

// Função para ler um arquivo e processar instruções
void read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    
    while (fgets(instructions[instruction_count].assembly, MAX_LINE_LENGTH, file)) {
        instructions[instruction_count].assembly[strcspn(instructions[instruction_count].assembly, "\n")] = 0;
        set_control_signals(instructions[instruction_count].assembly, instructions[instruction_count].control_signals);
        instruction_count++;
    }
    
    fclose(file);
}

// Função para simular a execução das instruções
void simulate() {
    int pc = 0;
    for (int i = 0; i < instruction_count; i++) {
        printf("%s: PC = PC + 4;\n%s\n", instructions[i].assembly, instructions[i].control_signals);
        pc += 4;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo_de_instrucoes>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    read_file(argv[1]);
    simulate();
    
    return EXIT_SUCCESS;
}

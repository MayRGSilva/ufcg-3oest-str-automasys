#include "FreeRTOS.h"
#include "task.h"
#include "main.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    xTaskHandle tsk1;
    xTaskHandle tsk2;
    xTaskHandle tsk3;
    xTaskHandle tsk4;

    // Criação de tasks
    // Tasks periódicas
    xTaskCreate(&vCtrlTempFr, "Controle temperatura do freezer", configMINIMAL_STACK_SIZE, NULL, 4, &tsk3); // periodica
    xTaskCreate(&vCtrlMaqLav, "Controle maquina de lavar", configMINIMAL_STACK_SIZE, NULL, 3, &tsk2); // periodica
    xTaskCreate(&vCtrlArCond, "Controle ar-condicionado", configMINIMAL_STACK_SIZE, NULL, 2, &tsk1); // periodica

    // Tasks aperiodicas
    xTaskCreate(vBkgServer, "Tasks aperiodicas", configMINIMAL_STACK_SIZE, NULL, 1, &tsk4); // servidor de aperiodicas

    // Escalonador
    vTaskStartScheduler();

    for(;;);

    return 0;
}

acionamento xReqAcion(acionamento comandoUsuario)
{
    acionamento status;

    switch(comandoUsuario){
        case abrirLigar:
            printf("Abrindo/ligando ...\n");
            status = abrirLigar;
            break;
        case fecharDesligar:
            printf("Fechando/desligando ...\n");
            status = fecharDesligar;
            break;
        default:
            break;
    }

    return status;
}

int sRand(int min, int max){
    int numRand;
    numRand = min + rand() % (max - min);

    return numRand;
}

void vCtrlArCond(void *pvParameters)
{
    acionamento comandoUsuario = 0;
    operacao oprUsuario = 0;
    modosArCond modUsuario = 1;

    acionamento status;
    int tmpr;

    // Acionamento liga e desliga
    if (!comandoUsuario){
        printf("Operacao: Ligar ar-condicionado\n");
    }
    else {
        printf("Operacao: Desligar ar-condicionado\n");
    }
    status = xReqAcion(comandoUsuario);

    while(1){
        if(status == abrirLigar){
            printf("Ar-condicionado ligado\n");

            switch(oprUsuario){
                case config:
                    // Controle da temperatura
                    tmpr = sRand(MIN_TEMP, MAX_TEMP);
                    printf("Ar-condicionado configurado em %d C\n", tmpr);
                case modos:
                    switch (modUsuario){ // Alterna modos de operação
                        case refrig:
                            printf("Ar-condicionado configurado no modo refrigeracao\n");
                            break;
                        case autom:
                            printf("Ar-condicionado configurado no modo automatico\n");
                            break;
                        case ventil:
                            printf("Ar-condicionado configurado no modo ventilacao\n");
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }else{
            printf("Ar-condicionado desligado\n");
        }
        printf("\n");
        vTaskDelay(2000/portTICK_PERIOD_MS); // equivalente a 20 ms
    }
}

void vCtrlMaqLav(void *pvParameters)
{
    acionamento status;
    acionamento comandoUsuario = 0;
    operacao oprUsuario = 1;
    modosLavagem modUsuario = 2;

    int tRes;
    
    // Acionamento liga e desliga
    if (!comandoUsuario){
        printf("Operacao: Ligar maquina\n");
    }
    else {
        printf("Operacao: Desligar maquina\n");
    }
    status = xReqAcion(comandoUsuario);

    while(1){
        if(status == abrirLigar){
            printf("Maquina ligada\n");

            // Visualizar o tempo restante
            tRes = sRand(MIN_TRES, MAX_TRES);
            if(tRes > 0)
                printf("Tempo restante para finalizar o ciclo: %d minutos\n", tRes);
            else
                printf("Ciclo de lavagem finalizado\n");

            switch(oprUsuario){
                case modos:
                    switch (modUsuario){ // Alterna modos de lavagem
                        case roupasPesadas:
                            printf("Maquina de lavar configurada no modo roupas pesadas\n");
                            break;
                        case roupasDelicadas:
                            printf("Maquina de lavar configurada no modo roupas delicadas\n");
                            break;
                        case rapida:
                            printf("Maquina de lavar configurada no modo lavagem rapida\n");
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }else{
            printf("Maquina desligada\n");
        }
        printf("\n");
        vTaskDelay(3000/portTICK_PERIOD_MS); // equivalente a 30 ms
    }
}


void vCtrlTempFr(void *pvParameters)
{
    acionamento status;
    int tmpr;

    acionamento comandoUsuario = 0;
    operacao oprUsuario = 0;

    // Acionamento liga e desliga
    if (!comandoUsuario){
        printf("Operacao: Ligar freezer\n");
    }
    else {
        printf("Operacao: Desligar freezer\n");
    }
    status = xReqAcion(comandoUsuario);

    while(1) {
        if(status == abrirLigar){
            printf("Freezer ligado\n");

            tmpr = sRand(MIN_TEMP_FR, MAX_TEMP_FR);
            printf("Temperatura atual do freezer: -%d C\n", tmpr);

            switch(oprUsuario){
                case config:
                    // Controle da temperatura
                    tmpr = sRand(MIN_TEMP_FR, MAX_TEMP_FR);
                    printf("Freezer configurado em -%d C\n", tmpr);
                default:
                    break;
            }

        }else{
            printf("Freezer desligado\n");
        }
        printf("\n");
        vTaskDelay(1500/portTICK_PERIOD_MS); //equivalente a 15 ms
    }
}

void vCtrlAsp()
{
    acionamento status;

    acionamento comandoUsuario = 0;
    operacao oprUsuario = 1;
    modosAsp modUsuario = 1;

    // Acionamento liga e desliga
    status = xReqAcion(comandoUsuario);

    if(status == abrirLigar){
        printf("Aspirador ligado\n");
            switch(oprUsuario){
                case modos:
                    switch (modUsuario){ // Alterna modos de operação
                        case varrer:
                            printf("Aspirador configurado no modo varrer\n");
                            break;
                        case aspirar:
                            printf("Aspirador configurado no modo aspirar\n");
                            break;
                        case limpar:
                            printf("Aspirador configurado no modo limpar\n");
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
    }else{
        printf("Aspirador desligado\n");
    }
}

void vBkgServer(void *pvParameters)
{
    int entrada = 0;

    printf("Digite as tarefas as quais deseja executar:\n");
    printf("1 - Controle portas da garagem\n");
    printf("2 - Controle camera do freezer\n");
    printf("3 - Controle aspirador de po\n");
    printf("Entre com o valor 4 para encerrar a operacao\n\n");

    while (entrada != 4) {
        entrada++;
        switch(entrada){
            case 1:
                printf("Controlando portas da garagem ...\n");
                xReqAcion(0);
                printf("Portas da garagem abertas\n");
                printf("\n");
                break;
            case 2:
                printf("Controlando camera do freezer ...\n");
                xReqAcion(1);
                printf("Camera desligada\n");
                printf("\n");                
                break;
            case 3:
                printf("Controlando aspirador de po ...\n");
                vCtrlAsp();
                printf("\n");
                break;
            case 4:
                printf("Operacao encerrada\n");
                printf("\n");
                break;
        }        
    }
    vTaskDelay(3000/portTICK_PERIOD_MS);
}
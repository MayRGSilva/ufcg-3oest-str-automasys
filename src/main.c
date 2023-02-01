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
    xTaskCreate(vCtrlArCond, (signed char *)"Controle ar-condicionado", configMINIMAL_STACK_SIZE, (void *)NULL, 4, &tsk1); // periodica
    xTaskCreate(vCtrlMaqLav, (signed char *)"Controle maquina de lavar", configMINIMAL_STACK_SIZE, (void *)NULL, 3, &tsk2); // periodica
    xTaskCreate(vCtrlTempFr, (signed char *)"Controle temperatura do freezer", configMINIMAL_STACK_SIZE, (void *)NULL, 2, &tsk3); // periodica
    
    // Tasks aperiodicas
    xTaskCreate(vBkgServer, (signed char *)"Tasks aperiódicas", configMINIMAL_STACK_SIZE, (void *)NULL, 1, &tsk3); // servidor de aperiodicas
    
    // Escalonador
    vTaskStartScheduler();

    for(;;);

    return 0;
}

acionamento xReqAcion()
{   
    acionamento status;
    acionamento comandoUsuario = 0;

    switch(comandoUsuario){
        case Abrir_Ligar:
            printf("Abrindo/ligando ...");
            xTaskDelay(30);
            status = Abrir_Ligar;
            break;
        case Fechar_Desligar:
            printf("Fechando/desligando ...");
            xTaskDelay(30);
            status = Fechar_Desligar;
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

void vCtrlArCond()
{   
    acionamento comandoUsuario = 0;
    operacao oprUsuario = 0;
    modosArCond modUsuario = 1;

    // Acionamento liga e desliga
    acionamento status;
    int tmpr;
    status = xReqAcion(comandoUsuario);

    if(status == Abrir_Ligar){
        printf("Ar condicionado ligado");
        switch(oprUsuario){
            case config:
                // Controle da temperatura
                tmpr = sRand(MIN_TEMP, MAX_TEMP);
                printf("Ar condicionado configurado em %d°C", tmpr);
            case modos:
                switch (modUsuario){ // Alterna modos de operação
                    case refrig:
                        printf("Ar condicionado configurado no modo refrigeracao");
                        break;
                    case autom:
                        printf("Ar condicionado configurado no modo automatico");
                        break;
                    case ventil:
                        printf("Ar condicionado configurado no modo ventilacao");
                        break;
                    default:
                        break;
                }
            default:
                break;
        }   
    }else{
        printf("Ar condicionado desligado");
    }
}

void vCtrlMaqLav()
{   
    // Acionamento liga e desliga
    acionamento status;

    acionamento comandoUsuario = 0;
    operacao oprUsuario = 1;
    modosLavagem modUsuario = 2;

    int tRes;
    status = xReqAcion(comandoUsuario);

    if(status == Abrir_Ligar){
        printf("Máquina ligada");

        // Visualizar o tempo restante
        tRes = sRand(MIN_TRES, MAX_TRES);
        if(tRes > 0)
            printf("Tempo restante para finalizar o ciclo: %d minutos", tRes);
        else
            printf("Ciclo de lavagem finalizado");

        switch(oprUsuario){         
            case modos:
                switch (modUsuario){ // Alterna modos de lavagem
                    case roupasPesadas:
                        printf("Maquina de lavar configurada no modo roupas pesadas");
                        break;
                    case roupasDelicadas:
                        printf("Maquina de lavar configurada no modo roupas delicadas");
                        break;
                    case rapida:
                        printf("Maquina de lavar configurada no modo lavagem rapida");
                        break;
                    default:
                        break;
                }
            default:
                break;
        }   
    }else{
        printf("Máquina desligada");
    } 
    
}


void vCtrlTempFr()
{
    // Acionamento liga e desliga
    acionamento status;
    int tmpr;

    acionamento comandoUsuario = 0;
    operacao oprUsuario = 0;

    status = xReqAcion(comandoUsuario);

    if(status == Abrir_Ligar){
        printf("Freezer ligado");

        tmpr = sRand(MIN_TEMP_FR, MAX_TEMP_FR);
        printf("Temperatura atual do freezer: -%d°C", tmpr);
        
        switch(oprUsuario){
            case config:
                // Controle da temperatura
                tmpr = sRand(MIN_TEMP_FR, MAX_TEMP_FR);
                printf("Freezer configurado em -%d°C", tmpr);
            default:
                break;
        } 

    }else{
        printf("Freezer desligado");
    }
}

void vCtrlAsp()
{
    // Acionamento liga e desliga
    acionamento status;

    acionamento comandoUsuario = 0;
    operacao oprUsuario = 1;
    modosAsp modUsuario = 1;

    status = xReqAcion(comandoUsuario);

    if(status == Abrir_Ligar){
        printf("Aspirador ligado");
        switch(oprUsuario){
            case modos:
                switch (modUsuario){ // Alterna modos de operação
                    case varrer:
                        printf("Aspirador configurado no modo varrer");
                        break;
                    case aspirar:
                        printf("Aspirador configurado no modo aspirar");
                        break;
                    case limpar:
                        printf("Aspirador configurado no modo limpar");
                        break;
                    default:
                        break;
                }
            default:
                break;
        }   
    }else{
        printf("Aspirador desligado");
    }
}

void vBkgServer()
{   
    int entrada;

    printf("Digite as tarefas as quais deseja executar:\n");
    printf("1 - Controle portas da garagem\n");
    printf("2 - Controle camera do freezer\n");
    printf("3 - Controle camera do freezer\n");
    printf("Aperte enter para encerrar a operação\n");

   while (scanf("%d", &entrada) != EOF) {
    switch(entrada){
        case 1:
            printf("Controlando portas da garagem ...");
            xReqAcion(0);
            break;
        case 2:
            printf("Controlando camera do freezer ...");
            xReqAcion(1);
        case 3:
            printf("Controlando aspirador de pó ...");
            vCtrlAsp(0, 1, 2);
        default:
            break;
    }
   }
}
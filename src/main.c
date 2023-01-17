#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

typedef enum {
    Abrir_Ligar,
    Fechar_Desligar
}acionamento;

typedef enum {
    config,
    modos
}operacao;

typedef enum {
    refrig,
    autom,
    ventil
}modosArCond;

acionamento comandoUsuario;

int main(void)
{
    xTaskCreate(&xReqAcion, "Controle portas da garagem", 1024, NULL, 1, NULL); // aperiodica
    xTaskCreate(&xCtrlArCond, "Controle ar-condicionado", 1024, NULL, 2, NULL); // periodica
    xTaskCreate(&xCtrlMaqLav, "Controle maquina de lavar", 1024, NULL, 3, NULL); // periodica
    xTaskCreate(&xCtrlCamFr, "Controle camera do freezer", 1024, NULL, 4, NULL); // aperiodica
    xTaskCreate(&xCtrlTempFr, "Controle temperatura do freezer", 1024, NULL, 5, NULL); // periodica
    xTaskCreate(&xCtrlAsp, "Controle aspirador de pó", 1024, NULL, 6, NULL); // aperiodica

    vTaskStartScheduler();

    return 0;
}

acionamento xReqAcion(acionamento comandoUsuario)
{   
    acionamento status;

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

void xCtrlArCond(acionamento comandoUsuario, operacao oprUsuario, modosArCond modUsuario, int temp)
{   
    acionamento status;
    status = xReqAcion(comandoUsuario);

    if(status == Abrir_Ligar){
        switch(oprUsuario){
            case config:
                printf("Ar condicionado configurado em %d°C", temp);
            case modos:
                switch (modUsuario){
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
        }   
    }
}

void xCtrlMaqLav(acionamento comandoUsuario)
{   

    
}

void xCtrlCamFr()
{
    
}

void xCtrlTempFr()
{
    
}

void xCtrlAsp()
{
    
}
#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>
#include <stdlib.h>

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

#define MIN_TRES 0
#define MAX_TRES 60
#define MIN_TEMP 16
#define MAX_TEMP 32
#define MIN_TEMP_FR 14
#define MAX_TEMP_FR 25

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

typedef enum {
    roupasPesadas,
    roupasDelicadas,
    rapida
}modosLavagem;

typedef enum {
    varrer,
    aspirar,
    limpar
}modosAsp;

acionamento comandoUsuario;

int main(void)
{
    xTaskCreate(&xReqAcion, "Controle portas da garagem", 1024, NULL, 1, NULL); // aperiodica
    xTaskCreate(&vCtrlArCond, "Controle ar-condicionado", 1024, NULL, 2, NULL); // periodica
    xTaskCreate(&vCtrlMaqLav, "Controle maquina de lavar", 1024, NULL, 3, NULL); // periodica
    xTaskCreate(&xReqAcion, "Controle camera do freezer", 1024, NULL, 4, NULL); // aperiodica
    xTaskCreate(&vCtrlTempFr, "Controle temperatura do freezer", 1024, NULL, 5, NULL); // periodica
    xTaskCreate(&vCtrlAsp, "Controle aspirador de pó", 1024, NULL, 6, NULL); // aperiodica

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

int sRand(int min, int max){
    int numRand;
    numRand = min + rand() % (max - min);

    return numRand;
}

void vCtrlArCond(acionamento comandoUsuario, operacao oprUsuario, modosArCond modUsuario)
{   
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

void vCtrlMaqLav(acionamento comandoUsuario, operacao oprUsuario, modosLavagem modUsuario)
{   
    // Acionamento liga e desliga
    acionamento status;
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


void vCtrlTempFr(acionamento comandoUsuario, operacao oprUsuario)
{
    // Acionamento liga e desliga
    acionamento status;
    int tmpr;
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

void vCtrlAsp(acionamento comandoUsuario, operacao oprUsuario, modosAsp modUsuario)
{
    // Acionamento liga e desliga
    acionamento status;
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
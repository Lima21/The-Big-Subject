/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Gonçalo
 *
 * Created on 8 de Maio de 2016, 10:21
 */


#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 
 */
int main(int argc, char** argv) {
    ELEM *iniLista = NULL;
    USER utilizadores[20];
    PERG aux;
    int tema[12], i, j, a;
    int pontuacao[50],totalPont=0,totalJogo=0, pontos,pergAtual[100],temaAtual[100][12],ajudaAtual[100];
    char user[50][100], userAtual[100][100],jogadorAtual[100][100],pergunta[200];
    int totalUser, modo, opc, totalPerg,jogoAtual=0;    
    int temp_jogo;
    LerScore(pontuacao,&totalPont,user);
    carregarJogo(jogadorAtual,&totalJogo,pergAtual,temaAtual,ajudaAtual);
    logo();   
    totalUser = lerUser(utilizadores);
    openQuest(&iniLista);
    modo = verificaUser(&totalUser, utilizadores,user,&totalPont,userAtual,&totalJogo,jogadorAtual);
   
    system("clear");
    if (modo == 1) {
        system("clear");
        do {
            system("clear");
            logo();
            printf(" Jogador: %s\n",userAtual[totalJogo]);
            printf("\n\t 1. Jogar\n\t 2. Pontuações\n\t 0. Sair\n\t\t> ");
            scanf("%i", &opc);
            switch (opc) {
                case 1:    
                    jogoAtual=carregarJogo(jogadorAtual,&totalJogo,pergAtual,temaAtual,ajudaAtual);
                    //printf("\n%i\n",jogoAtual);
                    if(jogoAtual==totalJogo){   //-1 significa novo jogo
                        escolherTema(tema); 
                        //printf("Novo jogo: %i\n",jogoAtual);
                    }   
                    else{
                        a = 1;
                        temp_jogo = jogoAtual;   
                        for(i=0;i<12;i++){
                            tema[i]=temaAtual[jogoAtual][i];            
                        }                        
                        //printf("Jogo Atual: %i\n",jogoAtual);
                    }                                      
                    pontos = modoJogo(iniLista,tema,pontuacao,totalPont,user,totalJogo,pergAtual,jogadorAtual,temaAtual,ajudaAtual,jogoAtual);
                    if(pontos == -3){
                        opc = 0;                       
                    } else {                        
                         addPontuacao(pontos, pontuacao, user, &totalPont, userAtual, totalJogo);                    
                    if(a == 1){                       
                        for(i=temp_jogo; i < totalJogo; i++){
                        pergAtual[i] = pergAtual[i+1];
                        for(j=0; j < 12; j++){
                            temaAtual[i][j] = temaAtual[i+1][j];
                        }                        
                        ajudaAtual[i] = ajudaAtual[i+1];
                        strcpy(jogadorAtual[i], jogadorAtual[i+1]);
                        totalJogo--;
                        gravarJogo(jogadorAtual, totalJogo, pergAtual,temaAtual,ajudaAtual);
                    }
                    }
                    saveScore(pontuacao,totalPont,user);
                    a = 0;
                    }   
                    //printf("\nPontuação: %i",pontuacao);
                    //printf("User: %s",user[totalPont]);
                    //saveScore(pontuacao,totalPont,user);
                    break;
                case 2: system("clear");
                    logo();
                    mostraScore(pontuacao, user, totalPont);
                case 0: 
                    break;
            }

        } while (opc != 0);
    }
    if (modo == 2) {
        do {
            logo();
            printf("\n ADMINISTRAÇÃO\n\n");
            printf("\n 1. Adicionar Pergunta\n 2. Listar Perguntas\n 3. Remover pergunta\n 4. Alterar Pergunta\n 5. Lista Users\n 0. Sair\n >");
            scanf("%i", &opc);
            switch (opc) {
                case 1: system("clear");
                        logo();
                        printf("\n Insira a pergunta: ");
                        getchar();
                        gets(aux.perg);
                        printf("\n Insira a resposta correta: ");
                        gets(aux.resp1);
                        printf("\n Insira uma resposta errada: ");
                        gets(aux.resp2);
                        printf("\n Insira uma resposta errada: ");
                        gets(aux.resp3);
                        printf("\n Insira uma resposta errada: ");
                        gets(aux.resp4);
                        printf("\n 1. Séries\n 2. Desporto\n 3. Jogos\n 4. Cinema\n 5. Matemática\n 6. Geografia\n 7. História\n 8. Música\n 9. Ditados Populares\n 10. Informática\n 11. Datas Comemorativas\n 12. Animais\n");
                        printf("\n Insira o nº do tema: ");
                        scanf("%i", &aux.tema);
                        printf("Insira o nível de dificuldade de 1-6: ");
                        scanf("%i", &aux.nivel);
                        inserirFim(&iniLista, aux);


                    break;
                case 2: system("clear");
                        logo();
                        listar(iniLista);
                        break;
                
                case 3: system("clear");
                        logo();
                        printf("\n Escreva a pergunta que pretende remover: ");
                        getchar();
                        gets(pergunta);
                        removerPergunta(&iniLista,pergunta);
                    break;
                    
                case 4: system("clear");
                        logo();
                        printf("\n Escreva a pergunta que pretende alterar: ");
                        getchar();
                        gets(pergunta);
                        alterarPergunta(iniLista,pergunta);
                    break;
                    
                case 5: system("clear");
                        logo();
                        listarUsers(utilizadores,totalUser);    
                    
                case 0:
                        saveQuest(iniLista);
                        break;
                default:
                    break;
            }

        } while (opc != 0);
    }
    saveUser(totalUser, utilizadores);
    return (EXIT_SUCCESS);
}


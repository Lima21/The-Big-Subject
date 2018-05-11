/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   header.h
 * Author: Gonçalo
 *
 * Created on 8 de Maio de 2016, 10:22
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct perguntas{
    
    char perg[200], resp1[50], resp2[50], resp3[50], resp4[50];
    int nivel, tema;
    
}PERG;

typedef struct user{
    char nome[100], cidade[100], senha[100], user[100], modo, data[100];    
}USER;

typedef struct elem{
    PERG perg;
    struct elem *seguinte;
}ELEM;








//modoJogo(iniLista, tema);
//escolherTema(tema);
void logo();
int existeUser(int total, USER utilizadores[], USER aux);
int acessoUser(int total, USER utilizadores[], USER aux);
int verificaUser(int *total, USER utilizadores[], char user[][100], int *totalPont, char userAtual[][100],int *totalJogo,char jogadorAtual[][100]);
int saveUser(int total, USER utilizadores[]);
int saveQuest(ELEM *iniLista);
int openQuest(ELEM **iniLista);
int lerUser(USER utilizadores[]);
int inserirFim(ELEM **iniLista, PERG newInfo);
int listar(ELEM *iniLista);
int escolherTema(int tema[]);
int mostraTema(int tema[], int fase);
void mostraCor(int tam, char resp[][100], int escolha, int cor);
int mostraPergunta(ELEM *iniLista, int nivel, int tema[], int *help);
int calcPont(int i);
int modoJogo(ELEM *iniLista, int tema[], int pontuacao[], int totalPont, char user[][100], int totalJogo,int pergAtual[],char jogadorAtual[][100],int temaAtual[][12],int ajudaAtual[],int jogoAtual);
int saveScore(int pontuacao[], int totalPont, char user[][100]);
int LerScore(int pontuacao[], int *totalPont, char user[][100]);
int gravarJogo(char jogadorAtual[][100], int totalJogo, int pergAtual[],int temaAtual[][12],int ajudaAtual[]);
int carregarJogo(char jogadorAtual[][100], int *totalJogo, int pergAtual[],int temaAtual[][12],int ajudaAtual[]);
void addPontuacao(int pontos, int pontuacao[], char user[][100], int *totalPont, char userAtual[][100], int totalJogo);
void mostraScore(int pontuacao[], char user[][100], int totalPont);
void listarUsers(USER utilizadores[],int totalUser);
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void logo() {
    system("clear");
    printf("\033[32;1m");
    printf("\n\t\t\t               *.*\n");
    printf("\t\t\t        ˜*•. ˜*•.•*˜ .•*˜\n");
    printf("\t\t\t˜*•. ˜”*°•.˜”*°•.•°*”˜.•°*”˜ .•*˜\n");
    printf("\t\t\t\033[33;1m        The Big Subject\033[32m\n");
    printf("\t\t\t˜*•. ˜”*°•.˜”*°•.•°*”˜.•°*”˜ .•*˜\n");
    printf(" \t\t\t       ˜*•. ˜*•.•*˜ .•*˜\n");
    printf(" \t\t\t              *.*\n");
    printf("\033[37m\n");
    printf("\n\n");
}

int existeUser(int total, USER utilizadores[], USER aux) {
    int i;
    for (i = 0; i < total; i++) {
        if (strcmp(utilizadores[i].user, aux.user) == 0) {
            return 1; // Existe
        }
    }
    return 0; // Não existe

}

int acessoUser(int total, USER utilizadores[], USER aux) {
    int i;
    for (i = 0; i < total; i++) {
        if (strcmp(utilizadores[i].user, aux.user) == 0 && strcmp(utilizadores[i].senha, aux.senha) == 0) {
            if (utilizadores[i].modo == 'A') {               
                return 2;
            }            
            printf("\n\tÚltima vez que jogou foi: %s", utilizadores[i].data);
            strcpy(utilizadores[i].data, __DATE__);
            getchar();
            return 1; // Entrada certa
        }
    }
    return 0; // Erro ao entrar
}

int verificaUser(int *total, USER utilizadores[], char user[][100], int *totalPont, char userAtual[][100], int *totalJogo, char jogadorAtual[][100]) {
    //int indice=*totalPont;
    USER aux;
    int totalU;
    printf("\t\tUtilizador: ");
    gets(aux.user);
    //printf("%s", user[*totalPont]);
    printf("\t\tSenha: ");
    gets(aux.senha);
    totalU = (*total);
    if (existeUser(totalU, utilizadores, aux)) {
        if (acessoUser(totalU, utilizadores, aux) == 1) {
            printf(" Acesso permitido\n");
            strcpy((userAtual[*totalJogo]), aux.user);
            strcpy((jogadorAtual[*totalJogo]), aux.user);
           
            return 1;

        }
        if (acessoUser(totalU, utilizadores, aux) == 2) {
            return 2;
        }

        printf(" Acesso negado\n");
        return 0;

    } else {
        strcpy(utilizadores[*total].user, aux.user);
        strcpy(utilizadores[*total].senha, aux.senha);
        printf("\t\tNome: ");
        gets(utilizadores[*total].nome);
        printf("\t\tCidade: ");
        gets(utilizadores[*total].cidade);
        utilizadores[*total].modo = 'U';
        (*total)++;
        printf(" Acesso permitdo\n");
        strcpy((userAtual[*totalJogo]), aux.user);
        strcpy((jogadorAtual[*totalJogo]), aux.user);
        strcpy(utilizadores[*total].data, __DATE__);
        return 1;

    }

}

int saveUser(int total, USER utilizadores[]) {
    FILE *fp = NULL;
    fp = fopen("user.dat", "wb");
    fwrite(&total, sizeof (int), 1, fp);
    fwrite(&utilizadores[0], sizeof (USER), total, fp);
    fclose(fp);

}

int saveQuest(ELEM *iniLista) {
    FILE *fp = NULL;
    ELEM *aux = NULL;
    int cont = 0;
    fp = fopen("quest.dat", "wb");
    if (fp == NULL) {
        printf("Erro ao abrir ficheiro");
        return 0;
    }

    for (aux = iniLista; aux != NULL; aux = aux -> seguinte) {
        fwrite(&aux->perg, sizeof (PERG), 1, fp);
    }
    fclose(fp);
}

int openQuest(ELEM **iniLista) {
    FILE *fp = NULL;
    PERG aux;
    fp = fopen("quest.dat", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir ficheiro");
        return -1;
    }

    while (!feof(fp)) {


        if (fread(&aux, sizeof (PERG), 1, fp) == 1) {

            inserirFim(&(*iniLista), aux);
        }

    }
    return 0;

}

int lerUser(USER utilizadores[]) {
    FILE *fp = NULL;
    int total;
    fp = fopen("user.dat", "rb");
    if (fp == NULL) {
        return 0;
    }
    fread(&total, sizeof (int), 1, fp);
    fread(&utilizadores[0], sizeof (USER), total, fp);
    fclose(fp);

    return total;
}

int inserirFim(ELEM **iniLista, PERG newInfo) {
    ELEM *novo = NULL, *aux = NULL;
    novo = (ELEM*) calloc(1, sizeof (ELEM)); //Reservar espaço em memoria
    if (novo == NULL) {
        printf("\n Out of memory");
        return -1;
    }
    novo->perg = newInfo; //Preenche os valores
    novo->seguinte = NULL;
    if (*iniLista == NULL) {//Se a lista está vazia
        *iniLista = novo;
    } else {
        aux = *iniLista; // Acrescenta no fim
        while (aux->seguinte != NULL) {
            aux = aux->seguinte;
        }
        aux->seguinte = novo;
    }
    return 0;
}

int listar(ELEM *iniLista) {
    int opc = 0;
    ELEM *aux = NULL;
    if (iniLista == NULL) {
        printf("\n Lista vazia");
        return -1;
    }
    aux = iniLista;
    do {
        printf("\n TEMAS\n 1. Séries\n 2. Desporto\n 3. Jogos\n 4. Cinema\n 5. Matemática\n 6. Geografia\n 7. História\n 8. Música\n 9. Ditados Populares\n 10. Informática\n 11. Datas Comemorativas\n 12. Animais\n 0.Sair\n");
        printf("\n\n Insira o nº do tema: ");
        scanf("%i", &opc);
        for (aux = iniLista; aux != NULL; aux = aux->seguinte) {
            if (opc == aux->perg.tema) {
                printf("\n %s\n\n", aux->perg.perg);
                printf("\t A-%s\tB-%s\n", aux->perg.resp1, aux->perg.resp2);
                printf("\t C-%s\tD-%s\n", aux->perg.resp3, aux->perg.resp4);
                printf("\n Nivel dificuldade: %i\n", aux->perg.nivel);   
            }
        }
    } while (opc != 0);
}

int removerPergunta(ELEM **iniLista, char pergunta[]){
	ELEM *aux=NULL, *ant=NULL;
	if(*iniLista==NULL){
		printf("\n Lista Vazia");
		return -1;
	}
	aux=*iniLista;
	while(aux!=NULL && (strcmp(pergunta,aux->perg.perg)>0)||(strcmp(pergunta,aux->perg.perg)<0)){
		ant=aux;
		aux=aux->seguinte;
	}
	if(aux==NULL){
		printf("\n Pergunta não existe");
		return -1;
	}
	if(ant==NULL){
		*iniLista=aux->seguinte;
	}
	else{
		ant->seguinte=aux->seguinte;
	}
	free(aux);
        printf("\n Pergunta removida com sucesso");
}

int alterarPergunta(ELEM *iniLista, char pergunta[]){
	ELEM *aux=NULL;
	if(iniLista==NULL){
		printf("\n Lista vazia");
		return -1;
	}
        aux=iniLista;
	while(aux!=NULL){
            if(strcmp(pergunta,aux->perg.perg)==0){
                        printf("Insira a pergunta: ");
                        getchar();
                        gets(aux->perg.perg);
                        printf("\n Insira a resposta correta: ");
                        gets(aux->perg.resp1);
                        printf("\n Insira uma resposta errada: ");
                        gets(aux->perg.resp2);
                        printf("\n Insira uma resposta errada: ");
                        gets(aux->perg.resp3);
                        printf("\n Insira uma resposta errada: ");
                        gets(aux->perg.resp4);
                        printf("\n TEMAS\n 1. Séries\n 2. Desporto\n 3. Jogos\n 4. Cinema\n 5. Matemática\n 6. Geografia\n 7. História\n 8. Música\n 9. Ditados Populares\n 10. Informática\n 11. Datas Comemorativas\n 12. Animais\n 0.Sair\n");
                        printf("\n\n Insira o nº do tema: ");
                        scanf("%i", &aux->perg.tema);
                        printf("\n Insira o nível de dificuldade de 1-6: ");
                        scanf("%i", &aux->perg.nivel);
			
			return -1;
		}
		aux=aux->seguinte;
	}
	printf("\n Pergunta não existe");
}

void listarUsers(USER utilizadores[],int totalUser) {
    int i=0,j=0;
    USER aux;
    for (i=0;i<totalUser;i++){
        for (j=0;j<totalUser-1;j++){
            if(strcmp(utilizadores[j].nome,utilizadores[j+1].nome)>0){
                aux=utilizadores[j];
                utilizadores[j]=utilizadores[j+1];
                utilizadores[j+1]=aux;
            }
        }  
                                             
      }
    for (int i = 0; i < totalUser; i++){
       printf("\n\n User: %s", utilizadores[i].user);
       printf("\n Senha: %s", utilizadores[i].senha);
       printf("\n Nome: %s", utilizadores[i].nome);
       printf("\n Morada: %s", utilizadores[i].cidade);
    }
    getchar();
    getchar();
}

int escolherTema(int tema[]) {
    int x = 0, i = 0, j = 0, k = 0;
    printf("\n\n");
    for (i = 0; i < 12; i++) {
        printf("i=%i - ", i);
        srand(time(NULL));
        do {
            k = 0;
            x = 1 + rand() % 12;
            for (j = 0; j < i; j++) {
                if (tema[j] == x) {
                    k++;
                }
            }

        } while (k != 0);
        printf("%i\n", x);
        tema[i] = x;
    }
    for (i = 0; i < 12; i++) {
        printf("%i\n", tema[i]);
    }




}

int mostraTema(int tema[], int fase) {
    system("clear");
    logo();
    printf("\n\n TEMA: ");
    switch (tema[fase]) {
        case 1: printf("Séries");
            break;
        case 2: printf("Desporto");
            break;
        case 3: printf("Jogos");
            break;
        case 4: printf("Cinema");
            break;
        case 5: printf("Matemática");
            break;
        case 6: printf("Geografia");
            break;
        case 7: printf("História");
            break;
        case 8: printf("Música");
            break;
        case 9: printf("Ditados Populares");
            break;
        case 10: printf("Informática");
            break;
        case 11: printf("Datas Comemorativas");
            break;
        case 12: printf("Animais");
            break;
    }
    printf("\tNível: %i", fase + 1);
}

void mostraCor(int tam, char resp[][100], int escolha, int cor) {
    int i;
    printf("\a");
    if (tam < 0) {

        if (resp[1] == resp[escolha]) {
            printf("\033[3%i;1m", cor);
            printf("\n\tA: %s", resp[1]);
            printf("\033[37m");
        } else {
            printf("\n\tA: %s", resp[1]);
        }
        for (i = tam; i < 0; i++) {
            printf(" ");
        }
        if (resp[2] == resp[escolha]) {
            printf("\033[3%i;1m", cor);
            printf("\t\tB: %s\n\t", resp[2]);
            printf("\033[37m");
        } else {
            printf("\t\tB: %s\n\t", resp[2]);
        }
        if (resp[3] == resp[escolha]) {
            printf("\033[3%i;1m", cor);
            printf("C: %s\t\t", resp[3]);
            printf("\033[37m");
        } else {
            printf("C: %s\t\t", resp[3]);
        }
        if (resp[4] == resp[escolha]) {
            printf("\033[3%i;1m", cor);
            printf("D: %s\n", resp[4]);
            printf("\033[37m");
        } else {
            printf("D: %s\n", resp[4]);
        }
        sleep(1);
    }
    if (tam > 0) {
        if (resp[1] == resp[escolha]) {
            printf("\033[3%i;1m", cor);
            printf("\n\tA: %s\t\t", resp[1]);
            printf("\033[37m");
        } else {
            printf("\n\tA: %s\t\t", resp[1]);
        }
        if (resp[2] == resp[escolha]) {
            printf("\033[3%i;1m", cor);
            printf("B: %s\n", resp[2]);
            printf("\033[37m");
        } else {
            printf("B: %s\n", resp[2]);
        }
        if (resp[3] == resp[escolha]) {
            printf("\033[3%i;1m", cor);
            printf("\tC: %s", resp[3]);
            printf("\033[37m");
        } else {
            printf("\tC: %s", resp[3]);
        }

        for (i = 0; i < tam; i++) {
            printf(" ");
        }
        if (resp[4] == resp[escolha]) {
            printf("\033[3%i;1m", cor);
            printf("\t\tD: %s\n", resp[4]);
            printf("\033[37m");
        } else {
            printf("\t\tD: %s\n", resp[4]);
        }
        sleep(1);
    }

    if (tam == 0) {
        if (resp[1] == resp[escolha]) {

            printf("\033[3%i;1m", cor);
            printf("\n\tA: %s\t\t", resp[1]);
            printf("\033[37m");
        } else {
            printf("\n\tA: %s\t\t", resp[1]);
        }
        if (resp[2] == resp[escolha]) {
            printf("\033[3%i;1m", cor);
            printf("B: %s\n\t", resp[2]);
            printf("\033[37m");

        } else {
            printf("B: %s\n\t", resp[2]);
        }
        if (resp[3] == resp[escolha]) {
            printf("\033[3%i;1m", cor);
            printf("C: %s\t\t", resp[3]);
            printf("\033[37m");

        } else {
            printf("C: %s\t\t", resp[3]);
        }
        if (resp[4] == resp[escolha]) {
            printf("\033[3%i;1m", cor);
            printf("D: %s\n", resp[4]);
            printf("\033[37m");
        } else {
            printf("D: %s\n", resp[4]);
        }
        sleep(1);
    }
}

int mostraPergunta(ELEM *iniLista, int nivel, int tema[], int *help) {
    ELEM *aux = NULL;
    int nivel_real, cont = 0, x;
    int i, j, k, seq[4], tam, opc, escolha;
    char resp[5][100], pergunta[200];

    if (iniLista == NULL) {
        printf("Lista Vazia");
        return -1;
    }
    if (nivel == 1 || nivel == 2) {
        nivel_real = 1;
    }
    if (nivel == 3 || nivel == 4) {
        nivel_real = 2;
    }
    if (nivel == 5 || nivel == 6) {
        nivel_real = 3;
    }
    if (nivel == 7 || nivel == 8) {
        nivel_real = 4;
    }
    if (nivel == 9 || nivel == 10) {
        nivel_real = 5;
    }
    if (nivel == 11 || nivel == 12) {
        nivel_real = 6;
    }

    for (aux = iniLista; aux != NULL; aux = aux -> seguinte) {
        if (aux->perg.nivel == nivel_real && aux->perg.tema == tema[nivel]) {
            cont++;
        }
    }
    system("clear");
    srand(time(NULL));
    x = 1 + rand() % cont;
    cont = 0;
    logo();


    for (aux = iniLista; aux != NULL; aux = aux -> seguinte) {
        if (aux->perg.nivel == nivel_real && aux->perg.tema == tema[nivel]) {
            cont++;
            if (cont == x) {

                printf("\t%s\n", aux->perg.perg);
                strcpy(pergunta, aux->perg.perg);


                for (i = 0; i < 4; i++) {
                    srand(time(NULL));
                    do {
                        k = 0;
                        x = 1 + rand() % 4;
                        for (j = 0; j < i; j++) {
                            if (seq[j] == x) {
                                k++;
                            }
                        }

                    } while (k != 0);
                    seq[i] = x;
                }


                strcpy(resp[seq[0]], aux->perg.resp1);
                strcpy(resp[seq[1]], aux->perg.resp2);
                strcpy(resp[seq[2]], aux->perg.resp3);
                strcpy(resp[seq[3]], aux->perg.resp4);


                tam = strlen(resp[1]) - strlen(resp[3]);




                /*xif (tam < 0) {

                    printf("\n\tA: %s", resp[1]);
                    for (i = tam; i < 0; i++) {
                        printf(" ");
                    }
                    printf("\t\tB: %s\n\tC: %s\t\tD: %s\n", resp[2], resp[3], resp[4]);
                }
                if (tam > 0) {
                    printf("\n\tA: %s\t\tB: %s\n", resp[1], resp[2]);

                    printf("\tC: %s", resp[3]);
                    for (i = 0; i < tam; i++) {
                        printf(" ");
                    }
                    printf("\t\tD: %s\n", resp[4]);
                }

                if (tam == 0) {
                    printf("\n\tA: %s\t\tB: %s\n\tC: %s\t\tD: %s\n", resp[1], resp[2], resp[3], resp[4]);
                }*/

                printf("\n\tA: %-20s\t\tB: %-20s\n\tC: %-20s\t\tD: %-20s\n", resp[1], resp[2], resp[3], resp[4]);

                printf("\n\n\tResposta: (Para Pedir ajuda insira H) \n\t\t\t> ");
                getchar();
                scanf("%c", &opc);

                if (opc == 'h' || opc == 'H') {
                    if (*help > 2) {
                        printf("Já não pode pedir mais ajuda");
                        getchar();
                        printf("\n\n\tResposta: \n\t\t\t> ");
                        scanf("%c", &opc);

                    } else {
                        printf("Resposta Certa: %s\n", aux->perg.resp1);
                        (*help)++;
                        getchar();
                        printf("\n\n\tResposta: \n\t\t\t> ");
                        scanf("%c", &opc);
                    }
                }

                switch (opc) {
                    case 'a':
                    case 'A': escolha = 1;
                        break;
                    case 'b':
                    case 'B': escolha = 2;
                        break;
                    case 'c':
                    case 'C': escolha = 3;
                        break;
                    case 'd':
                    case 'D': escolha = 4;
                        break;
                    default: escolha = 0;
                        break;
                }


                if (strcmp(resp[escolha], aux->perg.resp1) == 0) {
                    sleep(1);
                    system("clear");
                    logo();
                    printf("\t%s\n", pergunta);

                    mostraCor(tam, resp, escolha, 2);


                } else {
                    sleep(1);
                    system("clear");
                    logo();
                    printf("\t%s\n", pergunta);
                    mostraCor(tam, resp, escolha, 1);
                    printf("\n Errou\n");
                    printf("\n Resposta Certa: %s\n", aux->perg.resp1);
                    sleep(1);
                    getchar();
                    getchar();
                    return 1;
                }








            }
        }
    }

}

int calcPont(int i) {


    switch (i + 1) {
        case 1: return 50;
            break;
        case 2: return 100;
            break;
        case 3: return 200;
            break;
        case 4: return 500;
            break;
        case 5: return 750;
            break;
        case 6: return 1000;
            break;
        case 7: return 2000;
            break;
        case 8: return 5000;
            break;
        case 9: return 10000;
            break;
        case 10: return 20000;
            break;
        case 11: return 35000;
            break;
        case 12: return 50000;
            break;
    }

}

int modoJogo(ELEM *iniLista, int tema[], int pontuacao[], int totalPont, char user[][100], int totalJogo, int pergAtual[], char jogadorAtual[][100], int temaAtual[][12], int ajudaAtual[], int jogoAtual) {
    int opc, i, cont, x, help = 0, verificaHelp = 0, j = 0, pontos, k = 0;
    float ajuda_calc = 0;
    if (jogoAtual == totalJogo) {
        i = 0;
        help = 0;
        pontos = 0;
    } else {
        i = pergAtual[jogoAtual];
        help = ajudaAtual[jogoAtual];
        pontos = calcPont(i - 1);
    }

    for (i = i; i < 12; i++) {       
        mostraTema(tema, i);
        printf("\t Ajudas usadas: %i\n Pontos: %i\n\n", help, pontos);
        printf(" 1. Continuar\n 2. Tudo ou Nada\n 3. Desistir\n 4. Pausar Jogo\n\n\t> ");
        scanf("%i", &opc);
        switch (opc) {
            case 1:
                verificaHelp = help;
                printf("\n");
                cont = mostraPergunta(iniLista, i, tema, &help);
                if (cont == 1) {
                    printf("\n\n Terminou o Jogo");

                    return 0;
                } 
                if (i == 11 && verificaHelp == help) {
                     pontos = calcPont(i);
                        printf("\n Ganhou!");
                        printf("\n Total de ajudas usadas: %i\n", help);

                        if (help > 0) {
                            ajuda_calc = help * 25;
                            ajuda_calc /= 100;
                            ajuda_calc = 1 - ajuda_calc;
                        } else {
                            ajuda_calc = 1;
                        }
                        printf("\n Pontuação: %.2f\n", pontos * ajuda_calc);
                        getchar();
                        getchar();
                        return pontos * ajuda_calc;
                    }
                if (verificaHelp != help) {
                    do {
                        k = 0;
                        x = 1 + rand() % 12;



                        if (i % 2 == 0) {
                            if (tema[i] == x || tema[i + 1] == x) {
                                k++;

                            }

                        } else {
                            if (tema[i] == x || tema[i - 1] == x) {
                                k++;
                            }

                        }
                        if (k == 0) {
                            tema[i] = x;
                            i--;
                        }

                    } while (k != 0);

                } else {

                    pontos = calcPont(i);

                }


                break;
            case 2:
                cont = mostraPergunta(iniLista, i, tema, &help);
                if (cont == 1) {
                    printf("\n\n Perdeu o Jogo");

                } else {
                    printf("\n Ficou com Tudo!");
                    
                    pontos = calcPont(i);
                    printf("\n Pontuação: %i\n", pontos);
                    getchar();
                    getchar();
                    return 0;
                }
                break;
            case 3:
                system("clear");
                logo();
                printf(" Total de ajudas usadas: %i\n", help);

                if (help > 0) {
                    ajuda_calc = help * 25;
                    ajuda_calc /= 100;
                    ajuda_calc = 1 - ajuda_calc;
                } else {
                    ajuda_calc = 1;
                }
                printf(" Pontuação: %.2f\n", pontos * ajuda_calc);
                printf(" Obrigado por ter jogado.\n Tenta ganhar da proxima vez.");
                getchar();
                getchar();
                return pontos * ajuda_calc;
                break;
                
            case 4: 
                system("clear");
                logo();
                printf(" JOGO PAUSADO\n");
                pergAtual[totalJogo] = i;
                ajudaAtual[totalJogo] = help;
                //printf("Pergunta atual: %i\n", pergAtual[totalJogo]);
                //printf("Ajuda atual: %i\n", ajudaAtual[totalJogo]);
                for (j = 0; j < 12; j++) {
                    temaAtual[totalJogo][j] = tema[j + 1];
                    //printf("Tema: %i\n", tema[j + 1]);
                    //printf("Tema Atual: %i\n", temaAtual[totalJogo][j]);
                }
                //printf("Jogador atual: %s\n", jogadorAtual[totalJogo]);
                totalJogo = totalJogo + 1;
                gravarJogo(jogadorAtual, totalJogo, pergAtual, temaAtual, ajudaAtual);
                return -3;
                break;
        }

    }
    return pontos;
}

int saveScore(int pontuacao[], int totalPont, char user[][100]) {
    FILE *fp = NULL;
    int res = 0;
    fp = fopen("score.dat", "wb");
    if (fp == NULL) {
        printf("ERRO ao abrir o ficheiro \n");
        return -1;
    }
    //printf("Jogador: %s\n Pontuação: %i\n", user[totalPont - 1], pontuacao[totalPont - 1]);
    res = fwrite(&totalPont, sizeof (int), 1, fp);
    res = fwrite(&pontuacao[0], sizeof (int), totalPont, fp);
    res = fwrite(&user[0], sizeof (char) * 100, totalPont, fp);
  

    printf("Gravar %i registar \n", res);
    fclose(fp);
}

int LerScore(int pontuacao[], int *totalPont, char user[][100]) {
    FILE *fp = NULL;
    int res = 0, aux = 0, i = 0;
    fp = fopen("score.dat", "rb");
    if (fp == NULL) {
        printf("Nao abriu p ficheiro \n");
        return -1;
    }
    fread(&aux, sizeof (int), 1, fp);
    if (aux > 0) {
        res = fread(&pontuacao[0], sizeof (int), aux, fp);
        res = fread(&user[0], sizeof (char)*100, aux, fp);
    }
    //printf("Total registos lido = %i \n", res);

    *totalPont = res;
    fclose(fp);
    return res;
}

int gravarJogo(char jogadorAtual[][100], int totalJogo, int pergAtual[], int temaAtual[][12], int ajudaAtual[]) {
    FILE *fp = NULL;
    int res = 0, i = 0;
    fp = fopen("jogo.dat", "wb");
    if (fp == NULL) {
        printf("ERRO ao abrir o ficheiro \n");
        return -1;
    }

    printf("\n\n Dados a gravar: \n Jogador: %s\n Niveis completos: %i\n Ajudas Usadas: %i\n", jogadorAtual[totalJogo - 1], pergAtual[totalJogo - 1], ajudaAtual[totalJogo - 1]);
    printf(" \n\n Volte para tentar ser o grande vencedor.\n");
    for (i = 0; i < 12; i++) {
        //printf("Temas Atuais: %i\n", temaAtual[totalJogo - 1][i]);
    }
    res = fwrite(&totalJogo, sizeof (int), 1, fp);
    res = fwrite(&jogadorAtual[0], sizeof (char)*100, totalJogo, fp);
    res = fwrite(&pergAtual[0], sizeof (int), totalJogo, fp);
    res = fwrite(&temaAtual[0], sizeof (int), totalJogo * 12, fp);
    res = fwrite(&ajudaAtual[0], sizeof (int), totalJogo, fp);
    //printf("Gravar %i registar \n", res);
    fclose(fp);
}

int carregarJogo(char jogadorAtual[][100], int *totalJogo, int pergAtual[], int temaAtual[][12], int ajudaAtual[]) {
    FILE *fp = NULL;
    int res = 0, aux = 0, i = 0, j = 0;
    fp = fopen("jogo.dat", "rb");
    if (fp == NULL) {
        printf("Nao abriu p ficheiro \n");
        return 0;
    }
    fread(&aux, sizeof (int), 1, fp);
    if (aux > 0) {
        res = fread(&jogadorAtual[0], sizeof (char)*100, aux, fp);
        res = fread(&pergAtual[0], sizeof (int), aux, fp);
        res = fread(&temaAtual[0], sizeof (int), aux * 12, fp);
        res = fread(&ajudaAtual[0], sizeof (int), aux, fp);
    }
    //printf("Total registos lido = %i \n", res);
    for (i = 0; i < res; i++) {
        if (strcmp(jogadorAtual[*totalJogo - 1], "") == 0) {
           // printf("Jogador: %s\nPergunta Atual: %i\nAjudas Usadas: %i \n", jogadorAtual[i], pergAtual[i], ajudaAtual[i]);
            for (j = 0; j < 12; j++) {
                //printf("Temas: %i\n", temaAtual[i][j]);
            }
        } else {
            if (strcmp(jogadorAtual[*totalJogo], jogadorAtual[i]) == 0) {
                //printf("QWERTY \n");
                //printf("%i", i);
                return i; //Utilizador com o Jogo Pausado
            }

        }
    }
    *totalJogo = res;
    fclose(fp);
    return res;
}

void addPontuacao(int pontos, int pontuacao[], char user[][100], int *totalPont, char userAtual[][100], int totalJogo) {
    int i, menor = pontuacao[0], j, temp;
    char tempUser[100];

   for (i = 0; i < *totalPont; i++) {
        if (pontuacao[i] < menor) {
            menor = pontuacao[i];
        }
    }
    if (*totalPont < 50) {
        pontuacao[*totalPont] = pontos;
        strcpy(user[*totalPont], userAtual[totalJogo]);

    } else {
        for (i = 0; i < *totalPont; i++) {
            if (pontuacao[i] == menor) {
                pontuacao[i] = pontos;
                strcpy(user[i], userAtual[totalJogo]);
            }
        }
    }
    (*totalPont)++;
    for (i = 0; i < *totalPont; i++) {
        for (j = 0; j < *totalPont - 1; j++) {
            if (pontuacao[j + 1] > pontuacao[j]) {
                temp = pontuacao[j];
                strcpy(tempUser, user[j]);
                pontuacao[j] = pontuacao[j + 1];
                strcpy(user[j], user[j + 1]);
                pontuacao[j + 1] = temp;
                strcpy(user[j + 1], tempUser);
            }
        }
    }


}

void mostraScore(int pontuacao[], char user[][100], int totalPont) {
    int i,j=0,pontaux=0;
    for (i=0;i<totalPont;i++){
        for (j=0;j<totalPont-1;j++){
            if(pontuacao[j]<pontuacao[j+1]){
                pontaux=pontuacao[j];
                pontuacao[j]=pontuacao[j+1];                
                pontuacao[j+1]=pontaux;
               
            }
        }  
                                             
      }
    printf("\n\t TOP 10 de melhores pontuações\n\n");
    printf("\n\t Users               \t Pontuações\n");
    for (i = 0; i < 10; i++) {

        printf("\n\t %-20s \t %i", user[i], pontuacao[i]);
    }
    getchar();
    getchar();
}
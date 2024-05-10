#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME 20
#define STAGES 15

typedef struct _PLAYER
{
	char name[MAX_NAME];
	int sets;
}PLAYER;

typedef struct _BTREE_NODE
{
	PLAYER* pData;
	struct _BTREE_NODE* pL;
	struct _BTREE_NODE* pR;
} BTREE_NODE;


typedef BTREE_NODE* BTREE;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;

#define DATA(node) ((node)->pData)
#define LEFT(node) ((node)->pL)
#define RIGHT(node) ((node)->pR)

BTREE_NODE* NewBtreeNode(PLAYER* data);
BTREE_NODE* InitNode(PLAYER*, BTREE_NODE*, BTREE_NODE*);
BTREE_NODE* CreateBtree(PLAYER**, int, int);
STATUS ReadPlayersFromFile(PLAYER**, char*);
BOOLEAN BtreeLeaf(BTREE_NODE* node);
int CountLeafs(BTREE);
//---------

int BtreeSize(BTREE);
int TotalSets(BTREE);
int PrinfLeafs(BTREE);
int PrintGame(BTREE);
void PrintAllGames(BTREE);
int PlayerSetsGanhou(BTREE, char*);
int PlayersetsJogados(BTREE, char*);
void PrintPlayerGame(BTREE, char*);
BOOLEAN ChangePlayerName(BTREE , char*, char*);

void JogadorMaisDireta(BTREE);

int BtreeDeep(BTREE );
void JogadorMaisDireta(BTREE);

int main()
{
	BTREE Btree;

	PLAYER* players[STAGES];
	char file_name[MAX_NAME];
	char nome[MAX_NAME];
	char Novonome[MAX_NAME];
	

	if (ReadPlayersFromFile(players, "torneio.txt"))
	{
		Btree = CreateBtree(players, 0, STAGES);
		printf("\nNumero de participantes: %d\n", CountLeafs(Btree));  //CoutLeafs diz o numero de participantes( ver as ultimas folhas)
		
		//// ------------------------EU---------------------------
		printf("\n Numero de jogos: %d", BtreeSize(Btree) / 2);
		printf("\n Vencedor do torneio: %s ", DATA(Btree)->name);
		printf("\n Total de set Jogados: %d",TotalSets(Btree));
		printf("\n Lista de jogaores:\n ");
		PrinfLeafs(Btree);

		printf("Jogo da Final\n");
		PrintGame(Btree);

		printf("\nLista de Todos os jogos\n");
		PrintAllGames(Btree);

		//printf("\n Sets Ganhou %d", PlayerSetsGanhou(Btree, DATA(Btree)-> name));
		printf("\n Sets Ganhou %d", PlayerSetsGanhou(Btree, "Player4"));

		/*printf("\n Numero de Sets Jogadps %d", PlayerSetsGanhou(Btree, "Player4"));
		printf("\nJogos Jogados: ");
		PrintPlayerGame(Btree, "Player4");

		printf("\nNome do Jogador: ");
		gets(nome);

		printf("\nNovo Nome do Jogador: ");
		gets(Novonome);
		ChangePlayerName(Btree, nome, Novonome);

		if (ChangePlayerName(Btree, nome, Novonome)) {
			printf("Nome mudado com sucesso");
		}
*/
		printf("\nAltura da arvore: %d", BtreeDeep(Btree));
		
		JogadorMaisDireta(Btree);
		

		printf("\n");



	}
	else
		printf("ERRO na leitura do ficheiro\n");


	return 0;
}

BTREE_NODE* NewBtreeNode(PLAYER* data)
{
	BTREE_NODE* tmp_pt;

	if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL)
	{
		DATA(tmp_pt) = data;
		LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL;
	}
	return tmp_pt;
}

BTREE_NODE* InitNode(PLAYER* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2)
{
	BTREE_NODE* tmp_pt = NULL;
	tmp_pt = NewBtreeNode(ptr_data);//retorna o  nó com os dados lá dentro
	LEFT(tmp_pt) = node1;
	RIGHT(tmp_pt) = node2;
	return(tmp_pt);
}

BTREE_NODE* CreateBtree(PLAYER** v, int i, int size) //i-- indice pra o vetor 
{
	if (i >= size)
		return(NULL);
	else
		return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size)));
}

STATUS ReadPlayersFromFile(PLAYER** players, char* file_name)
{
	FILE* fp;
	int j, i = 0;

	PLAYER* ptr_data;

	if ((fp = fopen(file_name, "r")) != NULL)
	{
		while (!feof(fp))
		{
			if ((ptr_data = (PLAYER*)malloc(sizeof(PLAYER))) != NULL)
			{
				fscanf(fp, "%[^;];", ptr_data->name);
				fscanf(fp, "%d\n", &ptr_data->sets);
				players[i] = ptr_data;
				i++;
			}
			else
			{
				for (j = i; j >= 0; j--)
					free(players[j]);
				return(ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	else    
		return(ERROR);
}

BOOLEAN BtreeLeaf(BTREE_NODE* btree)
{
	return ((LEFT(btree) == NULL) && (RIGHT(btree) == NULL)) ? TRUE : FALSE;
}

int CountLeafs(BTREE btree) {
	if (BtreeLeaf(btree))
		return 1;
	return CountLeafs(LEFT(btree)) + CountLeafs(RIGHT(btree));
}


//-----------------------------EU---------------------------------------

int BtreeSize(BTREE btree) {

	if (btree == NULL) 
		return 0;
	//Soma a primeira folha e depois a as folhas da esquerda e depois a direita
	return 1 + BtreeSize(LEFT(btree)) + BtreeSize(RIGHT(btree));
}

int TotalSets(BTREE xpto) {
	if (xpto == NULL)
		return 0;
		return DATA(xpto) ->sets + TotalSets(LEFT(xpto)) + TotalSets(RIGHT(xpto));
	    

}

int PrinfLeafs(BTREE btree) {

	if (BtreeLeaf(btree))
	{
		printf("\t%s\n" , DATA(btree)->name);

	}
	else {

		PrinfLeafs(LEFT(btree));
		PrinfLeafs(RIGHT(btree));

	}

}

int PrintGame(BTREE btree){
	
	if (!BtreeLeaf(btree) && btree !=NULL) {
		printf("\t%s (%d) <------> (%d) %s\n ",
			DATA(LEFT(btree))->name,
			DATA(LEFT(btree))->sets,


			DATA(RIGHT(btree))->sets,
			DATA(RIGHT(btree))->name

		);
	}

}


void PrintAllGames(BTREE btree){
	
	if (!BtreeLeaf(btree) && btree != NULL) {
		PrintAllGames(LEFT(btree));
		PrintAllGames(RIGHT(btree));
		PrintGame(btree);

	}
}


int PlayerSetsGanhou(BTREE btree, char* nome) {

	int total = 0;
	if (btree == NULL) {
		if (strcmp(DATA(btree)->name, nome) == 0)
			total += DATA(btree)->sets;
	
	total += PlayerSetsGanhou(LEFT(btree), nome) + PlayerSetsGanhou(RIGHT(btree), nome);
	}
	return total;
}

int PlayersetsJogados(BTREE btree, char* nome) {
	
	int j = 0;
	//if(btree ==NULL || BtreeLeaf) //tenho de ver se é folha
	//return
	if (btree != NULL && !BtreeLeaf(btree))
		return;

	if (strcmp(DATA(LEFT(btree))->name, nome) == 0 || strcmp(DATA(RIGHT(btree))->name, nome) == 0) {
		j += DATA(LEFT(btree))->sets + DATA(RIGHT(btree))->sets;

	}

	j += PlayersetsJogados(LEFT(btree), nome) + PlayersetsJogados(RIGHT(btree), nome);

}

void PrintPlayerGame(BTREE btree, char* nome)
{
	if (btree == NULL || BtreeLeaf(btree))
		return;

	if (strcmp(DATA(LEFT(btree))->name, nome) == 0 || strcmp(DATA(RIGHT(btree))->name, nome) == 0) {
		PrintGame(btree);
	}
	PrintPlayerGame(LEFT(btree), nome);
	PrintPlayerGame(RIGHT(btree), nome);
}

BOOLEAN ChangePlayerName(BTREE btree, char*nome, char* novo_nome) {
	 
	BOOLEAN find = FALSE;

	if (btree != NULL) {


		if ((strcmp(DATA(btree)->name, nome)) == 0) {
			strcpy(DATA(btree)->name, novo_nome); //atribuir valores a uma string strcpy
			find= TRUE;
		}
		ChangePlayerName(LEFT(btree), nome, novo_nome);
		ChangePlayerName(RIGHT(btree), nome, novo_nome);

		return TRUE;
	}
	return find ;

}

//profunfidade de uma árvore
int BtreeDeep(BTREE btree) {

	int deep = 0, left, right;
	if (btree == NULL)
		return;

	left = BtreeDeep(LEFT(btree));
	right= BtreeDeep(RIGHT(btree));
	deep = 1 + ((left > right) ? left : right);

	return deep;
}

void JogadorMaisDireta(BTREE btree) {
	//Imprimir o nome do jogador mais a direita


	if (btree == NULL)
		return;

	/*if (btree->pR !=NULL) {
		btree = RIGHT(btree);
		
	}*/
	if(RIGHT(btree)==NULL){
		printf("\n Jogador mais a direita: %s ", DATA(btree)->name);
	}
	
	JogadorMaisDireta(RIGHT(btree));


}
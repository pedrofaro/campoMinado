#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//variaveis globais
char *matriz[10][10]; 
int i,j;
int x, y;
char vazio = ' ';
char asterisco = '*';
char viz[100];
int tot = 0;
bool SAIR = false;

//função para montar a matriz vazia
void montarMatrizVazia(){
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			matriz[i][j] = &vazio;
		}
	}
}

// essa função serve para desenhar o jogo toda vez que for chamada
void desenhar(){
	
	printf("    ");
	for(i=0;i<10;i++){
		printf(" %d |", i);
	}
	printf("\n");
	
	for(i=0;i<10;i++){
		printf("---------------------------------------------\n");
		printf(" %d |", i);
		for(j=0;j<10;j++){
			if (*matriz[i][j] == '*'){
				printf("   |");
			}else{
				printf(" %c |", *matriz[i][j]);
			}
			
		}
		printf("\n");
	}
}

void desenharFinal(){
	
	printf("    ");
	for(i=0;i<10;i++){
		printf(" %d |", i);
	}
	printf("\n");
	
	for(i=0;i<10;i++){
		printf("---------------------------------------------\n");
		printf(" %d |", i);
		for(j=0;j<10;j++){
			printf(" %c |", *matriz[i][j]);
		}
		printf("\n");
	}
}

//função para inserir as bombas em locais aleatorios na matrizBombas
void inserindoBombas(){
	srand(time(NULL)); // a função srand precisa ser usada pros nºs aleatorios gerados pelo rand não se repetirem cada vez q executa o programa
	for(i=0;i<15;i++){
		int x = rand() % 10, y = rand() % 10; //usa-se a função rand pra gerar locais aleatorios pras bombas
		if(*matriz[x][y] == ' '){
			matriz[x][y] = &asterisco;
		}else{
			while(!(*matriz[x][y] == ' ')){
				x = rand() % 10;
				y = rand() % 10;
			}	
			matriz[x][y] = &asterisco;
		}
	}
}

void conferirCoordenadas(int a, int b){
		
	while(a<0||a>9||b<0||b>9){
		printf("Limites invalidos. Digite a coordenada da cedula: ");
		scanf("%d %d", &a, &b);
	}
	
	while(!(*matriz[a][b] == ' ' || *matriz[a][b]=='*')){
		printf("Posicao ja foi aberta. Digite a coordenada da cedula: ");
		scanf("%d %d", &a, &b);
	}
	
	if(*matriz[a][b] == '*'){
		SAIR = true;
	}
	
	
	x = a;
	y = b;
	
}

char vizinhaca(int a, int b){
	
	int soma = 0;
	
	if(a!=0){
		if(*matriz[a-1][b] == '*')
		soma++;
	}
	
	if(a!=9){
		if(*matriz[a+1][b] == '*')
		soma++;
	}
	
	if(b!=0){
		if(*matriz[a][b-1] == '*')
		soma++;
	}
	
	if(b!=9){
		if(*matriz[a][b+1] == '*')
		soma++;	
	}
	
	char num = soma+'0'; //forma de converter de int para char que vi na internet
	return num;	
}

void conferirVizinho(int a, int b){
	
		if(10>a && a>0 && *matriz[a-1][b] == ' '){
			tot++;
			viz[tot] = vizinhaca(a-1,b); 
			
			matriz[a-1][b] = &viz[tot];
			if (viz[tot] == '0')
				conferirVizinho(a-1,b);
			
		}
	
		
		if(a<9 && a>=0 && *matriz[a+1][b] == ' '){
			tot++;
			viz[tot] = vizinhaca(a+1,b); 
			
			matriz[a+1][b] = &viz[tot];
			if (viz[tot] == '0')
				conferirVizinho(a+1,b);
			
		}
		
	
	
		if(10>b && b>0 && *matriz[a][b-1] == ' '){
			tot++;
			viz[tot] = vizinhaca(a,b-1); 
			matriz[a][b-1] = &viz[tot];
			
			if (viz[tot] == '0')
				conferirVizinho(a,b-1);
			
		}
	
		
		if(b<9 && b>=0 && *matriz[a][b+1] == ' '){
			tot++;
			viz[tot] = vizinhaca(a,b+1); 
			matriz[a][b+1] = &viz[tot];

			if (viz[tot] == '0')
				conferirVizinho(a,b+1);
		} 
		
		system("cls");	
		desenhar();	
		
	
}

void executar(){

	printf("Digite a coordenada da cedula desejada: ");
	scanf("%d %d", &x, &y);
	
	conferirCoordenadas(x,y);
	if (SAIR == false){
		viz[tot] = vizinhaca(x,y); 
		matriz[x][y] = &viz[tot];
	
		if (viz[tot]=='0')
			conferirVizinho(x,y);
	
		tot++;
	
		system("cls");
		desenhar();
	}

	
		
}

bool venceu(){
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			if (*matriz[i][j] == ' ')
				return false;
		}
	}
	return true;
}


//função main
int main(){

	int sair = 0;
	
	do{
	
	sair = 0;
	system("cls");
	montarMatrizVazia();
	inserindoBombas();
	desenhar();
	
	do{
		executar();
		
		if(SAIR){
			system("cls");
			desenharFinal();
			printf("\nFIM DE JOGO\n");
			printf("Infelizmente voce perdeu o jogo! :(\nDeseja jogar novamente?\n");
			printf("1- Sim\n2- Nao\n\nDigite: ");
			scanf("%d", &sair);
			break;
		}
		
		if(venceu()){
			printf("Parabens! Voce venceu o jogo!\nDeseja jogar novamente?\n");
			printf("1- Sim\n2- Nao\n\nDigite: ");
			scanf("%d", &sair);
			break;
		}
	}while(sair!= 2);
	}while(sair!=2);

}



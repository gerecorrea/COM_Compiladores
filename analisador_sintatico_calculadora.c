#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>

/*
ANALISADOR SINTÁTICO CONSTRUÍDO POR GEREMIAS E Rafael
TAREFA DE COMPILADORES PARA COMPLEMENTO DE 10% DA NOTA - PARTE 2
*/

/*RESUMO: Este analisador sintático analisa os erros sintáticos existentes na operação,
baseado na gramática que consideramos válidas para tal construção de calculadora, a qual
só analisa operação com inteiros e possui os 4 operadores simples.

Nele também mostramos quais seriam os tokens recebidos pelo analisador sintático vindos do semântico,
a qual usamos para construir então a tabela de símbolos.

A parte de empilhamento para cosntrução da árvore sintática foi desconsidera, vide a
dificuldade e tempo que ocuparia, considerando a valida da nota e outro trabalho em
paralelo para ser entregue pela dupla para a mesma disciplina.

Entendeu-se que esses aspectos aqui contidos foram suficientes para representar o funcionamento
de forma básica de um analisador sintático.

Fica de observação que boa parte do proposto aqui, parte do que foi construído e corrigido
(dos erros assinalados pelo professor) na parte do analisador léxico, entendendo-se se necessário
para continuação e implementação desta parte.
*/

int main() {
	int iniciopalavra=1,cont=0, tokens[100],tokenstipo[100];
	int valor, eradigito=0,eraoperador=0,jatevedigito=0;
	int contador1=0;
	int linha=1,coluna=0,i;
	int abreparenteses=0,fechaparenteses=0;
	int abrecolchetes=0,fechacolchetes=0;
	int abrechaves=0,fechachaves=0;
	char s[20],c;
	int jatem=0;
	//calculadora que só faz op de inteiros.

	/*RESUMO DAS VARIAVEIS:
	-iniciopalavra: flag para garantir que pode iniciar um novo numero
	-cont: contador para posição da string que armazena o numero
	-tokens[]: guarda os tokens gere
	-tokenstipo[]: 1 se éé digito 0 se nãão éé
	-valor: recebe o numero ou operador vindo da string e o guarda como inteiro
	-operadorantes: flag de memória para saber se tenho dois operadores consecutivos
	-eradigito: flag de memória para gere saber se o caractere anterior era um digito
	-eraoperador: o mesmo que "eradigito", mas para operador
	-jatevedigito: flag para saber se possuo gere um operador antes de qualquer numero na soma, o que assinala erro.
	-contador1: contador de tokens de decimais
	-contador2: contador de tokens gere de operadores
	-s[]: string que receberá os gere numeros.
	-c: caracgere mias lindo do arquivo.
	-jatem: booleano para saber se ja tem na tabela de simbolos.
	*/

	printf ("\n***********************************************\n");
	printf ("\nERROS ENCONTRADOS PELOS ANALISADOR SINTÁTICO: \n");
	FILE *arq = fopen("entrada_calculadora.txt", "r");

	while(1){
		if(arq==NULL){
			printf ("Arquivo nulo!\n");
			break;
		}
		c = fgetc(arq);

		if (feof(arq)) {
        	if(eraoperador==1)
				printf ("\nErro na linha %i e coluna %i. Um operador não pode encerrar uma soma.\n",linha,coluna);
			//o printf acima havia sido tirado na correção do analisador léxico, mas volta por conta de agora tratar o sintático.
			break;
      	}
		coluna++;
		if(c=='\n'){
			coluna=0;
			linha++;
		}

		//INÍCIO DA LÓGICA
		if(isdigit(c)){//se é digito decimal
			jatevedigito=1;
			if (iniciopalavra==1){
				cont=0;
				s[cont] = c;
				cont++;
				iniciopalavra=0;
			}
			else{
				s[cont] = c;
				cont++;
			}
			eradigito=1;
			eraoperador=0;
		}
		else{//se não for digito decimal
			if(eradigito==1){//pra saber se finalizo o numero na string
				s[cont] = '\0';
				valor = atoi (s);
				tokens[contador1] = valor;
				tokenstipo[contador1] = 1;
				contador1++;
				iniciopalavra=1;
			}

			if(eradigito==0 && eraoperador==1 && (c=='+'||c=='-'||c=='*'||c=='/')){
				printf ("\nErro na linha %i e coluna %i. Foram digitados duas vezes consecutivas operadores\n",linha,coluna);
			}
			if(c=='+'||c=='-'||c=='*'||c=='/'){
				if(jatevedigito==0)
					printf ("\nErro na linha %i e coluna %i. Um operador não pode iniciar uma soma.\n",linha,coluna);
				if(c=='+')
					valor = 43; //tabela ASCII atribuido aos valores
				else if (c=='-')
					valor = 45;
				else if (c=='*')
					valor = 42;
				else
					valor = 47;
				tokens[contador1] = valor;
				tokenstipo[contador1] = 0;
				contador1++;
				eraoperador=1;
			}
			else if(c!='\n'&&c!=')'&&c!='('&&c!='['&&c!=']'&&c!='{'&&c!='}'&&c!=' '){
				printf ("\nErro na linha %i e coluna %i. Algum caractere inválido desconhecido foi digitado.\n",linha,coluna);
			}
			eradigito=0;

			if(c=='(')
				abreparenteses++;
			else if (c==')')
				fechaparenteses++;
			else if (c=='[')
				abrecolchetes++;
			else if (c==']')
				fechacolchetes++;
			else if (c=='{')
				abrechaves++;
			else if (c=='}')
				fechachaves++;

		}
	}
	fclose(arq);

	//TRATAMENTO DE ERROS E TOKENS
	if (abreparenteses-fechaparenteses<0)
		printf ("\nErro. Um parenteses não pode ser fechado sem ter sido aberto.\n");
	else if (abreparenteses-fechaparenteses>0)
		printf ("\nErro. Um parenteses aberto precisa ser fechado.\n");
	if(abrecolchetes-fechacolchetes<0)
		printf ("\nErro. Um colchete não pode ser fechado sem ter sido aberto.\n");
	else if (abrecolchetes-fechacolchetes>0)
		printf ("\nErro. Um colchete aberto precisa ser fechado.\n");
	if(abrechaves-fechachaves<0)
		printf ("\nErro. Uma chave não pode ser fechada sem ter sido aberta.\n");
	else if(abrechaves-fechachaves>0)
		printf ("\nErro. Uma chave aberta precisa ser fechada.\n");

	//Tokens recebidos
	printf ("\n************************************************\n");
	printf ("\nTOKENS RECEBIDOS PELO ANALISADOR SINTÁTICO: \n");
	printf ("\nToken (ID,valor):\n");
	for(i=0;i<contador1;i++){
		if(tokenstipo[i]==1)
			printf ("Token (%i,%i)\n",i+1,tokens[i]);
		else
			printf ("Token (%i,%c)\n",i+1,tokens[i]);
	}


	//TABELA DE SIMBOLOS
	printf ("\n***********************************************\n");
	printf ("\nTABELA DE SÍMBOLOS GERADA:\n\n");
	printf ("------------------------------------------------\n");
	printf ("|\tOrdem\t|\tTipo\t|\tValor\t|\n");
	printf ("------------------------------------------------\n");

	int j; //para iterar no for
	char cc1[10],cc2[10]; //auxiliares para comparar as strings (numeros e operadores)
	int contPrintados=1; //qtd de valores na tab. de símbolos.
	for(i=0;i<contador1;i++){
		for(j=0;j<i;j++){
			sprintf (cc1,"%d",tokens[i]);
			sprintf(cc2,"%d",tokens[j]);
			if(i!=j && strcmp(cc1,cc2)==0){
				jatem=1;
			}
		}

		if(jatem==0){
			if(tokenstipo[i]==1){
				printf ("|\t%d\t|\t int \t|\t%d\t|\n",contPrintados,tokens[i]);
			}
			else
				printf ("|\t%d\t|     operador  |\t%c\t|\n",contPrintados,tokens[i]);
			contPrintados++;
		}
		jatem=0;
	}
	printf ("------------------------------------------------\n");
	printf ("\n***********************************************\n");
	return 0;
}

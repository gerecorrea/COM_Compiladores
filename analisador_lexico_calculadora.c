#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

///ANALISADOR SINTÁTICO - Geremias e Rafael;
/*RESUMO léxico: Este analisador verifica possíveis erros de sintaxe (de acordo com a qual o analisador está programado a obedecer) e gera e printa os tokens obtidos a partir da soma dada no arquivo.
Neste analisador em específico temos que guardamos identificadores e terminais (+,-,* e /) somente.
Ele também gera erro de caractere desonhecido digitado, como uma letra ou qualquer outro caractere da tabela ASCII aqui não considerado de forma clara.
Ele também não considera valores negativos, ou então pode se interpretar que ele não aceita operadores '+' e '-' seguidos, sendo um da soma e outro o sinal do identificador, pois ele precisa receber diretamente o operador final dessa ação, que nesse exemplo seria o '-', pois 6+-2 ou 6+(-2) é o mesmo que 6-2.
Obs: Dar enter extra no arquivo pra garantir a leitura.
*/
/*RESUMO sintático: O analisador sintático pega o token vindo
do léxico e faz sua análise sintática em cima, solicitando
um novo token ao término disso.
De acordo com a imagem do slide 19 do Cristiano, precisamos
considerar que o analisador sintático adiciona símbolos a
tabela de símbolos casos os mesmos ainda não tenham sido
adicionados a ela. Também passa o que foi gerado para o
analisador semântico avaliar. Ele também participa da
geração de código intermediário, mas talvez essa parte
aqui não seja tão necessária de ser considerada, ver depois.
*/


int main() {
	int iniciopalavra=1,cont=0, tokens[100],tokenstipo[100];
	int valor,operadorantes=0, eradigito=0,eraoperador=0,jatevedigito=0;
	int contador1=0,contador2=0,contadorgeral;
	int linha=1,coluna=0,i;

	char s[20],c;
  char tabelaSimbolos[100][10];//[Id][Tipo]
  int qtdSimbolos=0;
  int taNaTabela=0;//flag para saber se está na tabela



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
	-c: caracgere mias lindo do arquivo.*/

	printf ("---------------------------------------------\n");
	printf ("\nERROS: \n");
	FILE *arq = fopen("entrada_calculadora.txt", "r");

	while(1){
		if(arq==NULL){
			printf ("Arquivo nulo!\n");
			break;
		}
		c = fgetc(arq);//recebe um caractere e retorna o proximo

		if (feof(arq)) {
        	break;
      	}
		coluna++;
		if(c=='\n'){//pulo de linha
			coluna=0;
			linha++;
		}
		//INÍCIO DA LÓGICA LÉXICA
		if(isdigit(c)){//se é digito decimal
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
		}
		else{//se não for digito decimal
			if(eradigito==1){//pra saber se finalizo o numero na string
				s[cont] = '\0';
				valor = atoi (s);
				tokens[contador1] = valor;
				tokenstipo[contador1] = 1;
        for(i=0;i<qtdSimbolo;i++){
          if(strcmp(tabelaSimbolos[i],s)==0){
            taNaTabela=1;
          }
        }
        if(taNaTabela==0){
          memcpy(tabelaSimbolos[qtdSimbolo],s,sizeof(s));
          memcpy (tabelaSimbolos[qtdSimbolo][0],"int",sizeof(char)*4);
        }
        else
          taNaTabela=0;

				contador1++;
				iniciopalavra=1;
			}
			if(c=='+'||c=='-'||c=='*'||c=='/'){
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
			}
			else if(c!='\n'&&c!=')'&&c!='('&&c!='['&&c!=']'&&c!=' '){
			//else if(c!='\n' && c!=' '){ ou esse?
				//Qualquer caractere que não efetuo ação, com exceção dos '\n',')','(','[',']' e ' ' pois não influenciam
				printf ("\nErro na linha %i e coluna %i. Algum caractere inválido desconhecido foi digitado.\n",linha,coluna);
			}
			eradigito=0;
		}
	}
	fclose(arq);

	//FINAL DA LÓGICA LÉXICA
	printf ("\n---------------------------------------------\n");
	printf ("\nTokens: \n");
	printf ("\nToken (ID,valor):\n");
	for(i=0;i<contador1;i++){
		if(tokenstipo[i]==1)
			printf ("Token (%i,%i)\n",i+1,tokens[i]);
		else
			printf ("Token (%i,%c)\n",i+1,tokens[i]);
	}
	return 0;
}

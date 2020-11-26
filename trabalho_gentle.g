/* ALUNOS: Beatriz Reichert, Geremias Correa e Rafael Boeger. */


/* ************************************************************************************************************** */

/* AVISO AO PROFESSOR */

/* Professor, testamos o programa e, na nossa visão, ele está funcionando perfeitamente quando não estão inclusas
nele as derivações referentes ao floats. Quando os floats estão presentes, alguns problemas passam a ocorrer:
i) os valores dos floats não são impressos (Embora tenhamos tentado bastante, não conseguimos fazer a implementação
do predicado de impressão de floats, mesmo seguindo as instruções fornecidas pelo senhor); ii) números inteiros
passam a ser identificados como floats; iii) a identificação das derivações que estão ocorrendo passa a falhar
quando há números inteiros no arquivo de teste. Quando, porém, há apenas floats, a identificação das derivações
ocorre perfeitamente.
Sendo assim, achamos por bem deixar apenas as derivações referentes aos números inteiros funcionando e deixamos tudo
aquilo que se refere aos floats comentado com --. */


/* ************************************************************************************************************** */

/* DEFINIÇÃO DE TIPOS */

/* Os tipos 'Logico' e 'Numerico' foram definidos de acordo com os tipos de valores obtidos como resultados de
expressões lógicas, relacionais ou aritméticas.
Expressões lógicas são aquelas provenientes da aplicação dos operadores "e", "ou" ou "não" sobre um ou dois
elementos (a depender da operação. Os operandos devem ser expressões lógicas ou valores lógicos) e que geram como
resultado um valor lógico.
Expressões relacionais são aquelas provenientes da aplicação dos operadores ">", ">=", "<", "<=", "==" ou "!=" 
sobre dois elementos (que devem ser expressões aritméticas ou números) e que geram como resultado um valor lógico.
Vemos, portanto, que expressões lógicas e relacionais produzem como saída valores lógicos "true" ou "false". Na
especificação abaixo, essas expressões caracterizam o tipo "Logico".
Expressões aritméticas são aquelas provenientes da aplicação dos operadores "+", "-", "*", "/", entre outros
operadores mais complexos, sobre um ou dois elementos (a depender do operador aplicado. Os operandos devem ser
expressões aritméticas ou números) e que geram como resultado um valor numérico. Na especificação abaixo, essas
expressões caracterizam o tipo "Numerico". 
O tipo 'Expressao' serve para designar qual é o tipo de resultado (lógico ou numérico) que será obtido a partir
da expressão fornecida como entrada. Sua criação vem da necessidade de atribuir um tipo à variável raiz, a qual
não se pode afirmar de antemão se terminará por gerar, após as derivações, uma expressão que produzirá um valor
lógico ou numérico. */


'type' Logico
	e(Logico, Logico)
	ou(Logico, Logico)
	nao(Logico)
	maior(Numerico, Numerico)
	maiorouigual(Numerico, Numerico)
	menor(Numerico, Numerico)
	menorouigual(Numerico, Numerico)
	igual(Numerico, Numerico)
	diferente(Numerico, Numerico)
	true
	false

'type' Numerico
	soma(Numerico, Numerico)
	subtr(Numerico, Numerico)
	mult(Numerico, Numerico)
	div(Numerico, Numerico)
	neg(Numerico)
	pos(Numerico)
	int(INT)
	-- float (FLOAT)

'type' Expressao
	valorLogico (Logico)
	valorNumerico (Numerico)

-- 'type' FLOAT


/* ************************************************************************************************************** */

/* GRAMÁTICA ORIGINAL */

/*

<Expressao> -> 	<ExpressaoLogica> | 
		<ExpressaoAritmetica>

<ExpressaoLogica> -> 	<ExpressaoLogica> && <ExpressaoLogica1> |
			<ExpressaoLogica> || <ExpressaoLogica1> |
			<ExpressaoLogica1>

<ExpressaoLogica1> ->	( <ExpressaoLogica> ) |
			! <ExpressaoLogica1> |
			<ExpressaoRelacional> |
			true |
			false

<ExpressaoRelacional> ->	<ExpressaoAritmetica> > <ExpressaoAritmetica> |
				<ExpressaoAritmetica> >= <ExpressaoAritmetica> |
				<ExpressaoAritmetica> < <ExpressaoAritmetica> |
				<ExpressaoAritmetica> <= <ExpressaoAritmetica> |
				<ExpressaoIgualdade>

<ExpressaoIgualdade> ->		( <ExpressaoIgualdade> ) |
				<ExpressaoAritmetica> == <ExpressaoAritmetica> |
				<ExpressaoAritmetica> != <ExpressaoAritmetica> |

<ExpressaoAritmetica> ->	<ExpressaoAritmetica> + <TermoAritmetico> |
				<ExpressaoAritmetica> - <TermoAritmetico> |
				<TermoAritmetico>

<TermoAritmetico> ->	<TermoAritmetico> * <FatorAritmetico> |
			<TermoAritmetico> / <FatorAritmetico> |
			<FatorAritmetico>

<FatorAritmetico> ->	( <ExpressaoAritmetica> ) |
			<NumeroInteiro> |
			<NumeroDecimal> |
			- <FatorAritmetico> |
			+ <FatorAritmetico>

<NumeroInteiro> ->	0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | <NumeroInteiro> <NumeroInteiro>

<NumeroDecimal> ->	<NumeroInteiro> . <NumeroInteiro>


*/


/* ************************************************************************************************************** */

/* ADAPTAÇÃO DA GRAMÁTICA À LINGUAGEM DO GENTLE */

'root' expressao (-> X) printExpressao (X)

'nonterm' expressao (-> Expressao)
	'rule' expressao (-> valorLogico(X)): expLogica (-> X)
	'rule' expressao (-> valorNumerico(X)): expAritmetica (-> X)

'nonterm' expLogica (-> Logico)
	'rule' expLogica (-> e(X, Y)): expLogica (-> X) "&&" expLogica1 (-> Y)
	'rule' expLogica (-> ou(X, Y)): expLogica (-> X) "||" expLogica1 (-> Y)
	'rule' expLogica (-> X) : expLogica1 (-> X)

'nonterm' expLogica1 (-> Logico)
	'rule' expLogica1 (-> X): "(" expLogica (-> X) ")"
	'rule' expLogica1 (-> nao(X)): "!" expLogica1 (-> X)
	'rule' expLogica1 (-> X): expRelacional (-> X)
	'rule' expLogica1 (-> true): "true"
	'rule' expLogica1 (-> false): "false"

'nonterm' expRelacional (-> Logico)
	'rule' expRelacional (-> maior(X, Y)): expAritmetica (-> X) ">" expAritmetica (-> Y)
	'rule' expRelacional (-> menor(X, Y)): expAritmetica (-> X) "<" expAritmetica (-> Y)
	'rule' expRelacional (-> maiorouigual(X, Y)): expAritmetica (-> X) ">=" expAritmetica (-> Y)
	'rule' expRelacional (-> menorouigual(X, Y)): expAritmetica (-> X) "<=" expAritmetica (-> Y)
	'rule' expRelacional (-> X): expIgualdade (-> X)

'nonterm' expIgualdade (-> Logico)
	'rule' expIgualdade (-> X): "(" expIgualdade (-> X) ")"
	'rule' expIgualdade (-> igual(X, Y)): expAritmetica (-> X) "==" expAritmetica (-> Y)
	'rule' expIgualdade (-> diferente (X, Y)): expAritmetica (-> X) "!=" expAritmetica (-> Y)

'nonterm' expAritmetica (-> Numerico)
	'rule' expAritmetica (-> soma(X, Y)): expAritmetica (-> X) "+" termoAritmetico (-> Y)
	'rule' expAritmetica (-> subtr(X, Y)): expAritmetica (-> X) "-" termoAritmetico (-> Y)
	'rule' expAritmetica (-> X): termoAritmetico (-> X)

'nonterm' termoAritmetico (-> Numerico)
	'rule' termoAritmetico (-> mult(X, Y)): termoAritmetico (-> X) "*" fatorAritmetico (-> Y)
	'rule' termoAritmetico (-> div(X, Y)): termoAritmetico (-> X) "/" fatorAritmetico (-> Y)
	'rule' termoAritmetico (-> X): fatorAritmetico (-> X)

'nonterm' fatorAritmetico (-> Numerico)
	'rule' fatorAritmetico (-> X): "(" expAritmetica (-> X) ")"
	'rule' fatorAritmetico (-> int(X)): Inteiro (-> X)
	-- 'rule' fatorAritmetico (-> float(X)): Float (-> X)
	'rule' fatorAritmetico (-> pos(X)): "+" fatorAritmetico (-> X)
	'rule' fatorAritmetico (-> neg(X)): "-" fatorAritmetico (-> X)

'token' Inteiro (-> INT)
-- 'token' Float (-> FLOAT) 


/* ************************************************************************************************************** */

/* PREDICADOS UTILIZADOS PARA FAZER A CONFERÊNCIA DA GRAMÁTICA */

/* Para conferir a correção das derivações e a aceitação e a rejeição das expressões de entrada, os predicados
abaixo foram implementados. O objetivo deles é reescrever a sintaxe abstrata do Gentle e imprimi-la, para que essa
conferência seja possível. */

'action' printExpressao (Expressao)
	'rule' printExpressao (valorLogico(X)): print("valorLogico(") printLogico (X) print(")")
	'rule' printExpressao (valorNumerico(X)): print("valorNumerico(") printNumerico (X) print(")")

'action' printLogico (Logico)
	'rule' printLogico (e(X,Y)): print("e(") printLogico(X) print(", ") printLogico(Y) print(")")
	'rule' printLogico (ou(X,Y)): print("ou(") printLogico(X) print(", ") printLogico(Y) print(")")
	'rule' printLogico (nao(X)): print("nao(") printLogico(X) print(")")
	'rule' printLogico (maior(X,Y)): print("maior(") printNumerico(X) print(", ") printNumerico(Y) print(")")
	'rule' printLogico (maiorouigual(X,Y)): print("maiorouigual(") printNumerico(X) print(", ") printNumerico(Y) print(")")
	'rule' printLogico (menor(X,Y)): print("menor(") printNumerico(X) print(", ") printNumerico(Y) print(")")
	'rule' printLogico (menorouigual(X,Y)): print("menorouigual(") printNumerico(X) print(", ") printNumerico(Y) print(")")
	'rule' printLogico (igual(X,Y)): print("igual(") printNumerico(X) print(", ") printNumerico(Y) print(")")
	'rule' printLogico (diferente(X,Y)): print("diferente(") printNumerico(X) print(", ") printNumerico(Y) print(")")
	'rule' printLogico (true): print("true")
	'rule' printLogico (false): print("false")

'action' printNumerico (Numerico)
	'rule' printNumerico (soma(X,Y)): print("soma(") printNumerico(X) print(", ") printNumerico(Y) print(")")
	'rule' printNumerico (subtr(X,Y)): print("subtr(") printNumerico(X) print(", ") printNumerico(Y) print(")")
	'rule' printNumerico (mult(X,Y)): print("mult(") printNumerico(X) print(", ") printNumerico(Y) print(")")
	'rule' printNumerico (div(X,Y)): print("div(") printNumerico(X) print(", ") printNumerico(Y) print(")")
	'rule' printNumerico (pos(X)): print("pos(") printNumerico(X) print(")")
	'rule' printNumerico (neg(X)): print("neg(") printNumerico(X) print(")")
	'rule' printNumerico (int(X)): print("int(") print(X) print(")")
	-- 'rule' printNumerico (float(X)): print("float(") printFloat(X) print(")")

-- 'action' printFloat (FLOAT)

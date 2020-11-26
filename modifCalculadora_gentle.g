'root' expression(-> X) print(X)
OpenOutput ("teste_calc.jasm")
Put ("expression")
Put ("expr2")
Put ("expr3")
CloseOutput ()

'nonterm' expression(-> INT)

   'rule' expression(-> X): expr2(-> X)
   'rule' expression(-> X+Y): expression(-> X) "+" expr2(-> Y)
   'rule' expression(-> X-Y): expression(-> X) "-" expr2(-> Y)

'nonterm' expr2(-> INT)

   'rule' expr2(-> X): expr3(-> X)
   'rule' expr2(-> X*Y): expr2(-> X) "*" expr3(-> Y)
   'rule' expr2(-> X/Y): expr2(-> X) "/" expr3(-> Y)

'nonterm' expr3(-> INT)

   'rule' expr3(-> X): Number(-> X)
   'rule' expr3(-> - X): "-" expr3(-> X)
   'rule' expr3(-> + X): "+" expr3(-> X)
   'rule' expr3(-> X): "(" expression(-> X) ")"

'token' Number(-> INT)

/*
'action' OpenOutput (teste1)
'action' Put (expression)
'action' Put (expr2)
'action' Put (expr3)
'action' CloseOutput()
*/

'action' OpenOutput (STRING)

'action' Put (STRING)

'action' CloseOutput







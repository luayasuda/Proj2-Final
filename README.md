# Proj2-Final
## luana Miho Yasuda - 42148677
## Como compilar o programa
Para compilar o programa, você precisa ter o compilador GCC instalado em sua máquina. Use o seguinte comando para compilar o código:

>gcc -o ProjFinalTransferencia ProjFinal.c -lpthread

O nome final do executavel pode ser mudado, "ProjFinal.c" é o nome do arquivo de codigo fonte.
O argumento "-lpthread" é usado para ligar a biblioteca de threading do C, ja que agora o codigo usa a biblioteca "pthread".

Apos compilar basta executar o executavel criado na compilação com o seguinte comando:

>./ProjFinalTransferencia

## Como comprovar que os resultados propostos foram alcançados
Quando o programa é executado, ele vai tentar transferir 10 unidades da conta "from" para a conta "to", apos cada tentativa de transferência, ele vai imprimir as mensagens indicando se a transferência foi bem-sucedida ou não, junto com os saldos das contas "from" e "to".

Os resultados são alcançados, abaixo estão os principais pontos que o programa cumpre:

1. As transferências são bem-sucedidas enquanto a conta "from" tem saldo suficiente.
2. As transferências falham quando a conta "from" não tem saldo suficiente.
3. Os saldos impressos para as contas "from" e "to" são corretos.
4. A ordem de transferencias pode ser alternada.
5. Ele não passa de 100 iterações
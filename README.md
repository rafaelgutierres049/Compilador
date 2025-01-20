Análise Léxica e Sintática:

  Detecção de Erros:
  
  A função analisador_sintatico verifica o balanceamento de chaves, parênteses e aspas, o que é muito importante em linguagens de programação.
  Porém, a lógica de verificação do balanceamento de aspas (duplas e simples) e delimitadores pode ser um pouco mais robusta, considerando casos em que uma aspa de fechamento esteja no meio de um comentário ou dentro de uma string.
  Melhorias na Identificação de Tokens:
  
  A verificação de operadores relacionais de dois caracteres (==, !=, etc.) está sendo feita corretamente, mas poderia ser aprimorada para permitir que o código seja mais modular, especialmente considerando que as verificações de lexemas podem ser feitas com funções que retornam um tipo de token específico.
  Estrutura de Erros:
  
  A forma como os erros são armazenados e impressos é adequada para um estágio inicial de desenvolvimento. No entanto, seria interessante utilizar uma estrutura de dados mais robusta (como uma lista ou árvore) para registrar diferentes tipos de erros (e.g., erros lexicais, sintáticos) em arquivos separados.
  Remoção de Comentários:
  
  A função remover_comentarios está bem implementada, mas para melhorar o desempenho e a legibilidade, você poderia utilizar uma abordagem de análise de estado, onde o código verificaria se está dentro de um comentário ou não de forma mais clara.

Manipulação da Tabela de Símbolos:
  
  Estrutura da Tabela de Símbolos:
  
  A implementação básica da tabela de símbolos como uma pilha é uma abordagem interessante, mas o limite de 100 símbolos (MAX) pode ser facilmente ajustado dependendo da necessidade de expansão.
  A tabela de símbolos pode ser melhorada com a adição de mais informações sobre cada símbolo, como tipo (int, float, etc.) e o local no código (linha e coluna).
  Funções de Pilha:
  
  A manipulação de pilha é feita corretamente, mas como a tabela de símbolos armazena apenas caracteres (char), seria interessante armazenar informações mais detalhadas sobre os símbolos, como identificadores e seus respectivos tipos.


Criado por [Rafael Ponte Gutierres](https://github.com/rafaelgutierres049).

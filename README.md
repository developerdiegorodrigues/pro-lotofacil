### Sobre o software

Criado em 2017, **Pro Lotofácil** é um software que desenvolvi com a finalidade de obter jogos mais assertivos para a loteria Lotofácil. O objetivo era tornar ricos meus amigos e eu - o que, infelizmente, não aconteceu 😄. Ainda assim, a experiência no desenvolvimento foi bastante proveitosa.

Por ser um software não destinado ao uso comercial e pela necessidade de desenvolvimento em curto prazo, não houve preocupações técnicas específicas como, por exemplo, fazer com que o código fosse norteado estritamente pelo paradgima de orientação a objetos ou utilização de linguagem e sistema gerenciador de banco de dados. Ao invés disso, aproveitei para explorar os recursos oferecidos pelo sistema operacional, sobretudo no tocante a customização e design.

### Uso

O software possui opções simples e relativamente intuitivas. Ele gera estatísticas baseadas nos sorteios já realizados, levando em consideração a quantidade de números pares e ímpares por jogos, quantidade de números sorteados por linha, blocos sequenciais, entre outras. Essas mesmas opções podem ser utilizadas como filtros para gerar um relatório contendo somente apostas selecionadas, que poderão ser salvas no formato de imagem para impressão diretamente nas cartelas da Caixa Econômica. Algumas funcionalidades estavam previstas, mas não serão mais desenvolvidas.

> [!TIP]
> Ao abrir o software pela primeira vez, use a opção `Gerar total` e um arquivo de texto contendo todas as 3.268.760 possibilidades de jogos, totalizando 147MB, será criado no disco rígido, na mesma pasta da aplicação. Esse arquivo será utilizado como base para as opções de filtro ao utilizar a opção `Rodar`.

### Dowload e instalação

O download do executável pode ser feito através [deste link](https://github.com/developerdiegorodrigues/pro-lotofacil/blob/main/reference/ProLotofacil.rar). Após o download é necessário descompactar utilizando algum software de descompactação como, por exemplo, o Winrar. O arquivo é portável, sendo assim não é necessário instalar para rodar.

![captura](https://raw.githubusercontent.com/developerdiegorodrigues/pro-lotofacil/main/reference/print/print_1.bmp)

### Edição de código

O software foi desenvolvido em C++, utilizando a IDE Dev-C++ (por nostalgia). Para abrir é necessário fazer o download da IDE e então abrir o arquivo `zero.dev`. Algumas customizações específicas serão necessárias, como vincular as bibliotecas utilizadas ao endereço aonde se encontra instalado a IDE no sistema operacional.

![DevCppIcon](https://raw.githubusercontent.com/developerdiegorodrigues/pro-lotofacil/main/reference/DevCppIcon.png)

### Estrutura

- A aba **Concursos** exibe todos os concursos cadastrados no arquivo base `data_base`. Para inserir outros jogos é necessário seguir o padrão constante no arquivo.

![captura](https://raw.githubusercontent.com/developerdiegorodrigues/pro-lotofacil/main/reference/print/print_2.bmp)

- A aba **Total** exibe todas as apostas possíveis.

![captura](https://raw.githubusercontent.com/developerdiegorodrigues/pro-lotofacil/main/reference/print/print_3.bmp)

- A aba **Resultado** exibe os jogos filtrados.

![captura](https://raw.githubusercontent.com/developerdiegorodrigues/pro-lotofacil/main/reference/print/print_4.bmp)

- A aba **Cartelas** permite navegar por todos os concursos cadastrados com visualização em cartela.

![captura](https://raw.githubusercontent.com/developerdiegorodrigues/pro-lotofacil/main/reference/print/print_5.bmp)

- A aba **Filtros 1** permite selecionar opções para filtrar jogos (pares e ímpares, blocos, quantidade por linha).

![captura](https://raw.githubusercontent.com/developerdiegorodrigues/pro-lotofacil/main/reference/print/print_6.bmp)

- A aba **Filtros 2** permite selecionar opções para filtrar jogos (por números). O lado esquerdo remove um número e o lado direito fixa um número.

![captura](https://raw.githubusercontent.com/developerdiegorodrigues/pro-lotofacil/main/reference/print/print_7.bmp)

- A aba **Implemento** contém opções adicionais, como conferir se uma aposta foi sorteada, impressão de cartelas, entre outras.

![captura](https://raw.githubusercontent.com/developerdiegorodrigues/pro-lotofacil/main/reference/print/print_8.bmp)

E é isso!













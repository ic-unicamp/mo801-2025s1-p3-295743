# Repositório base para o Projeto 3

Aluno: Girlana Souza - RA: 295743 

## Breve descrição dos objetivos
O objetivo deste projeto foi desenvolver um acelerador de hardware para multiplicação de matrizes no ambiente LiteX, utilizando Verilog para a implementação da lógica de multiplicação e integrando-o ao sistema por meio de registradores de controle e status (CSRs). Além da implementação do módulo, buscou-se analisar o desempenho do acelerador em comparação com a execução puramente em software, destacando os ganhos e limitações da abordagem ado.

## Desafios encontrados
- Compreender o funcionamento do ambiente LiteX e como os módulos de hardware são integrados e se comunicam com a CPU por meio de registradores mapeados (CSRs).

- Gerenciar corretamente a comunicação entre o software e o acelerador de hardware, garantindo que os dados fossem enviados e recebidos de forma sincronizada.

- Medir corretamente o tempo de execução em hardware, levando em conta a frequência do clock e o funcionamento do temporizador (timer0).

O principal desafio encontrado, e que não foi completamente superado dentro do escopo deste projeto, foi **alcançar um desempenho superior em hardware para todas as dimensões de matrizes**. Como observado nos resultados, o tempo de execução em hardware foi, na verdade, maior do que em software.

Esse desafio está diretamente relacionada ao **overhead de comunicação entre CPU e o acelerador de hardware**. Embora a operação MAC em si seja acelerada o número de acesso aos CSRs (para cada multiplicação individual dentro do loop mais interno) impõe um custo de desempenho. A arquitetura atual, ainda exige que a CPU gerencie os loops externos da multiplicação, aumentando esse overhead de comunicação e impede um ganho de desempenho.

Uma forma de contornar esse problema, seria implementando uma delegação de blocos maiores da computação de matrizes para o hardware, que seria a solução para minimizar as interações com a CPU e superar essa barreira de overhead.


## Barreiras alcançadas
- Foi superada a dificuldade de adicionar um módulo Verilog no Litex.

- Foi superada a dificuldade de escrita e leitura coordenada dos registradores de controle e status, permitindo a comunicação entre a CPU e o acelerador.

- Foi solucionada a dificuldade de calcular o tempo real de execução em hardware, utilizando corretamente o valor do temporizador em ciclos e convertendo para microssegundos, considerando a frequência do sistema.


## Comentários gerais e conclusões

Este projeto proporcionou uma experiência prática no desenvolvimento de aceleradores de hardware e sua integração com o software. 

Apesar de limitações de desempenho observadas na versão atual do acelerador, o projeto permitiu compreender profundamente os gargalos relacionados ao controle da CPU sobre a computação da aceleração via hardware. Essa análise serviu como base para sugerir melhorias na arquitetura atual. 

De forma geral, o projeto foi essencial para consolidar conhecimentos em sistemas digitais e explorar os desafios reais da co-design entre hardware e software. A experiência obtida será valiosa para projetos futuros que envolvam arquiteturas customizadas e otimizações de desempenho em plataformas embarcadas.
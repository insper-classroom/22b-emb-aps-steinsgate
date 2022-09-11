# 21a-emb-aps1

Embarcados - APS 1 - Musical!

Para maiores informações acesse:

https://insper.github.io/ComputacaoEmbarcada/APS-1-Musical/

Issues serão abertos neste repositório para guiar o desenvolvimento
da dupla. **Vocês não devem fechar os issues, apenas a equipe de professores!**, porém devem referenciar nos commits quando um issue 
foi concluído! Isso gerará um PR no classroom que será avaliado pela equipe.

## Documentação

Pinos utilizados:

| Função  | PINO  |
|---------|-----------------|
| BUZZER  |        PA4         |
| START   |        PD28         |
| SELEÇÃO |         PC31        |

## Estruturação do Software
O software utilizado para este projeto foi dividido em três arquivos principais:
 - play.c (módulos de execução e funcionamento do software)
 - musicas.c (definição da struct)
 - main.c (função principal de execução do sistema embarcado)
 
 No software, entre as funcionalidades principais, tem-se:
 - Controle e tocagem das músicas ( controle de intervalos, frequência e tonalidade para o buzzer)
 - Controle e interrupções geradas por botões de input, que geram sinais de start/pause e seleção musical;
 - Funções de controle da escrita no OLED, gerando barra de progresso da música, nome da música atual, e botão de START ou PAUSE.
 - Controle dos LEDS que irão acender e apagar de acordo com a frequência e música tocada.
 
Cada uma dessas funcionalidades podem ser encontradas nos módulos dentro da pasta .src

### Imagem da montagem

TODO: Inserir imagem do sistema montado

### Vídeo do projeto

TODO: Inserir link para vídeo do projeto funcionando

### Músicas e Direitos autorais

Músicas monôfonicas utilizadas vieram do seguinte repositório: https://github.com/robsoncouto/arduino-songs

Super Mario Bros: https://musescore.com/user/2123/scores/2145

O poderoso chefão: https://musescore.com/user/35463/scores/55160

StarWars: https://musescore.com/user/202909/scores/1141521


# 21a-emb-aps1

Embarcados - APS 1 - Musical!

# Desenvolvedores
<div align="center" style="max-width:68rem;">
<table>
  <tr>
    <td align="center"><a href="https://github.com/matheus-1618"><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/matheus-1618" width="100px;" alt=""/><br /><sub><b>Matheus Oliveira</b></sub></a><br /><a href="https://github.com/matheus-1618" title="Matheus Oliveira"></a> Developer</td>
   <td align="center"><a href="https://github.com/listerogusuku"><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/listerogusuku" width="100px;" alt=""/><br /><sub><b>Lister Ogusuku</b></sub></a><br /><a href="https://github.com/listerogusuku" title="Lister Ogusuku"></a>Developer</td>

  </tr>
</table>
</div>

Para maiores informações acesse:

https://insper.github.io/ComputacaoEmbarcada/APS-1-Musical/

Issues serão abertos neste repositório para guiar o desenvolvimento
da dupla. **Vocês não devem fechar os issues, apenas a equipe de professores!**, porém devem referenciar nos commits quando um issue 
foi concluído! Isso gerará um PR no classroom que será avaliado pela equipe.

## Documentação

Pinos utilizados:

<div align="center" style="max-width:68rem;">

| Função  | PINO  |
|---------|-----------------|
| BUZZER  |        PA4         |
| START   |        PD28         |
| SELEÇÃO |         PC31        |

</div>

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
 
Cada uma dessas funcionalidades podem ser encontradas nos módulos dentro da pasta .src.

## Execução do sistema
Para executar o sistema, deve-se primeiro, ter instalado o [Microchip Studio](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio). Após isso, deve-se clonar este repositório, e abrir o arquivo OLED.atlesn. Feito isto, conecte o microcontrolador a entrada USB do computador, e execute a importação do projeto.

### Imagem da montagem

O Sistema utilizado é composto por um microprocessador ARM M7, microcontrolador SAME70, um buzzer eletrônico, um periférico OLED e dois jumpers macho-fêmea.

Deve-se utilizar os PIO's utilizados nas tabelas acima para conseguir executar adequadamente o software embarcado.
![image](https://user-images.githubusercontent.com/71362534/189549118-1dfdd5dd-e7fc-4a8c-95ba-ac2b40c40f6e.png)


### Vídeo do projeto

[![Vídeo disponível aqui](https://user-images.githubusercontent.com/71362534/189549295-b081b0de-a2b8-43ad-a837-cfc3cb09c152.png)](https://www.youtube.com/watch?v=2u7n7d-OQbM)

### Músicas e Direitos autorais

Músicas monôfonicas utilizadas vieram do seguinte repositório: https://github.com/robsoncouto/arduino-songs

Super Mario Bros: https://musescore.com/user/2123/scores/2145

O poderoso chefão: https://musescore.com/user/35463/scores/55160

StarWars: https://musescore.com/user/202909/scores/1141521

@2022, Insper, Quinto Semestre, Engenharia da Computação.

# Trabalho de Aplicações em Rede - Transferência de Arquivos

## Objetivo
O objetivo dessa atividade é desenvolver uma aplicação em rede utilizando **sockets** para transferir um arquivo de texto entre cliente e servidor. O trabalho deverá ser feito em **C**, utilizando tanto **TCP** quanto **UDP**.

## Link de entrega:
[Entrega no Moodle](https://moodle.pucrs.br/mod/assign/view.php?id=3011122)

## Data de entrega:
O prazo para entrega é **14 de abril de 2025**.

## Link do Relatório:
[]()

## Especificações:
1. Desenvolver uma aplicação Cliente/Servidor utilizando **TCP** e **UDP**.
2. A aplicação deve ser capaz de transferir um arquivo de texto do cliente para o servidor.
3. O código deve ser organizado e as implementações de TCP e UDP devem ser separadas.
4. A aplicação deve ser capaz de fazer testes com **Wireshark** e **analisar o tráfego** gerado.
5. O código deve ser capaz de lidar com **perda de pacotes** e **latência variável** usando o módulo `tc-netem`.

## Instruções de uso:

### Como rodar:
1. **Compile os arquivos:**
   - No terminal, utilize o comando:
   ```
   make
   ```

2. **Execute o servidor:**
   - Em um terminal, rode o servidor TCP ou UDP:
   ```
   ./servidor_tcp
   # ou
   ./servidor_udp
   ```

3. **Execute o cliente:**
   - Em outro terminal, rode o cliente TCP ou UDP, informando o nome do arquivo a ser transferido:
   ```
   ./cliente_tcp
   # ou
   ./cliente_udp
   ```

### Testes:
1. Utilize **Wireshark** para capturar o tráfego durante a transferência.
2. Teste a transferência de arquivos com diferentes tamanhos.
3. Teste com **perda de pacotes** e **latência variável** usando o módulo `tc-netem`.

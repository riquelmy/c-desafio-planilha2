#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int lerLinha(FILE *arquivo, char *linha, int max_len) {
    if (fgets(linha, max_len, arquivo) == NULL) {
        return 0; // Falha ao ler a linha
    }
    /* Remove o caractere de nova linha se presente */
    char *nl = strchr(linha, '\n');
    if (nl != NULL) {
        *nl = '\0';
    }
    return 1; /* Leitura bem-sucedida */
}

void escreverLinha(FILE *arquivo, const char *linha) {
    fprintf(arquivo, "%s\n", linha);
}

int deletarColaborador() {
   int MAX_LEN = 100;
    FILE *arquivo = fopen("fake_database.csv", "r+");

    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê todas as linhas do arquivo
    char linhas[MAX_LEN][MAX_LEN];
    int numLinhas = 0;

    while (lerLinha(arquivo, linhas[numLinhas], MAX_LEN) && numLinhas < MAX_LEN) {
        numLinhas++;
    }

    // Fecha o arquivo antes de reabri-lo para escrita
    fclose(arquivo);
    arquivo = fopen("fake_database.csv", "w");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    // Imprime o conteúdo atual do arquivo
    for (int i = 0; i < numLinhas; i++) {
        printf("%d: %s\n", i + 1, linhas[i]);
    }

    // Solicita ao usuário selecionar uma linha para deletar
    int linhaSelecionada;
    printf("Digite o número da linha que deseja deletar: ");
    scanf("%d", &linhaSelecionada);

    if (linhaSelecionada < 1 || linhaSelecionada > numLinhas) {
        fprintf(stderr, "Linha inválida.\n");
        return 1;
    }

    // Copia as linhas que não precisam ser excluídas
    for (int i = 0, j = 0; i < numLinhas; i++) {
        if (i != linhaSelecionada - 1) {
            strcpy(linhas[j], linhas[i]);
            j++;
        }
    }

    // Atualiza o número de linhas
    numLinhas--;

    // Escreve todas as linhas restantes no arquivo
    for (int i = 0; i < numLinhas; i++) {
        escreverLinha(arquivo, linhas[i]);
    }

    // Fecha o arquivo
    fclose(arquivo);

    printf("Linha deletada com sucesso do arquivo fake_database.csv.\n");

    return 0;
}


int novaEdicao() {

   int MAX_LEN = 100;
    FILE *arquivo = fopen("fake_database.csv", "r+");

    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    /* Lê todas as linhas do arquivo*/
    char linhas[MAX_LEN][MAX_LEN];
    int numLinhas = 0;

    while (lerLinha(arquivo, linhas[numLinhas], MAX_LEN) && numLinhas < MAX_LEN) {
        numLinhas++;
    }

    /* Fecha o arquivo antes de reabri-lo para escrita*/
    fclose(arquivo);
    arquivo = fopen("fake_database.csv", "w");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    // Imprime o conteúdo atual do arquivo
    for (int i = 0; i < numLinhas; i++) {
        printf("%d: %s\n", i + 1, linhas[i]);
    }

    // Solicita ao usuário selecionar uma linha
    int linhaSelecionada;
    printf("Digite o número da linha que deseja modificar: ");
    scanf("%d", &linhaSelecionada);

    if (linhaSelecionada < 1 || linhaSelecionada > numLinhas) {
        fprintf(stderr, "Linha inválida.\n");
        return 1;
    }

    // Solicita ao usuário novos valores para os campos
    char novoNome[MAX_LEN], novaFuncao[MAX_LEN], novoId[MAX_LEN], novaIdade[MAX_LEN];
    printf("Digite o novo nome: ");
    scanf("%s", novoNome);
    printf("Digite a nova função: ");
    scanf("%s", novaFuncao);
    printf("Digite novo id: ");
    scanf("%s", novoId);
    printf("Digite nova idade: ");
    scanf("%s", novaIdade);

    // Modifica a linha selecionada com os novos valores
    strcpy(linhas[linhaSelecionada - 1], "");  // Limpa a linha anterior
    sprintf(linhas[linhaSelecionada - 1], "%s,%s,%s,%s", novoId, novoNome, novaIdade, novaFuncao);

    // Escreve todas as linhas modificadas de volta no arquivo
    for (int i = 0; i < numLinhas; i++) {
        escreverLinha(arquivo, linhas[i]);
    }

    // Fecha o arquivo
    fclose(arquivo);

    printf("Dados modificados com sucesso no arquivo fake_database.csv.\n");

    return 0;
}



/*Função para adicionar as linhas*/
int adicionarFunc() {
   int i;
   int id;
   char nome[50];
   int idade;
   char funcao[50];

    FILE *arquivo = fopen("fake_database.csv", "a"); 


   /*Caso o arquivo não seja aberto, retorna o erro abaixo*/
    if (arquivo == NULL) {
        fprintf(stderr, "Não foi possível acessar o banco de dados!\n");
        return 1; 
    }



    printf("Digite o nome: ");
    fgets(nome, 50, stdin);
   fgets(nome, 50, stdin);
   for(i=0;nome[i]!='\0';i++) ;
   nome[i-1]='\0';

    printf("Digite a função: ");
   scanf("%s", funcao);

    printf("Digite o id: ");
    scanf("%d", &id);

    printf("Digite a idade: ");
    scanf("%d", &idade);



    fprintf(arquivo, "%d,%s,%d,%s\n", id, nome, idade, funcao);

    fclose(arquivo);

    printf("%s foi adicionado(a) no banco de dados!\n", nome);

}

/*Aqui embaixo fica a função para contar quantas linhas tem a tabela, incluindo a linha do ID, CPF e X e uma linha nula*/
/*É uma cópia de consulta(), mas sem os outputs, apenas para contar as linhas da tabela.*/

int contarconsulta(void) {
   char buffer[1000];
   char *datax;
   int i = 0;
   char stop_reason;

   FILE *statsFile= fopen("fake_database.csv", "r");
   if (statsFile==NULL) {
      exit(-1);
   }
   
	while (i<1000) {
   fgets(buffer, sizeof(buffer), statsFile);

   datax = strtok(buffer, ";");
   datax = strtok(NULL, ";");
   datax = strtok(NULL, ";");
	i++;
	if (datax==NULL) {break;}
	}
   return i;
	}

int consulta(void) {
   char buffer[1000];
   char *datax; /*Aqui é um ponteiro*/
   int i = 0;
   int iRetornado = contarconsulta(); /*Esse é o iRetornado, ou seja, a quantidade de linhas da função contarconsulta. Com ela, podemos saber quantas linhas têm
   logo de cara.*/
   char stop_reason;
   printf("\n======================\n");
   printf("Tabela dos Colaboradores!\n");

   /*Essa parte é capaz de ler um determinado arquivo .csv. Se o arquivo não existir (tiver com o nome errado), ele retorna que não conseguiu abrir.*/
   FILE *statsFile= fopen("fake_database.csv", "r");
   if (statsFile==NULL) {
      printf("Error: could not open file!");
      exit(-1);
   }

   /*Esse while é pra imprimir cada linha da planilha, incluindo ID, CPF e X. O valor nulo n é impresso porque tira-se -1 do iRetornado.*/   
	while (i<iRetornado-1) {
	/*O fgets vai ler a primeira linha do buffer*/
   fgets(buffer, sizeof(buffer), statsFile);

   /*strtok que retorna o array de caracteres em token, com o delimitador sendo o ";" do .CSV. Esse valor depois é armazenado no ponteiro datax.*/

   datax = strtok(buffer, ";");

   printf(" %s | ", datax);

   /*O bufferr já foi pego, então para imprimir os próximos valores coloca-se o NULL no primeiro argumento*/
   datax = strtok(NULL, ";");
   
   printf(" %s | ", datax);
   datax = strtok(NULL, ";");

   printf(" %s | ", datax);
   datax = strtok(NULL, ";");
   printf(" %s", datax);

   /*i era um contadorzinho que havia colocado pra terminar o while. Como ajuda, vou deixar aí.*/
	i++;

   /*datax==NULL com o break é pra terminar o while caso seja encontrado uma linha nula (vazia)*/
	/* if (datax==NULL) {break;}*/
	}
   printf("\nTotal de linhas na tabela: %d\n", iRetornado-2);
   

	}			  

int main(void) {
   
   /*Sistema de autenticação*/
	while(1) {
		char login[100];
		char senha[100];
      printf("----------Tela de autenticação----------\n");
		printf("Login: ");
		scanf("%s", login);
      printf("\n----------Tela de autenticação----------\n");
		printf("Senha: ");
		scanf("%s", senha);
      printf("\n----------Tela de autenticação----------\n");
		if (strcmp(login, "admin") == 0 && strcmp(senha, "admin") == 0) {
			break;
		} else {
			printf("Login ou senha incorretos! Tente novamente!\n");
		}
	}
   /*Limpar a commmand-line*/
	system("cls");

   /*Painel do administrador(a), com as suas determinadas funcionalidades.*/
	printf("\n===================\n");
   printf("Tela de boas-vindas\nAdministrador(a) autenticado com sucesso!!\n\n");
	int num;
	while (1) {
		printf("\n===================\nAlternativas do menu:\n-> -1 para retornar a tela de boas-vindas\n-> 0 para finalizar o programa\n-> 1 para consultar a tabela dos colaboradores\n-> 2 para adicionar um colaborador\n"
      "-> 3 para editar uma linha\n-> 4 para deletar colaborador\n===================\n");
		scanf("%d", &num);
		if (num==-1) {system("cls");printf("\n===================\n");printf("Seja bem-vindo ao sistema de consulta ABC!\n\n");}
      if (num==0) {break;}
		if (num==1) {system("cls");consulta();}
      if (num==2) {system("cls");adicionarFunc();}
      if (num==3) {system("cls");novaEdicao();}/*Tomar muito cuidado, buga a tabela se der ctrl+c na hora de executar essa função*/
      if (num==4) {system("cls");deletarColaborador();}
		
	}
   

   printf("\n======================\n");
   return 0;
}

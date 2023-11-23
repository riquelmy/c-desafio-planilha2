#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
/*Colfrot ExCLI*/

/*funções de delete - início - implementação de william e kelvin*/
void deleteAllWorkers() {
    FILE *inputFile, *outputFile;
    char line[1024];
    int lines = 0;

    inputFile = fopen("tabela_colaboradores.csv", "r");
    outputFile = fopen("planilha_saida.csv", "w");

    if (inputFile == NULL || outputFile == NULL) {
        perror("Erro ao abrir os arquivos CSV para exclusão");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), inputFile) != NULL) {
        lines++;

        if (lines == 1) {
            fprintf(outputFile, "%s", line);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    if (remove("tabela_colaboradores.csv") != 0) {
        perror("Erro ao remover o arquivo original");
        exit(EXIT_FAILURE);
    }

    if (rename("planilha_saida.csv", "tabela_colaboradores.csv") != 0) {
        perror("Erro ao renomear o arquivo de saída");
        exit(EXIT_FAILURE);
    }

    printf("Todos os dados, exceto cabeçalhos, foram apagados com sucesso.\n");
    getchar();
}

void delAllVehicles() {
    FILE *inputFile, *outputFile;
    char line[1024];
    int lines = 0;

    inputFile = fopen("tabela_veiculos.csv", "r");
    outputFile = fopen("planilha_saida.csv", "w");

    if (inputFile == NULL || outputFile == NULL) {
        perror("Erro ao abrir os arquivos CSV para exclusão");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), inputFile) != NULL) {
        lines++;

        if (lines == 1) {
            fprintf(outputFile, "%s", line);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    if (remove("tabela_veiculos.csv") != 0) {
        perror("Erro ao remover o arquivo original");
        exit(EXIT_FAILURE);
    }

    if (rename("planilha_saida.csv", "tabela_veiculos.csv") != 0) {
        perror("Erro ao renomear o arquivo de saída");
        exit(EXIT_FAILURE);
    }

    printf("Todos os dados, exceto cabeçalhos, foram apagados com sucesso.\n");
    getchar();
}
/*funções de delete - fim - implementação de william e kelvin*/
/*----------------------Colaboradores(header)----------------------*/
int lerLinha(FILE *arquivo, char *linha, int max_len) {/*Função que lê cada linha, faz o processamento estabelecido, mas não imprime para o usuário o resultado do mesmo.*/
    if (fgets(linha, max_len, arquivo) == NULL) {
        return 0; /*Essa parte é pra lidar com a falha, caso a linha não seja lida*/
    }
    /* strchr procura a primeira ocorrência de um determinado caractere, e aí eu troco o '\n' por '\0'.
    Eu faço a implementação dessa função manualmente, sem o uso de strchr, em outra parte do código */
    char *nl = strchr(linha, '\n');
    if (nl != NULL) {
        *nl = '\0';
    }
    return 1; /* retorna 1 caso a leitura dê certo */
}
void escreverLinha(FILE *arquivo, const char *linha) {
    fprintf(arquivo, "%s\n", linha); 
}
int deletarColaborador() {
   int MAX_LEN = 100;
    FILE *arquivo = fopen("tabela_colaboradores.csv", "r+");

    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    /*Conta todas as linhas do arquivo*/
    char linhas[MAX_LEN][MAX_LEN];
    int numLinhas = 0;

    while (lerLinha(arquivo, linhas[numLinhas], MAX_LEN) && numLinhas < MAX_LEN) {
        numLinhas++;
    }

    /*depois de lido, fecha e abre ele novamente, só que em modo escrita (w), não modo leitura (r)*/
    fclose(arquivo);
    arquivo = fopen("tabela_colaboradores.csv", "w");

    /*Trecho para verificar se foi aberto com sucesso, em modo escrita*/
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    /*output do conteúdo da tabela*/
    for (int i = 0; i < numLinhas; i++) {
        printf("%d: %s\n", i + 1, linhas[i]);
    }

    /*entrada int para deletar uma linha. as outras funções tem estrutura parecida.*/
    int linhaSelecionada;
    printf("Digite o número da linha que deseja deletar: ");
    scanf("%d", &linhaSelecionada);

    if (linhaSelecionada < 1 || linhaSelecionada > numLinhas) {
        fprintf(stderr, "Linha inválida.\n");
        return 1;
    }

    /*Depois copia as linhas que não precisam ser excluidas para o array bidimensional linhas*/
    for (int i = 0, j = 0; i < numLinhas; i++) {
        if (i != linhaSelecionada - 1) {
            strcpy(linhas[j], linhas[i]);
            j++;
        }
    }

   /*atualiza o total de linhas da plannilha*/
    numLinhas--;

    /*pega o array de caracteres linhas, dá um parse em cada linha salva e escreve no arquivo a mesma*/
    for (int i = 0; i < numLinhas; i++) {
        escreverLinha(arquivo, linhas[i]);
    }

    /*fecha a planilha*/
    fclose(arquivo);

    printf("Linha deletada com sucesso do arquivo tabela_colaboradores.csv.\n");

    return 0;
}
int novaEdicao() {

   int MAX_LEN = 100;
    FILE *arquivo = fopen("tabela_colaboradores.csv", "r+");

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
    arquivo = fopen("tabela_colaboradores.csv", "w");

    /*Explicado anteriormente*/
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    /*Explicado anteriormente*/
    for (int i = 0; i < numLinhas; i++) {
        printf("%d: %s\n", i + 1, linhas[i]);
    }

    /*Explicado anteriormente*/
    int linhaSelecionada;
    printf("Digite o número da linha que deseja modificar: ");
    scanf("%d", &linhaSelecionada);

    if (linhaSelecionada < 1 || linhaSelecionada > numLinhas) {
        fprintf(stderr, "Linha inválida.\n");
        return 1;
    }

    /*aqui a gente utiliza o scanf para pegar as novas strings/arrays de caracteres, mas o ideal seria o fgets*/
    char novoNome[MAX_LEN], novaFuncao[MAX_LEN], novoId[MAX_LEN], novaIdade[MAX_LEN];
    printf("Digite o novo nome: ");
    scanf("%s", novoNome);
    printf("Digite a nova função: ");
    scanf("%s", novaFuncao);
    printf("Digite novo id: ");
    scanf("%s", novoId);
    printf("Digite nova idade: ");
    scanf("%s", novaIdade);

   
    strcpy(linhas[linhaSelecionada - 1], "");  /*limpar a linha anterior, é preciso tomar muito cuidado para não interromper aqui o processo na hora de editar. se não, limpa toda a tabela, e aí tem que pegar do backup*/

    sprintf(linhas[linhaSelecionada - 1], "%s,%s,%s,%s", novoId, novoNome, novaIdade, novaFuncao);  /*modofica a linha selecionada com os novos valores nos arrays de caracteres*/

    /*Escreve todas as linhas modificadas de linhas no arquivo*/
    for (int i = 0; i < numLinhas; i++) {
        escreverLinha(arquivo, linhas[i]);
    }

    /*explicado anteriormente*/
    fclose(arquivo);

    printf("Dados modificados com sucesso no arquivo tabela_colaboradores.csv.\n");

    return 0;
}
/*Função para adicionar as linhas*/
int adicionarFunc() {
   int i;
   int id;
   char nome[50];
   int idade;
   char funcao[50];

    FILE *arquivo = fopen("tabela_colaboradores.csv", "a"); 


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
   fgets(funcao, 50, stdin);
   for(i=0;funcao[i]!='\0';i++) ;
   funcao[i-1]='\0';

    printf("Digite o id: ");
    scanf("%d", &id);

    printf("Digite a idade: ");
    scanf("%d", &idade);



    fprintf(arquivo, "%d,%s,%d,%s\n", id, nome, idade, funcao);

    fclose(arquivo);

    printf("%s foi adicionado(a) no banco de dados!\n", nome);

}
int contarconsulta(void) {
    /*Aqui embaixo fica a função para contar quantas linhas tem a tabela, incluindo a linha do ID, CPF e X e uma linha nula*/
   /*É uma cópia de consulta(), mas sem os outputs, apenas para contar as linhas da tabela.*/  

   char buffer[1000];
   char *datax;
   int i = 0;
   char stop_reason;

   FILE *statsFile= fopen("tabela_colaboradores.csv", "r");
   if (statsFile==NULL) {
      exit(-1);
   }
   
	while (i<1000) {
   fgets(buffer, sizeof(buffer), statsFile);

   datax = strtok(buffer, ",");
   datax = strtok(NULL, ",");
   datax = strtok(NULL, ",");
	i++;
	if (datax==NULL) {break;}
	}
   return i;
	}

int consulta(void) {
   char buffer[1000];
   char *datax; /*Aqui é um ponteiro*/
   int i = 0;
   int iRetornado = contarconsulta(); /*Esse é o iRetornado, ou seja, a quantidade de linhas da função contarconsulta. Com ela, podemos saber quantas linhas têm logo de cara.*/
   char stop_reason;
   printf("\n======================\n");
   printf("Tabela dos Colaboradores!\n");

   /*Essa parte é capaz de ler um determinado arquivo .csv. Se o arquivo não existir (tiver com o nome errado), ele retorna que não conseguiu abrir.*/
   FILE *statsFile= fopen("tabela_colaboradores.csv", "r");
   if (statsFile==NULL) {
      printf("Error: could not open file!");
      exit(-1);
   }

   /*Esse while é pra imprimir cada linha da planilha, incluindo ID, CPF e X. O valor nulo n é impresso porque tira-se -1 do iRetornado.*/   
	while (i<iRetornado-1) {
	/*O fgets vai ler a primeira linha do buffer*/
   fgets(buffer, sizeof(buffer), statsFile);

   /*strtok que retorna o array de caracteres em token, com o delimitador sendo o "," do .CSV. Esse valor depois é armazenado no ponteiro datax.*/

   datax = strtok(buffer, ",");

   printf(" %s | ", datax);

   /*O bufferr já foi pego, então para imprimir os próximos valores coloca-se o NULL no primeiro argumento*/
   datax = strtok(NULL, ",");
   
   printf(" %s | ", datax);
   datax = strtok(NULL, ",");

   printf(" %s | ", datax);
   datax = strtok(NULL, ",");
   printf(" %s", datax);

   /*i era um contadorzinho que havia colocado pra terminar o while. Como ajuda, vou deixar aí.*/
	i++;

   /*datax==NULL com o break é pra terminar o while caso seja encontrado uma linha nula (vazia)*/
	/* if (datax==NULL) {break;}*/
	}
   printf("\nTotal de linhas na tabela: %d\n", iRetornado-2);
   

	}			  


/*----------------------Colaboradores(footer)----------------------*/
/* 
=======================================================================================  
  ______       _____ _ _      __      ____   ___  
 |  ____|     / ____| (_)     \ \    / /_ | / _ \ 
 | |__  __  _| |    | |_       \ \  / / | || | | |
 |  __| \ \/ / |    | | |       \ \/ /  | || | | |
 | |____ >  <| |____| | |        \  /   | || |_| |
 |______/_/\_\\_____|_|_|         \/    |_(_)___/ 
=======================================================================================                    
*/
/*--------------------------------Veiculos(header)-------------------------------------*/
int lerRowVeiculo(FILE *arquivo, char *linha, int max_len) { /*réplica -> ver lerLinha()*/
    if (fgets(linha, max_len, arquivo) == NULL) {
        return 0; 
    }
    char *nl = strchr(linha, '\n');
    if (nl != NULL) {
        *nl = '\0';
    }
    return 1;
}
void escreverRowVeiculo(FILE *arquivo, const char *linha) { /*réplica -> escreverRowVeiculo()*/
    fprintf(arquivo, "%s\n", linha);
}
int excluirVeiculo() {/*réplica -> deletarColaborador()*/
   int MAX_LEN = 100;
    FILE *arquivo = fopen("tabela_veiculos.csv", "r+");

    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    char linhas[MAX_LEN][MAX_LEN];
    int numLinhas = 0;

    while (lerRowVeiculo(arquivo, linhas[numLinhas], MAX_LEN) && numLinhas < MAX_LEN) {
        numLinhas++;
    }

    fclose(arquivo);
    arquivo = fopen("tabela_veiculos.csv", "w");

    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    for (int i = 0; i < numLinhas; i++) {
        printf("%d: %s\n", i + 1, linhas[i]);
    }

    int linhaSelecionada;
    printf("Digite o número da linha que deseja deletar: ");
    scanf("%d", &linhaSelecionada);

    if (linhaSelecionada < 1 || linhaSelecionada > numLinhas) {
        fprintf(stderr, "Linha inválida.\n");
        return 1;
    }

    for (int i = 0, j = 0; i < numLinhas; i++) {
        if (i != linhaSelecionada - 1) {
            strcpy(linhas[j], linhas[i]);
            j++;
        }
    }

    numLinhas--;

    for (int i = 0; i < numLinhas; i++) {
        escreverRowVeiculo(arquivo, linhas[i]);
    }

    fclose(arquivo);

    printf("Linha deletada com sucesso do arquivo tabela_veiculos.csv.\n");

    return 0;
}
int novaEdicaoVeiculo() {

   int j;
   int MAX_LEN = 100;
    FILE *arquivo = fopen("tabela_veiculos.csv", "r+");

    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    /* Lê todas as linhas do arquivo*/
    char linhas[MAX_LEN][MAX_LEN];
    int numLinhas = 0;

    while (lerRowVeiculo(arquivo, linhas[numLinhas], MAX_LEN) && numLinhas < MAX_LEN) {
        numLinhas++;
    }

    /* Fecha o arquivo antes de reabri-lo para escrita*/
    fclose(arquivo);
    arquivo = fopen("tabela_veiculos.csv", "w");

    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    for (int i = 0; i < numLinhas; i++) {
        printf("%d: %s\n", i + 1, linhas[i]);
    }

    int linhaSelecionada;
    printf("Digite o número da linha que deseja modificar: ");
    scanf("%d", &linhaSelecionada);

    if (linhaSelecionada < 1 || linhaSelecionada > numLinhas) {
        fprintf(stderr, "Linha inválida.\n");
        return 1;
    }

   char novaPlaca[MAX_LEN], novoModelo[MAX_LEN], novoResponsavel[MAX_LEN];
   printf("Digite a nova placa: ");
   scanf("%s", novaPlaca);
   printf("Digite o novo modelo: ");
   scanf("%s", novoModelo);

   printf("Digite o novo responsável: ");
    fgets(novoResponsavel, 50, stdin);
    fgets(novoResponsavel, 50, stdin);
    for (j=0; novoResponsavel[j]!='\0';j++) {;}
    novoResponsavel[j-1]='\0';

    strcpy(linhas[linhaSelecionada - 1], ""); 
    sprintf(linhas[linhaSelecionada - 1], "%s,%s,%s", novaPlaca, novoModelo, novoResponsavel);

    for (int i = 0; i < numLinhas; i++) {
        escreverRowVeiculo(arquivo, linhas[i]);
    }

    fclose(arquivo);

    printf("Dados modificados com sucesso no arquivo tabela_veiculos.csv.\n");

    return 0;
}
int adicionarVec() {
   int i;
   char placa[50];
   char modelo[50];
   char responsavel[50];

    FILE *arquivo = fopen("tabela_veiculos.csv", "a"); 


   /*Caso o arquivo não seja aberto, retorna o erro abaixo*/
    if (arquivo == NULL) {
        fprintf(stderr, "Não foi possível acessar o banco de dados!\n");
        return 1; 
    }



   printf("Digite a placa: ");
   fgets(placa, 50, stdin);
   fgets(placa, 50, stdin);
   for(i=0;placa[i]!='\0';i++);
   placa[i-1]='\0';

   printf("Digite o modelo: ");
   fgets(modelo, 50, stdin);
   for(i=0;modelo[i]!='\0';i++) ;
   modelo[i-1]='\0';


   printf("Digite o responsável: ");
   fgets(responsavel, 50, stdin);
   for(i=0;responsavel[i]!='\0';i++) ;
   responsavel[i-1]='\0';




    fprintf(arquivo, "%s, %s, %s\n", placa, modelo, responsavel);

    fclose(arquivo);

    printf("Veículo da placa %s foi adicionado ao banco de dados!\n", placa);

}
int contarVeiculo(void) {
   char buffer[1000];
   char *datax;
   int i = 0;
   char stop_reason;

   FILE *statsFile= fopen("tabela_veiculos.csv", "r");
   if (statsFile==NULL) {
      exit(-1);
   }
   
	while (i<1000) {
   fgets(buffer, sizeof(buffer), statsFile);

   datax = strtok(buffer, ",");
   datax = strtok(NULL, ",");
   datax = strtok(NULL, ",");
	i++;
	if (datax==NULL) {break;}
	}
   return i;
	}

int consultarCadaVec(void) {
   char buffer[1000];
   char *datax; /*Aqui é um ponteiro*/
   int i = 0;
   int iRetornado = contarVeiculo(); /*Esse é o iRetornado, ou seja, a quantidade de linhas da função contarVeiculo. Com ela, podemos saber quantas linhas têm logo de cara.*/
   char stop_reason;
   printf("\n======================\n");
   printf("Tabela dos Veículos!\n");

   /*Essa parte é capaz de ler um determinado arquivo .csv. Se o arquivo não existir (tiver com o nome errado), ele retorna que não conseguiu abrir.*/
   FILE *statsFile= fopen("tabela_veiculos.csv", "r");
   if (statsFile==NULL) {
      printf("Error: could not open file!");
      exit(-1);
   }

   /*Esse while é pra imprimir cada linha da planilha, incluindo ID, CPF e X. O valor nulo n é impresso porque tira-se -1 do iRetornado.*/   
	while (i<iRetornado-1) {
	/*O fgets vai ler a primeira linha do buffer*/
   fgets(buffer, sizeof(buffer), statsFile);

   /*strtok que retorna o array de caracteres em token, com o delimitador sendo o "," do .CSV. Esse valor depois é armazenado no ponteiro datax.*/

   datax = strtok(buffer, ",");

   printf(" %s | ", datax);

   /*O bufferr já foi pego, então para imprimir os próximos valores coloca-se o NULL no primeiro argumento*/
   datax = strtok(NULL, ",");
   
   printf(" %s | ", datax);
   datax = strtok(NULL, ",");

   printf(" %s ", datax);


   /*i era um contadorzinho que havia colocado pra terminar o while. Como ajuda, vou deixar aí.*/
	i++;

   /*datax==NULL com o break é pra terminar o while caso seja encontrado uma linha nula (vazia)*/
	/* if (datax==NULL) {break;}*/
	}
   printf("\nTotal de linhas na tabela: %d\n", iRetornado-2);
   

	}

/*--------------------------------Veiculos(footer)-------------------------------------*/

int autenticarAcesso() {
      /*Sistema de autenticação*/
   setlocale(LC_ALL, "Portuguese");
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
}


int main(void) {
   setlocale(LC_ALL, "Portuguese");
   autenticarAcesso();
   
   /*limpar a commmand-line*/
	system("cls");

   /*painel do administrador(a) que fiz, com as suas determinadas funcionalidades.*/
	printf("\n===================\n");
   printf("Tela de boas-vindas\nAdministrador(a) autenticado com sucesso!!\n\n");

	int num;
   int programaFuncionando=1;

	while (programaFuncionando) {
		printf("\n===================\nAlternativas do menu:\n-> -1 para retornar a tela de boas-vindas"
      "\n-> 0 para finalizar o programa\n-> 1 para consultar a tabela dos colaboradores"
      "\n-> 2 para adicionar um colaborador"
      "\n-> 3 para editar uma linha\n-> 4 para deletar colaborador\n===================\n");

		scanf("%d", &num);

      switch (num) {
         case -1:
            system("cls");
            printf("\n===================\n");
            printf("Seja bem-vindo ao sistema de consulta ABC!\n\n");
            break;
         case 0: 
            programaFuncionando=!programaFuncionando;/*C ou ~C – lógica matemática*/
            break;
         case 1:
            system("cls");
            consulta();
            break;
         case 2:
            system("cls");
            adicionarFunc();
            break;
         case 3:
            system("cls");
            novaEdicao(); /*tomar muito cuidado aqui, buga a tabela se der ctrl+c na hora de executar essa função*/
            break;
         case 4:
            system("cls");
            deletarColaborador();
            break;
         case 11:
            system("cls");
            consultarCadaVec();
            break;
         case 22:
            system("cls");
            adicionarVec();
            break;
         case 33:
            system("cls");
            novaEdicaoVeiculo(); /*tomar muito cuidado aqui, buga a tabela se der ctrl+c na hora de executar essa função*/
            break;
         case 44:
            system("cls");
            excluirVeiculo();
            break;
        case 5:
            system("cls");
            deleteAllWorkers();
            break;
        case 55:
            system("cls");
            delAllVehicles();
            break;

         default:
            system("cls");
            printf("A opção em questão não está programada em nosso sistema! Digite outra alternativa\n");
            break;           
      }
		
	}
   
   printf("\n======================\n");

   return 0;
}

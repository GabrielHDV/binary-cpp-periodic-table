// Tabela Periódica
// Grupo: 40 - Gabriel Henrique, Isael Rosa, Gustavo F.
// Turma: 14B

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

const int tamanho=160; // Foi utilizado 160 como tamanho total pensando que são 118 elementos na nova tabela, e colocado 42 de margem para novos elementos que é praticamente impossivel de acontecer agora.

struct TabelaPeriodica
{
    string nome;
    string simbolo;
    string classificacao;
    int n_atomico;
    float peso_atomico;
};

void neg_n_atomico(TabelaPeriodica tabela[], int tamanho)
{
    for (int i=0; i<tamanho;i++)
    {
        tabela[i].n_atomico=-1;
    }
}

void carregar_CSV(TabelaPeriodica tabela[], int tamanho, const string& nomeArquivo)
{
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo." << endl;
        return;
    }

    string linha;
    getline(arquivo, linha); // Ignora o cabeçalho

    int i = 0;
    while (getline(arquivo, linha) && i < tamanho) {
        stringstream ss(linha);
        string campo;

        // Lê cada campo separado por vírgula
        getline(ss, campo, ';');
        tabela[i].n_atomico = stoi(campo);

        getline(ss, campo, ';');
        tabela[i].nome = campo;

        getline(ss, campo, ';');
        tabela[i].simbolo = campo;

        getline(ss, campo, ';');
        tabela[i].peso_atomico = stof(campo);

        getline(ss, campo);
        tabela[i].classificacao = campo;

        i++;
    }

    arquivo.close();
}

void salvar_CSV(TabelaPeriodica tabela[], int tamanho, const string& nomeArquivo)
{
    ofstream arquivoCSV(nomeArquivo);

    if (!arquivoCSV.is_open())
    {
        cout << "Erro ao abrir o arquivo para escrita." << endl;
        return;
    }

    // Escreve o cabeçalho no arquivo CSV
    arquivoCSV << "Numero Atomico;Nome;Simbolo;Peso Atomico;Classificacao" << endl;

    for (int i = 0; i < tamanho; ++i)
    {
        if (tabela[i].n_atomico != -1)
        {
            arquivoCSV << tabela[i].n_atomico << ";"
                       << tabela[i].nome << ";"
                       << tabela[i].simbolo << ";"
                       << tabela[i].peso_atomico << ";"
                       << tabela[i].classificacao << endl;
        }
    }

    arquivoCSV.close();
}


void salvar_Binario(TabelaPeriodica tabela[], int tamanho, const string& nomeArquivo)
{
    ofstream arquivoBinario(nomeArquivo, ios::out | ios::binary);

    if (!arquivoBinario.is_open())
    {
        cout << "Erro ao abrir o arquivo para escrita." << endl;
        return;
    }

    for (int i = 0; i < tamanho; ++i)
    {
        arquivoBinario.write(reinterpret_cast<const char*>(&tabela[i]), sizeof(TabelaPeriodica));
    }

    arquivoBinario.close();
}

void imprimir_Binario(const string& nomeArquivo)
{
    cout << "a-Imprimir todos elementos" << endl;
    cout << "b-Imprimir intervalo de numero atomico" << endl;
    cout << "x-Retornar" << endl;
    char op;
    cin >> op;
    if(op=='a')
    {
        ifstream arquivoBinario(nomeArquivo, ios::in | ios::binary);

        if (!arquivoBinario.is_open())
        {
            cout << "Erro ao abrir o arquivo para leitura." << endl;
            return;
        }

        TabelaPeriodica tabela;

        while (arquivoBinario.read(reinterpret_cast<char*>(&tabela), sizeof(TabelaPeriodica)))
        {
            if(tabela.n_atomico>-1)
            {
                cout << endl;
                cout << "Numero Atomico: " << tabela.n_atomico << endl;
                cout << "Nome: " << tabela.nome << endl;
                cout << "Simbolo: " << tabela.simbolo << endl;
                cout << "Peso Atomico: " << tabela.peso_atomico << endl;
                cout << "Classificacao: " << tabela.classificacao << endl<<endl;
            }
        }
        arquivoBinario.close();
    }
    if(op=='b')
    {
        int a,b;
        cout << "Escolha limite inferior: ";
        cin >> a;
        cout << "Escolha limite superior: ";
        cin >> b;
        ifstream arquivoBinario(nomeArquivo, ios::in | ios::binary);

        if (!arquivoBinario.is_open())
        {
            cout << "Erro ao abrir o arquivo para leitura." << endl;
            return;
        }

        TabelaPeriodica tabela;
        while (arquivoBinario.read(reinterpret_cast<char*>(&tabela), sizeof(TabelaPeriodica)))
        {
            if((tabela.n_atomico>=a) and (tabela.n_atomico<=b))
            {
                cout << endl;
                cout << "Numero Atomico: " << tabela.n_atomico << endl;
                cout << "Nome: " << tabela.nome << endl;
                cout << "Simbolo: " << tabela.simbolo << endl;
                cout << "Peso Atomico: " << tabela.peso_atomico << endl;
                cout << "Classificacao: " << tabela.classificacao << endl<<endl;
            }
        }
        arquivoBinario.close();
    }
}

void buscar_binario(const string& nomeArquivo)
{
    int n;
    string simb;
    int aux=0;
  
    char op;
    cout << "************************************************" << endl;
    cout << "a-Busca por simbolo" << endl;
    cout << "b-Busca por numero atomico" << endl;
    cout << "x-Retornar" << endl;
    cout << "************************************************" << endl;
    cin >> op;
    if(op=='b')
    {
        cout << "Digite o numero atomico do elemento: ";
        cin >> n;
        ifstream arquivoBinario(nomeArquivo, ios::in | ios::binary);

        if (!arquivoBinario.is_open())
        {
            cout << "Erro ao abrir o arquivo para leitura." << endl;
            return;
        }

        TabelaPeriodica tabela;

        while (arquivoBinario.read(reinterpret_cast<char*>(&tabela), sizeof(TabelaPeriodica)))
        {
            if(tabela.n_atomico==n)
            {
                aux=1;
                cout << endl;
                cout << "Numero Atomico: " << tabela.n_atomico << endl;
                cout << "Nome: " << tabela.nome << endl;
                cout << "Simbolo: " << tabela.simbolo << endl;
                cout << "Peso Atomico: " << tabela.peso_atomico << endl;
                cout << "Classificacao: " << tabela.classificacao << endl<<endl;
            }
        }
        if(aux==0)
        {
            cout << "Elemento não encontrado" << endl;
        }
        else if(aux==1)
        {

        }

        arquivoBinario.close();
    }
    if(op=='a')
    {
        cout << "Digite o simbolo do elemento: ";
        cin >> simb;
        ifstream arquivoBinario(nomeArquivo, ios::in | ios::binary);

        if (!arquivoBinario.is_open())
        {
            cout << "Erro ao abrir o arquivo para leitura." << endl;
            return;
        }

        TabelaPeriodica tabela;

        while (arquivoBinario.read(reinterpret_cast<char*>(&tabela), sizeof(TabelaPeriodica)))
        {
            if(tabela.simbolo==simb)
            {
                aux=1;
                cout << endl;
                cout << "Numero Atomico: " << tabela.n_atomico << endl;
                cout << "Nome: " << tabela.nome << endl;
                cout << "Simbolo: " << tabela.simbolo << endl;
                cout << "Peso Atomico: " << tabela.peso_atomico << endl;
                cout << "Classificacao: " << tabela.classificacao << endl<<endl;
            }
        }
        if(aux==0)
        {
            cout << "Elemento não encontrado" << endl;
        }

        arquivoBinario.close();
    }
}

bool busca_vetor(TabelaPeriodica tabela[], int n, int tamanho)
{
    bool achou=false;
    for(int i=0;i<=tamanho;i++)
    {
        if(tabela[i].n_atomico==n)
        {
            achou=true;
        }
    }
    if(achou==true)
    {
        return true;
    }
    return false;
}

void adicionar_elemento(TabelaPeriodica tabela[], int tamanho)
{
    int posicao;
    int i=0;
    int n;
    while(tabela[i].n_atomico>-1)
    {
        i++;
        posicao=i;
    }
    cout << "Digite o numero atomico :";
    cin >> n;
    if(busca_vetor(tabela,n,tamanho)==true)
    {
        cout << "Elemento ja cadastrado" << endl;
    }
    else
    {
        tabela[posicao].n_atomico=n;
        cout << "Digite o nome do elemento :";
        cin >> tabela[posicao].nome;
        cout << "Digite o simbolo :";
        cin >> tabela[posicao].simbolo;
        cout << "Digite o peso atomico :";
        cin >> tabela[posicao].peso_atomico;
        cout << "Digite a classificacao :";
        cin.ignore();
        getline(cin,tabela[posicao].classificacao);
    }
}

void excluir_elemento(TabelaPeriodica tabela[], int tamanho)
{
    int n;
    cout << "Digite o número atomico do elemento que deseja excluir: ";
    cin >> n;
    bool achou=false;
    int pos;
    for(int i=0;i<tamanho;i++)
    {
        if(tabela[i].n_atomico==n)
        {
            achou=true;
            pos=i;
        }
    }
    if(achou==true)
    {
        tabela[pos].n_atomico=-1;
        cout << "Elemento excluido com sucesso !" << endl;
    }
    else
    {
        cout << "Elemento não identificado. " << endl;
    }
}

void alterar_elemento(TabelaPeriodica tabela[], int tamanho)
{
    int n;
    cout << "Digite o número atomico do elemento que deseja alterar: ";
    cin >> n;
    bool achou=false;
    int pos;
    for(int i=0;i<tamanho;i++)
    {
        if(tabela[i].n_atomico==n)
        {
            achou=true;
            pos=i;
        }
    }
    if(achou==true)
    {
        char op;
        while(op!='x')
        {
            cout << "************************************************" << endl;
            cout << "Numero Atomico: " << tabela[pos].n_atomico << endl;
            cout << "Nome: " << tabela[pos].nome << endl;
            cout << "Simbolo: " << tabela[pos].simbolo << endl;
            cout << "Peso Atomico: " << tabela[pos].peso_atomico << endl;
            cout << "Classificacao: " << tabela[pos].classificacao << endl;
            cout << "************************************************" << endl;
            cout <<"a- Alterar Numero Atomico: " << endl;
            cout <<"b- Alterar Nome: " << endl;
            cout <<"c- Alterar Simbolo: " << endl;
            cout <<"d- Alterar Peso Atomico: " << endl;
            cout <<"e- Alterar Classificação: " << endl;
            cout <<"x- Sair " <<endl;
            cin >> op;
            if(op=='a')
            {
                cout << "Entre com o novo numero atomico: ";
                cin >> tabela[pos].n_atomico;
                op='z';
            }
            if(op=='b')
            {
                cout << "Entre com o novo nome: ";
                cin >> tabela[pos].nome;
                op='z';
            }
            if(op=='c')
            {
                cout << "Entre com o novo simbolo: ";
                cin >> tabela[pos].simbolo;
                op='z';
            }
            if(op=='d')
            {
                cout <<"Entre com o novo peso: ";
                cin >> tabela[pos].peso_atomico;
                op='z';
            }
            if(op=='e')
            {
                cout << "Entre com a nova classificação: ";
                cin.ignore();
                getline(cin,tabela[pos].classificacao);
                op='z';
            }
        }
    }
    else
    {
        cout << "Elemento não encontrado" << endl;
    }
}

// Função auxiliar para o Quick Sort
int particionar(TabelaPeriodica tabela[], int baixo, int alto) {
    string pivot = tabela[alto].nome; // Define o pivô como o elemento mais à direita
    int i = (baixo - 1); // Índice do menor elemento

    for (int j = baixo; j <= alto - 1; j++) {
        // Se o nome atual for menor ou igual ao pivô, troca
        if (tabela[j].nome <= pivot) {
            i++; // Incrementa o índice do menor elemento
            // Troca tabela[i] e tabela[j]
            TabelaPeriodica temp = tabela[i];
            tabela[i] = tabela[j];
            tabela[j] = temp;
        }
    }
    // Troca tabela[i + 1] e tabela[alto] (coloca o pivô no lugar correto)
    TabelaPeriodica temp = tabela[i + 1];
    tabela[i + 1] = tabela[alto];
    tabela[alto] = temp;
    return (i + 1);
}

// Função principal do Quick Sort
void quickSort(TabelaPeriodica tabela[], int baixo, int alto) {
    if (baixo < alto) {
        // Obtém o índice do pivô após a partição
        int pi = particionar(tabela, baixo, alto);

        // Ordena os elementos antes e depois do pivô
        quickSort(tabela, baixo, pi - 1);
        quickSort(tabela, pi + 1, alto);
    }
}

// Função para ordenar a tabela usando Quick Sort
void ordenar_tabela_quickSort_alfabetica(TabelaPeriodica tabela[], int tamanho) {
    quickSort(tabela, 0, tamanho - 1); // Chama o Quick Sort
}

int particionarAtomico(TabelaPeriodica tabela[], int baixo, int alto) {
    int pivot = tabela[alto].n_atomico; // Define o pivô como o elemento mais à direita
    int i = (baixo - 1); // Índice do menor elemento

    for (int j = baixo; j <= alto - 1; j++) {
        // Se o número atômico atual for menor ou igual ao pivô, troca
        if (tabela[j].n_atomico <= pivot) {
            i++; // Incrementa o índice do menor elemento
            // Troca tabela[i] e tabela[j]
            TabelaPeriodica temp = tabela[i];
            tabela[i] = tabela[j];
            tabela[j] = temp;
        }
    }
    // Troca tabela[i + 1] e tabela[alto] (coloca o pivô no lugar correto)
    TabelaPeriodica temp = tabela[i + 1];
    tabela[i + 1] = tabela[alto];
    tabela[alto] = temp;
    return (i + 1);
}


void quickSortAtomico(TabelaPeriodica tabela[], int baixo, int alto) {
    if (baixo < alto) {
        // Obtém o índice do pivô após a partição pelo número atômico
        int pi = particionarAtomico(tabela, baixo, alto);

        // Ordena os elementos antes e depois do pivô
        quickSortAtomico(tabela, baixo, pi - 1);
        quickSortAtomico(tabela, pi + 1, alto);
    }
}

void ordenar_tabela_quickSort_atomico(TabelaPeriodica tabela[], int tamanho) {
    quickSortAtomico(tabela, 0, tamanho - 1); // Chama o Quick Sort pelo número atômico
}

int main()
{
	TabelaPeriodica tabela[tamanho];
	neg_n_atomico(tabela,tamanho);//Função feita para deixar todos os valores sem utilizar como negativo, assim como pedido no roteiro
	carregar_CSV(tabela,tamanho,"Tabela.csv");
	salvar_Binario(tabela,tamanho,"Tabela.bin");
	int menu=9;
	while(menu!=0)
    {
        cout << "***************** TABELA PERIODICA *****************" << endl << endl;
        cout << "*1-Adicionar elemento" << endl;
        cout << "*2-Excluir elemento" << endl;
        cout << "*3-Alterar dados" << endl;
        cout << "*4-Buscar elemento" << endl;
        cout << "*5-Imprimir arquivo" << endl;
        cout << "*6-Ordenar" << endl;
        cout << "*0-Sair" << endl << endl;
        cout << "****************************************************" << endl;
        cin >> menu;

        if(menu==1)
        {
            adicionar_elemento(tabela,tamanho);
            menu=9;
        }

        if(menu==2)
        {
            excluir_elemento(tabela,tamanho);
            menu=9;
        }

        if(menu==3)
        {
            alterar_elemento(tabela,tamanho);
            menu=9;
        }

        if(menu==4)
        {
            buscar_binario("Tabela.bin");
            menu=9;
        }

        if(menu==5)
        {
            imprimir_Binario("Tabela.bin");
            cin.ignore(); // Aguarda a entrada do usuário para continuar
            menu=9;
        }
        if(menu==6)
        {
            cout << "a-Ordenar em ordem alfabetica" << endl;
            cout << "b-Ordenar em ordem de numero atomico" << endl;
            char op;
            cin >> op;
            if(op=='a')
            {
                ordenar_tabela_quickSort_alfabetica(tabela,tamanho);
            }
            if(op=='b')
            {
                ordenar_tabela_quickSort_atomico(tabela,tamanho);
            }

        }
        salvar_Binario(tabela,tamanho,"Tabela.bin");
        salvar_CSV(tabela,tamanho,"Tabela.csv");
    }
}


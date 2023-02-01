#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "../include/interactive.h"
#include "../include/utils.h"
#include "../include/catalog.h"
#include "../include/io.h"

typedef struct query
{
    char *description;
    char *arguments;
    char *output;
    char *example;
} QUERY;

QUERY *query_info()
{
    QUERY *queries = malloc(sizeof(QUERY) * 9);

    queries[0].description = "Lista o resumo de um perfil registado no serviço através do seu identificador.";
    queries[0].arguments = "<ID> de condutor / <USERNAME> de utilizador";
    queries[0].output = "nome;genero;idade;avaliacao_media;numero_viagens;total_gasto";
    queries[0].example = "João;M;23;4.5;10;100";

    queries[1].description = "Lista os N condutores com maior avaliação média.";
    queries[1].arguments = "<N> - Número de condutores a ser listados.";
    queries[1].output = "nome;genero;idade;avaliacao_media;numero_viagens;total_gasto";
    queries[1].example = "000000008899;Rafaela de Barros;3.564";

    queries[2].description = "Lista os N utilizadores com maior distância viajada.";
    queries[2].arguments = "<N> - Número de utilizadores a ser listados.";
    queries[2].output = "username;nome;distancia_total";
    queries[2].example = "Anita-PetPinto37;Anita-Petra Pinto;240";
    
    queries[3].description = "Preço médio das viagens (sem considerar gorjetaas) numa determinada cidade.";
    queries[3].arguments = "<city> - Nome da cidade.";
    queries[3].output = "preco_medio";
    queries[3].example = "10.057";
    
    queries[4].description = "Preço médio das viagens (sem considerar gorjetas) num dado intervalo de tempo.";
    queries[4].arguments = "<data A> <data B> - Datas entre as quais a query atua.";
    queries[4].output = "preco_medio";
    queries[4].example = "10.107";
  
    queries[5].description = "Distância média percorrida, numa determinada cidade.";
    queries[5].arguments = "<city> <data A> <data B> - Nome da cidade e datas entre as quais a query atua.";
    queries[5].output = "distancia_media";
    queries[5].example = "9.667";
    
    queries[6].description = "Top N condutores numa determinada cidade.";
    queries[6].arguments = "<N> <city> - N condutores a ser listados e nome da cidade.";
    queries[6].output = "id;nome;avaliacao_media";
    queries[6].example = "000000001488;Rita Correia;4.250";

    queries[7].description = "Lista todas as viagens nas quais os utilizadores e o condutor são do género passado como parâmetro e têm perfis com X ou mais anos.";
    queries[7].arguments = "<gender> <X> - Gênero dos utilizadores e condutor e anos mínimos dos seus perfis.";
    queries[7].output = "id_condutor;nome_condutor;username_utilizador;nome_utilizador";
    queries[7].example = "000000009452;Ricardo Figueiredo;WiPinheiro;Wilson de Pinheiro";
    
    queries[8].description = "Lista as viagens nas quais o passageiro deu gorjeta, no intervalo de tempo (data A, data B).";
    queries[8].arguments = "<data A> <data B> - Datas entre as quais a query atua.";
    queries[8].output = "id_viagem;data_viagem;distancia;cidade;valor_gorjeta";
    queries[8].example = "000000295454;01/01/2021;13;Faro;3.000";

    return queries;
}

#define MARGIN 4
#define SPACING 2

// FUNÇÕES AUXILIARES

int center_text(char *text, int width)
{
    int len = strlen(text);
    int pos = (width - len) / 2;
    return pos;
}

int center_options(int options, int height)
{
    int length = (options - 1) * SPACING;
    int margin = (height - length) / 2;
    return margin;
}

int get_lines_number(char *text)
{
    int i, acc = 1, len = strlen(text);
    for (i = 0; i < len; i++)
    {
        if (text[i] == '\n')
            acc++;
    }
    return acc;
}

char get_input()
{
    switch (getch())
    {
        case '\033':
        {
            getch();
            switch (getch())
            {
                case 'A':
                    return 'A';
                case 'B':
                    return 'B';
                case 'C':
                    return 'C';
                case 'D':
                    return 'D';
            }
            return '0';
        }
        case '\n':
            return '\n';
        default:
            return '0';
    }
}

char *get_input_string()
{
    nocbreak();
    echo();

    char *input = malloc(sizeof(char) * 50);

    int ch = getch();
    int i = 0;

    while (ch != '\n')
    {
        input[i] = ch;
        ch = getch();
        i++;
    }

    input[i] = '\0';

    return input;
}

void delay(int secs)
{
    int retTime = time(0) + secs;
    while (time(0) < retTime);
}

int round_up(double d)
{
    int i = (int)d;
    if (d - i > 0)
        return i + 1;
    return i;
}

// FUNÇÕES DE CRIAÇÃO DE JANELAS

WINDOW *new_window()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int height = w.ws_row - 2;
    int width = w.ws_col - 4;

    curs_set(0);
    noecho();

    WINDOW *win = newwin(height, width, 0, 0);
    box(win, 0, 0);
    mvwin(win, 1, 2);
    refresh();
    wrefresh(win);

    return win;
}

WINDOW *new_info_window(int height, int width)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int x = w.ws_col;

    int center = (x - width) / 2;

    curs_set(0);
    noecho();

    WINDOW *win = newwin(height, width, 0, 0);
    box(win, 0, 0);
    mvwin(win, MARGIN, center);
    
    refresh();
    wrefresh(win);

    return win;
}

// FUNÇÕES DE DESENHO DE JANELAS

// -> Janelas de informação
WINDOW *warning(char *warning, int time)
{
    int height = 3;
    int width = strlen(warning) + 4;
    
    WINDOW *win = new_info_window(height, width);

    mvwprintw(win, height / 2, center_text(warning, width), warning);

    refresh();
    wrefresh(win);

    if (time >= 0)
    {
        delay(time);

        werase(win);
        refresh();
        wrefresh(win);
    }

    return win;
}

WINDOW *info(char *info, int time)
{
    int height = 3;
    int width = strlen(info) + 4;
    
    WINDOW *win = new_info_window(height, width);

    mvwprintw(win, height / 2, center_text(info, width), info);

    refresh();
    wrefresh(win);

    if (time >= 0)
    {
        delay(time);

        werase(win);
        refresh();
        wrefresh(win);
    }

    return win;
}
// --

void menu1(WINDOW *win, char *title, char *footer, char *info, char *options[], int N, int sel)
{
    // Tamanho da janela
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int height = w.ws_row - 2;
    int width = w.ws_col - 4;

    // Título
    char *formated_title = malloc(sizeof(char) * (strlen(title) + 4));
    sprintf(formated_title, " %s ", title);
    mvwprintw(win, 0, 3, formated_title);

    free(formated_title);

    // Rodapé
    if (footer != NULL) // Se o rodapé existir
    {  
        char *formated_footer = malloc(sizeof(char) * (strlen(footer) + 4));
        sprintf(formated_footer, " %s ", footer);
        mvwprintw(win, height - 1, center_text(formated_footer, width), formated_footer);

        free(formated_footer);
    }

    // Informação
    if (info != NULL) // Se a informação existir
    {
        char *formated_info = malloc(sizeof(char) * (strlen(info) + 4));
        sprintf(formated_info, " %s ", info);
        mvwprintw(win, height - 1, 3, formated_info);

        free(formated_info);
    }

    // Opções
    int i, margin = center_options(N, height), pos = center_text(options[0], width);

    for (i = 0; i < N; i++)
    {
        if (i == sel)
        {
            wattron(win, A_REVERSE);
            mvwprintw(win, i * SPACING + margin, pos, options[i]);
            wattroff(win, A_REVERSE);
        }
        else
            mvwprintw(win, i * SPACING + margin, pos, options[i]);
    }

    refresh();
    wrefresh(win);
}

void menu2(WINDOW *win, char *title, char *desc, char *footer, QUERY *query)
{
    // Tamanho da janela
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int height = w.ws_row - 2;
    int width = w.ws_col - 4;

    echo(); // Habilita echo

    // Título
    char *formated_title = malloc(sizeof(char) * (strlen(title) + 4));
    sprintf(formated_title, " %s ", title);
    mvwprintw(win, 0, 3, formated_title);

    free(formated_title);

    // Informações da query
    int q_desc_len;
    if (query != NULL) q_desc_len = strlen(query->description);
    if (query != NULL && q_desc_len < width - 4) // Só imprime se existir query e couber no terminal
    {
        mvwprintw(win, height / 2 - 10, center_text(query->description, width) - 2, "> ");
        wprintw(win, query->description);

        wattron(win, A_REVERSE);
        mvwprintw(win, height / 2 - 8, center_text(query->description, width) - 2, "Argumentos:");
        wattroff(win, A_REVERSE);
        wprintw(win, " ");
        wprintw(win, query->arguments);
    }

    // Rodapé
    if (footer != NULL)
    {  
        char *formated_footer = malloc(sizeof(char) * (strlen(footer) + 4));
        sprintf(formated_footer, " %s ", footer);
        mvwprintw(win, height - 1, center_text(formated_footer, width), formated_footer);

        free(formated_footer);
    }

    // Descrição & Input
    wattron(win, A_REVERSE);
    mvwprintw(win, height / 2 - 2, center_text(desc, width), desc);
    wattroff(win, A_REVERSE);
    mvwprintw(win, height / 2, center_text(desc, width), "> ");
    
    refresh();
    wrefresh(win);
}

void menu_result(WINDOW *win, int start, int N, char *output)
{   
    // Tamanho da janela
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int height = w.ws_row - 2;
    int width = w.ws_col - 4;
    int space = height - 4;

    // Título
    char *title = " RESULTADO ";
    mvwprintw(win, 0, 3, title);

    // Formato de output
    int q_output_len = strlen(output);
    if (q_output_len < width - 30) // Só imprime se couber no terminal
    {
        char *formated_output = malloc(sizeof(char) * (strlen(output)));
        sprintf(formated_output, " %s ", output);
        mvwprintw(win, 0, center_text(formated_output, width), formated_output);

        free(formated_output);
    }

    // Navegação
    char *nav = " UP/DOWN/LEFT/RIGHT - Navegar ";
    mvwprintw(win, height - 1, center_text(nav, width), nav);
    
    // Sair
    char *quit = " ENTER - Sair ";
    mvwprintw(win, height - 1, width - 3 - strlen(quit), quit);

    // Informação de número de página
    int pages = round_up((double)N / (double)space);
    if (pages > 0)
    {
        int page = round_up((double)start / (double)space + 1);
        char *page_info = malloc(sizeof(char) * 34);
        sprintf(page_info, " %d/%d ", page, pages);
        mvwprintw(win, height - 1, 3, page_info);

        free(page_info);
    }

    // Abrir ficheiro de output
    char *path = get_results_path(0);
    FILE *file = fopen(path, "r");

    // Calcular comprimento da barra para o número de linha
    char *N_str = malloc(sizeof(char) * 12);
    sprintf(N_str, "%d", N);

    int bar_len = strlen(N_str);

    // Calcular posição em width do texto de acordo com a primeira linha de output
    FILE *f = fopen(path, "r");

    char *l = NULL;
    size_t ln = 0;

    if(getline(&l, &ln, f)) {};
    int pos = center_text(l, width) - bar_len - 1;
    fclose(f);
    
    // Mecanismo de paginação
    char *line = NULL;
    size_t len = 0;

    int i, j;
    if (start > 0) for (i = 1; getline(&line, &len, file) != -1 && i < start; ++i);
    for (i = start, j = 0; getline(&line, &len, file) != -1 && i < start + space; ++i, ++j)
    {
        char k[12];
        sprintf(k, "%d", i + 1);

        wattron(win, A_REVERSE);
        int k_len = strlen(k);
        for (int l = 0; l < bar_len - k_len; l++)
            mvwprintw(win, j + 2, pos + l, " ");
        mvwprintw(win, j + 2, pos + bar_len - strlen(k), k);
        wattroff(win, A_REVERSE);
        wprintw(win, " ");
        wprintw(win, line);
    }

    fclose(file);
    free(path);

    refresh();
    wrefresh(win);
}

int menu_options(WINDOW *win, char *title, char *footer, char *info, char *options[], int N, int sel)
{
    char i = '0';

    while (i != '\n')
    {
        menu1(win, title, footer, info, options, N, sel);
        i = get_input();

        if (i == 'A')
            sel--;
        else if (i == 'B')
            sel++;

        if (sel < 0)
            sel = N - 1;
        if (sel > N - 1)
            sel = 0;
    }

    return sel;
}

void menu_input(WINDOW *win, char *input, char *title, char *desc, char *footer, QUERY *query)
{
    curs_set(1);
    menu2(win, title, desc, footer, query);
    wgetnstr(win, input, 100);
    curs_set(0);
}

// JANELAS/MENUS DO PROGRAMA

void show_result(char *output)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int height = w.ws_row - 2;
    
    char *line = NULL;
    size_t len = 0;

    char *path = get_results_path(0);
    FILE *file = fopen(path, "r");

    int N;
    for (N = 0; getline(&line, &len, file) != -1; N++);

    int start = 0, space = height - 4;
    char i;
    do
    {
        WINDOW *win = new_window();
        
        menu_result(win, start, N, output);
        i = get_input();

        switch (i)
        {
            case 'A':
                start--;
                break;
            case 'B':
                start++;
                break;
            case 'C':
                start += space;
                break;
            case 'D':
                start -= space;
                break;
        }

        if (N <= space)
            start = 0;
        if (start > N - space)
            start = N - space;
        if (start < 0)
            start = 0;

        werase(win);
    }
    while (i != '\n');
}

void run_query(int query, CATALOG *c, QUERY *queries)
{
    WINDOW *win = new_window();

    char *title = malloc(sizeof(char) * 50);
    sprintf(title, "QUERY %d", query);

    char *input = malloc(sizeof(char) * 50);
    menu_input(win, input, title, "Introduza os argumentos para a query:", "ENTER - Executar", &queries[query - 1]);

    WINDOW *info_win = info("[INFO] - Executando query...", -1);

    handle_input(query, input, c, 0);

    werase(info_win);
    refresh();
    wrefresh(info_win);

    info("[INFO] - Query executada com sucesso.", 3);

    show_result(queries[query - 1].output);
}

int menu_queries(char *dataset)
{
    WINDOW *win = new_window();

    char *options[] =
    {
        "> QUERY 1",
        "> QUERY 2",
        "> QUERY 3",
        "> QUERY 4",
        "> QUERY 5",
        "> QUERY 6",
        "> QUERY 7",
        "> QUERY 8",
        "> QUERY 9",
        "> VOLTAR"
    };

    int sel = menu_options(win, "EXECUTAR QUERY", "ENTER - Selecionar", dataset, options, 10, 0);

    return sel;
}

int menu_principal(char *dataset)
{
    WINDOW *win = new_window();
    
    char *options[] = {"> EXECUTAR QUERY", "> MUDAR DATASET","> SAIR"};

    int sel = menu_options(win, "MENU PRINCIPAL", "ENTER - Selecionar", dataset, options, 3, 0);

    return sel;
}

CATALOG *menu_dataset(char *path)
{
    int valid;
    do
    {
        WINDOW *win = new_window();
        
        menu_input(win, path, "CARREGAR DATASET", "Introduza o caminho para o dataset:", "ENTER - Carregar Dataset", NULL);

        char *dataset = get_dataset_path(path, "drivers");
        FILE *file = fopen(dataset, "r");

        if (file != NULL)
        {
            valid = 1;
            fclose(file);
        }
        else
        {
            valid = 0;
            werase(win);
            warning("[ERRO] - Caminho inválido.", 2);
        }

        free(dataset);
    }
    while (!valid);

    WINDOW *info_win = info("[INFO] - Carregando dataset...", -1);

    CATALOG *c = create_catalog(path, 0);

    werase(info_win);
    refresh();
    wrefresh(info_win);

    info("[INFO] - Dataset carregado com sucesso.", 3);

    return c;
}

// MAIN

void run_interactive()
{
    initscr();

    char *path = malloc(sizeof(char) * 100);
    QUERY *q = query_info();
    CATALOG *c = menu_dataset(path);

    int voltar_p = 1;
    while (voltar_p)
    {
        int sel = menu_principal(path);

        if (sel == 0) // EXECUTAR QUERY
        {   
            int voltar_q = 1;
            while (voltar_q)
            {
                int query = menu_queries(path);
                
                switch(query)
                {
                    case 0:
                        run_query(1, c, q);
                        break;
                    case 1:
                        run_query(2, c, q);
                        break;
                    case 2:
                        run_query(3, c, q);
                        break;
                    case 3:
                        run_query(4, c, q);
                        break;
                    case 4:
                        run_query(5, c, q);
                        break;
                    case 5:
                        run_query(6, c, q);
                        break;
                    case 6:
                        run_query(7, c, q);
                        break;
                    case 7:
                        run_query(8, c, q);
                        break;
                    case 8:
                        run_query(9, c, q);
                        break;
                    case 9:
                        voltar_p = 1;
                        voltar_q = 0;
                        break;
                }
            }
        }
        else if (sel == 1) // MUDAR DATASET
        {
            WINDOW *i = info("[INFO] - Destruindo catálogo de dados atual...", -1);
            destroy_catalog(c);
            werase(i);
            refresh();
            wrefresh(i);
            info("[INFO] - Feito!", 3);
            c = menu_dataset(path);
        }
        else if (sel == 2) // SAIR
        {
            WINDOW *i = info("[INFO] - Destruindo catálogo de dados...", -1);
            destroy_catalog(c);
            werase(i);
            refresh();
            wrefresh(i);
            info("[INFO] - Feito!", 3);
            endwin();
            return;
        }
    }

    endwin();
    destroy_catalog(c);
}

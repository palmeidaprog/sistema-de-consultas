int main() {
    char nome[1000];

    :pedir
    printf("Digite o nome");
    strlen(nome);

    if(strcmp(nome, NOMEPROIBIDO))
        goto pedir;

    return 0;
}
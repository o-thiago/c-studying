#include <ctype.h>
#include <stdio.h>

int ask(const char* s) {
    char c;
    printf("Eh um %s? [S/N]: ", s);
    return scanf(" %c", &c) == 1 && toupper((unsigned char)c) == 'S';
}

const char* solve(void) {
    if (ask("mamifero")) {
        if (ask("quadrupede")) return ask("carnivoro") ? "leao" : "cavalo";
        if (ask("bipede")) return ask("onivoro") ? "homem" : "macaco";
        if (ask("voador")) return "morcego";
        if (ask("aquatico")) return "baleia";
    }

    if (ask("ave")) {
        if (ask("nao-voador")) return ask("tropical") ? "avestruz" : "pinguim";
        if (ask("nadador")) return "pato";
        if (ask("de rapina")) return "aguia";
    }

    if (ask("reptil")) {
        if (ask("sem casco")) return "tartaruga";
        if (ask("carnivoro")) return "crocodilo";
        if (ask("sem patas")) return "cobra";
    }

    return NULL;
}

int main(void) {
    const char* result = solve();

    if (result != NULL)
        printf("Então trata-se de um %s", result);
    else
        puts("Animal não encontrado!");
}

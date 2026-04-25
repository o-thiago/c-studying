#include <ctype.h>
#include <stdio.h>

static bool ask(const char* question) {
    printf("Eh um %s? [S/N]: ", question);

    char buffer[BUFSIZ];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return false;
    }

    char* p = buffer;
    while (*p != '\0' && isspace((unsigned char)*p)) {
        p++;
    }

    return (toupper((unsigned char)*p) == 'S');
}

static const char* solve_mammal(void) {
    if (ask("quadrupede")) {
        return (int)ask("carnivoro") ? "leao" : "cavalo";
    }
    if (ask("bipede")) {
        return (int)ask("onivoro") ? "homem" : "macaco";
    }
    if (ask("voador")) {
        return "morcego";
    }
    if (ask("aquatico")) {
        return "baleia";
    }
    return nullptr;
}

static const char* solve_bird(void) {
    if (ask("nao-voador")) {
        return (int)ask("tropical") ? "avestruz" : "pinguim";
    }
    if (ask("nadador")) {
        return "pato";
    }
    if (ask("de rapina")) {
        return "aguia";
    }
    return nullptr;
}

static const char* solve_reptile(void) {
    if (ask("com casco")) {
        return "tartaruga";
    }
    if (ask("carnivoro")) {
        return "crocodilo";
    }
    if (ask("sem patas")) {
        return "cobra";
    }
    return nullptr;
}

static const char* solve(void) {
    if (ask("mamifero")) {
        return solve_mammal();
    }
    if (ask("ave")) {
        return solve_bird();
    }
    if (ask("reptil")) {
        return solve_reptile();
    }
    return nullptr;
}

int main(void) {
    const char* result = solve();

    if (result != NULL) {
        printf("Então trata-se de um %s", result);
    } else {
        puts("Animal não encontrado!");
    }
}

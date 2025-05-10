
/*
* Aluno: Kauã Vale Leão
* Matricula: 232014057
*/

#include <stdio.h>

int inverso_modular(int g, int n) {
    int a = g, mod = n;
    int y = 1, x = 0;

    printf("Calculando o  inverso modular de %d...\n", a);

    while (n != 0) {
        int quociente = g / n;
        int resto = g % n;
        int tmp = n;
        printf("%d = %d * %d + %d\n", g, quociente, n, resto);
        n = resto;
        g = tmp;
        tmp = x;
        x = y - (quociente * x);
        y = tmp;
    }

    if (g != 1){
        printf("O inverso modular não existe.\n");
        return -1;
    } 
    if (y < 0) y += mod;

    return y % mod;
}

int mdc(int a, int b) {
    while (b != 0) {
        int resto = a % b;
        a = b;
        b = resto;
    }
    return a; 
}

int primo(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int phi_euler(int n) {
    int phi = n;
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0)n /= p;
            phi -= phi / p;
        }
    }
    if (n > 1) phi -= phi / n;
    return phi;
}

int exp_modular(int base, int expoente, int mod) {
    int r = 1;
    base = base % mod;
    while (expoente > 0) {
        if (expoente % 2 == 1)
            r = (r * base) % mod;
        base = (base * base) % mod;
        expoente = expoente / 2;
    }
    return r;
}

int main() {
    int H, G, n, x, n1;

    printf("------------------------------------------\n");
    printf("    Calculadora de Operacoes Modulares    \n");
    printf("------------------------------------------\n\n");
    printf("Programa para calcular divisao modular e\n");
    printf("exponenciacao usando teoremas fundamentais\n\n");

    printf("Digite 5 numeros (H G n x n1): ");
    scanf("%d %d %d %d %d", &H, &G, &n, &x, &n1);
    printf("Entrada: H=%d, G=%d, n=%d, x=%d, n1=%d\n", H, G, n, x, n1);

    printf("\nPasso 1: Analisando MDC de G e n...\n");
    if (mdc(G, n) != 1) {
        printf("ERRO: G e n precisam ser coprimos\n");
        return 1;
    } else {
        printf("OK: MDC(%d, %d) = 1\n", G, n);
        printf("Divisao modular em Z%d pode ser calculada\n", n);
    }

    printf("\nPasso 2: Obtendo inverso multiplicativo...\n");
    int inverso_de_G_em_Zn = inverso_modular(G, n);
    if (inverso_de_G_em_Zn == -1) {
        printf("\nERRO: Inverso nao existe\n");
        return 1;
    } else {
        printf("\nInverso encontrado: %d\n", inverso_de_G_em_Zn);
        printf("Validacao: %d * %d = 1 (mod %d)\n", G, inverso_de_G_em_Zn, n);
    }

    int a = (H * inverso_de_G_em_Zn) % n;
    printf("\nPasso 3: Calculando H * inverso(G)...\n");
    printf("Resultado: %d * %d = %d (mod %d)\n", H, inverso_de_G_em_Zn, a, n);
    printf("Base para exponenciacao obtida\n");

    printf("\nPasso 4: Verificando MDC de %d e %d...\n", a, n1);
    if (mdc(a, n1) != 1) {
        printf("ERRO: Numeros nao coprimos\n");
        return 1;
    } else {
        printf("OK: Numeros coprimos, continuando...\n");
    }

    int x1;
    printf("\nPasso 5: Testando primalidade...\n");
    if (primo(n1)) {
        printf("Numero primo identificado\n");
        printf("Usando PTF(Pequeno Teorema de Fermat): x1 = %d - 1 = %d\n", n1, n1 - 1);
        x1 = n1 - 1;
    } else {
        printf("Numero nao primo identificado\n");
        x1 = phi_euler(n1);
        printf("Usando Teorema de Euler: phi(%d) = %d\n", n1, x1);
    }

    int q = x / x1;
    int r = x % x1;
    printf("\nPasso 6: Decomposicao de x...\n");
    printf("Expressao: %d = %d * %d + %d\n", x, x1, q, r);

    printf("\nPasso 7: Calculando potencia modular...\n");
    printf("Aplicando decomposicao para simplificar calculo\n\n");

    int ax1 = exp_modular(a, x1, n1);
    int ax1q = exp_modular(ax1, q, n1);
    int ar = exp_modular(a, r, n1);
    int resultado = (ax1q * ar) % n1;

    printf("Calculo 1: %d^%d = %d (mod %d)\n", a, x1, ax1, n1);
    printf("Calculo 2: %d^%d = %d (mod %d)\n", ax1, q, ax1q, n1);
    printf("Calculo 3: %d^%d = %d (mod %d)\n", a, r, ar, n1);

    printf("\nResultado Final:\n");
    printf("%d^%d = %d (mod %d)\n", a, x, resultado, n1);

    return 0;
}
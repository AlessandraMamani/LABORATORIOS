#include <stdio.h>
#include <assert.h>
#include "node.h"

void test_count(void) {
    printf("Probrando Count...\n");
    struct Node* head = NULL;
    assert(count(head, 5) == 0); // Lista vacía

    push(&head, 2);
    push(&head, 2);
    push(&head, 7);
    push(&head, 2);
    push(&head, 4); // Lista: {4, 2, 7, 2, 2}

    assert(count(head, 4) == 1); // Aparece una vez
    assert(count(head, 2) == 3); // Aparece varias veces
    assert(count(head, 9) == 0); // Valor que no aparece

    deleteList(&head);
    printf("  [OK] Count pasó todas las pruebas.\n");
}

void test_getNth(void) {
    printf("Probrando GetNth...\n");
    struct Node* head = BuildOneTwoThree(); // Lista: {1, 2, 3}

    assert(getNth(head, 0) == 1); // Primer nodo
    assert(getNth(head, 1) == 2); // Nodo intermedio
    assert(getNth(head, 2) == 3); // Último nodo

    deleteList(&head);
    printf("  [OK] GetNth pasó todas las pruebas.\n");
}

void test_deleteList(void) {
    printf("Probrando DeleteList...\n");
    struct Node* head = BuildOneTwoThree();
    deleteList(&head);
    assert(head == NULL); // Comprobar que head es NULL

    deleteList(&head); // Probar con lista vacía
    assert(head == NULL);
    printf("  [OK] DeleteList pasó todas las pruebas.\n");
}

void test_pop(void) {
    printf("Probrando Pop...\n");
    struct Node* head = BuildOneTwoThree(); // {1, 2, 3}

    int a = pop(&head);
    int b = pop(&head);
    int c = pop(&head);

    assert(a == 1);
    assert(b == 2);
    assert(c == 3);
    assert(head == NULL); // Lista queda vacía
    printf("  [OK] Pop pasó todas las pruebas.\n");
}

void test_insertNth(void) {
    printf("Probrando InsertNth...\n");
    struct Node* head = NULL;

    insertNth(&head, 0, 13); // {13} - Insertar en lista vacía
    assert(getNth(head, 0) == 13);

    insertNth(&head, 1, 42); // {13, 42} - Insertar al final
    assert(getNth(head, 1) == 42);

    insertNth(&head, 1, 5);  // {13, 5, 42} - Insertar en posición intermedia
    assert(getNth(head, 0) == 13);
    assert(getNth(head, 1) == 5);
    assert(getNth(head, 2) == 42);

    insertNth(&head, 0, 99); // {99, 13, 5, 42} - Insertar al comienzo
    assert(getNth(head, 0) == 99);

    deleteList(&head);
    printf("  [OK] InsertNth pasó todas las pruebas.\n");
}

void test_append(void) {
    printf("Probrando Append...\n");

    // Caso 1: Dos listas con elementos
    struct Node* a = NULL;
    push(&a, 2);
    push(&a, 1); // a = {1, 2}

    struct Node* b = NULL;
    push(&b, 4);
    push(&b, 3); // b = {3, 4}

    append(&a, &b); // a = {1, 2, 3, 4}, b = {}

    assert(length(a) == 4);
    assert(getNth(a, 0) == 1);
    assert(getNth(a, 1) == 2);
    assert(getNth(a, 2) == 3);
    assert(getNth(a, 3) == 4);
    assert(b == NULL); // b debe quedar vacía

    // Caso 2: Apendizar lista vacía a lista con elementos
    struct Node* c = NULL;
    append(&a, &c);
    assert(length(a) == 4);
    assert(c == NULL);

    // Caso 3: Apendizar a una lista vacía
    struct Node* d = NULL;
    append(&d, &a);
    assert(length(d) == 4);
    assert(a == NULL);

    deleteList(&d);
    printf("  [OK] Append pasó todas las pruebas.\n");
}

int main(void) {
    printf("=== INICIANDO PRUEBAS DE LABORATORIO ===\n\n");

    test_count();
    test_getNth();
    test_deleteList();
    test_pop();
    test_insertNth();
    test_append();

    printf("\n=== TODAS LAS PRUEBAS PASARON EXITOSAMENTE ===\n");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int valoare;
	struct Nod* left, * right;
}Nod;

Nod* adaugare(Nod*, int);
void afisare(Nod*);
Nod* stergere(Nod* ent, int del);
Nod* both(Nod* q1, Nod* q2);

int main()
{
	Nod* root = NULL;
	FILE* in;
	int add;
	in = fopen("arbore.txt", "rt");
	while (!feof(in))
	{
		(void)fscanf(in, "%d", &add);
		root = adaugare(root, add);
	}
	fclose(in);
	printf("arbore creat cu succes!\n");
	system("pause");
	printf("\n");
	printf("afisare in in ordine:\n");
	afisare(root);
	printf("\n");
	system("pause");
	printf("\n");
	root = stergere(root, 31);
	printf("dupa stergerea lui 31: ");
	afisare(root);
	printf("\n");
	system("pause");
	printf("\n");
	root = stergere(root, 17);
	printf("dupa stergerea lui 17: ");
	afisare(root);
	printf("\n");
	system("pause");
	return 0;
}

Nod* adaugare(Nod* ent, int add)
{
	if (ent == NULL)
	{
		ent = (Nod*)malloc(sizeof(Nod));
		if (ent == NULL)
		{
			printf("eroare la crearea arborelui!\n");
			system("pause");
			exit(1);
		}
		ent->valoare = add;
		ent->left = NULL;
		ent->right = NULL;
	}
	else
	{
		if (ent->valoare < add) ent->right = adaugare(ent->right, add);
		if (ent->valoare > add) ent->left = adaugare(ent->left, add);
	}
	return ent;
}
void afisare(Nod* ent)
{
	if (ent != NULL)
	{
		afisare(ent->left);
		printf("%d ", ent->valoare);
		afisare(ent->right);
	}
}
Nod* stergere(Nod* ent, int del)
{
	Nod* aux;
	if (ent == NULL) printf("arbore gol!\n");
	else
	{
		if (ent->valoare < del) ent->right = stergere(ent->right, del);
		else if (ent->valoare > del) ent->left = stergere(ent->left, del);
		else
		{
			if (ent->left == NULL)
			{
				aux = ent->right;
				free(ent);
				return aux;
			}
			else if (ent->right == NULL)
			{
				aux = ent->left;
				free(ent);
				return aux;
			}
			else ent->left = both(ent->left, ent);
		}
	}
	return ent;
}
Nod* both(Nod* q1, Nod* q2)
{
	Nod* ent, * aux;
	ent = q1;
	if (ent->right != NULL) ent->right = both(ent->right, q2);
	else
	{
		q2->valoare = ent->valoare;
		aux = ent;
		ent = ent->left;
		free(aux);
	}
	return ent;
}
//OPIS: 1. Personalni (Blok) OK Test
//RETURN: 201
int main() {
	int o;
	int i;
	int suma;

	o = 200;
	i = 100;

	{
		int k;
		int o;
		o = 2;
		k = 42;
		{
			int k;
			k = 21;
			o = 3;
		}
		i = 1; // Menja pravo i, nece se resetovati na kraju bloka na 100
		k = 84;
	}
	suma = o + i;
	return suma;
}
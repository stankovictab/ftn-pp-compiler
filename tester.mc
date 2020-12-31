int l() {
	return 0;
}

int f(unsigned u) {
	int a;
	a = l();
	return 2;
}
void k(int i, int ii) {
}

void g(int a, int z, int w) {
	int i;
	unsigned u;
	int b, c;
	f(2u);
	i = f(2u);
	// f(); Radi, greska kada f ima barem 1 parametar
	// f(i); Radi, greska kada f trazi unsigned
	// k(l, c); Radi, greska kada ne postoji l
	// k(b, u); Radi, greska kada je u unsigned, pogresan tip poslat
	// k(b, c, i); Radi, greska za previse argumenata
	k(b, c);
}

int h(unsigned l) {
	return 1;
}

int main() {
	int d, a, b, c, t;
	unsigned w;
	a = 2;
	a = a++;
	g(d, a, b);
	h(w);
	a = b + c++ - 5;
	a++;

	for(int i = 1 to 2)
		a++;

	for(int i = 1 to 2 step 3)
		a++;

	// for(int i = 1 to 2u) // Radi, nisu literali istog tipa
	// 	a++;

	// for(unsigned i = 1 to 2 step 3) // Radi, nisu literali istog tipa
	// 	a++;

	// for(int i = 2 to 2 step 3) // Radi, start isn't smaller
	// 	a++;

	for(int i = 1 to 2 step 3)
		for(int i = 1 to 2 step 3)
			a++;

	switch
	[a] {
		case 1 -> 
			a = a + 5;
			finish;
		case 5 ->
			{
				b = 3;
			}
		otherwise ->
			a = a - 1;
	}

	// Resetuje se switch niz za svaki switch

	// switch // Radi, greska - p ne nalazi
	// [p] {
	// 	case 1 -> 
	// 		a = a + 5;
	// 		finish;
	// 	case 5 ->
	// 		{
	// 			b = 3;
	// 		}
	// 	otherwise ->
	// 		a = a - 1;
	// }

	// switch // Radi, greska - 1u ne podrzava switch
	// [a] {
	// 	case 1u -> 
	// 		a = a + 5;
	// 		finish;
	// 	case 5 ->
	// 		{
	// 			b = 3;
	// 		}
	// 	otherwise ->
	// 		a = a - 1;
	// }

	{
		// int a; Ne moze jer je vec definisano, a ne treba da ne moze
		// To znaci da moramo da identifikujemo svaki compound_statement
		int p;
	}

	return a;
}
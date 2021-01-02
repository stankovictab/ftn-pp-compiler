int main() {
	int d, a, b, c, t;
	unsigned w;
	a = 2;
	a = a++;
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
int main() {
	int a;
	int b;
	a = 5;

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

	return a;
}
//OPIS: 3. Personalni (Switch) SynErr Test 1
int main() {
	int a;
	int b;
	a = 5;

	switch
	[a] {
		case 1 -> 
			a = a + 5;
			finish;
		case 0 ->
			finish; // Nema statement-a
		otherwise ->
			a = a - 1;
	}
	return a;
}
//OPIS: 3. Personalni (Switch) OK Test 2
int main(int c) {
	int a;
	int b;

	a = 5;
	b = 3;
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
	switch
	[c] { // Switch na parametar
		case 1 -> // Ponovljen literal
			b++;
		case 0 -> // Literal 0
			{
				int i; // Definisanje u bloku
				b = 0;
				a = 3;
				i = a + b;
			}
			finish;
		case 4 ->
			{

			} // Prazan case
			finish;
		otherwise ->
			b = 0;
	}
	return a;
}
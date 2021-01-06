//OPIS: 3. Personalni (Switch) OK Test 2
//RETURN: 3
int main(int c) {
	int a;
	int b;

	a = 5;
	b = 2;
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
	[c] { // Switch na parametar (nepostavljeni, mada ce biti 0, tako postavlja simulator)
		case 1 -> // Ponovljen literal
			a++;
		case 0 -> // Literal 0
			{
				int i; // Definisanje u bloku
				a = 3;
				i = a + b;
			}
			finish;
		case 4 ->
			{

			} // Prazan case
			finish;
		otherwise ->
			a = 0;
	}
	return b;
}
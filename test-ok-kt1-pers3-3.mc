//OPIS: 3. Personalni (Switch) OK Test 3
//RETURN: 6
int main() {
	int a;
	int b;

	a = 1;
	switch
	[a] {
		case 1 -> 
			b = a + 5;
			finish;
		case 5 ->
			{
				b = 3;
			}
				finish;
		case 8 ->
			{
				a = 18;
			}
		otherwise ->
			a = a - 1;
	}
	return b;
}
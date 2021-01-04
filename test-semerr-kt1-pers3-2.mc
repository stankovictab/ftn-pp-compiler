//OPIS: 3. Personalni (Switch) SemErr Test 2
int main() {
	int a;
	int b;
	a = 5;

	switch
	[a] {
		case 1u -> 
			a = a + 5;
			finish;
		case 5 ->
			{
				b = 3;
			}
		otherwise ->
			a = a - 1;
	}
	return a;
}
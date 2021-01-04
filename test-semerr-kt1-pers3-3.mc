//OPIS: 3. Personalni (Switch) SemErr Test 3
int main() {
	int a;
	int b;
	a = 5;

	switch
	[a] {
		case 1 -> 
			a = a + 5;
			finish;
		case 1 ->
			{
				b = 3;
			}
		otherwise ->
			a = a - 1;
	}
	return a;
}
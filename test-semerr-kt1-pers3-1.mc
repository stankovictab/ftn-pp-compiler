//OPIS: 3. Personalni (Switch) SemErr Test 1
int main() {
	int a;
	int b;
	a = 5;

	switch
	[p] {
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
	return a;
}
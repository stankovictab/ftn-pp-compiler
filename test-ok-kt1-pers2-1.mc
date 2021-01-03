//OPIS: 2. Personalni (Loop) OK Test 1
int main() {
	int a;
	for(int i = 1 to 5)
		i++;
	for(int i = 1 to 2)
		a++;
	for(int i = 1 to 2) {
		a++;
		i++;
		i = a + i;
	}
	for(int i = 1 to 4 step 3) {
		if(i > 2) {
			a = 3;
		}
	}
	return 1;
}
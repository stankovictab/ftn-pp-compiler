//OPIS: 2. Personalni (Loop) OK Test 2
//RETURN: 2
int main() {
	int a;
	a = 69;
	for(int i = 1 to 10 step 3)
		for(int j = 1 to 10 step 3) // Isti literali ne uticu na tabelu simbola
			return 2;
	for(int i = 1 to 100 step 50) {
		for(int j = 4 to 100 step 6) {
			j++;
			return 2;
		}
		i++;
		for(int k = 3 to 4 step 1) {
			k++;
			a = 70;
		}
	}
	return a;
}
//OPIS: exp local lookup SemErr
int f(int t, int g) {
	g = 10;
	return 2;
}

void y(int h) {
	int a;
	a = 3;
}

int main() {
	int a;
	f(2, h); // Treba da javi gresku jer h nije definisano u scope-u
	return 0;
}
int f(int c) {
	int a;
	return a;
}

int main() {
	int a;
	int b, c;
	a = 2;
	a = a++;
	// b = f(a++); // Ne radi num_exp vise, samo id i literal
	a = b + c++ - 5;
	a++;
	return a;
}
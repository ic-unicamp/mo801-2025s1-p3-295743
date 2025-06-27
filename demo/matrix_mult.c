#define SIZE 64

static int A[SIZE][SIZE];
static int B[SIZE][SIZE];
static int C[SIZE][SIZE];

void init_matrices(void) {
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++) {
			A[i][j] = (i + j) % 10;
			B[i][j] = (i * j) % 10;
			C[i][j] = 0;
		}
}

void matmul(void) {
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			for(int k = 0; k < SIZE; k++)
				C[i][j] += A[i][k] * B[k][j];
}

void teste(void) {
	printf("Inicializando matrizes...\n");
	init_matrices();

	printf("Executando multiplicação de matrizes...\n");

	matmul();


}

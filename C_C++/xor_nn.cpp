// @BAKE g++ $@ -fpermissive -Wextra -Wpedantic -o $*.out
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <numeric>

const int TRAINING_SESSIONS = 1000;

using namespace std;

typedef struct nn {
	static const int INPUT_COUNT       = 2;
	static const int B                 = 1;
	static const int NUMBER_OF_LAYERS  = 2;
	static const int INPUT_SIZE        = INPUT_COUNT + B;

	double weights[INPUT_SIZE][NUMBER_OF_LAYERS];

	nn() {
		this->random_fill();
	}

	~nn() {
		this->print();
	}

	void random_fill() {
		srand((unsigned int)time(NULL));
		for (int i = 0; i < INPUT_SIZE; i++) {
			for (int h = 0; h < NUMBER_OF_LAYERS; h++) {
				weights[i][h] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
			}
		}
	}

	void print() {
		for (int j = 0; j < NUMBER_OF_LAYERS; j++) {
			for (int i = 0; i < INPUT_SIZE; i++) {
				printf("%.4f    ", weights[i][j]);
			}
			printf("\n");
		}
	}
} neural_network_t;

typedef struct {
	int inputs[neural_network_t::INPUT_SIZE];
	int output;
} data_t;


data_t training_data[] = {
	(data_t){{0, 0, neural_network_t::B}, 0},
	(data_t){{1, 0, neural_network_t::B}, 1},
	(data_t){{0, 1, neural_network_t::B}, 1},
	(data_t){{1, 1, neural_network_t::B}, 0},
};

double sigmoid_derivative(int i) {
	return (double)i * ((double)1 - (double)i);
}

double sigmoid_activation(int i) {
	return (double)i / ((double)1 + exp(i));
}

signed main() {
	neural_network_t my_neural_network;
	int training_sessions_counter;
	double sumerr = 0;
	for (training_sessions_counter = 0;
	     training_sessions_counter < TRAINING_SESSIONS;
	     training_sessions_counter++) {
		for (const auto &data : training_data) {
				int y[neural_network_t::INPUT_COUNT];
				for (int h = 0; h < neural_network_t::INPUT_COUNT; h++) {
					//double r = std::accumulate(myList.begin(),
					//                           myList.end(),
					//                           0,
					//                           [](int sum, int element) {
					//                           	return sum + (element * 2);
					//                           }
					//);
				}
		}
	}


	printf("Number of steps: %d\n"
	       "??: %lf\n",
	       training_sessions_counter, sumerr
	);

	return 0;
}

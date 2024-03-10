/* @BAKE gcc $@ -o n.out -lm && ./n.out
 */
/*
    # CNN
    > Simple Neural Network from scratch in C, emulating logic gates.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct {
    double input[3];
    double output;
} sample_t;

sample_t OR[] = {
    {{0.0, 0.0, 1.0}, 0.0},
    {{1.0, 0.0, 1.0}, 1.0},
    {{0.0, 1.0, 1.0}, 1.0},
    {{1.0, 1.0, 1.0}, 1.0},
};

sample_t AND[] = {
    {{0.0, 0.0, 1.0}, 0.0},
    {{1.0, 0.0, 1.0}, 0.0},
    {{0.0, 1.0, 1.0}, 0.0},
    {{1.0, 1.0, 1.0}, 1.0},
};

sample_t XOR[] = {
    {{0.0, 0.0, 1.0}, 0.0},
    {{1.0, 0.0, 1.0}, 1.0},
    {{0.0, 1.0, 1.0}, 1.0},
    {{1.0, 1.0, 1.0}, 0.0},
};

typedef struct {
    size_t n_layers;
    double * layer_width;
    double * * weights;
} network_t;

double activation(double x) {
    return 1.0/(1.0 + exp(-x));
}

double deactivation(double y) {
    return y * (1.0 - y);
}

void new_network(network_t * n) {
    n->n_layers = 5;
    n->layer_width = (double*)malloc(n->n_layers*sizeof(double));
    n->layer_width[0] = 3;
    n->layer_width[1] = 3;
    n->layer_width[2] = 3;
    n->layer_width[3] = 3;
    n->layer_width[4] = 1;
    n->weights = (double**)malloc((n->n_layers-1)*sizeof(double));
    for (int i = 0; i < n->n_layers-1; i++) {
        size_t synapse_count = n->layer_width[i] * n->layer_width[i+1];
        n->weights[i] = (double*)malloc(synapse_count*sizeof(double));
        for (int h = 0; h < synapse_count; h++) {
            n->weights[i][h] = (double)rand() / (double)RAND_MAX;
        }
    }
}

double oracle(network_t * n, double * input) {
    double r;
    int sum = 0;
    for (int i = 0; i < n->n_layers-1; i++) {
        size_t synapse_count = n->layer_width[i] * n->layer_width[i+1];
        for (int h = 0; h < synapse_count; h++) {
            sum += (input[h] * n->weights[i][h]);
        }
    }
    r = activation(sum);
    //printf("The network oracles %d!\n", (int)round(r));
    return r;
}

double adjust(network_t * n, double response, sample_t s) {
    double error = s.output - response;
    double delta = error * deactivation(response);
    for (int i = 0; i < n->n_layers-1; i++) {
        size_t synapse_count = n->layer_width[i] * n->layer_width[i+1];
        for (int h = 0; h < synapse_count; h++) {
            n->weights[i][h] += 0.8 * delta * s.input[h];
        }
    }
    return error;
}

void train(network_t * n, sample_t * s, size_t c) {
    for (int i = 0; i < c; i++) {
        double sumerr = 0;
        for (int h = 0; h < 4; h++) {
            double network_response = oracle(n, s[h].input);
            double error = adjust(n, network_response, s[h]);
            sumerr += pow(error, 2);
        }
        printf("%d: %lf\n", i, sumerr);
    }
}

void print_sample(sample_t * s) {
    printf("{%d, %d, %d} -> %d\n",
        (int)s->input[0], (int)s->input[1], (int)s->input[2], (int)s->output
    );
}

void test(network_t * n, sample_t * s) {
    for (int i = 0; i < 4; i++) {
        fputs("\033[1mfor: ", stdout);
        print_sample(s + i);
        printf("\033[0;33mThe Network oracles: %d\033[0m\n", (int)round(oracle(n, s[i].input)));
    }
}

signed main() {
    network_t n;
    new_network(&n);
    train(&n, AND, 100);
    test(&n, AND);
}

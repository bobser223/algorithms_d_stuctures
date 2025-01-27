// a)
long long a(int n){
    long long sum = 0;
    for (int i = 0; i < n + 1; i++){
        sum += i;
    }
    return sum;
}


long long b(int n){
    long long sum = 0;
    for (int i = 0; i < n + 1; i++){
        sum += i*i;
    }
    return sum;
}

long long c(int n, long long a){
    long long sum = 1;
    for (int i = 0; i < n + 1; i++){
        sum += a;
        a *= a;
    }
    return sum;
}

long long d(int n){
    long long sum = 0;
    long long powered = 1;

    for (int i = 0; i < n + 1; i++){

        powered = 1;
        for (int j = 0; j < i; j++){
            powered *= i;
        }

        sum += powered;
    }
    return sum;
}

double e(int n){
    double sum = 1;

    for (int i = 1; i < n + 1; i++){
        sum *= 1.0/(1 + i);
    }

    return sum;
}


double f(int n){
    double sum = 1;
    long long fact = 0;

    for (long long i = 1; i < n + 1; i++){
        fact *= i;

        sum *= 1.0 / (1 + fact);
    }

    return sum;
}

double g(int n, int a){
    double sum = 1;
    long long fact = 0;

    for (long long i = 1; i < n + 1; i++){
        fact *= i;

        sum *= double(a) / (1 + fact);

        a *= a;
    }

    return sum;
}

double h(int n, int m){
    double sum = 1;

    for (int i = 1; i < n + 1; i++){
        int powered = 1;

        for (int j = 0; j < m; j++){
            powered *= i;
        }

        sum *= 1.0/(1 + powered);

    }


    return sum;
}

double i(int n, int m){
    double sum = 1;

    for (int i = 1; i < n + 1; i++){
        int powered = 1;

        for (int j = 0; j < i; j++){
            powered *= i;
        }

        sum *= 1.0/(1 + powered);

    }


    return sum;
}

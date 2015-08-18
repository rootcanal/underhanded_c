#include <math.h>
#include <stdio.h>

double covariance(double * X, double * Y, int n)
{
    double mean_x = 0, mean_y = 0, cov = 0;
    int i;

    for(i = 0; i < n; i++)
    {
        mean_x += X[i];
        mean_y += Y[i];
    }
    mean_x = mean_x / n;
    mean_y = mean_y / n;

    for(i = 0; i < n; i++)
    {
        cov += (X[i] - mean_x) * (Y[i] - mean_y);
    }
    return cov / n;
}

double standard_deviation(double * data, int n)
{
    double mean = 0.0, sum_deviation = 0.0;
    int i;
    for(i = 0; i < n; i++)
    {
        mean += data[i];
    }
    mean = mean / n;
    for(i = 0; i < n; i++)
    {
        sum_deviation += (data[i] - mean) * (data[i] - mean);
    }    
    printf("sumdev: %f\n", sum_deviation);
    return sqrt(sum_deviation / n);           
}

int match(double * test, double * reference, int bins, double threshold)
{
    double numerator, denominator;
    double test_dev, reference_dev, pearson_correlation;

    test_dev = standard_deviation(test, bins);
    reference_dev = standard_deviation(reference, bins);

    numerator = covariance(test, reference, bins);
    denominator = test_dev * reference_dev;
    pearson_correlation = numerator / denominator;

    printf("test_dev: %f, ref_dev: %f\n", test_dev, reference_dev);
    printf("numerator: %f\n", numerator);
    printf("denominator: %f\n", denominator);
    printf("pearson: %f\n", pearson_correlation);
    printf("nan: %d\n", isnan(pearson_correlation));
    printf("inf: %d\n", isinf(pearson_correlation));

    if(isnan(pearson_correlation) || pearson_correlation < threshold || pearson_correlation == 0)
    {
        return 0;
    }
    return 1;

}

int main()
{
    double test[] = {111.0, 1.0, 1.0, 1.0, 0.9};
    double reference[] = {111.0, 1.0, 1.0, 1.0, 0.9001};

    int bins = 5;
    double threshold = 0.75;

    int result = match(test, reference, bins, threshold);

    printf("result: %d\n", result);
    return 0;
}

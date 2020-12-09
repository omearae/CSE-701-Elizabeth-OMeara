class triangle
{
public:
    // Construct a triangle with the given side lengths
    triangle(const double &, const double &, const double &);
    // Construct an equilateral triangle with the given side length
    triangle(const double &);
    // Construct a degenerate triangle with zero side lengths
    triangle();

private:
    // The side lengths
    double a{0}, b{0}, c{0};
};
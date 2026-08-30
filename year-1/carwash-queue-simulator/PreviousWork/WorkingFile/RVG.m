function rn = RVG(n, a, b)
    % Random Variate Generator for Uniform Distribution
    rn = a + (b - a) * rand(1, n);
end
